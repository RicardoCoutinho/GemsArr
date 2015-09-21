//
//  Texture.cpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 15/09/15.
//  Copyright © 2015 jrsc. All rights reserved.
//

#include "Texture.hpp"

Texture::Texture( string path )
{
    this->path = path;
    texture = NULL;
    
    width = 0;
    height = 0;
}

Texture::~Texture()
{
    path = "";
    unload();
    
    width = 0;
    height = 0;
}

bool Texture::load( SDL_Renderer * renderer )
{
    unload();
    
    bool success = true;
    
    SDL_Surface * surface = IMG_Load( path.c_str() );
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    if ( texture == NULL)
    {
        printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        success = false;
    }
    else
    {
        width  = surface->w;
        height = surface->h;
    }
    
    SDL_FreeSurface( surface );
    
    return success;
}

void Texture::unload()
{
    if ( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;
    }
}

void Texture::render(SDL_Renderer * renderer, int x, int y, SDL_Rect * clip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, width, height };
    
    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w * scaleX;
        renderQuad.h = clip->h * scaleY;
    }
    
    //Render to screen
    SDL_RenderCopy( renderer, texture, clip, &renderQuad );
}


string Texture::getPath()
{
    return path;
}
SDL_Texture * Texture::getTexture()
{
    return texture;
}
