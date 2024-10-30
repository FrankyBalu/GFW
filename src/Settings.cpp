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

#include "Settings.hpp"
#include "Log.hpp"
#include <fstream>
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <raylib.h>

GFW::Settings *GFW::Settings::privateInstance = nullptr;

GFW::Settings::Settings()
: privateMusicVolume(0.5), privateEffectVolume(0.5), privateFullscreen(false), privateCollisionBoxes(true),privateShowVersion(false),privateWindowWidth(800), privateWindowHeight(600), privateFPS(60),privateExitKey(291),privateLogLevel(LOG_DEBUG) {

}

GFW::Settings *GFW::Settings::Instance() {
    if (privateInstance == nullptr)
        privateInstance = new Settings();
    return privateInstance;
}

bool GFW::Settings::Load(std::string file) {
    bool return_value = false;
    std::string script_file;

    sol::state lua;
    lua.open_libraries(sol::lib::base);
    lua.open_libraries(sol::lib::string);

    if (!FileExists(file.c_str())){
        ERROR_LOG("Konnte Datei {} nicht öffnen", file);
        return false;
    }

        lua.script_file(file);
        privateMusicVolume = lua.get<float>("MUSICVOLUME");
        privateEffectVolume = lua.get<float>("EFFECTVOLUME");
        privateFullscreen = lua.get<bool>("FULLSCREEN");
        privateCollisionBoxes = lua.get<bool>("DEBUG");
        privateWindowWidth = lua.get<int>("SCREENWIDTH");
        privateWindowHeight = lua.get<int>("SCREENHEIGHT");
        privateFPS = lua.get<int>("FPS");
        privateExitKey = lua.get<int>("EXITKEY");
        privateLogLevel = lua.get<int>("LOGLEVEL");
        privateShowVersion = lua.get<bool>("SHOWVERSION");

    TRACE_LOG("\t_MusicVolume : ",privateMusicVolume);
    TRACE_LOG("\t_EffectVolume: ",privateEffectVolume);
    TRACE_LOG("\t_Fullscreen  : ",privateFullscreen);
    TRACE_LOG("\t_CollisionBox: ",privateCollisionBoxes);
    TRACE_LOG("\t_ShowVersion : ",privateShowVersion);
    TRACE_LOG("\t_WindowWidth : ",privateWindowWidth);
    TRACE_LOG("\t_WindowHeight: ",privateWindowHeight);
    TRACE_LOG("\t_FPS         : ",privateFPS);
    TRACE_LOG("\t_LogLevel    : ",privateLogLevel);
    TRACE_LOG("\t_ExitKey     : ",privateExitKey);

    return true;
}

float GFW::Settings::MusicVolume() const {
    return privateMusicVolume;
}

float GFW::Settings::EffectVolume() const {
    return privateEffectVolume;
}

bool GFW::Settings::FullScreen() const {
    return privateFullscreen;
}

bool GFW::Settings::Debug() const {
    return privateCollisionBoxes;
}

int GFW::Settings::WindowWidth() const {
    return privateWindowWidth;
}

int GFW::Settings::WindowHeight() const {
    return privateWindowHeight;
}

int GFW::Settings::FPS() const {
    return privateFPS;
}

int GFW::Settings::ExitKey() const{
    return privateExitKey;
}

int GFW::Settings::LogLevel() const{
    return privateLogLevel;
}

bool GFW::Settings::ShowVersion() const{
    return privateShowVersion;
}


void GFW::Settings::MusicVolume(float vol){
    if (vol >= 0.0 && vol <= 1.0){
        privateMusicVolume = vol;
        INFO_LOG ("Musiklautstärke auf ",  100*vol," gesetzt");
        return;
    }
    else{
        WARN_LOG ("Konnte Musiklautstärke nicht auf ",  100*vol," gesetzt");
        return;
    }
}

void GFW::Settings::EffectVolume(float vol){
    if (vol >= 0.0 && vol <= 1.0){
        privateEffectVolume = vol;
        INFO_LOG ("Effektlautstärke auf ",  100*vol," gesetzt");
        return;
    }
    else{
        WARN_LOG ("Konnte Effektlautstärke nicht auf ", 100*vol, "setzen");
        return;
    }
}

void GFW::Settings::FullScreen(bool val){
    privateFullscreen = val;
    //TODO: Die Anwendung über die Änderung informieren
}

void GFW::Settings::Debug(bool val){
    privateCollisionBoxes = val;
}

void GFW::Settings::WindowWidth(int width){
    //TODO Prüfen ob möglich
    privateWindowWidth = width;
}

void GFW::Settings::WindowHeight(int height){
    //TODO Prüfen ob möglich
    privateWindowHeight = height;
}

void GFW::Settings::FPS(int fps){
    //TODO Prüfen ob möglich
    privateFPS = fps;
}

void GFW::Settings::ExitKey(int key){
    privateExitKey = key;
}

void GFW::Settings::LogLevel(int logLevel){
    if (logLevel >= LOG_NONE && logLevel <= LOG_TRACE){
        Log::Instance()->SetLogLevel(logLevel);
        privateLogLevel = logLevel;
    }
    else
        WARN_LOG ("LogLevel ", logLevel, " nicht Unterstützt");
}

void GFW::Settings::ShowVersion(bool version){
    privateShowVersion = version;
}


void GFW::Settings::Save(std::string file)const{
    /*std::string realpath;
    #ifdef __linux__
    realpath = PHYSFS_getRealDir("system");
    #elifdef _WIN64
    realpath = "data\\";
    #endif
    std::string saveFile = realpath + std::string ("\\") + "settings.lua";*/

    std::ofstream ofFile;
    ofFile.open(file);
    ofFile << "MUSICVOLUME = " << privateMusicVolume << "\n";
    ofFile << "EFFECTVOLUME = " << privateEffectVolume << "\n";
    ofFile << "SCREENWIDTH = " << privateWindowWidth  << "\n";
    ofFile << "SCREENHEIGHT = " << privateWindowHeight << "\n";
    ofFile << "FPS = " << privateFPS << "\n";
    ofFile << "LOGLEVEL = " << privateLogLevel << "\n";
    ofFile << "EXITKEY = " << privateExitKey << "\n";
    if (privateFullscreen){
        ofFile << "FULLSCREEN = true\n";
    }
    else{
        ofFile << "FULLSCREEN = false\n";
    }
    if (privateCollisionBoxes){
        ofFile << "DEBUG = true\n";
    }
    else{
        ofFile << "DEBUG = false\n";
    }
    if (privateShowVersion){
        ofFile << "SHOWVERSION = true\n";
    }
    else{
        ofFile << "SHOWVERSION = false\n";
    }

}
