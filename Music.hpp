//
//  Music.hpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 18/09/15.
//  Copyright © 2015 jrsc. All rights reserved.
//

#ifndef __GemsArr__Music__
#define __GemsArr__Music__

#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#ifdef _WIN64
//define something for Windows (64-bit only)
#endif
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#elif TARGET_OS_IPHONE
// iOS device
#elif TARGET_OS_MAC

#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>

#else
// Unsupported platform
#endif
#elif __linux

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif

#include <stdio.h>
#include <string>

using namespace std;

const string REGEX_MUSIC = "^.*\\.(flac|ogg|oga|mp3)$";

class Music
{
    string path;
    Mix_Music * music;
    
public:
    
    Music( string path );
    ~Music();
    
    bool load();
    void unload();
    
    void play();
    void resume();
    void pause();
    void stop();
    
    string getPath();
    Mix_Music * getMusic();
    
};

#endif /* __GemsArr__Music__ */
