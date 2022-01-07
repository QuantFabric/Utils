#ifndef MARKETDATALOGGER_H
#define MARKETDATALOGGER_H

#include <unordered_map>
#include <unordered_set>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/pattern_formatter.h"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <string>
#include "MarketData.hpp"
#include "Singleton.hpp"

namespace Utils
{
class MarketDataLogger
{
    friend Utils::Singleton<MarketDataLogger>;

public:
    void WriteMarketData(const MarketData::StockIndexMarketDataSet &dataset)
    {
        WriteMarketDataFile(dataset);
    }

    void WriteMarketDataFile(const MarketData::StockIndexMarketDataSet &data)
    {
        m_MarketDataLogger->info(
            "{},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{},{},{},\
            {},{},{},{},{},{},{},{}",
            data.Tick,
            data.UpdateTime,
            data.IC[0].RevDataLocalTime,
            data.IC[0].Tick,
            data.IC[0].SectionFirstTick,
            data.IC[0].SectionLastTick,
            data.IC[0].TotalTick,
            data.IC[0].ErrorID,
            data.IC[0].Ticker,
            data.IC[0].UpdateTime,
            data.IC[0].MillSec,
            data.IC[0].LastPrice,
            data.IC[0].Volume,
            data.IC[0].Turnover,
            data.IC[0].OpenInterest,
            data.IC[0].OpenPrice,
            data.IC[0].HighestPrice,
            data.IC[0].LowestPrice,
            data.IC[0].UpperLimitPrice,
            data.IC[0].LowerLimitPrice,
            data.IC[0].BidPrice1,
            data.IC[0].BidVolume1,
            data.IC[0].AskPrice1,
            data.IC[0].AskVolume1,
            data.IC[0].BidPrice2,
            data.IC[0].BidVolume2,
            data.IC[0].AskPrice2,
            data.IC[0].AskVolume2,
            data.IC[0].BidPrice3,
            data.IC[0].BidVolume3,
            data.IC[0].AskPrice3,
            data.IC[0].AskVolume3,
            data.IC[0].BidPrice4,
            data.IC[0].BidVolume4,
            data.IC[0].AskPrice4,
            data.IC[0].AskVolume4,
            data.IC[0].BidPrice5,
            data.IC[0].BidVolume5,
            data.IC[0].AskPrice5,
            data.IC[0].AskVolume5,
            data.IC[1].RevDataLocalTime,
            data.IC[1].Tick,
            data.IC[1].SectionFirstTick,
            data.IC[1].SectionLastTick,
            data.IC[1].TotalTick,
            data.IC[1].ErrorID,
            data.IC[1].Ticker,
            data.IC[1].UpdateTime,
            data.IC[1].MillSec,
            data.IC[1].LastPrice,
            data.IC[1].Volume,
            data.IC[1].Turnover,
            data.IC[1].OpenInterest,
            data.IC[1].OpenPrice,
            data.IC[1].HighestPrice,
            data.IC[1].LowestPrice,
            data.IC[1].UpperLimitPrice,
            data.IC[1].LowerLimitPrice,
            data.IC[1].BidPrice1,
            data.IC[1].BidVolume1,
            data.IC[1].AskPrice1,
            data.IC[1].AskVolume1,
            data.IC[1].BidPrice2,
            data.IC[1].BidVolume2,
            data.IC[1].AskPrice2,
            data.IC[1].AskVolume2,
            data.IC[1].BidPrice3,
            data.IC[1].BidVolume3,
            data.IC[1].AskPrice3,
            data.IC[1].AskVolume3,
            data.IC[1].BidPrice4,
            data.IC[1].BidVolume4,
            data.IC[1].AskPrice4,
            data.IC[1].AskVolume4,
            data.IC[1].BidPrice5,
            data.IC[1].BidVolume5,
            data.IC[1].AskPrice5,
            data.IC[1].AskVolume5,
            data.IC[2].RevDataLocalTime,
            data.IC[2].Tick,
            data.IC[2].SectionFirstTick,
            data.IC[2].SectionLastTick,
            data.IC[2].TotalTick,
            data.IC[2].ErrorID,
            data.IC[2].Ticker,
            data.IC[2].UpdateTime,
            data.IC[2].MillSec,
            data.IC[2].LastPrice,
            data.IC[2].Volume,
            data.IC[2].Turnover,
            data.IC[2].OpenInterest,
            data.IC[2].OpenPrice,
            data.IC[2].HighestPrice,
            data.IC[2].LowestPrice,
            data.IC[2].UpperLimitPrice,
            data.IC[2].LowerLimitPrice,
            data.IC[2].BidPrice1,
            data.IC[2].BidVolume1,
            data.IC[2].AskPrice1,
            data.IC[2].AskVolume1,
            data.IC[2].BidPrice2,
            data.IC[2].BidVolume2,
            data.IC[2].AskPrice2,
            data.IC[2].AskVolume2,
            data.IC[2].BidPrice3,
            data.IC[2].BidVolume3,
            data.IC[2].AskPrice3,
            data.IC[2].AskVolume3,
            data.IC[2].BidPrice4,
            data.IC[2].BidVolume4,
            data.IC[2].AskPrice4,
            data.IC[2].AskVolume4,
            data.IC[2].BidPrice5,
            data.IC[2].BidVolume5,
            data.IC[2].AskPrice5,
            data.IC[2].AskVolume5,
            data.IC[3].RevDataLocalTime,
            data.IC[3].Tick,
            data.IC[3].SectionFirstTick,
            data.IC[3].SectionLastTick,
            data.IC[3].TotalTick,
            data.IC[3].ErrorID,
            data.IC[3].Ticker,
            data.IC[3].UpdateTime,
            data.IC[3].MillSec,
            data.IC[3].LastPrice,
            data.IC[3].Volume,
            data.IC[3].Turnover,
            data.IC[3].OpenInterest,
            data.IC[3].OpenPrice,
            data.IC[3].HighestPrice,
            data.IC[3].LowestPrice,
            data.IC[3].UpperLimitPrice,
            data.IC[3].LowerLimitPrice,
            data.IC[3].BidPrice1,
            data.IC[3].BidVolume1,
            data.IC[3].AskPrice1,
            data.IC[3].AskVolume1,
            data.IC[3].BidPrice2,
            data.IC[3].BidVolume2,
            data.IC[3].AskPrice2,
            data.IC[3].AskVolume2,
            data.IC[3].BidPrice3,
            data.IC[3].BidVolume3,
            data.IC[3].AskPrice3,
            data.IC[3].AskVolume3,
            data.IC[3].BidPrice4,
            data.IC[3].BidVolume4,
            data.IC[3].AskPrice4,
            data.IC[3].AskVolume4,
            data.IC[3].BidPrice5,
            data.IC[3].BidVolume5,
            data.IC[3].AskPrice5,
            data.IC[3].AskVolume5,
            data.IF[0].RevDataLocalTime,
            data.IF[0].Tick,
            data.IF[0].SectionFirstTick,
            data.IF[0].SectionLastTick,
            data.IF[0].TotalTick,
            data.IF[0].ErrorID,
            data.IF[0].Ticker,
            data.IF[0].UpdateTime,
            data.IF[0].MillSec,
            data.IF[0].LastPrice,
            data.IF[0].Volume,
            data.IF[0].Turnover,
            data.IF[0].OpenInterest,
            data.IF[0].OpenPrice,
            data.IF[0].HighestPrice,
            data.IF[0].LowestPrice,
            data.IF[0].UpperLimitPrice,
            data.IF[0].LowerLimitPrice,
            data.IF[0].BidPrice1,
            data.IF[0].BidVolume1,
            data.IF[0].AskPrice1,
            data.IF[0].AskVolume1,
            data.IF[0].BidPrice2,
            data.IF[0].BidVolume2,
            data.IF[0].AskPrice2,
            data.IF[0].AskVolume2,
            data.IF[0].BidPrice3,
            data.IF[0].BidVolume3,
            data.IF[0].AskPrice3,
            data.IF[0].AskVolume3,
            data.IF[0].BidPrice4,
            data.IF[0].BidVolume4,
            data.IF[0].AskPrice4,
            data.IF[0].AskVolume4,
            data.IF[0].BidPrice5,
            data.IF[0].BidVolume5,
            data.IF[0].AskPrice5,
            data.IF[0].AskVolume5,
            data.IF[1].RevDataLocalTime,
            data.IF[1].Tick,
            data.IF[1].SectionFirstTick,
            data.IF[1].SectionLastTick,
            data.IF[1].TotalTick,
            data.IF[1].ErrorID,
            data.IF[1].Ticker,
            data.IF[1].UpdateTime,
            data.IF[1].MillSec,
            data.IF[1].LastPrice,
            data.IF[1].Volume,
            data.IF[1].Turnover,
            data.IF[1].OpenInterest,
            data.IF[1].OpenPrice,
            data.IF[1].HighestPrice,
            data.IF[1].LowestPrice,
            data.IF[1].UpperLimitPrice,
            data.IF[1].LowerLimitPrice,
            data.IF[1].BidPrice1,
            data.IF[1].BidVolume1,
            data.IF[1].AskPrice1,
            data.IF[1].AskVolume1,
            data.IF[1].BidPrice2,
            data.IF[1].BidVolume2,
            data.IF[1].AskPrice2,
            data.IF[1].AskVolume2,
            data.IF[1].BidPrice3,
            data.IF[1].BidVolume3,
            data.IF[1].AskPrice3,
            data.IF[1].AskVolume3,
            data.IF[1].BidPrice4,
            data.IF[1].BidVolume4,
            data.IF[1].AskPrice4,
            data.IF[1].AskVolume4,
            data.IF[1].BidPrice5,
            data.IF[1].BidVolume5,
            data.IF[1].AskPrice5,
            data.IF[1].AskVolume5,
            data.IF[2].RevDataLocalTime,
            data.IF[2].Tick,
            data.IF[2].SectionFirstTick,
            data.IF[2].SectionLastTick,
            data.IF[2].TotalTick,
            data.IF[2].ErrorID,
            data.IF[2].Ticker,
            data.IF[2].UpdateTime,
            data.IF[2].MillSec,
            data.IF[2].LastPrice,
            data.IF[2].Volume,
            data.IF[2].Turnover,
            data.IF[2].OpenInterest,
            data.IF[2].OpenPrice,
            data.IF[2].HighestPrice,
            data.IF[2].LowestPrice,
            data.IF[2].UpperLimitPrice,
            data.IF[2].LowerLimitPrice,
            data.IF[2].BidPrice1,
            data.IF[2].BidVolume1,
            data.IF[2].AskPrice1,
            data.IF[2].AskVolume1,
            data.IF[2].BidPrice2,
            data.IF[2].BidVolume2,
            data.IF[2].AskPrice2,
            data.IF[2].AskVolume2,
            data.IF[2].BidPrice3,
            data.IF[2].BidVolume3,
            data.IF[2].AskPrice3,
            data.IF[2].AskVolume3,
            data.IF[2].BidPrice4,
            data.IF[2].BidVolume4,
            data.IF[2].AskPrice4,
            data.IF[2].AskVolume4,
            data.IF[2].BidPrice5,
            data.IF[2].BidVolume5,
            data.IF[2].AskPrice5,
            data.IF[2].AskVolume5,
            data.IF[3].RevDataLocalTime,
            data.IF[3].Tick,
            data.IF[3].SectionFirstTick,
            data.IF[3].SectionLastTick,
            data.IF[3].TotalTick,
            data.IF[3].ErrorID,
            data.IF[3].Ticker,
            data.IF[3].UpdateTime,
            data.IF[3].MillSec,
            data.IF[3].LastPrice,
            data.IF[3].Volume,
            data.IF[3].Turnover,
            data.IF[3].OpenInterest,
            data.IF[3].OpenPrice,
            data.IF[3].HighestPrice,
            data.IF[3].LowestPrice,
            data.IF[3].UpperLimitPrice,
            data.IF[3].LowerLimitPrice,
            data.IF[3].BidPrice1,
            data.IF[3].BidVolume1,
            data.IF[3].AskPrice1,
            data.IF[3].AskVolume1,
            data.IF[3].BidPrice2,
            data.IF[3].BidVolume2,
            data.IF[3].AskPrice2,
            data.IF[3].AskVolume2,
            data.IF[3].BidPrice3,
            data.IF[3].BidVolume3,
            data.IF[3].AskPrice3,
            data.IF[3].AskVolume3,
            data.IF[3].BidPrice4,
            data.IF[3].BidVolume4,
            data.IF[3].AskPrice4,
            data.IF[3].AskVolume4,
            data.IF[3].BidPrice5,
            data.IF[3].BidVolume5,
            data.IF[3].AskPrice5,
            data.IF[3].AskVolume5,
            data.IH[0].RevDataLocalTime,
            data.IH[0].Tick,
            data.IH[0].SectionFirstTick,
            data.IH[0].SectionLastTick,
            data.IH[0].TotalTick,
            data.IH[0].ErrorID,
            data.IH[0].Ticker,
            data.IH[0].UpdateTime,
            data.IH[0].MillSec,
            data.IH[0].LastPrice,
            data.IH[0].Volume,
            data.IH[0].Turnover,
            data.IH[0].OpenInterest,
            data.IH[0].OpenPrice,
            data.IH[0].HighestPrice,
            data.IH[0].LowestPrice,
            data.IH[0].UpperLimitPrice,
            data.IH[0].LowerLimitPrice,
            data.IH[0].BidPrice1,
            data.IH[0].BidVolume1,
            data.IH[0].AskPrice1,
            data.IH[0].AskVolume1,
            data.IH[0].BidPrice2,
            data.IH[0].BidVolume2,
            data.IH[0].AskPrice2,
            data.IH[0].AskVolume2,
            data.IH[0].BidPrice3,
            data.IH[0].BidVolume3,
            data.IH[0].AskPrice3,
            data.IH[0].AskVolume3,
            data.IH[0].BidPrice4,
            data.IH[0].BidVolume4,
            data.IH[0].AskPrice4,
            data.IH[0].AskVolume4,
            data.IH[0].BidPrice5,
            data.IH[0].BidVolume5,
            data.IH[0].AskPrice5,
            data.IH[0].AskVolume5,
            data.IH[1].RevDataLocalTime,
            data.IH[1].Tick,
            data.IH[1].SectionFirstTick,
            data.IH[1].SectionLastTick,
            data.IH[1].TotalTick,
            data.IH[1].ErrorID,
            data.IH[1].Ticker,
            data.IH[1].UpdateTime,
            data.IH[1].MillSec,
            data.IH[1].LastPrice,
            data.IH[1].Volume,
            data.IH[1].Turnover,
            data.IH[1].OpenInterest,
            data.IH[1].OpenPrice,
            data.IH[1].HighestPrice,
            data.IH[1].LowestPrice,
            data.IH[1].UpperLimitPrice,
            data.IH[1].LowerLimitPrice,
            data.IH[1].BidPrice1,
            data.IH[1].BidVolume1,
            data.IH[1].AskPrice1,
            data.IH[1].AskVolume1,
            data.IH[1].BidPrice2,
            data.IH[1].BidVolume2,
            data.IH[1].AskPrice2,
            data.IH[1].AskVolume2,
            data.IH[1].BidPrice3,
            data.IH[1].BidVolume3,
            data.IH[1].AskPrice3,
            data.IH[1].AskVolume3,
            data.IH[1].BidPrice4,
            data.IH[1].BidVolume4,
            data.IH[1].AskPrice4,
            data.IH[1].AskVolume4,
            data.IH[1].BidPrice5,
            data.IH[1].BidVolume5,
            data.IH[1].AskPrice5,
            data.IH[1].AskVolume5,
            data.IH[2].RevDataLocalTime,
            data.IH[2].Tick,
            data.IH[2].SectionFirstTick,
            data.IH[2].SectionLastTick,
            data.IH[2].TotalTick,
            data.IH[2].ErrorID,
            data.IH[2].Ticker,
            data.IH[2].UpdateTime,
            data.IH[2].MillSec,
            data.IH[2].LastPrice,
            data.IH[2].Volume,
            data.IH[2].Turnover,
            data.IH[2].OpenInterest,
            data.IH[2].OpenPrice,
            data.IH[2].HighestPrice,
            data.IH[2].LowestPrice,
            data.IH[2].UpperLimitPrice,
            data.IH[2].LowerLimitPrice,
            data.IH[2].BidPrice1,
            data.IH[2].BidVolume1,
            data.IH[2].AskPrice1,
            data.IH[2].AskVolume1,
            data.IH[2].BidPrice2,
            data.IH[2].BidVolume2,
            data.IH[2].AskPrice2,
            data.IH[2].AskVolume2,
            data.IH[2].BidPrice3,
            data.IH[2].BidVolume3,
            data.IH[2].AskPrice3,
            data.IH[2].AskVolume3,
            data.IH[2].BidPrice4,
            data.IH[2].BidVolume4,
            data.IH[2].AskPrice4,
            data.IH[2].AskVolume4,
            data.IH[2].BidPrice5,
            data.IH[2].BidVolume5,
            data.IH[2].AskPrice5,
            data.IH[2].AskVolume5,
            data.IH[3].RevDataLocalTime,
            data.IH[3].Tick,
            data.IH[3].SectionFirstTick,
            data.IH[3].SectionLastTick,
            data.IH[3].TotalTick,
            data.IH[3].ErrorID,
            data.IH[3].Ticker,
            data.IH[3].UpdateTime,
            data.IH[3].MillSec,
            data.IH[3].LastPrice,
            data.IH[3].Volume,
            data.IH[3].Turnover,
            data.IH[3].OpenInterest,
            data.IH[3].OpenPrice,
            data.IH[3].HighestPrice,
            data.IH[3].LowestPrice,
            data.IH[3].UpperLimitPrice,
            data.IH[3].LowerLimitPrice,
            data.IH[3].BidPrice1,
            data.IH[3].BidVolume1,
            data.IH[3].AskPrice1,
            data.IH[3].AskVolume1,
            data.IH[3].BidPrice2,
            data.IH[3].BidVolume2,
            data.IH[3].AskPrice2,
            data.IH[3].AskVolume2,
            data.IH[3].BidPrice3,
            data.IH[3].BidVolume3,
            data.IH[3].AskPrice3,
            data.IH[3].AskVolume3,
            data.IH[3].BidPrice4,
            data.IH[3].BidVolume4,
            data.IH[3].AskPrice4,
            data.IH[3].AskVolume4,
            data.IH[3].BidPrice5,
            data.IH[3].BidVolume5,
            data.IH[3].AskPrice5,
            data.IH[3].AskVolume5);
    }

    void FormatMarketDataHeader(const std::string& delimiter, std::string& out)
    {
        std::string field =
            "Tick" + delimiter +
            "TickUpdateTime" + delimiter +
            "IC_IndexFuturesData_0_RevDataLocalTime" + delimiter +
            "IC_IndexFuturesData_0_Tick" + delimiter +
            "IC_IndexFuturesData_0_SectionFirstTick" + delimiter +
            "IC_IndexFuturesData_0_SectionLastTick" + delimiter +
            "IC_IndexFuturesData_0_TotalTick" + delimiter +
            "IC_IndexFuturesData_0_ErrorID" + delimiter +
            "IC_IndexFuturesData_0_Ticker" + delimiter +
            "IC_IndexFuturesData_0_UpdateTime" + delimiter +
            "IC_IndexFuturesData_0_MillSec" + delimiter +
            "IC_IndexFuturesData_0_LastPrice" + delimiter +
            "IC_IndexFuturesData_0_Volume" + delimiter +
            "IC_IndexFuturesData_0_Turnover" + delimiter +
            "IC_IndexFuturesData_0_OpenInterest" + delimiter +
            "IC_IndexFuturesData_0_OpenPrice" + delimiter +
            "IC_IndexFuturesData_0_HighestPrice" + delimiter +
            "IC_IndexFuturesData_0_LowestPrice" + delimiter +
            "IC_IndexFuturesData_0_UpperLimitPrice" + delimiter +
            "IC_IndexFuturesData_0_LowerLimitPrice" + delimiter +
            "IC_IndexFuturesData_0_BidPrice1" + delimiter +
            "IC_IndexFuturesData_0_BidVolume1" + delimiter +
            "IC_IndexFuturesData_0_AskPrice1" + delimiter +
            "IC_IndexFuturesData_0_AskVolume1" + delimiter +
            "IC_IndexFuturesData_0_BidPrice2" + delimiter +
            "IC_IndexFuturesData_0_BidVolume2" + delimiter +
            "IC_IndexFuturesData_0_AskPrice2" + delimiter +
            "IC_IndexFuturesData_0_AskVolume2" + delimiter +
            "IC_IndexFuturesData_0_BidPrice3" + delimiter +
            "IC_IndexFuturesData_0_BidVolume3" + delimiter +
            "IC_IndexFuturesData_0_AskPrice3" + delimiter +
            "IC_IndexFuturesData_0_AskVolume3" + delimiter +
            "IC_IndexFuturesData_0_BidPrice4" + delimiter +
            "IC_IndexFuturesData_0_BidVolume4" + delimiter +
            "IC_IndexFuturesData_0_AskPrice4" + delimiter +
            "IC_IndexFuturesData_0_AskVolume4" + delimiter +
            "IC_IndexFuturesData_0_BidPrice5" + delimiter +
            "IC_IndexFuturesData_0_BidVolume5" + delimiter +
            "IC_IndexFuturesData_0_AskPrice5" + delimiter +
            "IC_IndexFuturesData_0_AskVolume5" + delimiter +
            "IC_IndexFuturesData_1_RevDataLocalTime" + delimiter +
            "IC_IndexFuturesData_1_Tick" + delimiter +
            "IC_IndexFuturesData_1_SectionFirstTick" + delimiter +
            "IC_IndexFuturesData_1_SectionLastTick" + delimiter +
            "IC_IndexFuturesData_1_TotalTick" + delimiter +
            "IC_IndexFuturesData_1_ErrorID" + delimiter +
            "IC_IndexFuturesData_1_Ticker" + delimiter +
            "IC_IndexFuturesData_1_UpdateTime" + delimiter +
            "IC_IndexFuturesData_1_MillSec" + delimiter +
            "IC_IndexFuturesData_1_LastPrice" + delimiter +
            "IC_IndexFuturesData_1_Volume" + delimiter +
            "IC_IndexFuturesData_1_Turnover" + delimiter +
            "IC_IndexFuturesData_1_OpenInterest" + delimiter +
            "IC_IndexFuturesData_1_OpenPrice" + delimiter +
            "IC_IndexFuturesData_1_HighestPrice" + delimiter +
            "IC_IndexFuturesData_1_LowestPrice" + delimiter +
            "IC_IndexFuturesData_1_UpperLimitPrice" + delimiter +
            "IC_IndexFuturesData_1_LowerLimitPrice" + delimiter +
            "IC_IndexFuturesData_1_BidPrice1" + delimiter +
            "IC_IndexFuturesData_1_BidVolume1" + delimiter +
            "IC_IndexFuturesData_1_AskPrice1" + delimiter +
            "IC_IndexFuturesData_1_AskVolume1" + delimiter +
            "IC_IndexFuturesData_1_BidPrice2" + delimiter +
            "IC_IndexFuturesData_1_BidVolume2" + delimiter +
            "IC_IndexFuturesData_1_AskPrice2" + delimiter +
            "IC_IndexFuturesData_1_AskVolume2" + delimiter +
            "IC_IndexFuturesData_1_BidPrice3" + delimiter +
            "IC_IndexFuturesData_1_BidVolume3" + delimiter +
            "IC_IndexFuturesData_1_AskPrice3" + delimiter +
            "IC_IndexFuturesData_1_AskVolume3" + delimiter +
            "IC_IndexFuturesData_1_BidPrice4" + delimiter +
            "IC_IndexFuturesData_1_BidVolume4" + delimiter +
            "IC_IndexFuturesData_1_AskPrice4" + delimiter +
            "IC_IndexFuturesData_1_AskVolume4" + delimiter +
            "IC_IndexFuturesData_1_BidPrice5" + delimiter +
            "IC_IndexFuturesData_1_BidVolume5" + delimiter +
            "IC_IndexFuturesData_1_AskPrice5" + delimiter +
            "IC_IndexFuturesData_1_AskVolume5" + delimiter +
            "IC_IndexFuturesData_2_RevDataLocalTime" + delimiter +
            "IC_IndexFuturesData_2_Tick" + delimiter +
            "IC_IndexFuturesData_2_SectionFirstTick" + delimiter +
            "IC_IndexFuturesData_2_SectionLastTick" + delimiter +
            "IC_IndexFuturesData_2_TotalTick" + delimiter +
            "IC_IndexFuturesData_2_ErrorID" + delimiter +
            "IC_IndexFuturesData_2_Ticker" + delimiter +
            "IC_IndexFuturesData_2_UpdateTime" + delimiter +
            "IC_IndexFuturesData_2_MillSec" + delimiter +
            "IC_IndexFuturesData_2_LastPrice" + delimiter +
            "IC_IndexFuturesData_2_Volume" + delimiter +
            "IC_IndexFuturesData_2_Turnover" + delimiter +
            "IC_IndexFuturesData_2_OpenInterest" + delimiter +
            "IC_IndexFuturesData_2_OpenPrice" + delimiter +
            "IC_IndexFuturesData_2_HighestPrice" + delimiter +
            "IC_IndexFuturesData_2_LowestPrice" + delimiter +
            "IC_IndexFuturesData_2_UpperLimitPrice" + delimiter +
            "IC_IndexFuturesData_2_LowerLimitPrice" + delimiter +
            "IC_IndexFuturesData_2_BidPrice1" + delimiter +
            "IC_IndexFuturesData_2_BidVolume1" + delimiter +
            "IC_IndexFuturesData_2_AskPrice1" + delimiter +
            "IC_IndexFuturesData_2_AskVolume1" + delimiter +
            "IC_IndexFuturesData_2_BidPrice2" + delimiter +
            "IC_IndexFuturesData_2_BidVolume2" + delimiter +
            "IC_IndexFuturesData_2_AskPrice2" + delimiter +
            "IC_IndexFuturesData_2_AskVolume2" + delimiter +
            "IC_IndexFuturesData_2_BidPrice3" + delimiter +
            "IC_IndexFuturesData_2_BidVolume3" + delimiter +
            "IC_IndexFuturesData_2_AskPrice3" + delimiter +
            "IC_IndexFuturesData_2_AskVolume3" + delimiter +
            "IC_IndexFuturesData_2_BidPrice4" + delimiter +
            "IC_IndexFuturesData_2_BidVolume4" + delimiter +
            "IC_IndexFuturesData_2_AskPrice4" + delimiter +
            "IC_IndexFuturesData_2_AskVolume4" + delimiter +
            "IC_IndexFuturesData_2_BidPrice5" + delimiter +
            "IC_IndexFuturesData_2_BidVolume5" + delimiter +
            "IC_IndexFuturesData_2_AskPrice5" + delimiter +
            "IC_IndexFuturesData_2_AskVolume5" + delimiter +
            "IC_IndexFuturesData_3_RevDataLocalTime" + delimiter +
            "IC_IndexFuturesData_3_Tick" + delimiter +
            "IC_IndexFuturesData_3_SectionFirstTick" + delimiter +
            "IC_IndexFuturesData_3_SectionLastTick" + delimiter +
            "IC_IndexFuturesData_3_TotalTick" + delimiter +
            "IC_IndexFuturesData_3_ErrorID" + delimiter +
            "IC_IndexFuturesData_3_Ticker" + delimiter +
            "IC_IndexFuturesData_3_UpdateTime" + delimiter +
            "IC_IndexFuturesData_3_MillSec" + delimiter +
            "IC_IndexFuturesData_3_LastPrice" + delimiter +
            "IC_IndexFuturesData_3_Volume" + delimiter +
            "IC_IndexFuturesData_3_Turnover" + delimiter +
            "IC_IndexFuturesData_3_OpenInterest" + delimiter +
            "IC_IndexFuturesData_3_OpenPrice" + delimiter +
            "IC_IndexFuturesData_3_HighestPrice" + delimiter +
            "IC_IndexFuturesData_3_LowestPrice" + delimiter +
            "IC_IndexFuturesData_3_UpperLimitPrice" + delimiter +
            "IC_IndexFuturesData_3_LowerLimitPrice" + delimiter +
            "IC_IndexFuturesData_3_BidPrice1" + delimiter +
            "IC_IndexFuturesData_3_BidVolume1" + delimiter +
            "IC_IndexFuturesData_3_AskPrice1" + delimiter +
            "IC_IndexFuturesData_3_AskVolume1" + delimiter +
            "IC_IndexFuturesData_3_BidPrice2" + delimiter +
            "IC_IndexFuturesData_3_BidVolume2" + delimiter +
            "IC_IndexFuturesData_3_AskPrice2" + delimiter +
            "IC_IndexFuturesData_3_AskVolume2" + delimiter +
            "IC_IndexFuturesData_3_BidPrice3" + delimiter +
            "IC_IndexFuturesData_3_BidVolume3" + delimiter +
            "IC_IndexFuturesData_3_AskPrice3" + delimiter +
            "IC_IndexFuturesData_3_AskVolume3" + delimiter +
            "IC_IndexFuturesData_3_BidPrice4" + delimiter +
            "IC_IndexFuturesData_3_BidVolume4" + delimiter +
            "IC_IndexFuturesData_3_AskPrice4" + delimiter +
            "IC_IndexFuturesData_3_AskVolume4" + delimiter +
            "IC_IndexFuturesData_3_BidPrice5" + delimiter +
            "IC_IndexFuturesData_3_BidVolume5" + delimiter +
            "IC_IndexFuturesData_3_AskPrice5" + delimiter +
            "IC_IndexFuturesData_3_AskVolume5" + delimiter +
            "IF_IndexFuturesData_0_RevDataLocalTime" + delimiter +
            "IF_IndexFuturesData_0_Tick" + delimiter +
            "IF_IndexFuturesData_0_SectionFirstTick" + delimiter +
            "IF_IndexFuturesData_0_SectionLastTick" + delimiter +
            "IF_IndexFuturesData_0_TotalTick" + delimiter +
            "IF_IndexFuturesData_0_ErrorID" + delimiter +
            "IF_IndexFuturesData_0_Ticker" + delimiter +
            "IF_IndexFuturesData_0_UpdateTime" + delimiter +
            "IF_IndexFuturesData_0_MillSec" + delimiter +
            "IF_IndexFuturesData_0_LastPrice" + delimiter +
            "IF_IndexFuturesData_0_Volume" + delimiter +
            "IF_IndexFuturesData_0_Turnover" + delimiter +
            "IF_IndexFuturesData_0_OpenInterest" + delimiter +
            "IF_IndexFuturesData_0_OpenPrice" + delimiter +
            "IF_IndexFuturesData_0_HighestPrice" + delimiter +
            "IF_IndexFuturesData_0_LowestPrice" + delimiter +
            "IF_IndexFuturesData_0_UpperLimitPrice" + delimiter +
            "IF_IndexFuturesData_0_LowerLimitPrice" + delimiter +
            "IF_IndexFuturesData_0_BidPrice1" + delimiter +
            "IF_IndexFuturesData_0_BidVolume1" + delimiter +
            "IF_IndexFuturesData_0_AskPrice1" + delimiter +
            "IF_IndexFuturesData_0_AskVolume1" + delimiter +
            "IF_IndexFuturesData_0_BidPrice2" + delimiter +
            "IF_IndexFuturesData_0_BidVolume2" + delimiter +
            "IF_IndexFuturesData_0_AskPrice2" + delimiter +
            "IF_IndexFuturesData_0_AskVolume2" + delimiter +
            "IF_IndexFuturesData_0_BidPrice3" + delimiter +
            "IF_IndexFuturesData_0_BidVolume3" + delimiter +
            "IF_IndexFuturesData_0_AskPrice3" + delimiter +
            "IF_IndexFuturesData_0_AskVolume3" + delimiter +
            "IF_IndexFuturesData_0_BidPrice4" + delimiter +
            "IF_IndexFuturesData_0_BidVolume4" + delimiter +
            "IF_IndexFuturesData_0_AskPrice4" + delimiter +
            "IF_IndexFuturesData_0_AskVolume4" + delimiter +
            "IF_IndexFuturesData_0_BidPrice5" + delimiter +
            "IF_IndexFuturesData_0_BidVolume5" + delimiter +
            "IF_IndexFuturesData_0_AskPrice5" + delimiter +
            "IF_IndexFuturesData_0_AskVolume5" + delimiter +
            "IF_IndexFuturesData_1_RevDataLocalTime" + delimiter +
            "IF_IndexFuturesData_1_Tick" + delimiter +
            "IF_IndexFuturesData_1_SectionFirstTick" + delimiter +
            "IF_IndexFuturesData_1_SectionLastTick" + delimiter +
            "IF_IndexFuturesData_1_TotalTick" + delimiter +
            "IF_IndexFuturesData_1_ErrorID" + delimiter +
            "IF_IndexFuturesData_1_Ticker" + delimiter +
            "IF_IndexFuturesData_1_UpdateTime" + delimiter +
            "IF_IndexFuturesData_1_MillSec" + delimiter +
            "IF_IndexFuturesData_1_LastPrice" + delimiter +
            "IF_IndexFuturesData_1_Volume" + delimiter +
            "IF_IndexFuturesData_1_Turnover" + delimiter +
            "IF_IndexFuturesData_1_OpenInterest" + delimiter +
            "IF_IndexFuturesData_1_OpenPrice" + delimiter +
            "IF_IndexFuturesData_1_HighestPrice" + delimiter +
            "IF_IndexFuturesData_1_LowestPrice" + delimiter +
            "IF_IndexFuturesData_1_UpperLimitPrice" + delimiter +
            "IF_IndexFuturesData_1_LowerLimitPrice" + delimiter +
            "IF_IndexFuturesData_1_BidPrice1" + delimiter +
            "IF_IndexFuturesData_1_BidVolume1" + delimiter +
            "IF_IndexFuturesData_1_AskPrice1" + delimiter +
            "IF_IndexFuturesData_1_AskVolume1" + delimiter +
            "IF_IndexFuturesData_1_BidPrice2" + delimiter +
            "IF_IndexFuturesData_1_BidVolume2" + delimiter +
            "IF_IndexFuturesData_1_AskPrice2" + delimiter +
            "IF_IndexFuturesData_1_AskVolume2" + delimiter +
            "IF_IndexFuturesData_1_BidPrice3" + delimiter +
            "IF_IndexFuturesData_1_BidVolume3" + delimiter +
            "IF_IndexFuturesData_1_AskPrice3" + delimiter +
            "IF_IndexFuturesData_1_AskVolume3" + delimiter +
            "IF_IndexFuturesData_1_BidPrice4" + delimiter +
            "IF_IndexFuturesData_1_BidVolume4" + delimiter +
            "IF_IndexFuturesData_1_AskPrice4" + delimiter +
            "IF_IndexFuturesData_1_AskVolume4" + delimiter +
            "IF_IndexFuturesData_1_BidPrice5" + delimiter +
            "IF_IndexFuturesData_1_BidVolume5" + delimiter +
            "IF_IndexFuturesData_1_AskPrice5" + delimiter +
            "IF_IndexFuturesData_1_AskVolume5" + delimiter +
            "IF_IndexFuturesData_2_RevDataLocalTime" + delimiter +
            "IF_IndexFuturesData_2_Tick" + delimiter +
            "IF_IndexFuturesData_2_SectionFirstTick" + delimiter +
            "IF_IndexFuturesData_2_SectionLastTick" + delimiter +
            "IF_IndexFuturesData_2_TotalTick" + delimiter +
            "IF_IndexFuturesData_2_ErrorID" + delimiter +
            "IF_IndexFuturesData_2_Ticker" + delimiter +
            "IF_IndexFuturesData_2_UpdateTime" + delimiter +
            "IF_IndexFuturesData_2_MillSec" + delimiter +
            "IF_IndexFuturesData_2_LastPrice" + delimiter +
            "IF_IndexFuturesData_2_Volume" + delimiter +
            "IF_IndexFuturesData_2_Turnover" + delimiter +
            "IF_IndexFuturesData_2_OpenInterest" + delimiter +
            "IF_IndexFuturesData_2_OpenPrice" + delimiter +
            "IF_IndexFuturesData_2_HighestPrice" + delimiter +
            "IF_IndexFuturesData_2_LowestPrice" + delimiter +
            "IF_IndexFuturesData_2_UpperLimitPrice" + delimiter +
            "IF_IndexFuturesData_2_LowerLimitPrice" + delimiter +
            "IF_IndexFuturesData_2_BidPrice1" + delimiter +
            "IF_IndexFuturesData_2_BidVolume1" + delimiter +
            "IF_IndexFuturesData_2_AskPrice1" + delimiter +
            "IF_IndexFuturesData_2_AskVolume1" + delimiter +
            "IF_IndexFuturesData_2_BidPrice2" + delimiter +
            "IF_IndexFuturesData_2_BidVolume2" + delimiter +
            "IF_IndexFuturesData_2_AskPrice2" + delimiter +
            "IF_IndexFuturesData_2_AskVolume2" + delimiter +
            "IF_IndexFuturesData_2_BidPrice3" + delimiter +
            "IF_IndexFuturesData_2_BidVolume3" + delimiter +
            "IF_IndexFuturesData_2_AskPrice3" + delimiter +
            "IF_IndexFuturesData_2_AskVolume3" + delimiter +
            "IF_IndexFuturesData_2_BidPrice4" + delimiter +
            "IF_IndexFuturesData_2_BidVolume4" + delimiter +
            "IF_IndexFuturesData_2_AskPrice4" + delimiter +
            "IF_IndexFuturesData_2_AskVolume4" + delimiter +
            "IF_IndexFuturesData_2_BidPrice5" + delimiter +
            "IF_IndexFuturesData_2_BidVolume5" + delimiter +
            "IF_IndexFuturesData_2_AskPrice5" + delimiter +
            "IF_IndexFuturesData_2_AskVolume5" + delimiter +
            "IF_IndexFuturesData_3_RevDataLocalTime" + delimiter +
            "IF_IndexFuturesData_3_Tick" + delimiter +
            "IF_IndexFuturesData_3_SectionFirstTick" + delimiter +
            "IF_IndexFuturesData_3_SectionLastTick" + delimiter +
            "IF_IndexFuturesData_3_TotalTick" + delimiter +
            "IF_IndexFuturesData_3_ErrorID" + delimiter +
            "IF_IndexFuturesData_3_Ticker" + delimiter +
            "IF_IndexFuturesData_3_UpdateTime" + delimiter +
            "IF_IndexFuturesData_3_MillSec" + delimiter +
            "IF_IndexFuturesData_3_LastPrice" + delimiter +
            "IF_IndexFuturesData_3_Volume" + delimiter +
            "IF_IndexFuturesData_3_Turnover" + delimiter +
            "IF_IndexFuturesData_3_OpenInterest" + delimiter +
            "IF_IndexFuturesData_3_OpenPrice" + delimiter +
            "IF_IndexFuturesData_3_HighestPrice" + delimiter +
            "IF_IndexFuturesData_3_LowestPrice" + delimiter +
            "IF_IndexFuturesData_3_UpperLimitPrice" + delimiter +
            "IF_IndexFuturesData_3_LowerLimitPrice" + delimiter +
            "IF_IndexFuturesData_3_BidPrice1" + delimiter +
            "IF_IndexFuturesData_3_BidVolume1" + delimiter +
            "IF_IndexFuturesData_3_AskPrice1" + delimiter +
            "IF_IndexFuturesData_3_AskVolume1" + delimiter +
            "IF_IndexFuturesData_3_BidPrice2" + delimiter +
            "IF_IndexFuturesData_3_BidVolume2" + delimiter +
            "IF_IndexFuturesData_3_AskPrice2" + delimiter +
            "IF_IndexFuturesData_3_AskVolume2" + delimiter +
            "IF_IndexFuturesData_3_BidPrice3" + delimiter +
            "IF_IndexFuturesData_3_BidVolume3" + delimiter +
            "IF_IndexFuturesData_3_AskPrice3" + delimiter +
            "IF_IndexFuturesData_3_AskVolume3" + delimiter +
            "IF_IndexFuturesData_3_BidPrice4" + delimiter +
            "IF_IndexFuturesData_3_BidVolume4" + delimiter +
            "IF_IndexFuturesData_3_AskPrice4" + delimiter +
            "IF_IndexFuturesData_3_AskVolume4" + delimiter +
            "IF_IndexFuturesData_3_BidPrice5" + delimiter +
            "IF_IndexFuturesData_3_BidVolume5" + delimiter +
            "IF_IndexFuturesData_3_AskPrice5" + delimiter +
            "IF_IndexFuturesData_3_AskVolume5" + delimiter +
            "IH_IndexFuturesData_0_RevDataLocalTime" + delimiter +
            "IH_IndexFuturesData_0_Tick" + delimiter +
            "IH_IndexFuturesData_0_SectionFirstTick" + delimiter +
            "IH_IndexFuturesData_0_SectionLastTick" + delimiter +
            "IH_IndexFuturesData_0_TotalTick" + delimiter +
            "IH_IndexFuturesData_0_ErrorID" + delimiter +
            "IH_IndexFuturesData_0_Ticker" + delimiter +
            "IH_IndexFuturesData_0_UpdateTime" + delimiter +
            "IH_IndexFuturesData_0_MillSec" + delimiter +
            "IH_IndexFuturesData_0_LastPrice" + delimiter +
            "IH_IndexFuturesData_0_Volume" + delimiter +
            "IH_IndexFuturesData_0_Turnover" + delimiter +
            "IH_IndexFuturesData_0_OpenInterest" + delimiter +
            "IH_IndexFuturesData_0_OpenPrice" + delimiter +
            "IH_IndexFuturesData_0_HighestPrice" + delimiter +
            "IH_IndexFuturesData_0_LowestPrice" + delimiter +
            "IH_IndexFuturesData_0_UpperLimitPrice" + delimiter +
            "IH_IndexFuturesData_0_LowerLimitPrice" + delimiter +
            "IH_IndexFuturesData_0_BidPrice1" + delimiter +
            "IH_IndexFuturesData_0_BidVolume1" + delimiter +
            "IH_IndexFuturesData_0_AskPrice1" + delimiter +
            "IH_IndexFuturesData_0_AskVolume1" + delimiter +
            "IH_IndexFuturesData_0_BidPrice2" + delimiter +
            "IH_IndexFuturesData_0_BidVolume2" + delimiter +
            "IH_IndexFuturesData_0_AskPrice2" + delimiter +
            "IH_IndexFuturesData_0_AskVolume2" + delimiter +
            "IH_IndexFuturesData_0_BidPrice3" + delimiter +
            "IH_IndexFuturesData_0_BidVolume3" + delimiter +
            "IH_IndexFuturesData_0_AskPrice3" + delimiter +
            "IH_IndexFuturesData_0_AskVolume3" + delimiter +
            "IH_IndexFuturesData_0_BidPrice4" + delimiter +
            "IH_IndexFuturesData_0_BidVolume4" + delimiter +
            "IH_IndexFuturesData_0_AskPrice4" + delimiter +
            "IH_IndexFuturesData_0_AskVolume4" + delimiter +
            "IH_IndexFuturesData_0_BidPrice5" + delimiter +
            "IH_IndexFuturesData_0_BidVolume5" + delimiter +
            "IH_IndexFuturesData_0_AskPrice5" + delimiter +
            "IH_IndexFuturesData_0_AskVolume5" + delimiter +
            "IH_IndexFuturesData_1_RevDataLocalTime" + delimiter +
            "IH_IndexFuturesData_1_Tick" + delimiter +
            "IH_IndexFuturesData_1_SectionFirstTick" + delimiter +
            "IH_IndexFuturesData_1_SectionLastTick" + delimiter +
            "IH_IndexFuturesData_1_TotalTick" + delimiter +
            "IH_IndexFuturesData_1_ErrorID" + delimiter +
            "IH_IndexFuturesData_1_Ticker" + delimiter +
            "IH_IndexFuturesData_1_UpdateTime" + delimiter +
            "IH_IndexFuturesData_1_MillSec" + delimiter +
            "IH_IndexFuturesData_1_LastPrice" + delimiter +
            "IH_IndexFuturesData_1_Volume" + delimiter +
            "IH_IndexFuturesData_1_Turnover" + delimiter +
            "IH_IndexFuturesData_1_OpenInterest" + delimiter +
            "IH_IndexFuturesData_1_OpenPrice" + delimiter +
            "IH_IndexFuturesData_1_HighestPrice" + delimiter +
            "IH_IndexFuturesData_1_LowestPrice" + delimiter +
            "IH_IndexFuturesData_1_UpperLimitPrice" + delimiter +
            "IH_IndexFuturesData_1_LowerLimitPrice" + delimiter +
            "IH_IndexFuturesData_1_BidPrice1" + delimiter +
            "IH_IndexFuturesData_1_BidVolume1" + delimiter +
            "IH_IndexFuturesData_1_AskPrice1" + delimiter +
            "IH_IndexFuturesData_1_AskVolume1" + delimiter +
            "IH_IndexFuturesData_1_BidPrice2" + delimiter +
            "IH_IndexFuturesData_1_BidVolume2" + delimiter +
            "IH_IndexFuturesData_1_AskPrice2" + delimiter +
            "IH_IndexFuturesData_1_AskVolume2" + delimiter +
            "IH_IndexFuturesData_1_BidPrice3" + delimiter +
            "IH_IndexFuturesData_1_BidVolume3" + delimiter +
            "IH_IndexFuturesData_1_AskPrice3" + delimiter +
            "IH_IndexFuturesData_1_AskVolume3" + delimiter +
            "IH_IndexFuturesData_1_BidPrice4" + delimiter +
            "IH_IndexFuturesData_1_BidVolume4" + delimiter +
            "IH_IndexFuturesData_1_AskPrice4" + delimiter +
            "IH_IndexFuturesData_1_AskVolume4" + delimiter +
            "IH_IndexFuturesData_1_BidPrice5" + delimiter +
            "IH_IndexFuturesData_1_BidVolume5" + delimiter +
            "IH_IndexFuturesData_1_AskPrice5" + delimiter +
            "IH_IndexFuturesData_1_AskVolume5" + delimiter +
            "IH_IndexFuturesData_2_RevDataLocalTime" + delimiter +
            "IH_IndexFuturesData_2_Tick" + delimiter +
            "IH_IndexFuturesData_2_SectionFirstTick" + delimiter +
            "IH_IndexFuturesData_2_SectionLastTick" + delimiter +
            "IH_IndexFuturesData_2_TotalTick" + delimiter +
            "IH_IndexFuturesData_2_ErrorID" + delimiter +
            "IH_IndexFuturesData_2_Ticker" + delimiter +
            "IH_IndexFuturesData_2_UpdateTime" + delimiter +
            "IH_IndexFuturesData_2_MillSec" + delimiter +
            "IH_IndexFuturesData_2_LastPrice" + delimiter +
            "IH_IndexFuturesData_2_Volume" + delimiter +
            "IH_IndexFuturesData_2_Turnover" + delimiter +
            "IH_IndexFuturesData_2_OpenInterest" + delimiter +
            "IH_IndexFuturesData_2_OpenPrice" + delimiter +
            "IH_IndexFuturesData_2_HighestPrice" + delimiter +
            "IH_IndexFuturesData_2_LowestPrice" + delimiter +
            "IH_IndexFuturesData_2_UpperLimitPrice" + delimiter +
            "IH_IndexFuturesData_2_LowerLimitPrice" + delimiter +
            "IH_IndexFuturesData_2_BidPrice1" + delimiter +
            "IH_IndexFuturesData_2_BidVolume1" + delimiter +
            "IH_IndexFuturesData_2_AskPrice1" + delimiter +
            "IH_IndexFuturesData_2_AskVolume1" + delimiter +
            "IH_IndexFuturesData_2_BidPrice2" + delimiter +
            "IH_IndexFuturesData_2_BidVolume2" + delimiter +
            "IH_IndexFuturesData_2_AskPrice2" + delimiter +
            "IH_IndexFuturesData_2_AskVolume2" + delimiter +
            "IH_IndexFuturesData_2_BidPrice3" + delimiter +
            "IH_IndexFuturesData_2_BidVolume3" + delimiter +
            "IH_IndexFuturesData_2_AskPrice3" + delimiter +
            "IH_IndexFuturesData_2_AskVolume3" + delimiter +
            "IH_IndexFuturesData_2_BidPrice4" + delimiter +
            "IH_IndexFuturesData_2_BidVolume4" + delimiter +
            "IH_IndexFuturesData_2_AskPrice4" + delimiter +
            "IH_IndexFuturesData_2_AskVolume4" + delimiter +
            "IH_IndexFuturesData_2_BidPrice5" + delimiter +
            "IH_IndexFuturesData_2_BidVolume5" + delimiter +
            "IH_IndexFuturesData_2_AskPrice5" + delimiter +
            "IH_IndexFuturesData_2_AskVolume5" + delimiter +
            "IH_IndexFuturesData_3_RevDataLocalTime" + delimiter +
            "IH_IndexFuturesData_3_Tick" + delimiter +
            "IH_IndexFuturesData_3_SectionFirstTick" + delimiter +
            "IH_IndexFuturesData_3_SectionLastTick" + delimiter +
            "IH_IndexFuturesData_3_TotalTick" + delimiter +
            "IH_IndexFuturesData_3_ErrorID" + delimiter +
            "IH_IndexFuturesData_3_Ticker" + delimiter +
            "IH_IndexFuturesData_3_UpdateTime" + delimiter +
            "IH_IndexFuturesData_3_MillSec" + delimiter +
            "IH_IndexFuturesData_3_LastPrice" + delimiter +
            "IH_IndexFuturesData_3_Volume" + delimiter +
            "IH_IndexFuturesData_3_Turnover" + delimiter +
            "IH_IndexFuturesData_3_OpenInterest" + delimiter +
            "IH_IndexFuturesData_3_OpenPrice" + delimiter +
            "IH_IndexFuturesData_3_HighestPrice" + delimiter +
            "IH_IndexFuturesData_3_LowestPrice" + delimiter +
            "IH_IndexFuturesData_3_UpperLimitPrice" + delimiter +
            "IH_IndexFuturesData_3_LowerLimitPrice" + delimiter +
            "IH_IndexFuturesData_3_BidPrice1" + delimiter +
            "IH_IndexFuturesData_3_BidVolume1" + delimiter +
            "IH_IndexFuturesData_3_AskPrice1" + delimiter +
            "IH_IndexFuturesData_3_AskVolume1" + delimiter +
            "IH_IndexFuturesData_3_BidPrice2" + delimiter +
            "IH_IndexFuturesData_3_BidVolume2" + delimiter +
            "IH_IndexFuturesData_3_AskPrice2" + delimiter +
            "IH_IndexFuturesData_3_AskVolume2" + delimiter +
            "IH_IndexFuturesData_3_BidPrice3" + delimiter +
            "IH_IndexFuturesData_3_BidVolume3" + delimiter +
            "IH_IndexFuturesData_3_AskPrice3" + delimiter +
            "IH_IndexFuturesData_3_AskVolume3" + delimiter +
            "IH_IndexFuturesData_3_BidPrice4" + delimiter +
            "IH_IndexFuturesData_3_BidVolume4" + delimiter +
            "IH_IndexFuturesData_3_AskPrice4" + delimiter +
            "IH_IndexFuturesData_3_AskVolume4" + delimiter +
            "IH_IndexFuturesData_3_BidPrice5" + delimiter +
            "IH_IndexFuturesData_3_BidVolume5" + delimiter +
            "IH_IndexFuturesData_3_AskPrice5" + delimiter +
            "IH_IndexFuturesData_3_AskVolume5";
        out = field;
    }

    void Init()
    {
        std::string data_log_path;
        std::string log_name;
        char* p = getenv("DATA_LOG_PATH");
        if(p != NULL)
        {
            data_log_path = p;
            log_name = data_log_path + "/market_data.csv";
        }
        else
        {
            log_name = "./market_data.csv";
        }
        spdlog::init_thread_pool(1024 * 10, 2);
        auto tmp_sink = std::make_shared<spdlog::sinks::daily_file_sink_st>(log_name, 18, 30);
        tmp_sink->set_pattern("%v");
        m_MarketDataLogger = std::make_shared<spdlog::async_logger>("global", tmp_sink, spdlog::thread_pool(), spdlog::async_overflow_policy::overrun_oldest);
        spdlog::register_logger(m_MarketDataLogger);
        std::string marketHeader;
        FormatMarketDataHeader(",", marketHeader);
        m_MarketDataLogger->info(marketHeader);
    }

private:
    MarketDataLogger() {}
    MarketDataLogger &operator=(const MarketDataLogger &);
    MarketDataLogger(const MarketDataLogger &);

private:
    std::shared_ptr<spdlog::logger> m_MarketDataLogger;
};

}

#endif // MARKETDATALOGGER_H
