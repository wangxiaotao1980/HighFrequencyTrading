/*******************************************************************************************
 *  @file      HighFrequencyTradingConfig.cpp 2016\8\29 20:04:05 $
 *  @author    Wang Xiaotao<wangxt@hiscene.com> (÷–Œƒ±‡¬Î≤‚ ‘)
 *******************************************************************************************/

#include "HighFrequencyTradingConfig.hpp"

#include "Log/Log.h"

#include "boost/foreach.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

// ------------------------------------------------------------------------------------------
// 
bool parseHighFrequencyTradingConfig(const char* thePath, HighFrequencyTradingConfig& conf)
{
    boost::property_tree::ptree pt;
    try
    {
        std::string theFullPath(thePath);
        boost::property_tree::json_parser::read_json(theFullPath, pt);

        conf.login.ip           =  pt.get<std::string>("logIn.ip");
        conf.login.port         =  pt.get<int>("logIn.port");
        conf.login.user         =  pt.get<std::string>("logIn.user");
        conf.login.password     =  pt.get<std::string>("logIn.password");
        conf.login.txPass       =  pt.get<std::string>("logIn.txPass");
        conf.login.yyb          =  pt.get<std::string>("logIn.yyb");
        conf.login.timeInterval =  pt.get<int>("logIn.timeInterval");




        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("transactionItems"))
        {
            HighFrequencyTradingInfo tradingInfo;

            tradingInfo.threadNum   = v.second.get<int>("threadNum");
            tradingInfo.requestNum  = v.second.get<int>("requestNum");
            tradingInfo.fx          = v.second.get<int>("fx");
            tradingInfo.gddm        = v.second.get<std::string>("gddm");
            tradingInfo.gpdm        = v.second.get<std::string>("gpdm");
            tradingInfo.quantity    = v.second.get<int>("quantity");
            tradingInfo.price       = v.second.get<float>("price");

            conf.tradingInfoes.push_back(tradingInfo);

        }
    }
    catch (std::runtime_error& e)
    {
        HIS_LOG_ERROR("parse the SearchServerConf error : " << e.what());
        return false;
    }
    catch (...)
    {
        HIS_LOG_ERROR("parse the SearchServerConf error");

        return false;
    }

    return true;
}


//
// ------------------------------------------------------------------------------------------

