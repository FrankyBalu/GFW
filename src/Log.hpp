/*
 * GFW
 * Copyright (C) 2024   Frank Kartheuser <frank.kartheuser1988@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef GFW_LOG
#define GFW_LOG


#include <iostream>
#include <string>
#include <mutex>
#include <sstream>
#include <source_location>
#include <iomanip>


//regelt wieviel platz für die Funktionsnamen gelassen wird
#define NAME_WIDTH 30

#define LOG_COLOR_RESET   "\033[39m\033[48;2m"
#define LOG_COLOR_BLACK   "\033[30m"      /* Black */
#define LOG_COLOR_RED     "\033[31m"      /* Red */
#define LOG_COLOR_GREEN   "\033[32m"      /* Green */
#define LOG_COLOR_YELLOW  "\033[33m"      /* Yellow */
#define LOG_COLOR_BLUE    "\033[34m"      /* Blue */
#define LOG_COLOR_MAGENTA "\033[35m"      /* Magenta */
#define LOG_COLOR_CYAN    "\033[36m"      /* Cyan */
#define LOG_COLOR_WHITE   "\033[37m"      /* White */
#define LOG_COLOR_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define LOG_COLOR_BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define LOG_COLOR_BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define LOG_COLOR_BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define LOG_COLOR_BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define LOG_COLOR_BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define LOG_COLOR_BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define LOG_COLOR_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


namespace GFW {

    enum LogLevel {
        LOG_NONE = 0,
        LOG_ERROR = 1,
        LOG_WARNING = 2,
        LOG_INFO = 3,
        LOG_DEBUG = 4,
        LOG_TRACE = 5
    };



    class Log {
    public:
        template<class... Args>
        void log_msg(int level, const std::source_location loc, Args &&... args) {
            if (_LogLevel < level)
                return;
            static std::mutex myMutex;
            std::ostringstream os;
            #ifdef _WIN64
            os << LevelToName(level) << ": " << std::setw(15) << loc.file_name() << std::setw(NAME_WIDTH) << loc.function_name() << " (" << loc.line()
            << "):" << std::boolalpha;

            ((os << ' ' << args), ...);
            os << std::endl;
            #else
            os << LogLevelToColor(level) << LogLevelToName(level) << ": [" << std::setw(15) << loc.file_name() << "] " << std::setw(NAME_WIDTH) << loc.function_name() << " (" << loc.line()
            << "):" << std::boolalpha;
            // fold expression:
            ((os << ' ' << args), ...);
            os << LOG_COLOR_RESET << std::endl;
            #endif

            std::lock_guard<std::mutex> lock(myMutex);
            std::clog << os.str();
        }
        static Log *Instance();

        void SetLogLevel(int logLevel);

    private:
        Log();

        int _LogLevel;
        static Log *_Instance;
        std::string LogLevelToName(int level){
            switch (level){
                case LOG_NONE:
                    return "FATAL";
                    break;
                case LOG_ERROR:
                    return "ERROR";
                    break;
                case LOG_WARNING:
                    return "WARN ";
                    break;
                case LOG_INFO:
                    return "INFO ";
                    break;
                case LOG_DEBUG:
                    return "DEBUG";
                    break;
                case LOG_TRACE:
                    return "TRACE";
                    break;
                default:
                    return "UNKNOWN";
            };
        }

        // \033[38;2;<r>;<g>;<b>m     #Select RGB foreground color
        // \033[48;2;<r>;<g>;<b>m     #Select RGB background color
        std::string LogLevelToColor(int level){
            switch (level){
                case LOG_NONE:
                    return LOG_COLOR_BOLDRED;
                    break;
                case LOG_ERROR:
                    return "\033[38;2;255;255;0;48;2;255;0;0m";
                    break;
                case LOG_WARNING:
                    return "\033[38;2;255;0;0;48;2;255;255;0m";
                    break;
                case LOG_INFO:
                    return "\033[38;2;255;255;0;48;2;0;0;0m";
                    break;
                case LOG_DEBUG:
                    return "\033[38;2;0;0;255;48;2;0;0;0m";
                    break;
                case LOG_TRACE:
                    return "\033[38;2;0;255;0;48;2;0;0;0m";
                    break;
                default:
                    return "\033[38;2;255;255;255;48;2;0;0;0m";
            };
        }
    };


} // namespace GFW

//FIXME: warum muss man die Loglevel in falscher Reihenfolge schrieben?
#define ERROR_LOG(...) GFW::Log::Instance()->log_msg(LOG_ERROR, std::source_location::current(), __VA_ARGS__)
#define WARN_LOG(...) GFW::Log::Instance()->log_msg(LOG_WARNING, std::source_location::current(), __VA_ARGS__)
#define INFO_LOG(...) GFW::Log::Instance()->log_msg(LOG_INFO, std::source_location::current(), __VA_ARGS__)
#define DEBUG_LOG(...) GFW::Log::Instance()->log_msg(LOG_DEBUG, std::source_location::current(), __VA_ARGS__)
#define TRACE_LOG(...) GFW::Log::Instance()->log_msg(LOG_TRACE, std::source_location::current(), __VA_ARGS__)


#endif //GFW_LOG
