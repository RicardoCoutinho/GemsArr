//
//  LButton.cpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 16/09/15.
//  Copyright © 2015 jrsc. All rights reserved.
//

#include "LButton.hpp"

//SDL_Rect gSpriteClips[ BUTTON_STATE_TOTAL ];
//Texture gButtonSpriteSheetTexture;

LButton::LButton()
{
    position.x = 0;
    position.y = 0;
    size = 0;
    isDown = false;
    
    currentState = BUTTON_STATE_MOUSE_OUT;
}

void LButton::setPosition( int x, int y )
{
    position.x = x;
    position.y = y;
}

void LButton::setSize( int size )
{
    this->size = size;
}

void LButton::handleEvent( SDL_Event * e )
{
    //If mouse event happened
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );
        
        //Check if mouse is in button
        bool inside  = true;
        
        //Mouse is left of the button
        if( x < position.x )
        {
            inside = false;
        }
        //Mouse is right of the button
        else if( x > position.x + size )
        {
            inside = false;
        }
        //Mouse above the button
        else if( y < position.y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( y > position.y + size )
        {
            inside = false;
        }
        
        //Mouse is outside button
        if( !inside )
        {
            currentState = BUTTON_STATE_MOUSE_OUT;
        }
        //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch( e->type )
            {
                case SDL_MOUSEMOTION:
                    currentState = BUTTON_STATE_MOUSE_OVER_MOTION;
                    isDown = false;
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    currentState = BUTTON_STATE_MOUSE_DOWN;
                    isDown = true;
                    break;
                    
                case SDL_MOUSEBUTTONUP:
                    if ( isDown )
                    {
                        currentState = BUTTON_STATE_MOUSE_UP;
                    }
                    else
                    {
                        currentState = BUTTON_STATE_MOUSE_OUT;
                    }
                    break;
            }
        }
        
    }
}

void LButton::render( SDL_Renderer * renderer )
{
    //Show current button sprite
    //gButtonSpriteSheetTexture.render( position.x, position.y, &gSpriteClips[ currentSprite ] );
}


