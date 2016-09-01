/*******************************************************************************************
 * This file is HiScene's property. It contains HiScene's trade secret, proprietary and
 * confidential information.
 *
 * The information and code contained in this file is only for authorized HiScene employees
 * to design, create, modify, or review.
 *
 * DO NOT DISTRIBUTE, DO NOT DUPLICATE OR TRANSMIT IN ANY FORM WITHOUT PROPER AUTHORIZATION.
 *
 * If you are not an intended recipient of this file, you must not copy, distribute, modify,
 * or take any action in reliance on it.
 *
 * If you have received this file in error, please immediately notify HiScene and
 * permanently delete the original and any copy of any file and any printout thereof.
 *
 *  @file      Log.h 2015\10\23 15:46:19 $
 *  @author    Wang Xiaotao<wangxt@hiscene.com> (中文编码测试)
 *  @note      summary
 *******************************************************************************************/
#ifndef KEYSERVER_KEYSERVER_LOG_H__
#define KEYSERVER_KEYSERVER_LOG_H__

#include <string>

/*******************************************************************************************/

#ifndef NO_USING_LOG

    //使用 glog 库
    #ifdef USING_GLOG
        #define  GLOG_NO_ABBREVIATED_SEVERITIES
        #include "glog/logging.h"
        #include "glog/raw_logging.h"
        #include "GlogConfig.hpp"
    #endif //USING_GLOG

    //使用log4cplus
    #ifdef USING_LOG4PLUS
    //using log4plus
    #endif //USING_LOG4PLUS


    //使用boost.log
    #ifdef USING_BOOST_LOG
        #include "BoostLogConfig.hpp"
    #endif // USING_BOOST_LOG

#endif // NO_USING_LOG


/*******************************************************************************************/
// 定义此宏后日志系将要失效
#ifndef NO_USING_LOG

    #ifdef USING_GLOG
        #define HIS_LOG_REQUEST( thestream ) \
            LOG(INFO) << thestream


        #define HIS_LOG_RESPONSE( thestream ) \
            LOG(INFO) << thestream

        #define HIS_LOG_INFO( thestream ) \
            LOG(INFO) << thestream

        #define HIS_LOG_WARNING( thestream ) \
            LOG(WARNING) << thestream

        #define HIS_LOG_ERROR( thestream) \
            LOG(ERROR) << thestream

        #define HIS_LOG_FATAL( thestream ) \
            LOG(FATAL) << thestream
    #endif //USING_GLOG


    #ifdef USING_LOG4PLUS
    //using log4plus
    #endif //USING_LOG4PLUS



    #ifdef USING_BOOST_LOG

        #define HIS_LOG_REQUEST( thestream ) \
            BOOST_LOG_SEV(theGlobalLogger::get(), HIS_REQUEST_LEVEL) << thestream


        #define HIS_LOG_RESPONSE( thestream ) \
            BOOST_LOG_SEV(theGlobalLogger::get(), HIS_RESPONSE_LEVEL) << thestream

        #define HIS_LOG_INFO( thestream ) \
            BOOST_LOG_SEV(theGlobalLogger::get(), HIS_INFO_LEVEL) << thestream << \
            "\t" << __FILE__ << "\t" << __LINE__

        #define HIS_LOG_WARNING( thestream ) \
            BOOST_LOG_SEV(theGlobalLogger::get(), HIS_WARNING_LEVEL) << thestream << \
            "\t" << __FILE__ << "\t" << __LINE__

        #define HIS_LOG_ERROR( thestream) \
            BOOST_LOG_SEV(theGlobalLogger::get(), HIS_ERROR_LEVEL) << thestream << \
            "\t" << __FILE__ << "\t" << __LINE__

        #define HIS_LOG_FATAL( thestream ) \
            BOOST_LOG_SEV(theGlobalLogger::get(), HIS_FATAL_LEVEL) << thestream << \
            "\t" << __FILE__ << "\t" << __LINE__


    #endif // USING_BOOST_LOG

#else
    #define HIS_LOG_REQUEST( thestream )
    #define HIS_LOG_RESPONSE( thestream )
    #define HIS_LOG_INFO( thestream )
    #define HIS_LOG_WARNING( thestream )
    #define HIS_LOG_ERROR( thestream )
    #define HIS_LOG_FATAL( thestream )
#endif


int initialLog(const char* name, const std::string& path, const std::string& file);
void terminalLog();

/*******************************************************************************************/
#endif// KEYSERVER_KEYSERVER_LOG_H__