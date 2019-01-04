#include <iostream>
#include <memory>
#include <glog/logging.h>

#include "dataprocessor.h"
#include "timeprocesser.h"
#include "mysqlconnectpool.h"
#include "traderspi.h"
#include "niutraderspi.h"
#include "property.h"
#include "chkthread.h"

using boost::lexical_cast;
using boost::locale::conv::between;

using boost::algorithm::trim_copy;
using namespace std;
DataInitInstance dii;

// UserApi对象
// 请求编号
//int iRequestID;
boost::thread_group thread_log_group;

//unordered_map<string, CThostFtdcTraderApi*>CTraderSpi:: _tradeApiMap;
//unordered_map<string,  CTraderSpi*>CTraderSpi:: _tradeSpiMap;
int main(int argc, char**argv)
{
    google::InitGoogleLogging(argv[0]);
    //    google::InitGoogleLogging("");
    system("mkdir -p log");
    google::SetLogDestination(google::GLOG_INFO, "./log/info_");
    google::SetLogDestination(google::GLOG_WARNING, "./log/warn_");
    google::SetLogDestination(google::GLOG_ERROR, "./log/error_");
    //google::SetStderrLogging(2);
    //    google::SetLogFilenameExtension("log_");
    dii.GetConfigFromFile();
     dii.DataInit();
    dii.GetConfigFromRedis();
    dii.initTradeApi();

    while(1){
        sleep(2);
    }
    google::ShutdownGoogleLogging();
    return 0;
}
