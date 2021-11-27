#include "IPCLockFreeQueue.hpp"
#include <thread>
#include <sys/time.h>
#include <time.h>

struct TOrderStatus
{
    char Colo[16];
    char Product[16];
    char Broker[16];
    char Account[16];
    char Ticker[16];
    char ExchangeID[16];
    char OrderRef[32];
    char OrderSysID[32];
    char OrderLocalID[32];
    int OrderToken;
    int EngineID;
    uint8_t OrderType;
    uint8_t OrderSide;
    uint8_t OrderStatus;
    double SendPrice;
    unsigned int SendVolume;
    unsigned int TotalTradedVolume;
    double TradedAvgPrice;
    unsigned int TradedVolume;
    double TradedPrice;
    unsigned int CanceledVolume;
    char SendTime[32];
    char InsertTime[32];
    char BrokerACKTime[32];
    char ExchangeACKTime[32];
    char UpdateTime[32];
    int ErrorID;
    char ErrorMsg[128];
    char RiskID[16];
};

double getdetlatimeofday(struct timeval *begin, struct timeval *end)
{
    return (end->tv_sec + end->tv_usec * 1.0 / 1000000) -
           (begin->tv_sec + begin->tv_usec * 1.0 / 1000000);
}


Utils::IPCLockFreeQueue<TOrderStatus, 1000> queue(0XFF0000FF);

#define N (10000 * (10 << 10))

static unsigned long getTimeUs()
{
    struct timespec timeStamp = {0, 0};
    clock_gettime(CLOCK_REALTIME, &timeStamp);
    return timeStamp.tv_sec * 1e6 + timeStamp.tv_nsec/1000;
}

void produce(const char* account)
{
    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    unsigned int i = 0;
    unsigned int tid = pthread_self();
    TOrderStatus OrderStatus;
    while(i < N)
    {
        OrderStatus.OrderToken = i;
        strncpy(OrderStatus.Account, account, sizeof(OrderStatus.Account));
        if(queue.Push(OrderStatus))
        {   
            if(0 == i)
            {
                gettimeofday(&begin, NULL);
            }
            i++;
        }
    }
    gettimeofday(&end, NULL);
    double tm = getdetlatimeofday(&begin, &end);
    printf("producer %s tid=%lu %.2f MB/s %.2f msg/s %.2f ns/msg elapsed= %.2f size= %u T Size: %u\n", 
        account, tid, N * sizeof(TOrderStatus) / (tm * 1024 * 1024), N / tm, tm * 1000000000 / i, tm, i, sizeof(TOrderStatus));
}

void consume(const char* account)
{
    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    unsigned int i = 0;
    unsigned int tid = pthread_self();
    TOrderStatus OrderStatus;
    while(i < N)
    {
        if(queue.Pop(OrderStatus))
        {
            if(0 == i)
            {
                gettimeofday(&begin, NULL);
            }
            // printf("Account: %s OrderToken: %d\n", OrderStatus.Account, OrderStatus.OrderToken);
            i++;
        }
    }
    gettimeofday(&end, NULL);
    double tm = getdetlatimeofday(&begin, &end);
    printf("consumer %s tid=%lu %.2f MB/s %.2f msg/s %.2f ns/msg elapsed= %.2f size= %u T Size: %u\n", 
        account, tid, N * sizeof(TOrderStatus) / (tm * 1024 * 1024), N / tm, tm * 1000000000 / i, tm, i, sizeof(TOrderStatus));
}

int main(int argc, char const *argv[])
{

#ifdef PRODUCER
    queue.RegisterChannel(argv[1]);
    queue.ResetChannel(argv[1]);
    std::thread producer1(produce, argv[1]);
#endif

#ifdef CONSUMER
    queue.RegisterChannel(argv[1]);
    std::thread consumer1(consume, argv[1]);
#endif

#ifdef PRODUCER
    producer1.join();
#endif

#ifdef CONSUMER
    consumer1.join();
#endif

    return 0;
}
// Add Lock
// g++ --std=c++11 -O2 -DLOCK -DPRODUCER IPCLockFreeQueueTest.cpp -o producer -lrt -pthread
// g++ --std=c++11 -O2 -DLOCK -DCONSUMER IPCLockFreeQueueTest.cpp -o consumer -lrt -pthread
// Lock Free
// g++ --std=c++11 -O2 -DPRODUCER IPCLockFreeQueueTest.cpp -o producer -lrt -pthread
// g++ --std=c++11 -O2 -DCONSUMER IPCLockFreeQueueTest.cpp -o consumer -lrt -pthread