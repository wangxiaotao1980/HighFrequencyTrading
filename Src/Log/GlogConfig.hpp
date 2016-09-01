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
 *  @file      GlogConfig.hpp 2015\10\23 15:42:31 $
 *  @author    Wang Xiaotao<wangxt@hiscene.com> (中文编码测试)
 *  @note      summary
 *******************************************************************************************/
#ifndef KEYSERVER_KEYSERVER_GLOGCONFIG_HPP__
#define KEYSERVER_KEYSERVER_GLOGCONFIG_HPP__

#include <string>
/*******************************************************************************************/

#ifndef NO_USING_LOG
    #ifdef USING_GLOG
        #ifndef WIN32
            //应用程序崩溃 回掉函数 将信息输出到单独的文件和 LOG(ERROR)
            void signalHandle(const char* data, int size);
        #endif
    #endif
#endif

int initialGlogLog(const char* name, const std::string& path, const std::string& file);
void terminalGlogLog();

/*******************************************************************************************/
#endif// KEYSERVER_KEYSERVER_GLOGCONFIG_HPP__
