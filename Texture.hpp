//
//  Texture.hpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 15/09/15.
//  Copyright © 2015 jrsc. All rights reserved.
//

#ifndef __GemsArr__Texture__
#define __GemsArr__Texture__

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
#include <iostream>
#include <string>
#include <regex>

#include "Transform.hpp"

using namespace std;

const string REGEX_TEXTURE = "^.*\\.(jpg|png|gif|bmp|jpeg|lbm|pcx|pnm|tga|tiff|webp|xcf|xpm|xv)$";

class Texture : public Transform
{
protected:
    string path;
    SDL_Texture * texture;
    
public:
    
    Texture( string path );
    ~Texture();
    
    bool load( SDL_Renderer * renderer );
    void unload();
    
    void render(SDL_Renderer * renderer, int x, int y, SDL_Rect * clip);
    
    string getPath();
    SDL_Texture * getTexture();
    
};

#endif /* defined(__GemsArr__Texture__) */
