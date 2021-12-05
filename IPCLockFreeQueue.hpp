#ifndef IPCLOCKFREEQUEUE_HPP
#define IPCLOCKFREEQUEUE_HPP

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
#include <list>
#include <string>
#include <unordered_map>

namespace Utils
{
template <class T, int N>
class IPCLockFreeQueue
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
            m_Lock = 0;
            m_UnLock = 1;
        }
        inline void Lock()
        {
            while (!__sync_bool_compare_and_swap(&m_Mutex, m_Lock, 1))
            {
                usleep(1);
            }
        }
        inline void UnLock()
        {
            __sync_bool_compare_and_swap(&m_Mutex, m_UnLock, 0);
        }
    }TSpinLock;

    typedef struct
    {
        int Index;
        char Account[32];
        int Head;
        int Tail;
        T Queue[N];
    }TChannel;
public:
    IPCLockFreeQueue()
    {

    }
    // key:共享内存key
    // channelCount: 通道数量，即支持账户数量
    void Init(unsigned int key = 0XFF000001, unsigned int channelCount = 20)
    {
        m_IPCKey = key;
        m_ChannelSize = N;
        m_ChannelCount = channelCount;
        m_Buffer = NULL;
        m_ChannelIndexMap.clear();
        m_ChannelIndex = -1;
        if(key <= 0 || m_ChannelSize == 0 || m_ChannelCount == 0)
        {
            printf("IPCLockFreeQueue Parameter Error, key=0X%X, channelSize=%u, channelCount= %u\n", 
                    m_IPCKey, m_ChannelSize, m_ChannelCount);
            return;
        }
        int shmid = shmget(m_IPCKey, sizeof(TChannel) * m_ChannelCount, 0666 | IPC_CREAT);
        m_Buffer = static_cast<TChannel*>(shmat(shmid, 0, 0));
        m_SpinLock.Init();
        printf("IPCLockFreeQueue key=0X%X, channelSize=%u, channelCount= %u Size: %.2fMB\n", 
                    m_IPCKey, m_ChannelSize, m_ChannelCount, 1.0 * sizeof(TChannel) * m_ChannelCount / (1024*1024));
    }

    ~IPCLockFreeQueue()
    {
        shmdt((void *)m_Buffer);
        m_Buffer = NULL;
    }

    inline int CurrentChannel() const
    {
        return m_ChannelIndex;
    }

    inline void Reset()
    {
        memset(m_Buffer, 0, sizeof(TChannel) * m_ChannelCount);
    }

    inline void RegisterChannel(const char* account)
    {
        InitChannelIndex(account);
    }

    inline void ResetChannel(const char* account)
    {
        std::string Account = account;
        for(int i = 0; i < m_ChannelCount; i++)
        { 
            if(Account == m_Buffer[i].Account)
            {
                memset(&m_Buffer[i].Queue, 0, m_ChannelSize * sizeof(T));
                m_Buffer[i].Index = i;
                #ifdef LOCK
                m_SpinLock.Lock();
                #endif
                m_Buffer[i].Head = 0;
                m_Buffer[i].Tail = 0;
                #ifdef LOCK
                 m_SpinLock.UnLock();
                #endif
                break;
            }
        }
    }

    bool Push(const T& value)
    {
        bool ret = false;
        if (!IsFull())
        {
            memcpy(&m_Buffer[m_ChannelIndex].Queue[m_Buffer[m_ChannelIndex].Tail], &value, sizeof(T));
            #ifdef LOCK
            m_SpinLock.Lock();
            #endif
            m_Buffer[m_ChannelIndex].Tail = (m_Buffer[m_ChannelIndex].Tail + 1) % m_ChannelSize;
            #ifdef LOCK
            m_SpinLock.UnLock();
            #endif
            ret = true;
        }
        return ret;
    }

    bool Pop(T& value)
    {
        bool ret = false;
        if(!IsEmpty())
        {
            memcpy(&value, &m_Buffer[m_ChannelIndex].Queue[m_Buffer[m_ChannelIndex].Head], sizeof(T));
            #ifdef LOCK
            m_SpinLock.Lock();
            #endif
            m_Buffer[m_ChannelIndex].Head = (m_Buffer[m_ChannelIndex].Head + 1) % m_ChannelSize;
            #ifdef LOCK
            m_SpinLock.UnLock();
            #endif
            ret = true;
        }
        return ret;
    }

    bool Pop(std::list<T>& items)
    {
        bool ret = false;
        while(!IsEmpty())
        {
            T value;
            memcpy(&value, &m_Buffer[m_ChannelIndex].Queue[m_Buffer[m_ChannelIndex].Head], sizeof(T));
            #ifdef LOCK
            m_SpinLock.Lock();
            #endif
            m_Buffer[m_ChannelIndex].Head = (m_Buffer[m_ChannelIndex].Head + 1) % m_ChannelSize;
            #ifdef LOCK
            m_SpinLock.UnLock();
            #endif
            items.push_back(value);
            ret = true;
        }
        return ret;
    }

    int Head() const
    {
        return m_Buffer[m_ChannelIndex].Head;
    }

    int Tail() const
    {
        return m_Buffer[m_ChannelIndex].Tail;
    }

    bool IsFull() const
    {
        return m_Buffer[m_ChannelIndex].Head == (m_Buffer[m_ChannelIndex].Tail + 1) % m_ChannelSize;
    }

    bool IsEmpty() const
    {
        return m_Buffer[m_ChannelIndex].Head == m_Buffer[m_ChannelIndex].Tail;
    }
protected:
    void InitChannelIndex(const char* account)
    {
        for (size_t i = 0; i < m_ChannelCount; i++)
        {
            std::string Account = m_Buffer[i].Account;
            if(Account.empty())
            {
                auto it = m_ChannelIndexMap.find(account);
                if(it == m_ChannelIndexMap.end())
                {
                    m_Buffer[i].Index = i;
                    strncpy(m_Buffer[i].Account, account, sizeof(m_Buffer[i].Account));
                    #ifdef LOCK
                    m_SpinLock.Lock();
                    #endif
                    m_Buffer[i].Head = 0;
                    m_Buffer[i].Tail = 0;
                    #ifdef LOCK
                    m_SpinLock.UnLock();
                    #endif
                    memset(m_Buffer[i].Queue, 0, m_ChannelSize * sizeof(T));
                    m_ChannelIndexMap[account] = i;
                    break;
                }
            }
            else
            {
                m_ChannelIndexMap[Account] = i;
            }
            // printf("index: %d Account: %s\n", i, m_Buffer[i].Account);
        }
        m_ChannelIndex = m_ChannelIndexMap[account];
        printf("Account: %s  Current Channel: %d\n", account, m_ChannelIndex);
    }
protected:
    unsigned int m_IPCKey;
    unsigned int m_ChannelSize;
    unsigned int m_ChannelCount;
    int m_ChannelIndex;
    TSpinLock m_SpinLock;
    TChannel* m_Buffer;
    std::unordered_map<std::string, int> m_ChannelIndexMap;
};

}

#endif // IPCLOCKFREEQUEUE_HPP