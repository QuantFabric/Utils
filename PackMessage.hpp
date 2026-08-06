#ifndef PACKMESSAGE_HPP
#define PACKMESSAGE_HPP
#include <string>
#include "MarketData.hpp"

namespace Message
{

#define MESSAGE_FUTUREMARKET           "FutureMarket"
#define MESSAGE_STOCKMARKET            "StockMarket"
#define MESSAGE_SPOTMARKET             "SpotMarket"
#define MESSAGE_ORDERSTATUS            "OrderStatus"
#define MESSAGE_ACCOUNTFUND            "AccountFund"
#define MESSAGE_ACCOUNTPOSITION        "AccountPosition"
#define MESSAGE_EVENTLOG               "EventLog"
#define MESSAGE_COLOSTATUS             "ColoStatus"
#define MESSAGE_APPSTATUS              "AppStatus"
#define MESSAGE_RISKREPORT             "RiskReport"
#define MESSAGE_LIST                   "FutureMarket|StockMarket|SpotMarket|OrderStatus|AccountFund|AccountPosition|EventLog|ColoStatus|AppStatus|RiskReport"

#define PLUGIN_MARKET            "Market"
#define PLUGIN_ORDERMANAGER      "OrderManager"
#define PLUGIN_EVENTLOG          "EventLog"
#define PLUGIN_MONITOR           "Monitor"
#define PLUGIN_RISKJUDGE         "RiskJudge"
#define PLUGIN_FUTUREANALYSIS    "FutureAnalysis"
#define PLUGIN_STOCKANALYSIS     "StockAnalysis"
#define PLUGIN_PERMISSION        "Permission"

#define PLUGIN_LIST             "Market|OrderManager|EventLog|Monitor|RiskJudge|FutureAnalysis|StockAnalysis|Permission"

struct TTest
{
   char Account[16];
   char Content[800]; 
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
    EXTRADER = 1,
    EXMONITOR = 2,
    EXMARKETCENTER = 3,
    EXRISKJUDGE = 4,
    EXWATCHER = 5, 
    EXQUANT = 6,
    EHFTRADER = 7,
    EXDATAPLAYER = 8,
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
    char Messages[400];
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
    char Messages[400];
    char UpdateTime[32];
    int ErrorID;
    char ErrorMsg[64];
};

enum EExchange
{
    ESHSE = 01,
    ESZSE = 02,
    EBJSE = 03,
    ECFFEX = 11,
    EDCE = 12,
    ECZCE = 13,
    ESHFE = 14,
};

enum EBusinessType
{
    ESTOCK = 1,
    ECREDIT = 2,
    EFUTURE = 3,
    ESPOT = 4,
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
    ESELL = 2,
    EREVERSE_REPO = 3, // 国债逆回购申购
    ESUBSCRIPTION = 4, // 新股、新债申购
    EALLOTMENT = 5, // 配股配债认购
    ECOLLATERAL_TRANSFER_IN = 6, // 担保品转入
    ECOLLATERAL_TRANSFER_OUT = 7, // 担保品转出
    EMARGIN_BUY = 8, // 融资买入
    EREPAY_MARGIN_BY_SELL = 9, // 卖券还款
    ESHORT_SELL = 10, // 融券卖出
    EREPAY_STOCK_BY_BUY = 11, // 买券还券
    EREPAY_STOCK_DIRECT = 12, // 现券还券
};

enum EOrderOffset
{
    EOPEN = 1,
    ECLOSE = 2,
    ECLOSE_TODAY = 3,
    ECLOSE_YESTODAY = 4,
};

enum ERiskStatusType
{
    EPREPARE_CHECKED = 0, // 等待检查
    ECHECKED_PASS = 1, // 风控检查通过
    ECHECKED_NOPASS = 2, // 风控检查不通过
    ENOCHECKED = 3, // 不进行风控检查
    ECHECK_INIT = 4, // 初始化检查
};

enum EEngineType
{
    ETRADER_ORDER = 1,
};

enum StrategyEngine
{
    ELATENCYTEST = 0XFF00,
    EPORTFOLIO   = 0XFF01,
};

struct TOrderRequest
{
    char Colo[16];
    char Broker[16];
    char Product[16];
    char Account[16];
    char Ticker[20];
    char ExchangeID[16];
    uint8_t BusinessType;
    uint8_t OrderType;
    uint8_t Direction;
    uint8_t Offset;
    uint8_t RiskStatus;
    int OrderToken;
    int EngineID;
    int UserReserved1;
    int UserReserved2;
    double Price;
    int Volume;
    char RecvMarketTime[32];
    char SendTime[32];
    char RiskID[16];
    char Trader[16];
    int ErrorID;
    char ErrorMsg[256];
    char UpdateTime[32];
};

struct TActionRequest
{
    char Colo[16];
    char Account[16];
    char OrderRef[32];
    char ExchangeID[16];
    uint8_t BusinessType;
    int EngineID;
    uint8_t RiskStatus;
    char Trader[16];
    char RiskID[16];
    int ErrorID;
    char ErrorMsg[256];
    char UpdateTime[32];
};

enum EOrderStatusType
{
    EORDER_SENDED = 1,
    EBROKER_ACK = 2,
    EEXCHANGE_ACK = 3,
    EPARTTRADED = 4,
    EALLTRADED = 5,
    ECANCELLING = 6,
    ECANCELLED = 7,
    EPARTTRADED_CANCELLED = 8,
    EBROKER_ERROR = 9,
    EEXCHANGE_ERROR = 10,
    EACTION_ERROR = 11,
    ERISK_ORDER_REJECTED = 12,
    ERISK_ACTION_REJECTED = 13,
    ERISK_CHECK_INIT = 14,
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
    ECLOSE_SHORT = 8,
    ESIDE_REVERSE_REPO = 9, // 国债逆回购申购
    ESIDE_SUBSCRIPTION = 10, // 新股、新债申购
    ESIDE_ALLOTMENT = 11, // 配股配债认购
    ESIDE_COLLATERAL_BUY = 12, // 担保品买入
    ESIDE_COLLATERAL_SELL = 13, // 担保品卖出
    ESIDE_MARGIN_BUY = 14, // 融资买入
    ESIDE_REPAY_MARGIN_BY_SELL = 15, // 卖券还款
    ESIDE_SHORT_SELL = 16, // 融券卖出
    ESIDE_REPAY_STOCK_BY_BUY = 17, // 买券还券
    ESIDE_REPAY_STOCK_DIRECT = 18, // 现券还券

};

struct TOrderStatus
{
    char Colo[16];
    char Broker[16];
    char Product[16];
    char Account[16];
    char Ticker[20];
    char ExchangeID[16];
    uint8_t BusinessType;
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

struct TFastOrder
{
    char Account[16];
    char Ticker[32];
    char ExchangeID[16];
    uint64_t OrderRef;
    uint64_t OrderSysID;
    uint64_t OrderLocalID;
    uint64_t OrderToken;
    uint32_t EngineID;
    uint8_t OrderType;
    uint8_t Direction;
    uint8_t Offset;
    uint8_t OrderStatus;
    uint32_t RiskStatus;
    double SendPrice;
    uint32_t SendVolume;
    uint32_t TotalTradedVolume;
    uint32_t TradedVolume;
    double TradedAvgPrice;
    double TradedPrice;
    uint32_t CanceledVolume;
    uint64_t RecvMarketTime;
    uint64_t SendTime;
    uint64_t InsertTime;
    uint64_t BrokerACKTime;
    uint64_t ExchangeACKTime;
    uint64_t OrderTradedTime;
    uint64_t UpdateTime;
    uint32_t ErrorID;
    char ErrorMsg[128];
    char SOrderLocalID[32];
    char SOrderSysID[32];
};

struct TAccountFund
{
    char Colo[16];
    char Broker[16];
    char Product[16];
    char Account[16];
    uint8_t BusinessType;
    double Deposit; // 入金
    double Withdraw; // 出金
    double CurrMargin; // 当前保证金
    double Commission; // 手续费
    double CloseProfit; // 平仓盈亏
    double PositionProfit; // 持仓盈亏
    double Available; // 可用资金
    double WithdrawQuota; // 可取资金额度
    double ExchangeMargin; // 交易所保证金
    double Balance; // 总资产
    double PreBalance; // 日初总资产
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
    int LongYdPosition; // 日初可用持仓
    int LongPosition; // 当前总持仓
    int LongTdBuy; // 今日买入量
    int LongTdSell; // 今日卖出量
    int MarginYdPosition; // 日初可用融资负债数量 
    int MarginPosition; // 融资负债数量;
    int MarginTdBuy; // 融资今日买入数量
    int MarginTdSell; // 今日卖券还款数量
    int ShortYdPosition; // 日初融券负债可用数量 
    int ShortPosition; // 融券负债数量
    int ShortTdSell; // 今日融券卖出数量
    int ShortTdBuy; // 今日买券还券数量
    int ShortDirectRepaid; // 直接还券数量
    int SpecialPositionAvl; // 融券专项证券头寸可用数量
};

struct TAccountPosition
{
    char Colo[16];
    char Broker[16];
    char Product[16];
    char Account[16];
    char Ticker[20];
    char ExchangeID[16];
    uint8_t BusinessType;
    union
    {
        TFuturePosition FuturePosition;
        TStockPosition StockPosition;
    };
    char UpdateTime[32];
};

enum ECommandType
{
    EUPDATE_RISK_LIMIT = 1,
    EUPDATE_RISK_POSITION_LIMIT = 2,
    EUPDATE_RISK_ACCOUNT_LOCKED = 3,
    EUPDATE_USERPERMISSION = 4,
    EKILL_APP = 5, 
    ESTART_APP = 6,
    ETRANSFER_FUND_IN = 7,
    ETRANSFER_FUND_OUT = 8,
    EREPAY_MARGIN_DIRECT = 9,
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
    EINFO = 1,
    EWARNING = 2,
    EERROR = 3
};

struct TEventLog
{
    char Colo[16];
    char Broker[16];
    char Product[16];
    char Account[16];
    char Ticker[20];
    char ExchangeID[16];
    char App[32];
    char Event[400];
    int Level;
    char UpdateTime[32];
};

enum ERiskRejectedType
{
    EFLOW_LIMITED = 1,  // 流速限制
    ESELF_MATCHED = 2,  // 防自成交
    ETICKER_ACTION_LIMITED = 3, // Ticker撤单限制
    EORDER_ACTION_LIMITED = 4,  // 订单撤单限制
    EINVALID_PRICE = 5, // 价格无效
    EACCOUNT_NOT_FOUND = 6,  // 账户无效
    ETICKER_NOT_FOUND = 7,  // 合约无效
    EVOLUME_EXCEEDED = 8,   // 订单委托数量超限
    EREQUEST_LIMITED = 9,   // 订单申报次数限制
    EACCOUNT_LOCKED_ALL = 20,   // 禁止账户交易
    EACCOUNT_LOCKED_BUY = 21,   // 禁止账户买入
    EACCOUNT_LOCKED_BUY_OPEN = 22,   // 禁止账户买入开仓
    EACCOUNT_LOCKED_BUY_CLOSE = 23,   // 禁止账户买入平仓
    EACCOUNT_LOCKED_BUY_CLOSE_TODAY = 24,   // 禁止账户买入平今
    EACCOUNT_LOCKED_BUY_CLOSE_YESTODAY = 25,   // 禁止账户买入平今
    EACCOUNT_LOCKED_SELL = 26,   // 禁止账户卖出
    EACCOUNT_LOCKED_SELL_OPEN = 27,   // 禁止账户卖出开仓
    EACCOUNT_LOCKED_SELL_CLOSE = 28,   // 禁止账户卖出平仓
    EACCOUNT_LOCKED_SELL_CLOSE_TODAY = 29,   // 禁止账户卖出平今
    EACCOUNT_LOCKED_SELL_CLOSE_YESTODAY = 30,   // 禁止账户卖出平今
    EACCOUNT_LOCKED_OPEN = 31,   // 禁止账户开仓
    EACCOUNT_LOCKED_CLOSE = 32,   // 禁止账户开仓
    ETICKER_LOCKED_ALL = 40,   // 禁止合约交易
    ETICKER_LOCKED_BUY = 41,   // 禁止合约买入
    ETICKER_LOCKED_BUY_OPEN = 42,   // 禁止合约买入开仓
    ETICKER_LOCKED_BUY_CLOSE = 43,   // 禁止合约买入平仓
    ETICKER_LOCKED_BUY_CLOSE_TODAY = 44,   // 禁止合约买入平今
    ETICKER_LOCKED_BUY_CLOSE_YESTODAY = 45,   // 禁止合约买入平今
    ETICKER_LOCKED_SELL = 46,   // 禁止合约卖出
    ETICKER_LOCKED_SELL_OPEN = 47,   // 禁止合约卖出开仓
    ETICKER_LOCKED_SELL_CLOSE = 48,   // 禁止合约卖出平仓
    ETICKER_LOCKED_SELL_CLOSE_TODAY = 49,   // 禁止合约卖出平今
    ETICKER_LOCKED_SELL_CLOSE_YESTODAY = 50,   // 禁止合约卖出平今
    ETICKER_LOCKED_OPEN = 51,   // 禁止合约开仓
    ETICKER_LOCKED_CLOSE = 52,   // 禁止合约平仓
    ETICKER_LONG_LIMIT = 60,    // 账户多头持仓限制
    ETICKER_SHORT_LIMIT = 61,    // 账户空头持仓限制
    ETICKER_NET_LONG_LIMIT = 62,    // 账户净多头持仓限制
    ETICKER_NET_SHORT_LIMIT = 63,    // 账户净空头持仓限制
    ETICKER_LONG_INSUFFICIENT = 64,   // 账户多头持仓不足
    ETICKER_SHORT_INSUFFICIENT = 65,   // 账户空头持仓不足
    ESTRATEGY_LONG_LIMIT = 70,    // 策略多头持仓限制
    ESTRATEGY_SHORT_LIMIT = 71,    // 策略空头持仓限制
    ESTRATEGY_NET_LONG_LIMIT = 72,    // 策略净多头持仓限制
    ESTRATEGY_NET_SHORT_LIMIT = 73,    // 策略净空头持仓限制
};

enum ERiskReportType
{
    ERISK_LIMIT = 1,
    ERISK_POSITION_LIMIT = 2,
    ERISK_ACCOUNT_LOCKED = 3,
    ERISK_EVENTLOG = 4,
};

enum EAccountLockSide
{
    EUNLOCK = 0,
    ELOCK_ACCOUNT = 1,
    ELOCK_OPEN = 2,
    ELOCK_CLOSE = 3,
    ELOCK_BUY = 11,
    ELOCK_BUY_OPEN = 12,
    ELOCK_BUY_CLOSE = 13,
    ELOCK_BUY_CLOSE_TODAY = 14,
    ELOCK_BUY_CLOSE_YESTODAY = 15,
    ELOCK_SELL = 21,
    ELOCK_SELL_OPEN = 22,
    ELOCK_SELL_CLOSE = 23,
    ELOCK_SELL_CLOSE_TODAY = 24,
    ELOCK_SELL_CLOSE_YESTODAY = 25,
};

struct TRiskReport
{
    // common
    uint8_t ReportType;
    uint8_t BusinessType;
    char Colo[16];
    char Broker[16];
    char Product[16];
    char Account[16];
    char Ticker[20];
    char ExchangeID[16];
    char RiskID[16];
    char Trader[32];
    //  RiskLimitTable
    int FlowLimit;
    int CancelCount;
    int CancelLimit;
    int OrderCount;
    int OrderLimit;
    int OrderCancelLimit;
    // PositionLimitTable
    int EngineID;
    int LongVolume;
    int ShortVolume;
    int LongLimit;
    int ShortLimit;
    int ExposureLowerLimit;
    int ExposureUpperLimit;
    // AccountLockedTable
    int LockSide;
    // common
    char Event[400];
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
    EFastOrder = 0XFF0D,
    EFutureMarketData = 0XFFB1,
    EStockMarketData = 0XFFB2,
    ESpotMarketData = 0XFFB3,
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
        TFastOrder FastOrder;                           // 0XFF0D
        MarketData::TFutureMarketData FutureMarketData; // 0XFFB1
        MarketData::TStockMarketData StockMarketData;   // 0XFFB2
        MarketData::TSpotMarketData SpotMarketData;     // 0XFFB1
    };
    int ChannelID;
    long long TimeStamp;
};

}

#endif // PACKMESSAGE_HPP
