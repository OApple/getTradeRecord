#ifndef NIUTRADER_H
#define NIUTRADER_H
#include <list>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/timer.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>
#include <ThostFtdcTraderApi.h>
#include "property.h"
#include "dataprocessor.h"
#include "traderspi.h"
using namespace std;
using namespace boost::gregorian;
class NiuTraderSpi:public CThostFtdcTraderSpi
{
public:
    NiuTraderSpi();
    NiuTraderSpi(DataInitInstance&di,string  investorID,string passWord);

    NiuTraderSpi( DataInitInstance&di,  bool loginOK,CThostFtdcTraderApi* pUserApi);

    bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);

    virtual void OnFrontConnected();

    ///登录请求响应
    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询结算信息确认响应
    virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询投资者结算结果响应
    virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

    ///投资者结算结果确认响应
    virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    //    ///请求查询合约响应
    //    virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询资金账户响应
    virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询投资者持仓响应
    virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///报单通知
    virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

    ///成交通知
    virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

    void startApi();
    //    int ReqOrderInsert(UserOrderField* userOrderField);

    CThostFtdcTraderSpi* pUserSpi ;

    CThostFtdcTraderApi* _pUserApi;
    string getPassword() const;
    void setPassword(const string &value);

    string getInvestorID() const;
    void setInvestorID(const string &investorID);

    vector<CTraderSpi *> & getFollow();
    void setFollow(const vector<CTraderSpi *> &follow);

    int total_trade_num() const;
    void setTotal_trade_num(int total_trade_num);

    int profit_num() const;
    void setProfit_num(int profit_num);

    int close_num() const;
    void setClose_num(int close_num);

    double profit() const;
    void setProfit(double profit);

    double loss() const;
    void setLoss(double loss);

    int loss_num() const;
    void setLoss_num(int loss_num);

    double total_income() const;
    void setTotal_income(double total_income);

    int trade_days_num() const;
    void setTrade_days_num(int trade_days_num);

    double max_single_income() const;
    void setMax_single_income(double max_single_income);

    double total_commission() const;
    void setTotal_commission(double total_commission);

protected:


private:
    string _trade_front_addr;
    int _requestID=1;
    bool _all_follow_ok=false;
    bool _positon_req_send=false;
    bool _loginOK;
    vector<CTraderSpi *> _follow;

    string _brokerID;
    string  _investorID="";
    string _password="";
    string _user_id;

    int _frontID;
    int _sessionID;
    int _orderRef;
    string _settlemsg;
    DataInitInstance &dii;
    SQLite::Database *sqlite_handle;
    int _total_trade_num;
    int _trade_days_num;

    int _profit_num;
    int _close_num;

    double _profit;
    double _loss;

    double _total_income;
    double _max_single_income;
    double _total_commission;

    int _loss_num;

    date _begin;
    date _end;
    //     day_iterator d_iter;
    ///用户登录请求
    void ReqUserLogin();

    ///请求查询结算信息确认
    int ReqQrySettlementInfoConfirm();

    ///投资者结算结果确认
    void ReqQrySettlementInfo();

    void ReqSettlementInfoConfirm();

    void ReqQryTradingAccount();

    void ReqQryInvestorPosition();

    bool IsMyOrder(CThostFtdcOrderField *pOrder);
    void SaveTransactionRecord();
    HoldPositionInfo* initpst(CThostFtdcInvestorPositionField *pInvestorPosition);
};

#endif // NIUTRADER_H
