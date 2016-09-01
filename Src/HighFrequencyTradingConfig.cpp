/*******************************************************************************************
 *  @file      HighFrequencyTradingConfig.cpp 2016\8\29 20:04:05 $
 *  @author    Wang Xiaotao<wangxt@hiscene.com> (÷–Œƒ±‡¬Î≤‚ ‘)
 *******************************************************************************************/

#include "HighFrequencyTradingConfig.hpp"

#include "Log/Log.h"

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
        conf.threadNum   = pt.get<int>("threadNum");
        conf.requestNum  = pt.get<int>("requestNum");
        conf.ip          = pt.get<std::string>("ip");
        conf.port        = pt.get<int>("port");
        conf.user        = pt.get<std::string>("user");
        conf.password    = pt.get<std::string>("password");
        conf.txPass      = pt.get<std::string>("txPass");
        conf.fx          = pt.get<int>("fx");
        conf.yyb         = pt.get<std::string>("yyb");
        conf.gddm        = pt.get<std::string>("gddm");
        conf.gpdm        = pt.get<std::string>("gpdm");
        conf.quantity    = pt.get<int>("quantity");
        conf.price       = pt.get<float>("price");

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

