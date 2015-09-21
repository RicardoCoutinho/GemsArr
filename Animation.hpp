//
//  Animation.hpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 20/09/15.
//  Copyright © 2015 jrsc. All rights reserved.
//

#ifndef __GemsArr__Animation__
#define __GemsArr__Animation__

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
#include <utility>
#include <cmath>

#include "Texture.hpp"

using namespace std;

typedef unsigned short int usint;
typedef pair<usint, usint> point;

class Animation
{
protected:
    unsigned int duration;
    unsigned int frame;
    Texture * texture;
    
public:
    bool animationHasEnded();
    virtual void render(SDL_Renderer * renderer, SDL_Rect * clip) = 0;
};

class Slide : public Animation
{
    pair<int,int> startPos;
    pair<int,int> endPos;
    
    pair<int,int> step;
 
public:
    Slide(unsigned int duration, Texture * texture, point startPos, point endPos);
    ~Slide();
    void render(SDL_Renderer * renderer, SDL_Rect * clip);
};

class Fade : public Animation
{
    usint startAlpha;
    usint endAlpha;
    
public:
    Fade(unsigned int duration, Texture * texture, usint startAlpha, usint endAlpha);
    ~Fade();
    void render(SDL_Renderer * renderer, SDL_Rect * clip);
};

class Scale : public Animation
{
    float startScale;
    float endScale;
    
public:
    Scale();
    ~Scale();
    void render(SDL_Renderer * renderer, SDL_Rect * clip);
};

#endif /* __GemsArr__Animation__ */
