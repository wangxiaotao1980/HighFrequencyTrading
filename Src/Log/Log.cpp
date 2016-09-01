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
 *  @file      Log.cpp 2015\10\23 15:47:41 $
 *  @author    Wang Xiaotao<wangxt@hiscene.com> (中文编码测试)
 *******************************************************************************************/

#include "Log.h"
/*******************************************************************************************/

// ------------------------------------------------------------------------------------------
// 
int initialLog(const char* name, const std::string& path, const std::string& file)
{
    #ifndef NO_USING_LOG

        #ifdef USING_GLOG
            return initialGlogLog(name, path, file);
        #endif //USING_GLOG

        #ifdef USING_LOG4PLUS
            //using log4plus
        #endif //USING_LOG4PLUS

        #ifdef USING_BOOST_LOG
            return initialBoostLog(name, path, file);
        #endif // USING_BOOST_LOG
    #else
        return 0;
    #endif // NO_USING_LOG
}

// ------------------------------------------------------------------------------------------
// 
void terminalLog()
{
    #ifndef NO_USING_LOG

        #ifdef USING_GLOG
            terminalGlogLog();
        #endif

        #ifdef USING_LOG4PLUS
            //using log4plus
        #endif //USING_LOG4PLUS

        #ifdef USING_BOOST_LOG
            terminalBoostLog();
        #endif // USING_BOOST_LOG

    #endif // NO_USING_LOG
}

// 
// ------------------------------------------------------------------------------------------
