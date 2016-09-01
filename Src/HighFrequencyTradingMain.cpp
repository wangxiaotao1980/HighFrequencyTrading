/*******************************************************************************************
 *  @file      HighFrequencyTradingMain.cpp 2016\8\29 19:28:35 $
 *  @author    Wang Xiaotao<wangxt@hiscene.com> (中文编码测试)
 *******************************************************************************************/

#include "ImportFunction.hpp"
#include "HighFrequencyTradingConfig.hpp"
#include "Log/Log.h"

#include "boost/thread/thread.hpp"
#include "boost/bind.hpp"



// ------------------------------------------------------------------------------------------
//

HighFrequencyTradingConfig g_highFrequencyTradingConfig;
JL_Login      g_pJLLogin      = NULL;
JL_SendOrder  g_pJLSendOrder  = NULL;


void runHighFrequencyTrading(const int tradingInfoesNum, const int n)
{
    int num = g_highFrequencyTradingConfig.tradingInfoes[tradingInfoesNum].requestNum;

    for (int i = 0; i < num; ++i)
    {
        boost::chrono::time_point<boost::chrono::high_resolution_clock> timeBegin
            = boost::chrono::high_resolution_clock::now();
        char* result = g_pJLSendOrder
            (
                              g_highFrequencyTradingConfig.tradingInfoes[tradingInfoesNum].fx,
            const_cast<char*>(g_highFrequencyTradingConfig.login.user.c_str()),
            const_cast<char*>(g_highFrequencyTradingConfig.tradingInfoes[tradingInfoesNum].gddm.c_str()),
            const_cast<char*>(g_highFrequencyTradingConfig.tradingInfoes[tradingInfoesNum].gpdm.c_str()),
                              g_highFrequencyTradingConfig.tradingInfoes[tradingInfoesNum].quantity,
                              g_highFrequencyTradingConfig.tradingInfoes[tradingInfoesNum].price
            );
        boost::chrono::time_point<boost::chrono::high_resolution_clock> timeEnd
            = boost::chrono::high_resolution_clock::now();

        HIS_LOG_INFO(
            "tradingInfoesNum:" << tradingInfoesNum <<
            "|threadNum:" << n <<
            "|count:" << i <<
            "|time:" << boost::chrono::duration_cast<boost::chrono::milliseconds>(timeEnd - timeBegin).count() <<
            "|result:" << result);

    }
}



int main(int argc, char* argv[])
{

    // 初始化日志系统
    int result = initialLog(argv[0], std::string("./"), std::string("log.conf"));
    if (0 != result)
    {
        std::cout << "initial log fail" << std::endl;
        terminalLog();
        return 1;
    }


    HINSTANCE hdll = ::LoadLibrary(L"JLAPI.dll");

    if (NULL == hdll)
    {
        HIS_LOG_FATAL("load library JLAPI.dll error!");
        ::FreeLibrary(hdll);
        terminalLog();
        return 1;
    }

    g_pJLLogin     = (JL_Login)::GetProcAddress(hdll, "JL_Login");
    g_pJLSendOrder  = (JL_SendOrder)::GetProcAddress(hdll, "JL_SendOrder");

    if (g_pJLLogin == NULL)
    {

        HIS_LOG_FATAL("get proc JL_Login address error");
        FreeLibrary(hdll);
        terminalLog();
        return 1;
    }


    if (g_pJLSendOrder == NULL)
    {
        HIS_LOG_FATAL("get proc JL_SendOrder address error");
        FreeLibrary(hdll);
        terminalLog();
        return 1;
    }

    bool issuccessed = parseHighFrequencyTradingConfig("./conf/HighFrequencyTrading.conf", g_highFrequencyTradingConfig);

    if (false == issuccessed)
    {
        HIS_LOG_FATAL("parseHighFrequencyTradingConfig error!");
        return 1;
    }

    
    int res = g_pJLLogin
                    (
                        const_cast<char*>(g_highFrequencyTradingConfig.login.ip.c_str()),
                        g_highFrequencyTradingConfig.login.port,
                        const_cast<char*>(g_highFrequencyTradingConfig.login.user.c_str()),
                        const_cast<char*>(g_highFrequencyTradingConfig.login.password.c_str()),
                        const_cast<char*>(g_highFrequencyTradingConfig.login.txPass.c_str()),
                        const_cast<char*>(g_highFrequencyTradingConfig.login.yyb.c_str())
                    );

    if (res == 0)
    {
        std::cout << "LogIn failed" << std::endl;
        HIS_LOG_FATAL("LogIn failed");
        FreeLibrary(hdll);
        terminalLog();
    }

    boost::thread_group group;
    
    for (int i = 0; i < g_highFrequencyTradingConfig.tradingInfoes.size(); ++i)
    {
        for (int j = 0; j < g_highFrequencyTradingConfig.tradingInfoes[i].threadNum; ++j)
        {
            group.create_thread(boost::bind(&runHighFrequencyTrading, i, j));
        }
    }

    group.join_all();
    
    FreeLibrary(hdll);
    terminalLog();

    std::cout << "run over" << std::endl;
    return 0;
}




// 
// ------------------------------------------------------------------------------------------
