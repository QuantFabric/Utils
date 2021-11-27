#include "concurrentqueue.h"


moodycamel::ConcurrentQueue<int> queue(32);

void produce()
{
    long tid = pthread_self();
    int i = 0;
    while (i < 1 << 20)
    {
        queue.try_enqueue(i++);
    }
    printf("tid: %ld produce done\n", tid);
}

void consume()
{
    while (true)
    {
        long tid = pthread_self();
        int items[10];
        if (queue.try_dequeue_bulk(items, 10)) 
        {
            for (size_t k = 0; k < 10; k++)
            {
                printf("tid: %ld dequeue: %d\n", tid, items[k]);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    
    int dequeued[100] = {0};
    std::thread threads[6];
    // Producers
    for (int i = 0; i < 4; ++i) {
        threads[i] = std::thread(produce);
    }
    // Consumers
    for (int i = 4; i < 6; ++i) {
        threads[i] = std::thread(consume);
    }
    // Wait for all threads
    for (int i = 0; i < 6; ++i) {
        threads[i].join();
    }

    return 0;
}