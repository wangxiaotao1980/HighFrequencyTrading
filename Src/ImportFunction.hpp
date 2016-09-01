/*******************************************************************************************
 *  @file      ImportFunction.hpp 2016\8\29 19:28:47 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 *  @note      summary
 *******************************************************************************************/
#ifndef IMPORTFUNCTION_960D792A_C1AD_4B82_AD16_E1479A25AC0F_HPP__
#define IMPORTFUNCTION_960D792A_C1AD_4B82_AD16_E1479A25AC0F_HPP__

/*******************************************************************************************/

#include <Windows.h>


typedef char(WINAPI *JL_Login)
(
    char* pIp,               // ip 
    int   Port,              // 端口
    char* pUser,             // 账户
    char* pPassWord,         // 密码
    char* pTxPassworld,      // 通讯密码（如果没有就为空）
    char* pYyb               // 营业部号
);

typedef char* (WINAPI *JL_SendOrder)
(
    int    fx,                 // 交易方向（0为买入，1为卖出），
    char*  pUser,              // 账户
    char*  pGddm,              // 股东代码
    char*  pGpdm,              // 股票代码
    int    Quantity,           // 股票数量
    float  Price               // 价格
);


/*******************************************************************************************/
#endif// IMPORTFUNCTION_960D792A_C1AD_4B82_AD16_E1479A25AC0F_HPP__