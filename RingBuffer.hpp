
#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>

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
class RingBuffer
{
public:
    RingBuffer(unsigned int size = 1024, unsigned int key = 0) : m_QueueSize(size), m_Head(0), m_Tail(0)
    {
        m_QueueSize = RoundPower2(size);
        m_QueueKey = key;
        // 堆空间分配
        if (0 == m_QueueKey)
        {
            m_Buffer = new T[m_QueueSize];
            m_Head = new int(0);
            m_Tail = new int(0);
        }
        else // 共享内存分配
        {
            int shmid = shmget(m_QueueKey, m_QueueSize * sizeof(T) + sizeof(int) * 2, 0666 | IPC_CREAT);
            m_Buffer = static_cast<T *>(shmat(shmid, 0, 0));
            m_Head = (int *)(m_Buffer + m_QueueSize);
            m_Tail = (int *)((m_Buffer + m_QueueSize) + sizeof(int));
        }
    }

    ~RingBuffer()
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

        m_Buffer = NULL;
        m_Head = NULL;
        m_Tail = NULL;
    }

    force_inline inline void Reset()
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

    force_inline inline bool IsEmpty() const
    {
        return *m_Head == *m_Tail;
    }

    force_inline inline bool IsFull() const
    {
        return *m_Head == ((*m_Tail + 1) & (m_QueueSize - 1));
    }

    force_inline bool Push(const T& value)
    {
        if(unlikely(IsFull()))
        {
            return false;
        }
        m_Buffer[*m_Tail] = value;
        *m_Tail = (*m_Tail + 1) & (m_QueueSize - 1);
        return true;
    }

    force_inline bool Push(const T *value)
    {
        if(unlikely(IsFull()))
        {
            return false;
        }
        m_Buffer[*m_Tail] = *value;
        *m_Tail = (*m_Tail + 1) & (m_QueueSize - 1);
        return true;
    }

    force_inline inline bool Pop(T &value)
    {
        if (unlikely(IsEmpty()))
        {
            return false;
        }
        value = m_Buffer[*m_Head];
        *m_Head = (*m_Head + 1) & (m_QueueSize - 1);
        return true;
    }
    
    force_inline inline unsigned int Head() const
    {
        return *m_Head;
    }

    force_inline inline unsigned int Tail() const
    {
        return *m_Tail;
    }
    force_inline inline unsigned int Size() const
    {
        return m_QueueSize;
    }
protected:
    static uint32_t RoundPower2(uint32_t size) 
    {
        uint32_t i;
        for ( i = 0; (1U << i) < size; i++);
        return 1U << i;
    }
private:
    alignas(128) unsigned int m_QueueSize; // 队列长度
    alignas(128) int *m_Head;        // 队列头部索引
    alignas(128) int *m_Tail;         // 队列尾部索引
    T *m_Buffer;           // 数据缓冲区
    int m_QueueKey;
};

}
#endif // RINGBUFFER_HPP
