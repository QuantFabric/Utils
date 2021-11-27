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

namespace Utils
{
template <class T>
class LockFreeQueue
{
protected:
    typedef struct
    {
        int m_mutex;
        int lock;
        int unlock;
        inline void spinlock_init()
        {
            m_mutex = 0;
            lock = 0;
            unlock = 1;
        }
        inline void spinlock_lock()
        {
            while (!__sync_bool_compare_and_swap(&m_mutex, lock, 1))
            {
                usleep(1);
            }
        }
        inline void spinlock_unlock()
        {
            __sync_bool_compare_and_swap(&m_mutex, unlock, 0);
        }
    } spinlock_t;

public:
    // size:队列大小
    // key:共享内存key，默认为0，使用heap作为底层缓冲区。
    LockFreeQueue(unsigned int size, unsigned int key = 0)
    {
        m_key = key;
        m_size = size;
        m_head = m_tail = NULL;
        if (0 == m_key)
        {
            m_buffer = new T[m_size];
            m_head = new int(0);
            m_tail = new int(0);
        }
        else
        {
            int shmid = shmget(m_key, size * sizeof(T) + sizeof(int) * 2, 0666 | IPC_CREAT);
            m_buffer = static_cast<T *>(shmat(shmid, 0, 0));
            m_head = (int *)(m_buffer + m_size);
            m_tail = (int *)((m_buffer + m_size) + sizeof(int));
        }
        m_spinLock.spinlock_init();
    }
    ~LockFreeQueue()
    {
        if (0 == m_key)
        {
            delete[] m_buffer;
            delete m_head;
            delete m_tail;
        }
        else
        {
            shmdt((void *)m_buffer);
        }
        m_head = NULL;
        m_tail = NULL;
        m_buffer = NULL;
    }

    inline void reset()
    {
        if (0 == m_key)
        {
            memset(m_buffer, 0, m_size * sizeof(T));
            *m_head = 0;
            *m_tail = 0;
        }
        else
        {
            memset(m_buffer, 0, m_size * sizeof(T) + sizeof(int) * 2);
        }
    }

    bool isFull() const
    {
        return *m_head == (*m_tail + 1) % m_size;
    }

    bool isEmpty() const
    {
        return *m_head == *m_tail;
    }
    unsigned int front() const
    {
        return *m_head;
    }

    unsigned int tail() const
    {
        return *m_tail;
    }

    bool push(const T &value)
    {
        m_spinLock.spinlock_lock();
        if (isFull())
        {
            m_spinLock.spinlock_unlock();
            return false;
        }
        memcpy(m_buffer + *m_tail, &value, sizeof(T));
        *m_tail = (*m_tail + 1) % m_size;
        m_spinLock.spinlock_unlock();
        return true;
    }

    bool pop(T &value)
    {
        m_spinLock.spinlock_lock();
        if (isEmpty())
        {
            m_spinLock.spinlock_unlock();
            return false;
        }
        memcpy(&value, m_buffer + *m_head, sizeof(T));
        *m_head = (*m_head + 1) % m_size;
        m_spinLock.spinlock_unlock();
        return true;
    }

protected:
    unsigned int m_key;
    int *m_head;
    int *m_tail;
    unsigned int m_size;
    spinlock_t m_spinLock;
    T *m_buffer;
};

}

#endif // LOCKFREEQUEUE_HPP
