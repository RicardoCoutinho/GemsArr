//
//  SDLApp.hpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 10/09/15.
//  Copyright © 2015 jrsc. All rights reserved.
//

#ifndef __GemsArr__SDLApp__
#define __GemsArr__SDLApp__

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
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>

#else
// Unsupported platform
#endif
#elif __linux

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif

#include <stdio.h>

#include "Game.hpp"
#include "LTimer.hpp"

class SDLApp {
    
    const int SCREEN_WIDTH = 773;
    const int SCREEN_HEIGHT = 480;
    
    SDL_Window   * window;
    SDL_Renderer * renderer;

protected:

    Game * game;
    
public:
    
    SDLApp();
    
    bool init();
    void close();
    void run();
};


#endif /* defined(__GemsArr__SDLApp__) */
