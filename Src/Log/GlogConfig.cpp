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
 *  @file      GlogConfig.cpp 2015\10\23 15:43:49 $
 *  @author    Wang Xiaotao<wangxt@hiscene.com> (中文编码测试)
 *******************************************************************************************/

#define GLOG_NO_ABBREVIATED_SEVERITIES // 没这个编译会出错,传说因为和Windows.h冲突

#include "Log.h"
#include "GlogConfig.hpp"

/*******************************************************************************************/
#ifndef NO_USING_LOG
    #ifdef  USING_GLOG
        #include "glog/logging.h"
        #include "boost/filesystem.hpp"
        #include "boost/property_tree/ptree.hpp"
        #include "boost/property_tree/json_parser.hpp"
    #endif
#endif

/**
{
    "logtostderr" : false,            //  日志是否输出到 stderr
    "alsologtostderr" : false,        //  是否同时将日志输出到文件和stderr
    "minloglevel" : 0,                //  限制输出到 stderr 的部分信息，包括此错误级别和更高错误级别的日志信息
    "colorlogtostderr" : false,       //  将输出到 stderr 上的错误日志显示相应的颜色
    "logbufsecs":30,                  //  设置buf缓冲时间，单位 秒
    "max_log_size":100,               //  单个日志最大尺寸
    "stop_logging_if_full_disk": true,//  磁盘满了后是否不写日志
    "log_dir" : "./log/",             //  设置日志文件输出目录

}
*/

#ifndef NO_USING_LOG
    #ifdef  USING_GLOG
        #ifndef WIN32
            void signalHandle(const char* data, int size)
            {
                //等待细化
                std::ofstream fs("./core_dump.log", std::ios::app);
                std::string str = std::string(data, size);
                fs << str;
                fs.close();
                LOG(ERROR) << str;
            }
        #endif 
    #endif //USING_GLOG
#endif //NO_USING_LOG

// ------------------------------------------------------------------------------------------
//
int initialGlogLog(const char* name, const std::string& path, const std::string& file)
{
    int result = 0;
#ifndef NO_USING_LOG
    #ifdef  USING_GLOG

    google::InitGoogleLogging(name);
    
    boost::property_tree::ptree pt;

    try
    {
        boost::property_tree::read_json(path + file, pt);
        FLAGS_logtostderr               = pt.get<bool>("logtostderr", false);
        FLAGS_alsologtostderr           = pt.get<bool>("alsologtostderr", false);
        FLAGS_minloglevel               = pt.get<int>("minloglevel", google::GLOG_INFO);
        FLAGS_colorlogtostderr          = pt.get<bool>("colorlogtostderr", false);
        FLAGS_logbufsecs                = pt.get<int>("logbufsecs", 10);
        FLAGS_max_log_size              = pt.get<int>("max_log_size", 100);
        FLAGS_stop_logging_if_full_disk = pt.get<bool>("stop_logging_if_full_disk", true);
        FLAGS_log_dir                   = pt.get<std::string>("log_dir", "./log/");

        boost::filesystem::path logFolder(FLAGS_log_dir);
        if (!boost::filesystem::exists(logFolder))
        {
            if (!boost::filesystem::create_directories(logFolder))
            {
                result = 1;
                return result;
            }
        }

        HIS_LOG_INFO("initial log system according to"
            << path << file);
    }

    catch (...)
    {
        FLAGS_logtostderr               = false;
        FLAGS_alsologtostderr           = true;
        FLAGS_minloglevel               = google::GLOG_INFO;
        FLAGS_colorlogtostderr          = false;
        FLAGS_logbufsecs                = 30;
        FLAGS_max_log_size              = 10;      //最大日志大小为 100MB
        FLAGS_stop_logging_if_full_disk = true;     //当磁盘被写满时，停止日志输出
        FLAGS_log_dir                   = "./log";

        boost::filesystem::path logFolder(FLAGS_log_dir);
        if (!boost::filesystem::exists(logFolder))
        {
            boost::system::error_code ec;
            if (boost::filesystem::create_directories(logFolder, ec))
            {
                std::cout << "create directories : " << logFolder.filename() << std::endl;
            }
            else
            {

                std::cout << ec.message() << std::endl;
                result = 1;
                return result;
            }
        }

        LOG(WARNING) << "initial log system according to default configuration";

    }

    #ifndef WIN32
        // 安装coredump 后的写日志函数,在windows下函数无效。
        google::InstallFailureSignalHandler();
        google::InstallFailureWriter(&signalHandle);
    #endif

    #endif //  USING_GLOG
#endif

    return result;
}

// ------------------------------------------------------------------------------------------
//
void terminalGlogLog()
{
#ifndef NO_USING_LOG
    #ifdef  USING_GLOG
    google::ShutdownGoogleLogging();
    #endif
#endif
}

// 
// ------------------------------------------------------------------------------------------