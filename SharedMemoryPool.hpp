#include <iostream>
#include <atomic>
#include <cstring>
#include <cstdint>
#include <new>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

constexpr void* SHM_BASE_ADDR = reinterpret_cast<void*>(0x600000000000);

// 共享内存头部结构（无锁）
struct SharedMemHeader 
{
    std::atomic<void*> free_list;   // 空闲链表头（绝对地址）
    size_t             block_size;  // 每个数据块的大小（字节）
    uint32_t           num_blocks;  // 总块数
    std::atomic<uint32_t> allocated; // 已分配块数（调试用）
    uint32_t           first_block_offset; // 第一个块相对于 header 起始的偏移（字节）
};

template <typename T>
class SharedMemoryPool 
{
    static_assert(sizeof(T) >= sizeof(void*), "Type T is too small to hold free list pointer(must be at least pointer size)");
public:
    // 创建者：创建共享内存对象并初始化无锁内存池（供 T 类型使用）
    static SharedMemoryPool<T>* Create(const char* name, uint32_t num_objects) 
    {
        if (!name || num_objects == 0) return nullptr;

        // 1. 计算第一个块的起始偏移（按 alignof(T) 对齐）
        size_t header_size = sizeof(SharedMemHeader);
        uintptr_t base_addr = reinterpret_cast<uintptr_t>(SHM_BASE_ADDR);
        uintptr_t first_block_addr = base_addr + header_size;
        size_t alignment = alignof(T);
        size_t pad = (alignment - (first_block_addr % alignment)) % alignment;
        uint32_t first_block_offset = static_cast<uint32_t>(header_size + pad);

        // 2. 计算总大小（页对齐）
        size_t total_size = first_block_offset + sizeof(T) * num_objects;
        total_size = (total_size + 4095) & ~4095;

        // 3. 创建共享内存对象
        int fd = shm_open(name, O_CREAT | O_EXCL | O_RDWR, 0644);
        if (fd == -1) {
            if (errno == EEXIST)
                std::cerr << "Shared memory already exists. Use Open() instead." << std::endl;
            return nullptr;
        }

        if (ftruncate(fd, total_size) == -1) {
            close(fd);
            shm_unlink(name);
            return nullptr;
        }

        // 4. 固定地址映射
        void* addr = mmap(SHM_BASE_ADDR, total_size,
                          PROT_READ | PROT_WRITE,
                          MAP_SHARED | MAP_FIXED,
                          fd, 0);
        if (addr == MAP_FAILED || addr != SHM_BASE_ADDR) {
            std::cerr << "mmap with MAP_FIXED failed: " << strerror(errno) << std::endl;
            close(fd);
            shm_unlink(name);
            return nullptr;
        }
        close(fd);

        // 5. 初始化头部
        SharedMemHeader* header = reinterpret_cast<SharedMemHeader*>(addr);
        new (&header->free_list) std::atomic<void*>(nullptr);
        new (&header->allocated) std::atomic<uint32_t>(0);
        header->block_size = sizeof(T);
        header->num_blocks = num_objects;
        header->first_block_offset = first_block_offset;

        // 6. 构建空闲链表（每个块的前 sizeof(void*) 字节存放 next 指针）
        char* first_block = static_cast<char*>(addr) + first_block_offset;
        void* prev = nullptr;
        for (uint32_t i = 0; i < num_objects; ++i) {
            void* block_ptr = first_block + i * sizeof(T);
            *static_cast<void**>(block_ptr) = prev;   // 当前块指向之前的块（逆序）
            prev = block_ptr;
        }
        header->free_list.store(prev, std::memory_order_release);

        return new SharedMemoryPool<T>(header, total_size, name, true);
    }

    // 使用者：打开已存在的共享内存池
    static SharedMemoryPool<T>* Open(const char* name) 
    {
        if (!name) return nullptr;

        int fd = shm_open(name, O_RDWR, 0644);
        if (fd == -1) return nullptr;

        struct stat st;
        if (fstat(fd, &st) == -1) {
            close(fd);
            return nullptr;
        }
        size_t total_size = st.st_size;

        void* addr = mmap(SHM_BASE_ADDR, total_size,
                          PROT_READ | PROT_WRITE,
                          MAP_SHARED | MAP_FIXED,
                          fd, 0);
        if (addr == MAP_FAILED || addr != SHM_BASE_ADDR) {
            std::cerr << "mmap with MAP_FIXED failed: " << strerror(errno) << std::endl;
            close(fd);
            return nullptr;
        }
        close(fd);

        SharedMemHeader* header = reinterpret_cast<SharedMemHeader*>(addr);
        return new SharedMemoryPool<T>(header, total_size, name, false);
    }

    ~SharedMemoryPool() 
    {
        if (m_header) 
        {
            munmap(m_header, m_total_size);
            if (m_is_creator && m_name) 
            {
                shm_unlink(m_name);
            }
        }
        delete [] m_name;
    }

    // 分配一块内存（返回 T*，未构造对象）
    T* Allocate() 
    {
        SharedMemHeader* h = m_header;
        std::atomic<void*>& free_list = h->free_list;
        void* old_head = free_list.load(std::memory_order_acquire);
        while (old_head) 
        {
            void* next = *static_cast<void**>(old_head);
            if (free_list.compare_exchange_weak(old_head, next,
                                                std::memory_order_release,
                                                std::memory_order_acquire)) {
                h->allocated.fetch_add(1, std::memory_order_relaxed);
                return static_cast<T*>(old_head);
            }
        }
        return nullptr;   // 无空闲块
    }

    // 释放由 Allocate() 返回的内存（用户应已调用析构）
    void Deallocate(T* ptr)
     {
        if (!ptr) return;

        // 调试：检查指针是否属于本池
        char* base = reinterpret_cast<char*>(m_header);
        char* end = base + m_total_size;
        if (reinterpret_cast<char*>(ptr) < base || reinterpret_cast<char*>(ptr) >= end) {
            std::cerr << "Deallocate: pointer out of range" << std::endl;
            return;
        }

        SharedMemHeader* h = m_header;
        std::atomic<void*>& free_list = h->free_list;
        void* old_head = free_list.load(std::memory_order_acquire);
        do {
            *static_cast<void**>(ptr) = old_head;   // 将待释放块的 next 指向当前栈顶
        } while (!free_list.compare_exchange_weak(old_head, ptr,
                                                  std::memory_order_release,
                                                  std::memory_order_acquire));
        h->allocated.fetch_sub(1, std::memory_order_relaxed);
    }

    // 方便构造对象：分配内存并 placement new 构造
    template <typename... Args>
    T* Construct(Args&&... args) 
    {
        T* mem = Allocate();
        if (!mem) return nullptr;
        new (mem) T(std::forward<Args>(args)...);
        return mem;
    }

    // 方便析构对象：调用析构并释放内存
    void Destroy(T* ptr) 
    {
        if (ptr) 
        {
            ptr->~T();
            Deallocate(ptr);
        }
    }

    void PrintStats() const 
    {
        std::cout << "Block size: " << m_header->block_size
                  << ", Total blocks: " << m_header->num_blocks
                  << ", Allocated: " << m_header->allocated.load(std::memory_order_relaxed)
                  << std::endl;
    }

private:
    SharedMemoryPool(SharedMemHeader* header, size_t total_size, const char* name, bool is_creator)
        : m_header(header), m_total_size(total_size), m_is_creator(is_creator) 
    {
        if(name) 
        {
            m_name = new char[strlen(name) + 1];
            strcpy(m_name, name);
        } 
        else 
        {
            m_name = nullptr;
        }
    }

    SharedMemHeader* m_header;
    size_t           m_total_size;
    char*            m_name;
    bool             m_is_creator;
};

// ---------- 使用示例 ----------
/*
struct Order {
    int64_t id;
    double price;
    uint32_t volume;
};

// 进程 A（创建者）
int main_creator() {
    auto pool = SharedMemoryPool<Order>::Create("/order_pool", 10000);
    if (!pool) return 1;
    Order* ord = pool->Construct(12345, 99.5, 100);
    // 使用 ord ...
    pool->Destroy(ord);
    delete pool;   // 创建者负责 finally unlink
    return 0;
}

// 进程 B（使用者）
int main_user() {
    auto pool = SharedMemoryPool<Order>::Open("/order_pool");
    if (!pool) return 1;
    Order* ord = pool->Allocate();
    if (ord) {
        new (ord) Order(12345, 99.5, 100);   // placement new
        // ...
        ord->~Order();
        pool->Deallocate(ord);
    }
    delete pool;   // 不 unlink
    return 0;
}
*/