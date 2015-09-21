//
//  Font.cpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 15/09/15.
//  Copyright © 2015 jrsc. All rights reserved.
//

#include "Font.hpp"

Font::Font( string path ):Texture( path )
{
    font = NULL;
}

Font::~Font()
{
    unload();
}

bool Font::load()
{
    return load(35);
}

bool Font::load( int size )
{
    unload();
    
    bool success = true;
    
    // Open the font
    font = TTF_OpenFont( getPath().c_str(), size );
    
    if ( font == NULL)
    {
        printf( "Unable to load font from %s! SDL Error: %s\n", getPath().c_str(), SDL_GetError() );
        success = false;
    }
    
    return success;
}

void Font::unload()
{
    if ( font != NULL )
    {
        TTF_CloseFont( font );
        font = NULL;
    }
    
    if ( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;
    }
}

bool Font::createTextureFromText( SDL_Renderer * renderer, string text, SDL_Color color )
{
    //Get rid of preexisting texture
    if ( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;
    }
    
    bool success = true;
    
    //Render text surface
    SDL_Surface * textSurface = TTF_RenderText_Blended(font, text.c_str(), color );
    
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get texture dimensions
            width = textSurface->w;
            height = textSurface->h;
        }
        
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    
    return success;

}
