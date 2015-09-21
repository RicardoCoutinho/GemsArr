//
//  Animation.cpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 20/09/15.
//  Copyright © 2015 jrsc. All rights reserved.
//

#include "Animation.hpp"

bool Animation::animationHasEnded()
{
    return frame >= duration;
}

Slide::Slide(unsigned int duration, Texture * texture, point startPos, point endPos)
{
    this->frame = 0;
    this->step = make_pair( (endPos.first - startPos.first) / duration , (endPos.second - startPos.second) / duration );
    this->duration = duration * 60;
    this->texture  = texture;
    
    this->startPos = startPos;
    this->endPos = endPos;
}

Slide::~Slide()
{

}

void Slide::render(SDL_Renderer * renderer, SDL_Rect * clip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { startPos.first, startPos.second, texture->getWidth(), texture->getHeight() };
    
    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w * texture->getScaleX();
        renderQuad.h = clip->h * texture->getScaleY();
    }
    
    //Render to screen
    SDL_RenderCopy( renderer, texture->getTexture(), clip, &renderQuad );
    
    // Tick frame
    if (frame % 60 == 0)
    {
        startPos.first += step.first;
        startPos.second += step.second;
    }
    
    frame++;
    //cout << startPos.first << " " << step.first << " " << startPos.second << " " << step.second << " " << frame << endl;
}

Fade::Fade(unsigned int duration, Texture * texture, usint startAlpha, usint endAlpha)
{
    this->frame = 0;
    this->duration = duration;
    this->texture  = texture;
    
    this->startAlpha = startAlpha;
    this->endAlpha = endAlpha;
}
Fade::~Fade()
{

}
void Fade::render(SDL_Renderer * renderer, SDL_Rect * clip)
{
    // Tick frame
    frame++;
}

Scale::Scale()
{
    this->frame = 0;
    this->duration = duration;
    this->texture  = texture;
}
Scale::~Scale()
{
    this->frame = 0;
    this->duration = duration;
    this->texture  = texture;
}
void Scale::render(SDL_Renderer * renderer, SDL_Rect * clip)
{
    // Tick frame
    frame++;
}