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
 *  @file      BoostLogConfig.hpp 2015\10\23 15:35:12 $
 *  @author    Wang Xiaotao<wangxt@hiscene.com> (中文编码测试)
 *  @note      summary
 *******************************************************************************************/
#ifndef KEYSERVER_KEYSERVER_BOOSTLOGCONFIG_HPP__
#define KEYSERVER_KEYSERVER_BOOSTLOGCONFIG_HPP__

#include <iostream>
#include <string>
/*******************************************************************************************/

#ifndef NO_USING_LOG
    #ifdef USING_BOOST_LOG

        #include "boost/date_time/posix_time/posix_time.hpp"
        #include "boost/log/support/date_time.hpp"
        #include "boost/log/common.hpp"
        #include "boost/log/expressions.hpp"
        #include "boost/log/expressions/keyword.hpp"

        #include "boost/log/attributes.hpp"
        #include "boost/log/attributes/timer.hpp"
        #include "boost/log/sources/logger.hpp"
        #include "boost/log/sources/severity_logger.hpp"



        #include "boost/log/utility/setup/file.hpp"
        #include "boost/log/utility/setup/console.hpp"
        #include "boost/log/utility/setup/common_attributes.hpp"

        #include "boost/log/attributes/named_scope.hpp"

        namespace logging  = boost::log;
        namespace attrs    = boost::log::attributes;
        namespace src      = boost::log::sources;
        namespace sinks    = boost::log::sinks;
        namespace expr     = boost::log::expressions;
        namespace keywords = boost::log::keywords;

        /**
        * 日志级别
        *
        */
        enum EnumLogSeverityLevel
        {
            HIS_REQUEST_LEVEL = 0,
            HIS_RESPONSE_LEVEL,
            HIS_INFO_LEVEL,
            HIS_WARNING_LEVEL,
            HIS_ERROR_LEVEL,
            HIS_FATAL_LEVEL,
        };

        template< typename CharT, typename TraitsT >
        inline std::basic_ostream< CharT, TraitsT >& operator << (
                std::basic_ostream< CharT, TraitsT >& strm, 
                EnumLogSeverityLevel enumSeverityLevel)
        {
            static const char* const str[] =
            {
                "request",
                "response",
                "info",
                "warning",
                "error",
                "fatal",
            };

            if (static_cast<std::size_t>(enumSeverityLevel) < (sizeof(str) / sizeof(*str)))
            {
                strm << str[enumSeverityLevel];
            }
            else
            {
                strm << static_cast<int>(enumSeverityLevel);
            }
            return strm;
        }


        BOOST_LOG_ATTRIBUTE_KEYWORD(log_severity,  "Severity",  EnumLogSeverityLevel)
        BOOST_LOG_ATTRIBUTE_KEYWORD(log_timestamp, "TimeStamp", boost::posix_time::ptime)
        BOOST_LOG_ATTRIBUTE_KEYWORD(log_uptime,    "Uptime",    attrs::timer::value_type)
        BOOST_LOG_ATTRIBUTE_KEYWORD(log_scope,     "Scope",     attrs::named_scope::value_type)


        // 全局日志对象
        BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(theGlobalLogger, boost::log::sources::severity_logger_mt<EnumLogSeverityLevel>)

    #endif //USING_BOOST_LOG
#endif //NO_USING_LOG

int initialBoostLog(const char* name, const std::string& path, const std::string& file);
void terminalBoostLog();


/*******************************************************************************************/
#endif// KEYSERVER_KEYSERVER_BOOSTLOGCONFIG_HPP__
