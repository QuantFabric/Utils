#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#include "libipc/ipc.h"

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

static unsigned long getTimeUs()
{
    struct timespec timeStamp = {0, 0};
    clock_gettime(CLOCK_REALTIME, &timeStamp);
    return timeStamp.tv_sec * 1e6 + timeStamp.tv_nsec/1000;
}

const int N = 2000000;
const char* IPC_CHANNEL_NAME = "IPC";

void produce()
{
    ipc::route sender{IPC_CHANNEL_NAME, ipc::sender};
    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    unsigned int i = 0;
    unsigned int tid = pthread_self();
    sender.wait_for_recv(4);
    while(i < N)
    {
        if(sender.send((const void*)new Test(i, i), sizeof(Test)))
        {
            i++;
        }
    }
    gettimeofday(&end, NULL);
    double tm = getdeltatimeofday(&begin, &end);
    printf("producer tid=%lu %f MB/s %f msg/s elapsed= %f size= %u\n", tid, N * sizeof(Test) * 1.0 / (tm * 1024 * 1024), N * 1.0 / tm, tm, i);
}

void consume()
{
    ipc::route receiver{IPC_CHANNEL_NAME, ipc::receiver};
    Test test;
    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    unsigned int i = 0;
    unsigned int tid = pthread_self();
    while(i < N)
    {
        auto buf = receiver.recv();
        auto obj = static_cast<Test*>(buf.data());
        obj->display();
        i++;
    }
    gettimeofday(&end, NULL);
    double tm = getdeltatimeofday(&begin, &end);
    printf("consumer tid=%lu %f MB/s %f msg/s elapsed= %f size= %u\n", tid, N * sizeof(Test) * 1.0 / (tm * 1024 * 1024), N * 1.0 / tm, tm, i);
}

int main(int argc, char const *argv[])
{

#ifdef PRODUCER
    std::thread producer1(produce);
    // std::thread producer2(produce);
#endif

#ifdef CONSUMER
    usleep(2000);
    std::thread consumer1(consume);
    // std::thread consumer2(consume);
#endif

#ifdef PRODUCER
    producer1.join();
    // producer2.join();
#endif

#ifdef CONSUMER
    consumer1.join();
    // consumer2.join();
#endif

    return 0;
}

// g++ --std=c++11 -O2 -DPRODUCER CPP_IPC_Test.cpp -o producer -lrt -lipc -pthread -I/home/yangyl/XOS/QuantFabric/XAPI/CPP-IPC/include/ -L/home/yangyl/XOS/QuantFabric/XAPI/CPP-IPC/lib/
// g++ --std=c++11 -O2 -DCONSUMER CPP_IPC_Test.cpp -o consumer -lrt -lipc -pthread -I/home/yangyl/XOS/QuantFabric/XAPI/CPP-IPC/include/ -L/home/yangyl/XOS/QuantFabric/XAPI/CPP-IPC/lib/