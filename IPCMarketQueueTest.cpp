#include "IPCMarketQueue.hpp"
#include <thread>
#include <sys/time.h>
#include <time.h>

struct TMarketData
{
    char Colo[16];
    int Tick;
    char UpdateTime[32];
    char Data[4096];
};

double getdetlatimeofday(struct timeval *begin, struct timeval *end)
{
    return (end->tv_sec + end->tv_usec * 1.0 / 1000000) -
           (begin->tv_sec + begin->tv_usec * 1.0 / 1000000);
}

#define N (30000)

Utils::IPCMarketQueue<TMarketData> queue(N, 0XFF0000FE);


static unsigned long getTimeUs()
{
    struct timespec timeStamp = {0, 0};
    clock_gettime(CLOCK_REALTIME, &timeStamp);
    return timeStamp.tv_sec * 1e6 + timeStamp.tv_nsec/1000;
}

void produce()
{
    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    long count = 0;
    unsigned int tid = pthread_self();
    for (size_t j = 0; j < 1000; j++)
    {
        int i = 0;
        TMarketData MarketData;
        memset(&MarketData, 0, sizeof(TMarketData));
        while(i < N)
        {
            MarketData.Tick = i;
            if(queue.Write(i, MarketData))
            {   
                // printf("Tick %d\n", i);
                i++;
                count++;
            }
        }
    }
    
    gettimeofday(&end, NULL);
    double tm = getdetlatimeofday(&begin, &end);
    printf("producer tid=%lu %.2f MB/s %.2f msg/s %.2f ns/msg elapsed= %.2f size= %u T Size: %u\n", 
        tid, count * sizeof(TMarketData) / (tm * 1024 * 1024), count / tm, tm * 1000000000 / count, tm, count, sizeof(TMarketData));
}

void consume()
{
    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    long count = 0;
    unsigned int tid = pthread_self();

    for (size_t j = 0; j < 1000; j++)
    {
        queue.ResetTick(0);
        int i = 0;
        TMarketData MarketData;
        memset(&MarketData, 0, sizeof(TMarketData));
        while(i < N)
        {
            MarketData.Tick = i;
            if(queue.Write(i, MarketData))
            {   
                // printf("Tick %d\n", i);
                i++;
                count++;
            }
        }
    }

    gettimeofday(&end, NULL);
    double tm = getdetlatimeofday(&begin, &end);
    printf("consumer tid=%lu %.2f MB/s %.2f msg/s %.2f ns/msg elapsed= %.2f size= %u T Size: %u\n", 
        tid, count * sizeof(TMarketData) / (tm * 1024 * 1024), count / tm, tm * 1000000000 / count, tm, count, sizeof(TMarketData));
}

int main(int argc, char const *argv[])
{

#ifdef PRODUCER
    std::thread producer1(produce);
#endif

#ifdef CONSUMER
    std::thread consumer1(consume);
#endif

#ifdef PRODUCER
    producer1.join();
#endif

#ifdef CONSUMER
    consumer1.join();
#endif

    return 0;
}
// g++ --std=c++11 -O2 -DPRODUCER IPCMarketQueueTest.cpp -o producer -lrt -pthread
// g++ --std=c++11 -O2 -DCONSUMER IPCMarketQueueTest.cpp -o consumer -lrt -pthread