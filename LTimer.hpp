//
//  LTimer.hpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 17/09/15.
//  Copyright © 2015 jrsc. All rights reserved.
//

#ifndef __GemsArr__LTimer__
#define __GemsArr__LTimer__

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
#include <SDL2_image/SDL_image.h>

#else
// Unsupported platform
#endif
#elif __linux

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif

#include <stdio.h>
#include <string>
#include <sstream>

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

//The application time based timer
class LTimer
{
public:
    //Initializes variables
    LTimer();
    
    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();
    
    //Gets the timer's time
    Uint32 getTicks();
    
    //Checks the status of the timer
    bool isStarted();
    bool isPaused();
    
private:
    //The clock time when the timer started
    Uint32 mStartTicks;
    
    //The ticks stored when the timer was paused
    Uint32 mPausedTicks;
    
    //The timer status
    bool mPaused;
    bool mStarted;
};

#endif /* defined(__GemsArr__LTimer__) */
