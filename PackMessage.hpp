#ifndef PACKMESSAGE_HPP
#define PACKMESSAGE_HPP
#include <string>
#include "MarketData.hpp"

namespace Message
{

#define PLUGIN_MARKET           "Market"
#define PLUGIN_ORDERMANAGER     "OrderManager"
#define PLUGIN_EVENTLOG         "EventLog"
#define PLUGIN_MONITOR          "Monitor"
#define PLUGIN_RISKJUDGE        "RiskJudge"
#define PLUGIN_PERMISSION       "Permission"

#define PLUGIN_LIST             "Market|OrderManager|EventLog|Monitor|RiskJudge|Permission"

struct TTest
{
   char Account[16];
   char Content[256]; 
};

enum ELoginStatus
{
    ELOGIN_PREPARED = 1, // 尚未登录
    ELOGIN_CONNECTED = 2, // 已连接正在登录
    ELOGIN_SUCCESSED = 3, // 登录成功
    ELOGIN_FAILED = 4, // 登录失败，或者已经断开连接
};

enum EClientType
{
    ETrader = 1,
    EMonitor = 2,
    EMarket = 3,
    ERisk = 4,
    EWatcher = 5, 
    EQuant = 6
};

struct TLoginRequest
{
    uint8_t ClientType;
    char Colo[16];
    char Account[16];
    char PassWord[16];
    char Operation[16];
    char Role[16];
    char Plugins[400];
    char UUID[32];
};

enum EPermissionOperation
{
    EUSER_ADD = 1,
    EUSER_UPDATE = 2,
    EUSER_DELETE = 3
};

struct TLoginResponse
{
    uint8_t ClientType;
    uint8_t Operation;
    char Colo[16];
    char Account[16];
    char PassWord[16];
    char Role[16];
    char Plugins[400];
    char UpdateTime[32];
    int ErrorID;
    char ErrorMsg[64];
};

enum EBusinessType
{
    ESTOCK = 1,
    ECREDIT = 2,
    EFUTURE = 3
};

enum EOrderType
{
    EFAK = 1,
    EFOK = 2,
    ELIMIT = 3,
    EMARKET = 4,
};

enum EOrderDirection
{
    EBUY = 1,
    ESELL = 2
};

enum EOrderOffset
{
    EOPEN = 1,
    ECLOSE = 2,
    ECLOSETODAY = 3,
    ECLOSEYESTODAY = 4
};

enum ERiskStatusType
{
    EPrepareChecked = 1, // 等待检查
    ECheckedPass = 2, // 风控检查通过
    ECheckedNoPass = 3, // 风控检查不通过
    ENoChecked = 4, // 不进行风控检查
    EInitChecked = 5, // 初始化检查
};

enum EEngineType
{
    ETraderOrder = 0XAF01,
};

struct TOrderRequest
{
    char Colo[16];
    char Broker[16];
    char Product[16];
    char Account[16];
    char Ticker[16];
    uint8_t OrderType;
    uint8_t Direction;
    uint8_t Offset;
    uint8_t RiskStatus;
    uint8_t BussinessType;
    int OrderToken;
    int EngineID;
    int UserReserved1;
    int UserReserved2;
    double Price;
    int Volume;
    char RecvMarketTime[32];
    char SendTime[32];
    char UpdateTime[32];
    int ErrorID;
    char ErrorMsg[256];
    char RiskID[16];
};

struct TActionRequest
{
    char Colo[16];
    char Account[16];
    char OrderRef[32];
    int EngineID;
    uint8_t RiskStatus;
    char UpdateTime[32];
    int ErrorID;
    char ErrorMsg[256];
    char RiskID[16];
};

enum EOrderStatus
{
    EOrderSended = 1,
    EBrokerACK = 2,
    EExchangeACK = 3,
    EPartTraded = 4,
    EAllTraded = 5,
    ECancelling = 6,
    ECancelled = 7,
    EPartTradedCancelled = 8,
    EBrokerError = 9,
    EExchangeError = 10,
    EActionError = 11,
    ERiskRejected = 12,
    ERiskCancelRejected = 13,
    ERiskCheckInit = 14,
};

enum EOrderSide
{
    EOPEN_LONG = 1,
    ECLOSE_TD_LONG = 2,
    ECLOSE_YD_LONG = 3,
    EOPEN_SHORT = 4,
    ECLOSE_TD_SHORT = 5,
    ECLOSE_YD_SHORT = 6,
    ECLOSE_LONG = 7,
    ECLOSE_SHORT = 8
};

enum ECommandType
{
    EUpdate_Risk_Limit = 1,
    EUpdate_Risk_Account_Locked = 2,
    EUpdate_UserPermission = 3,
    EKillApp = 4, 
    EStartApp = 5
};

struct TCommand
{
    uint8_t CmdType;
    char Colo[16];
    char Account[16];
    char Command[512];
};

enum EEventLogLevel
{
    EInfo = 1,
    EWarning = 2,
    EError = 3
};

struct TEventLog
{
    char Colo[16];
    char Broker[16];
    char Product[16];
    char Account[16];
    char Ticker[16];
    char App[32];
    char Event[400];
    int Level;
    char UpdateTime[32];
};

struct TOrderStatus
{
    char Colo[16];
    char Broker[16];
    char Product[16];
    char Account[16];
    char Ticker[16];
    char ExchangeID[16];
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
    uint8_t BussinessType;
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
    char UpdateTime[32];
    int ErrorID;
    char ErrorMsg[256];
    char RiskID[16];
};

struct TAccountFund
{
    char Colo[16];
    char Broker[16];
    char Product[16];
    char Account[16];
    uint8_t BussinessType;
    double Deposit; // 入金
    double Withdraw; // 出金
    double CurrMargin; // 当前保证金
    double Commission; // 手续费
    double CloseProfit; // 平仓盈亏
    double PositionProfit; // 持仓盈亏
    double Available; // 可用资金
    double WithdrawQuota; // 
    double ExchangeMargin; // 交易所保证金
    double Balance; // 
    double PreBalance; // 
    char UpdateTime[32]; 
};

struct TFuturePosition
{
    int LongTdVolume;
    int LongYdVolume;
    int LongOpenVolume;
    int LongOpeningVolume;
    int LongClosingTdVolume;
    int LongClosingYdVolume;
    int ShortTdVolume;
    int ShortYdVolume;
    int ShortOpenVolume;
    int ShortOpeningVolume;
    int ShortClosingTdVolume;
    int ShortClosingYdVolume;
};

struct TStockPosition
{
    int LongYdPosition; // 现货昨仓
    int LongPosition; // 现货持仓
    int LongTdBuy; // 现货今日买入量
    int LongTdSell; // 现货今日卖出量
    int LongTdSell4RePay; // 卖券还款数量
    int ShortYdPosition; // 融券昨仓
    int ShortPosition; // 融券持仓
    int TdBuy4RePay; // 买券还券数量
    int TdDirectRepay; // 现券还券数量
    int MarginPosition; // 融券头寸
    int reserved;
};

struct TAccountPosition
{
    char Colo[16];
    char Broker[16];
    char Product[16];
    char Account[16];
    char Ticker[16];
    uint8_t BussinessType;
    char ExchangeID[16];
    union
    {
        TFuturePosition FuturePosition;
        TStockPosition StockPosition;
    };
    char UpdateTime[32];
};

enum ERiskRejectedType
{
    EFlowLimited = 1,
    ESelfMatched = 2,
    EAccountLocked = 3,
    EOpenLongLocked = 4,
    EOpenShortLocked = 5,
    ECloseLongYdLocked = 6,
    ECloseLongTdLocked = 7,
    ECloseShortYdLocked = 8,
    ECloseShortTdLocked = 9,
    ETickerCancelLimited = 10,
    EOrderCancelLimited = 11,
    EInvalidPrice = 12
};

enum ERiskLockedSide
{
    EUNLOCK = 0,
    ELOCK_BUY = 1,
    ELOCK_SELL = 1 << 1,
    ELOCK_ACCOUNT = ELOCK_BUY | ELOCK_SELL,
};

enum ERiskReportType
{
    ERiskLimit = ECommandType::EUpdate_Risk_Limit,
    ERiskAccountLocked = ECommandType::EUpdate_Risk_Account_Locked,
    ERiskTickerCancelled,
    ERiskEventLog,
};

struct TRiskReport
{
    // common
    uint8_t ReportType;
    char Colo[16];
    char Broker[16];
    char Product[16];
    char Account[16];
    char Ticker[16];
    char RiskID[16];
    uint8_t BussinessType;
    //  RiskLimitTable
    int FlowLimit;
    int TickerCancelLimit;
    int OrderCancelLimit;
    // LockedAccountTable
    int LockedSide;
    // CancelledCountTable
    int CancelledCount;
    int UpperLimit;
    // common
    char Event[400];
    char Trader[32];
    char UpdateTime[32];
};

struct TLoadAverage
{
    double Min1;
    double Min5;
    double Min15;
    int CPUS;
};

struct TCPUUsage
{
    double UserRate; // %user
    double SysRate; // %system
    double IdleRate; // %idle
    double IOWaitRate; // %iowait
    double IrqRate; // %irq
    double SoftIrqRate; // %softirq
    double UsedRate;// %CPU
};

struct TMemoryInfo
{
    double Total;
    double Free;
    double UsedRate;
};

struct TDiskInfo
{
    double Total;
    double Free;
    double UsedRate;
    double Mount1UsedRate;// 根目录挂载点使用率
    double Mount2UsedRate;// Home挂载点使用率
};

struct TColoStatus
{
    char Colo[16];
    char OSVersion[32];// 操作系统版本
    char KernelVersion[32];// 内核版本
    TLoadAverage LoadAverage;
    TCPUUsage CPUUsage;
    TMemoryInfo MemoryInfo;
    TDiskInfo DiskInfo;
    char UpdateTime[32];
};

struct TAppStatus
{
    char Colo[16];
    char Account[16];
    char AppName[32];
    int PID;
    char Status[16];
    double UsedCPURate;
    double UsedMemSize;
    char StartTime[32];
    char LastStartTime[32];
    char CommitID[16];
    char UtilsCommitID[16];
    char APIVersion[32];
    char StartScript[400];
    char UpdateTime[32];
};

enum EMessageType
{
    ETest = 0XFF00,
    ELoginRequest = 0XFF01,
    ELoginResponse = 0XFF02,
    ECommand = 0XFF03,
    EEventLog = 0XFF04,
    EOrderStatus = 0XFF05,
    EAccountFund = 0XFF06,
    EAccountPosition = 0XFF07,
    EOrderRequest = 0XFF08,
    EActionRequest = 0XFF09,
    ERiskReport = 0XFF0A,
    EColoStatus = 0XFF0B,
    EAppStatus = 0XFF0C,
    EFutureMarketData = 0XFFB1,
    EStockMarketData = 0XFFB2,
};

struct PackMessage
{
    unsigned int MessageType;
    union
    {
        TTest Test;                                     // 0XFF00
        TLoginRequest LoginRequest;                     // 0XFF01
        TLoginResponse LoginResponse;                   // 0XFF02
        TCommand Command;                               // 0XFF03
        TEventLog EventLog;                             // 0XFF04
        TOrderStatus OrderStatus;                       // 0XFF05
        TAccountFund AccountFund;                       // 0XFF06
        TAccountPosition AccountPosition;               // 0XFF07
        TOrderRequest OrderRequest;                     // 0XFF08
        TActionRequest ActionRequest;                   // 0XFF09
        TRiskReport RiskReport;                         // 0XFF0A
        TColoStatus ColoStatus;                         // 0XFF0B
        TAppStatus AppStatus;                           // 0XFF0C
        MarketData::StockIndexMarketDataSet FutureMarketData; // 0XFFB1
        MarketData::StockIndexMarketDataSet StockMarketData;  // 0XFFB2
    };
};

}

#endif // PACKMESSAGE_HPP