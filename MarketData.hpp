#ifndef MARKETDATA_HPP
#define MARKETDATA_HPP

#include <string>
#include <string.h>
#include <vector>
#include <float.h>
#include "Util.hpp"

namespace MarketData
{

#define TICKER_LEN 20

struct TFutureMarketData
{
    char Colo[16];
    char Broker[16];
    char Ticker[20]; // 商品组合合约长度可能大于16字节
    char ExchangeID[16];
    int LastTick;
    int Tick;
    char TradingDay[16];
    char ActionDay[16];
    char UpdateTime[32];
    int MillSec;
    double LastPrice;
    int Volume;
    double Turnover;
    double OpenPrice;
    double ClosePrice;
    double PreClosePrice;
    double SettlementPrice;
    double PreSettlementPrice;
    double OpenInterest;
    double PreOpenInterest;
    double CurrDelta;
    double PreDelta;
    double HighestPrice;
    double LowestPrice;
    double UpperLimitPrice;
    double LowerLimitPrice;
    double AveragePrice;
    double BidPrice1;
    int BidVolume1;
    double AskPrice1;
    int AskVolume1;
    double BidPrice2;
    int BidVolume2;
    double AskPrice2;
    int AskVolume2;
    double BidPrice3;
    int BidVolume3;
    double AskPrice3;
    int AskVolume3;
    double BidPrice4;
    int BidVolume4;
    double AskPrice4;
    int AskVolume4;
    double BidPrice5;
    int BidVolume5;
    double AskPrice5;
    int AskVolume5;
    int SectionFirstTick;
    int SectionLastTick;
    int TotalTick;
    int ErrorID;
    char RecvLocalTime[32];
};

typedef TFutureMarketData TSpotMarketData;

struct TStockMarketData
{
    char Colo[16];
    char Broker[16];
    char Ticker[20]; // 商品组合合约长度可能大于16字节
    char ExchangeID[16];
    int LastTick;
    int Tick;
    char UpdateTime[32];
    int MillSec;
    double LastPrice;
    int Volume;
    double Turnover;
    double PreSettlementPrice;
    double PreClosePrice;
    double OpenInterest;
    double OpenPrice;
    double HighestPrice;
    double LowestPrice;
    double UpperLimitPrice;
    double LowerLimitPrice;
    double BidPrice[10];
    int BidVolume[10];
    double AskPrice[10];
    int AskVolume[10];
    int ErrorID;
    char RecvLocalTime[32];
};

static bool Check(TFutureMarketData& data)
{
    bool ret = true;
    if(data.LastPrice > 1e15)
    {
        data.LastPrice = 0;
        ret = false;
    }
    if(data.OpenPrice > 1e15)
    {
        data.OpenPrice = 0;
        ret = false;
    }
    if(data.Turnover > 1e15)
    {
        data.Turnover = 0;
        ret = false;
    }
    if(data.Volume == 0)
    {
        data.Volume = 0;
        ret = false;
    }
    if(data.SettlementPrice > 1e15)
    {
        data.SettlementPrice = 0;
    }
    if(data.PreSettlementPrice > 1e15)
    {
        data.PreSettlementPrice = 0;
    }
    if(data.ClosePrice > 1e15)
    {
        data.ClosePrice = 0;
    }
    if(data.PreClosePrice > 1e15)
    {
        data.PreClosePrice = 0;
    }
    if(data.OpenInterest > 1e15)
    {
        data.OpenInterest = 0;
    }
    if(data.PreOpenInterest > 1e15)
    {
        data.PreOpenInterest = 0;
    }
    if(data.CurrDelta > 1e15)
    {
        data.CurrDelta = 0;
    }
    if(data.PreDelta > 1e15)
    {
        data.PreDelta = 0;
    }
    if(data.HighestPrice > 1e15)
    {
        data.HighestPrice = 0;
    }
    if(data.LowestPrice > 1e15)
    {
        data.LowestPrice = 0;
    }
    if(data.UpperLimitPrice > 1e15)
    {
        data.UpperLimitPrice = 0;
    }
    if(data.LowerLimitPrice > 1e15)
    {
        data.LowerLimitPrice = 0;
    }
    if(data.AveragePrice > 1e15)
    {
        data.AveragePrice = 0;
    }
    if(data.BidPrice1 > 1e15)
    {
        data.BidPrice1 = 0;
    }
    if(data.BidPrice2 > 1e15)
    {
        data.BidPrice2 = 0;
    }
    if(data.BidPrice3 > 1e15)
    {
        data.BidPrice3 = 0;
    }
    if(data.BidPrice4 > 1e15)
    {
        data.BidPrice4 = 0;
    }
    if(data.BidPrice5 > 1e15)
    {
        data.BidPrice5 = 0;
    }
    if(data.AskPrice1 > 1e15)
    {
        data.AskPrice1 = 0;
    }
    if(data.AskPrice2 > 1e15)
    {
        data.AskPrice2 = 0;
    }
    if(data.AskPrice3 > 1e15)
    {
        data.AskPrice3 = 0;
    }
    if(data.AskPrice4 > 1e15)
    {
        data.AskPrice4 = 0;
    }
    if(data.AskPrice5 > 1e15)
    {
        data.AskPrice5 = 0;
    }
    return ret;
}

}

#endif // MARKETDATA_HPP