/*******************************************************************************************
 *  @file      ImportFunction.hpp 2016\8\29 19:28:47 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (���ı������)
 *  @note      summary
 *******************************************************************************************/
#ifndef IMPORTFUNCTION_960D792A_C1AD_4B82_AD16_E1479A25AC0F_HPP__
#define IMPORTFUNCTION_960D792A_C1AD_4B82_AD16_E1479A25AC0F_HPP__

/*******************************************************************************************/

#include <Windows.h>


typedef char(WINAPI *JL_Login)
(
    char* pIp,               // ip 
    int   Port,              // �˿�
    char* pUser,             // �˻�
    char* pPassWord,         // ����
    char* pTxPassworld,      // ͨѶ���루���û�о�Ϊ�գ�
    char* pYyb               // Ӫҵ����
);

typedef char* (WINAPI *JL_SendOrder)
(
    int    fx,                 // ���׷���0Ϊ���룬1Ϊ��������
    char*  pUser,              // �˻�
    char*  pGddm,              // �ɶ�����
    char*  pGpdm,              // ��Ʊ����
    int    Quantity,           // ��Ʊ����
    float  Price               // �۸�
);


/*******************************************************************************************/
#endif// IMPORTFUNCTION_960D792A_C1AD_4B82_AD16_E1479A25AC0F_HPP__