/*******************************************************************************************
 *  @file      HighFrequencyTradingConfig.hpp 2016\8\29 19:59:28 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (÷–Œƒ±‡¬Î≤‚ ‘)
 *  @note      summary
 *******************************************************************************************/
#ifndef HIGHFREQUENCYTRADINGCONFIG_E6311F46_7881_4376_9993_DE27C32F53F7_HPP__
#define HIGHFREQUENCYTRADINGCONFIG_E6311F46_7881_4376_9993_DE27C32F53F7_HPP__

/*******************************************************************************************/
#include <string>
/**
 * The class <code>HighFrequencyTradingConfig</code>
 *
 */
struct HighFrequencyTradingConfig
{
    int                         threadNum;
    int                         requestNum;
    std::string                 ip; 
    int                         port;
    std::string                 user;
    std::string                 password;
    std::string                 txPass;
    std::string                 yyb;
    int                         fx;
    std::string                 gddm;
    std::string                 gpdm;
    int                         quantity;
    float                       price;
};                              

bool parseHighFrequencyTradingConfig(const char* thePath, HighFrequencyTradingConfig& conf);


/*******************************************************************************************/
#endif// HIGHFREQUENCYTRADINGCONFIG_E6311F46_7881_4376_9993_DE27C32F53F7_HPP__