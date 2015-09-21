//
//  SDLApp.cpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 10/09/15.
//  Copyright © 2015 jrsc. All rights reserved.
//

#include "SDLApp.hpp"


SDLApp::SDLApp()
{
    window  = NULL;
    game = NULL;
}

// initialize application display variables 
bool SDLApp::init()
{
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
            success = false;
        }
        
        //Create window
        window = SDL_CreateWindow( "GemsArr", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
            if( renderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                
                //Initialize SDL_mixer
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
                
                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
            }
            
            game = new Game();
            
            // fetches media from respective folders
            game->fetchMedia();
            
            // loads all the media required
            game->loadMedia( renderer );
            
            // prints board
            cout << game->stringGrid();
            
            // prints available moves
            cout << game->stringMoveList( game->moveList() );
            
            return true;
        }
    }
    
    return success;
}

// close and delete every allocated asset
void SDLApp::close()
{
    delete game;
    game = NULL;
    
    //Destroy window
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window   = NULL;
    renderer = NULL;
    
    //Quit SDL subsystems
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

// run application
void SDLApp::run()
{
    game->music.front()->play();
    
    SDL_Texture * backgroundTex = game->backgrounds.front()->getTexture();
    
    Texture * jewelTex1 = game->jewels.at(0);
    
    usint
          screenSize = min(SCREEN_WIDTH,SCREEN_HEIGHT),
          gridSize   = (screenSize * 4 / 5),
    
          gridStartX = (SCREEN_WIDTH - gridSize - gridSize/8),
          gridStartY = (SCREEN_HEIGHT - gridSize - gridSize/8),
    
          cellSize   = gridSize / 8,
          cellArea   = cellSize - 1,
          jewelSize  = jewelTex1->getWidth() * jewelTex1->getScaleX(),
          jewelStart = (usint) ((cellSize - jewelSize) / 2) + 1;
    
    SDL_Rect jewelPos;
    jewelPos.w = 70;
    jewelPos.h = 70;
    jewelPos.x = 0;
    jewelPos.y = 0;
    
    //Main loop flag
    bool quit = false;
    
    //Event handler
    SDL_Event e;
    
    LButton mArray[8][8];
    
    for (usint i=0; i<GRIDSIZE; i++)
    {
        for (usint j=0; j<GRIDSIZE; j++)
        {
            mArray[i][j].setPosition( gridStartX + cellSize * j + 1, gridStartY + cellSize * i + 1 );
            mArray[i][j].setSize( cellArea );
        }
    }
    
    //The frames per second timer
    LTimer fpsTimer;
    
    //The frames per second cap timer
    LTimer capTimer;
    
    float avgFPS;
    
    //In memory text stream
    std::stringstream timeText, scoreText, endText;
    
    //Start counting frames per second
    int countedFrames = 0, frameTicks;
    fpsTimer.start();
    
    bool keyDown;
    
    usint pI,pJ, jewel;
    
    SDL_Rect fillRect, cell;
    
    Font * scoreFont = game->fonts.front();
    
    bool clickingOn = false;
    
    Animation * animation;
    
    //game->animations.push( new Slide(60, game->jewels.front(), make_pair(0,0), make_pair(0, 480)) );
    
    //While application is running
    while( !quit )
    {
        countedFrames++;
        keyDown = false;
        
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            switch( e.type )
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    keyDown = true;
                    break;
                case SDL_KEYUP:
                    keyDown = false;
                    break;
                default:
                    break;
            }
        }
        if ( keyDown )
            printf("Key down!\n");
        
        
        //Calculate and correct fps
        avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
        
        //Set text to be rendered
        //timeText.str(std::string());
        //timeText << "Average Frames Per Second (With Cap): " << avgFPS << endl;
        //cout << timeText.str().c_str() << endl;
        
        scoreText.str(std::string());
        scoreText << "Score: " << game->getScore();
        
        if( !scoreFont->createTextureFromText( renderer, scoreText.str(), {0xFF,0xFF,0xFF,0xFF}))
        {
            printf( "Unable to render FPS texture!\n" );
        }
        
        //Clear screen
        SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );
        SDL_RenderClear( renderer );
        
        //Apply the image
        SDL_RenderCopy( renderer, backgroundTex, NULL, NULL );
        SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_BLEND );
        
        // Draw text
        fillRect = {0, 0, scoreFont->getWidth(), scoreFont->getHeight() };
        scoreFont->render(renderer, 40, 100, &fillRect);
        
        // displays jewels on board
        for (usint i=0; i<GRIDSIZE; i++)
        {
            for (usint j=0; j<GRIDSIZE; j++)
            {
                mArray[i][j].handleEvent( &e );
                
                switch ( game->currentState )
                {
                    case IDLE:
                        if (!game->animations.empty()){
                            game->currentState = ANIMATING;
                            break;
                        }
                        
                        if ( mArray[i][j].currentState == BUTTON_STATE_MOUSE_DOWN )
                        {
                            clickingOn = true;
                        }
                            
                        if ( mArray[i][j].currentState == BUTTON_STATE_MOUSE_UP && clickingOn )
                        {
                            clickingOn = false;
                            
                            if ( game->isValidType(i,j) )
                            {
                                if ( game->isJewelSelected && game->move(i, j, game->jewelSelected.first, game->jewelSelected.second) )
                                {
                                    
                                    // plays sound when move is made
                                    if (game->sounds.size() > 0)
                                    {
                                        game->sounds.at( rand() % game->sounds.size() )->play();
                                    }
                                    
                                    game->shiftAll();
                                    
                                    while ( game->isThereAChain(pI,pJ) ) // is chains
                                    {
                                        if ( !game->chain(pI, pJ) )
                                            cout << "WOOPS NO CHAIN HERE!!!";
                                        game->shiftAll();
                                    }
                                    
                                    game->resetCombo();
                                    
                                    if ( game->moveList().size() == 0 )
                                    {
                                        cout << "GAME OVER!" << endl;
                                        quit = true;
                                    }
                                    
                                    game->isJewelSelected = false;
                                    
                                }
                                else
                                {
                                    game->isJewelSelected = true;
                                    game->jewelSelected = make_pair(i,j);
                                }
                            }
                        
                            
                        }
                        
                        if ( game->isJewelSelected && i == game->jewelSelected.first && j == game->jewelSelected.second )
                        {
                            cell = { mArray[i][j].position.x, mArray[i][j].position.y, cellArea, cellArea };
                            SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
                            SDL_RenderFillRect( renderer, &cell );
                        }
                        else
                        {
                            if ( mArray[i][j].currentState == BUTTON_STATE_MOUSE_OVER_MOTION )
                            {
                                cell = { mArray[i][j].position.x, mArray[i][j].position.y, cellArea, cellArea};
                                SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
                                SDL_RenderFillRect( renderer, &cell );
                            }
                            else if ( mArray[i][j].currentState == BUTTON_STATE_MOUSE_DOWN )
                            {
                                cell = { mArray[i][j].position.x, mArray[i][j].position.y, cellArea, cellArea };
                                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0x00, 0xFF );
                                SDL_RenderFillRect( renderer, &cell );
                            }
                            else if ( mArray[i][j].currentState == BUTTON_STATE_MOUSE_UP )
                            {
                                cell = { mArray[i][j].position.x, mArray[i][j].position.y, cellArea, cellArea };
                                SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );
                                SDL_RenderFillRect( renderer, &cell );
                            }
                            
                        }
                        
                        break;
                        
                    case ANIMATING:
                        
                        if ( !game->animations.empty() )
                        {
                            // Draw animations here
                            
                            
                            animation = game->animations.front();
                            
                            animation->render( renderer, &jewelPos );
                            
                            if ( animation->animationHasEnded() )
                            {
                                game->animations.pop();
                            }
                            
                            //game->animations.pop();
                            
                            
                        } else
                        {
                            game->currentState = IDLE;
                        }
                        
                        break;
                    
                    case END:
                        break;
                        
                    default:
                        break;
                }
                
                
                jewel = game->get(i,j) - 1;
                
                if ( jewel >= 0 && jewel <= JEWELTYPES )
                {
                    game->jewels.at( jewel )->render(renderer,
                                                            gridStartX + jewelStart + cellSize * j,
                                                            gridStartY + jewelStart + cellSize * i,
                                                            &jewelPos);
                }
                
            }
        }
        
        //Update the surface
        SDL_UpdateWindowSurface( window );
        
        //Update screen
        SDL_RenderPresent( renderer );
        
        
        //If frame finished early
        frameTicks = capTimer.getTicks();
        if( frameTicks < SCREEN_TICK_PER_FRAME )
        {
            //Wait remaining time
            SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
        }
        
        
    }
    

}
