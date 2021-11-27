#ifndef MARKETDATA_HPP
#define MARKETDATA_HPP

#include <string>
#include <string.h>
#include <vector>
#include <float.h>
#include "Util.hpp"

namespace MarketData
{

struct StockIndexMarketData
{
    char RevDataLocalTime[32];
    char Ticker[16];
    char UpdateTime[32];
    int MillSec;
    double LastPrice;
    int Volume;
    double Turnover;
    double OpenInterest;
    double OpenPrice;
    double HighestPrice;
    double LowestPrice;
    double UpperLimitPrice;
    double LowerLimitPrice;
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
    int Tick;
    int SectionFirstTick;
    int SectionLastTick;
    int TotalTick;
    int ErrorID;
};

struct StockIndexMarketDataSet
{
    char Colo[16];
    int Tick;
    StockIndexMarketData IF[4];
    StockIndexMarketData IC[4];
    StockIndexMarketData IH[4];
    char UpdateTime[32];
};

static void Check(StockIndexMarketData& data)
{
    int ErrorID = 0;
    // rule 1
    if (!((data.BidPrice1 < 1e7 && data.BidPrice1 > 0) || (data.AskPrice1 > 0 && data.AskPrice1 < 1e7)))
    {
        ErrorID = 1;
    }
    else
    {
        // rule 2
        std::string time1;
        if(strnlen(data.UpdateTime, sizeof(data.UpdateTime)) == 0)
        {
            time1 = Utils::getCurrentDay();
            time1 = time1 + " 00:00:00";
        }
        else
        {
            time1 = data.UpdateTime + 11;
        }
        std::string time2 = data.RevDataLocalTime + 11;
        if (abs(Utils::TimeDiffUs(time1, time2)) >= 120 * 1e6)
        {
            ErrorID = 2;
        }
    }
    data.ErrorID = ErrorID;
    if(data.BidPrice1 == DBL_MAX)
    {
        data.BidPrice1 = 0;
    }
    if(data.BidPrice2 == DBL_MAX)
    {
        data.BidPrice2 = 0;
    }
    if(data.BidPrice3 == DBL_MAX)
    {
        data.BidPrice3 = 0;
    }
    if(data.BidPrice4 == DBL_MAX)
    {
        data.BidPrice4 = 0;
    }
    if(data.BidPrice5 == DBL_MAX)
    {
        data.BidPrice5 = 0;
    }
    if(data.AskPrice1 == DBL_MAX)
    {
        data.AskPrice1 = 0;
    }
    if(data.AskPrice2 == DBL_MAX)
    {
        data.AskPrice2 = 0;
    }
    if(data.AskPrice3 == DBL_MAX)
    {
        data.AskPrice4 = 0;
    }
    if(data.AskPrice4 == DBL_MAX)
    {
        data.AskPrice4 = 0;
    }
    if(data.AskPrice5 == DBL_MAX)
    {
        data.AskPrice5 = 0;
    }
}


}

#endif // MARKETDATA_HPP