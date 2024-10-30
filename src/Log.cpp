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

#include "Log.hpp"

GFW::Log *GFW::Log::_Instance = nullptr;


GFW::Log::Log() {
#ifndef _WIN64
        static std::mutex myMutex;
        std::ostringstream os;
        os << "\033[2J" << "\033[H";
        std::lock_guard<std::mutex> lock(myMutex);
        std::clog << os.str();
#endif
    _LogLevel = LOG_TRACE;
}

GFW::Log *GFW::Log::Instance() {
    if (_Instance == nullptr) {
        _Instance = new Log();
    }
    return _Instance;
}

void GFW::Log::SetLogLevel(int logLevel) {
    _LogLevel = logLevel;
}
