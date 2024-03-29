#include "LockFreeQueue.hpp"
#include <thread>
#include <sys/time.h>
#include <time.h>

class Test
{
public:
   Test(int id = 0, int value = 0)
   {
	    this->id = id;
        this->value = value;
   }
   void display()
   {
        this->value += 10;
        this->value -= 10;
        sprintf(data, "id = %lu, value = %d", this->id, this->value);
   }
public:
   unsigned int id;
   int value;
   char data[760];
};

double getdeltatimeofday(struct timeval *begin, struct timeval *end)
{
    return (end->tv_sec + end->tv_usec * 1.0 / 1000000) -
           (begin->tv_sec + begin->tv_usec * 1.0 / 1000000);
}

// multi thread in one process
#ifdef HEAP
Utils::LockFreeQueue<Test> queue(1 << 10);
#endif

// IPC ShareMemory
#ifdef IPC
Utils::LockFreeQueue<Test> queue(1 << 10, 0xFF02);
#endif

#define N (20000000)

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
    unsigned int i = 0;
    unsigned int tid = pthread_self();
    while(i < N)
    {
        if(queue.Push(Test(i, i)))
	        i++;
        // int currentTimeStamp = getTimeUs();
        // if(currentTimeStamp % 5000000 == 0)
        // {
        //     printf("produce tid: %lu i= %d queue full: %d\n", tid, i, queue.IsFull());
        // }
    }
    gettimeofday(&end, NULL);
    double tm = getdeltatimeofday(&begin, &end);
    printf("producer tid=%lu %f MB/s %f msg/s elapsed= %f size= %u\n", tid, N * sizeof(Test) * 1.0 / (tm * 1024 * 1024), N * 1.0 / tm, tm, i);
}

void consume()
{
    Test test;
    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    unsigned int i = 0;
    unsigned int tid = pthread_self();
    while(i < N * 2)
    {
        if(queue.Pop(test))
        {
            i += 1;
        }
        // int currentTimeStamp = getTimeUs();
        // if(currentTimeStamp % 5000000 == 0)
        // {
        //     printf("consume tid: %lu i= %d queue empty: %d\n", tid, i, queue.IsEmpty());
        // }
    }
    gettimeofday(&end, NULL);
    double tm = getdeltatimeofday(&begin, &end);
    printf("consumer tid=%lu %f MB/s %f msg/s elapsed= %f size= %u\n", tid, N * sizeof(Test) * 1.0 / (tm * 1024 * 1024), N * 1.0 / tm, tm, i);
}

int main(int argc, char const *argv[])
{
    queue.Reset();
#ifdef PRODUCER
    std::thread producer1(produce);
    std::thread producer2(produce);
#endif

#ifdef CONSUMER
    usleep(2000);
    std::thread consumer1(consume);
    // std::thread consumer2(consume);
#endif

#ifdef PRODUCER
    producer1.join();
    producer2.join();
#endif

#ifdef CONSUMER
    consumer1.join();
    // consumer2.join();
#endif

    return 0;
}
// Multi Thread in one Process
// g++ --std=c++11 -O2 -DHEAP -DPRODUCER -DCONSUMER LockFreeQueueTest.cpp -o test -lrt -pthread
// IPC
// g++ --std=c++11 -O2 -DIPC -DPRODUCER LockFreeQueueTest.cpp -o producer -lrt -pthread
// g++ --std=c++11 -O2 -DIPC -DCONSUMER LockFreeQueueTest.cpp -o consumer -lrt -pthread
// g++编译时，如果GLIBC库版本低于2.17，则clock_gettime需要使用指定-lrt选项。
