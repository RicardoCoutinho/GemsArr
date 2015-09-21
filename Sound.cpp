//
//  Sound.cpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 18/09/15.
//  Copyright © 2015 jrsc. All rights reserved.
//

#include "Sound.hpp"

Sound::Sound( string path )
{
    this->path = path;
    sound = NULL;
}
Sound::~Sound()
{
    path = "";
    unload();
}

bool Sound::load()
{
    unload();
    
    bool success = true;
    
    sound = Mix_LoadWAV( path.c_str() );
    
    if( sound == NULL )
    {
        printf( "Failed to load Sound from %s! SDL_mixer Error: %s\n", path.c_str(), Mix_GetError() );
        success = false;
    }
    
    return success;
}
void Sound::unload()
{
    if ( sound != NULL )
    {
        Mix_FreeChunk( sound );
        sound = NULL;
    }
}

void Sound::play()
{
    Mix_PlayChannel( -1, sound, 0 );
}

string Sound::getPath()
{
    return path;
}
Mix_Chunk * Sound::getSound()
{
    return sound;
}