//
//  Font.hpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 15/09/15.
//  Copyright © 2015 jrsc. All rights reserved.
//

#ifndef __GemsArr__Font__
#define __GemsArr__Font__

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
#include <SDL2_ttf/SDL_ttf.h>

#else
// Unsupported platform
#endif
#elif __linux

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif

#include <stdio.h>
#include <string>

#include "Texture.hpp"

using namespace std;

const string REGEX_FONT = "^.*\\.(ttf)$";

class Font : public Texture
{
    TTF_Font * font;
    
public:
    
    Font( string path );
    ~Font();
    
    bool load();
    bool load( int size );
    void unload();
    
    bool createTextureFromText( SDL_Renderer * renderer, string text, SDL_Color color );
};


#endif /* defined(__GemsArr__Font__) */
