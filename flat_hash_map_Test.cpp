#include <unordered_map>
#include <mutex>
#include <shared_mutex>
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
typedef phmap::flat_hash_map<std::string, TOrderStatus,
                            phmap::priv::hash_default_hash<std::string>,
                            phmap::priv::hash_default_eq<std::string>,
                            std::allocator<std::pair<const std::string, TOrderStatus>>> 
                            OrderStatusMapT;

int main(int argc, char const *argv[])
{
    OrderStatusMapT OrderStatusMap;
    printf("Init size:%d bucket_count:%d\n", OrderStatusMap.size(),
    OrderStatusMap.bucket_count());
    OrderStatusMap.reserve(256);
    printf("reserve size:%d bucket_count:%d\n", OrderStatusMap.size(),
    OrderStatusMap.bucket_count());
    int i = 0;
    while(i < 20)
    {
        char OrderRef[32] = {0};
        sprintf(OrderRef, "%010d", i);
        if(i < 10)
        {
            TOrderStatus& OrderStatus = OrderStatusMap[OrderRef];
        }
        else
        {
            TOrderStatus OrderStatus;
            OrderStatusMap.emplace(OrderRef, OrderStatus);
        }
        i++;
    }
    i = 0;
    while(i < 20)
    {
        char OrderRef[32] = {0};
        sprintf(OrderRef, "%010d", i);
        auto it = OrderStatusMap.find(OrderRef);
        if(it != OrderStatusMap.end())
        {
            printf("size:%d bucket_count:%d remove OrderRef:%s\n",
            OrderStatusMap.size(), OrderStatusMap.bucket_count(), OrderRef);
            OrderStatusMap.erase(OrderRef);
        }
        i++;
    }
    printf("end size:%d bucket_count:%d\n", OrderStatusMap.size(),
    OrderStatusMap.bucket_count());
    return 0;
}
// g++ -std=c++17 flat_hash_map_Test.cpp -o testmap -I../XAPI/parallel_hashmap/