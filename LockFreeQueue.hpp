#ifndef LOCKFREEQUEUE_HPP
#define LOCKFREEQUEUE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <mutex>

// Branch Prediction
#ifndef likely
#define likely(x)    __builtin_expect(!!(x), 1)
#endif

#ifndef unlikely
#define unlikely(x)  __builtin_expect(!!(x), 0)
#endif

// Forced inline
#ifndef force_inline
#define force_inline __attribute__ ((__always_inline__))
#endif

namespace Utils
{
template <class T>
class LockFreeQueue
{
protected:
    typedef struct
    {
        int m_Mutex;
        int m_Lock;
        int m_UnLock;
        inline void Init()
        {
            m_Mutex = 0;
            m_Lock = 1;
            m_UnLock = 0;
        }
        inline void Lock()
        {
            while (!__sync_bool_compare_and_swap(&m_Mutex, 0, 1));
        }
        inline void UnLock()
        {
            __sync_lock_release(&m_Mutex);
        }
    }TSpinLock;
public:
    // size:队列大小
    // key:共享内存key，默认为0，使用heap作为底层缓冲区。
    LockFreeQueue(unsigned int size = 1024, unsigned int key = 0)
    {
        m_QueueKey = key;
        m_QueueSize = RoundPower2(size);
        m_Head = m_Tail = NULL;
        if (0 == m_QueueKey)
        {
            m_Buffer = new T[m_QueueSize];
            m_Head = new int(0);
            m_Tail = new int(0);
        }
        else
        {
            int shmid = shmget(m_QueueKey, size * sizeof(T) + sizeof(int) * 2, 0666 | IPC_CREAT);
            m_Buffer = static_cast<T *>(shmat(shmid, 0, 0));
            m_Head = (int *)(m_Buffer + m_QueueSize);
            m_Tail = (int *)((m_Buffer + m_QueueSize) + sizeof(int));
        }
        m_SpinLock.Init();
    }
    ~LockFreeQueue()
    {
        if (0 == m_QueueKey)
        {
            delete[] m_Buffer;
            delete m_Head;
            delete m_Tail;
        }
        else
        {
            shmdt((void *)m_Buffer);
        }
        m_Head = NULL;
        m_Tail = NULL;
        m_Buffer = NULL;
    }

    inline void Reset()
    {
        if (0 == m_QueueKey)
        {
            memset(m_Buffer, 0, m_QueueSize * sizeof(T));
            *m_Head = 0;
            *m_Tail = 0;
        }
        else
        {
            memset(m_Buffer, 0, m_QueueSize * sizeof(T) + sizeof(int) * 2);
        }
    }

    force_inline inline bool IsFull() const
    {
        return *m_Head == ((*m_Tail + 1) & (m_QueueSize - 1));
    }

    force_inline inline bool IsEmpty() const
    {
        return *m_Head == *m_Tail;
    }

    force_inline inline unsigned int Front() const
    {
        return *m_Head;
    }

    force_inline inline unsigned int Tail() const
    {
        return *m_Tail;
    }

    force_inline inline bool Push(const T &value)
    {
        m_SpinLock.Lock();
        if(unlikely(IsFull()))
        {
            m_SpinLock.UnLock();
            return false;
        }
        memcpy(m_Buffer + *m_Tail, &value, sizeof(T));
        *m_Tail = (*m_Tail + 1) & (m_QueueSize - 1);
        m_SpinLock.UnLock();
        return true;
    }

    force_inline inline bool Pop(T &value)
    {
        m_SpinLock.Lock();
        if(unlikely(IsEmpty()))
        {
            m_SpinLock.UnLock();
            return false;
        }
        memcpy(&value, m_Buffer + *m_Head, sizeof(T));
        *m_Head = (*m_Head + 1) & (m_QueueSize - 1);
        m_SpinLock.UnLock();
        return true;
    }
protected:
    static uint32_t RoundPower2(uint32_t size) 
    {
        uint32_t i;
        for ( i = 0; (1U << i) < size; i++);
        return 1U << i;
    }
protected:
    unsigned int m_QueueKey;
    alignas(128) int *m_Head;
    alignas(128) int *m_Tail;
    alignas(128) unsigned int m_QueueSize;
    TSpinLock m_SpinLock;
    T *m_Buffer;
};

}

#endif // LOCKFREEQUEUE_HPP
