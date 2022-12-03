#include <unordered_map>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <unistd.h>
#include "phmap.h"


struct TOrderStatus
{
    char Colo[16];
    char Broker[16];
    char Product[16];
    char Account[16];
    char Ticker[32];
    char ExchangeID[16];
    uint8_t BussinessType;
    char OrderRef[32];
    char OrderSysID[32];
    char OrderLocalID[32];
    int OrderToken;
    int EngineID;
    int UserReserved1;
    int UserReserved2;
    uint8_t OrderType;
    uint8_t OrderSide;
    uint8_t OrderStatus;
    uint8_t AlgoType;
    double SendPrice;
    unsigned int SendVolume;
    unsigned int TotalTradedVolume;
    double TradedAvgPrice;
    unsigned int TradedVolume;
    double TradedPrice;
    unsigned int CanceledVolume;
    double Commission;
    char RecvMarketTime[32];
    char SendTime[32];
    char InsertTime[32];
    char BrokerACKTime[32];
    char ExchangeACKTime[32];
    char RiskID[16];
    char Trader[16];
    int ErrorID;
    char ErrorMsg[256];
    char UpdateTime[32];
};

typedef phmap::parallel_flat_hash_map<std::string, TOrderStatus, 
                                        phmap::priv::hash_default_hash<std::string>,
                                        phmap::priv::hash_default_eq<std::string>,
                                        std::allocator<std::pair<const std::string, TOrderStatus>>, 
                                        8, 
                                        std::shared_mutex> OrderStatusMapT;
OrderStatusMapT OrderStatusMap;
const int N = 1000000;

void produce()
{
    OrderStatusMap.reserve(1000);
    int i = 0;
    while(i < N)
    {
        char OrderRef[32] = {0};
        sprintf(OrderRef, "%010d", i);
        TOrderStatus& OrderStatus = OrderStatusMap[OrderRef];
        memcpy(OrderStatus.OrderRef, OrderRef, sizeof(OrderStatus.OrderRef)); 
        i++;
    }
    printf("produce size:%d bucket_count:%d i=%d\n", OrderStatusMap.size(), OrderStatusMap.bucket_count(), i);
}

void consume()
{
    usleep(1000);
    int i = 0;
    while(i < N)
    {
        char OrderRef[32] = {0};
        sprintf(OrderRef, "%010d", i);
        auto it = OrderStatusMap.find(OrderRef);
        if(it != OrderStatusMap.end())
        {
            OrderStatusMap.erase(OrderRef);
            i++;
        }
    }
    printf("consume size:%d bucket_count:%d i=%d\n", OrderStatusMap.size(), OrderStatusMap.bucket_count(), i);
}

int main(int argc, char const *argv[])
{
    std::thread producer(produce);
    std::thread consumer(consume);
    producer.join();
    consumer.join();
    
    return 0;
}

// g++ -std=c++17 parallel_node_hash_map_Test.cpp -o testmap -pthread -I../XAPI/parallel_hashmap/