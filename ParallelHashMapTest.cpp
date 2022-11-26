#include <unordered_map>
#include <mutex>
#include <shared_mutex>
#include "PackMessage.hpp"
#include "Util.hpp"
#include "RingBuffer.hpp"
#include "phmap.h"

#ifdef PHMAP
typedef phmap::parallel_flat_hash_map<std::string, Message::TOrderStatus,
                                        phmap::priv::hash_default_hash<std::string>,
                                        phmap::priv::hash_default_eq<std::string>,
                                        std::allocator<std::pair<const std::string, Message::TOrderStatus>>,
                                        8,
                                        std::shared_mutex> OrderStatusMapT;
OrderStatusMapT OrderStatusMap;
#else
std::unordered_map<std::string, Message::TOrderStatus> OrderStatusMap;
#endif


const int N = 1000000;
Utils::RingBuffer<std::string> OrderRefQueue(1 << 10);

void produce()
{
    OrderStatusMap.reserve(1000);
    int i = 0;
    while(i < N)
    {
        char OrderRef[32] = {0};
        sprintf(OrderRef, "%010d", i);
        #ifndef PHMAP
        std::mutex mtx;
        mtx.lock();
        #endif
        Message::TOrderStatus& OrderStatus = OrderStatusMap[OrderRef];
        #ifndef PHMAP
        mtx.unlock();
        #endif
        memcpy(OrderStatus.OrderRef, OrderRef, sizeof(OrderStatus.OrderRef));
        printf("produce OrderRef:%s\n", OrderRef);
        if(OrderRefQueue.push(OrderRef))
        {
            i++;
        }
    }
}

void consume()
{
    usleep(1000);
    while(true)
    {
        std::string OrderRef;
        if(OrderRefQueue.pop(OrderRef))
        {
            #ifndef PHMAP
            std::mutex mtx;
            mtx.lock();
            #endif
            auto it = OrderStatusMap.find(OrderRef);
            if(it != OrderStatusMap.end())
            {
                OrderStatusMap.erase(OrderRef);
            }
            else
            {
                printf("consume OrderRef:%s not found\n", OrderRef.c_str());
            }
            #ifndef PHMAP
            mtx.unlock();
            #endif
        }
    }
}

int main(int argc, char const *argv[])
{
    std::thread producer(produce);
    std::thread consumer(consume);
    producer.join();
    consumer.join();

    return 0;
}

// g++ -std=c++17 ParallelHashMapTest.cpp -o testmap -pthread -I../XAPI/parallel_hashmap/
// g++ -std=c++17 -DPHMAP ParallelHashMapTest.cpp -o testmap -pthread -I../XAPI/parallel_hashmap/