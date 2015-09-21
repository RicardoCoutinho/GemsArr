//
//  LButton.hpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 16/09/15.
//  Copyright © 2015 jrsc. All rights reserved.
//

#ifndef __GemsArr__LButton__
#define __GemsArr__LButton__

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

#include "Texture.hpp"

enum LButtonState
{
    BUTTON_STATE_MOUSE_OUT = 0,
    BUTTON_STATE_MOUSE_OVER_MOTION = 1,
    BUTTON_STATE_MOUSE_DOWN = 2,
    BUTTON_STATE_MOUSE_UP = 3,
    BUTTON_STATE_TOTAL = 4
};

class LButton
{
    int size;
    bool isDown;
    
public:
    
    SDL_Point position;
    LButtonState currentState;
    
    LButton();
    
    void setPosition( int x, int y );
    void setSize(int size);
    
    void handleEvent( SDL_Event * e );
    void render( SDL_Renderer * renderer );    
};


#endif /* defined(__GemsArr__LButton__) */
