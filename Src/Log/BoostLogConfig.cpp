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
 *  @file      BoostLogConfig.cpp 2015\10\23 15:33:01 $
 *  @author    Wang Xiaotao<wangxt@hiscene.com> (中文编码测试)
 *******************************************************************************************/

#include "BoostLogConfig.hpp"

/*******************************************************************************************/
#ifndef NO_USING_LOG
#ifdef USING_BOOST_LOG
    #define  BOOST_LOG_USE_NATIVE_SYSLOG
    #include "boost/log/sinks/async_frontend.hpp"
    #include "boost/log/sinks/sync_frontend.hpp"
    #include "boost/log/sinks/text_file_backend.hpp"
    #include "boost/log/sinks/syslog_backend.hpp"
    #include "boost/make_shared.hpp"
    #include "boost/filesystem.hpp"
#endif
#endif

// ------------------------------------------------------------------------------------------
//
// 日志 record 格式
#define LOG_RECORD_FORMAT \
    expr::format("%1%\t%2%\t%3%\t%4%\t%5%") \
    % expr::attr<EnumLogSeverityLevel>("Severity") \
    % expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d/%H:%M:%S:%f") \
    % expr::attr<attrs::current_process_id::value_type>("ProcessID") \
    % expr::attr<attrs::current_thread_id::value_type >("ThreadID") \
    % expr::smessage


// ------------------------------------------------------------------------------------------
//
int initialBoostLog(const char* name, const std::string& path, const std::string& file)
{

#ifndef NO_USING_LOG
#ifdef USING_BOOST_LOG

    std::string serverFileName;

    boost::filesystem::path theServerPath(name);
    if (theServerPath.has_filename())
    {
        serverFileName = theServerPath.stem().string();
    }
    else
    {
        serverFileName = name;
    }

    const std::string requestLogNameTemplate(std::string("log/") + serverFileName + ".req.%Y-%m-%d");
    const std::string pResponseLogNameTemplate(std::string("log/") + serverFileName + ".res.%Y-%m-%d");
    const std::string commonLogNameTemplate(std::string("log/") + serverFileName + ".log.%Y-%m-%d");
    const std::string warningLogNameTemplate(std::string("log/") + serverFileName + ".log.wef.%Y-%m-%d");

    boost::shared_ptr< logging::core > logCore = logging::core::get();


    typedef boost::log::sinks::text_file_backend TBackend;
    typedef boost::log::sinks::syslog_backend    SysBackend;

    typedef boost::log::sinks::asynchronous_sink<TBackend> RequestSink;     // 请求sink
    typedef boost::log::sinks::asynchronous_sink<TBackend> ResponseSink;    // 响应sink
    typedef boost::log::sinks::synchronous_sink<TBackend>   LogSink;        // 正常日志
    typedef boost::log::sinks::synchronous_sink<TBackend>   LogWarningSink; // log warning and fatal
    typedef boost::log::sinks::synchronous_sink<SysBackend> SysLogSink;     // sys log sink



    //1 初始化请求日志
    boost::shared_ptr< TBackend > pRequestBackEnd = boost::make_shared<TBackend>
    (
        keywords::file_name = requestLogNameTemplate.c_str(),
        keywords::open_mode = (std::ios::out | std::ios::app),
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0)
    );
    pRequestBackEnd->auto_flush(true);

    boost::shared_ptr< RequestSink > pRequestSink = boost::make_shared< RequestSink >(pRequestBackEnd);
    pRequestSink->set_formatter(LOG_RECORD_FORMAT);


    pRequestSink->set_filter(expr::attr<EnumLogSeverityLevel>("Severity") == HIS_REQUEST_LEVEL);
    logCore->add_sink(pRequestSink);


    //2 初始化响应日志
    boost::shared_ptr< TBackend > pResponseBackEnd = boost::make_shared<TBackend>
    (
        keywords::file_name = pResponseLogNameTemplate.c_str(),
        keywords::open_mode = (std::ios::out | std::ios::app),
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0)
    );
    pResponseBackEnd->auto_flush(true);

    boost::shared_ptr< ResponseSink > responseSink = boost::make_shared< ResponseSink >(pResponseBackEnd);

    responseSink->set_formatter(LOG_RECORD_FORMAT);


    responseSink->set_filter(expr::attr<EnumLogSeverityLevel>("Severity") == HIS_RESPONSE_LEVEL);
    logCore->add_sink(responseSink);


    //3 初始化基本日志
    boost::shared_ptr< TBackend > pLogBackEnd = boost::make_shared<TBackend>
    (
        keywords::file_name = commonLogNameTemplate.c_str(),
        keywords::open_mode = (std::ios::out | std::ios::app),
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0)
    );
    pLogBackEnd->auto_flush(true);

    boost::shared_ptr< LogSink > pLogSink = boost::make_shared< LogSink >(pLogBackEnd);
    pLogSink->set_formatter(LOG_RECORD_FORMAT);

    pLogSink->set_filter(expr::attr<EnumLogSeverityLevel>("Severity") >= HIS_INFO_LEVEL);
    logCore->add_sink(pLogSink);
    


    //4 初始化错误日志
    boost::shared_ptr< TBackend > pLogWarningBackEnd = boost::make_shared<TBackend>
    (
        keywords::file_name = warningLogNameTemplate.c_str(),
        keywords::open_mode = (std::ios::out | std::ios::app),
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0)
    );
    pLogWarningBackEnd->auto_flush(true);

    boost::shared_ptr< LogWarningSink > pLogWarningSink = boost::make_shared< LogWarningSink >(pLogWarningBackEnd);
    pLogWarningSink->set_formatter(LOG_RECORD_FORMAT);

    pLogWarningSink->set_filter(expr::attr<EnumLogSeverityLevel>("Severity") >= HIS_WARNING_LEVEL);
    logCore->add_sink(pLogWarningSink);
    // 5初始化syslog
    boost::shared_ptr<SysBackend> pSysLogBackEnd = boost::make_shared < SysBackend >
        (
        keywords::facility = sinks::syslog::local0,
        keywords::use_impl = sinks::syslog::native
        );
    sinks::syslog::custom_severity_mapping< std::string > mapping("Severity");
    mapping["fatal"]   = sinks::syslog::critical;
    mapping["error"]   = sinks::syslog::error;
    mapping["warning"] = sinks::syslog::warning;
    mapping["info"]    = sinks::syslog::info;

    pSysLogBackEnd->set_severity_mapper(mapping);


    boost::shared_ptr<SysLogSink> pSysLogSink = boost::make_shared<SysLogSink>(pSysLogBackEnd);

    pSysLogSink->set_formatter(LOG_RECORD_FORMAT);
    pSysLogSink->set_filter(expr::attr<EnumLogSeverityLevel>("Severity") >= HIS_WARNING_LEVEL);

    logCore->add_sink(pSysLogSink);


    logging::add_common_attributes();
    logCore->add_thread_attribute("ThreadID", attrs::current_thread_id());

#endif //USING_BOOST_LOG
#endif //NO_USING_LOG

    return 0;
}

// ------------------------------------------------------------------------------------------
//
void terminalBoostLog()
{

#ifndef NO_USING_LOG
    #ifdef USING_BOOST_LOG
        logging::core::get()->flush();
        logging::core::get()->remove_all_sinks();
    #endif //USING_BOOST_LOG
#endif //NO_USING_LOG
}

//
// ------------------------------------------------------------------------------------------
