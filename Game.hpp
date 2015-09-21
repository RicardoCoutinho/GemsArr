//
//  Game.hpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 10/09/15.
//  Copyright © 2015 jrsc. All rights reserved.
//

#ifndef __GemsArr__Game__
#define __GemsArr__Game__

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>

#include "Texture.hpp"
#include "Music.hpp"
#include "Sound.hpp"
#include "Font.hpp"
#include "LButton.hpp"
#include "Animation.hpp"

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <dirent.h>
#define GetCurrentDir getcwd
#endif

using namespace std;

typedef unsigned short int usint;
typedef pair<usint, usint> point;
typedef set<point> list;

const usint GRIDSIZE   = 8;
const usint JEWELTYPES = 5;
const usint BASEVALUE  = 50;
const usint COMBVALUE  = 1;
const usint LEVLVALUE  = 0.5;

enum direction { TOP, LEFT, BOTTOM, RIGHT };

enum gameState { IDLE, ANIMATING, END };

class Game {
    
    usint grid[GRIDSIZE][GRIDSIZE];
    unsigned int score;
    usint combo;
    usint level;
    
public:
    
    gameState currentState;
    
    queue<Animation *> animations;
    
    vector<Texture *> backgrounds;
    vector<Texture *> jewels;
    vector<Music *>   music;
    vector<Sound *>   sounds;
    vector<Font *>    fonts;
    
    bool isJewelSelected;
    pair<usint,usint> jewelSelected;
    
    
    Game();
    ~Game();
    
    usint get(usint i, usint j);
    unsigned int getScore();
    
    void set(usint i, usint j, usint value);
    void set(usint ai, usint aj, usint bi, usint bj);
    void resetCombo();
    
    void init();
    void testInit();
    
    void close();
    
    void build();
    
    bool  move(usint ai, usint aj, usint bi, usint bj);
    bool  chain(usint i, usint j);
    
    // counts how many continuous jewels of same type
    usint check(usint type, direction dir, usint i, usint j);
    
    // removes continuous jewels of same type in a direction
    void  clear(usint type, direction dir, usint i, usint j);
    
    // shifts down all columns
    void shiftAll();
    
    // generate a random and valid jewel type
    usint generate();
    
    bool isChain(usint type, usint i, usint j);
    bool isThereAChain(usint & pI, usint & pJ);
    bool isValidType(usint i, usint j);
    
    // fetch all media related items in './media/' folder and stores in vectors
    bool fetchMedia();
    bool fetchBackgrounds();
    bool fetchJewels();
    bool fetchMusic();
    bool fetchSounds();
    bool fetchFonts();
    
    // loads pre-fetched media from respective vectors
    bool loadMedia(SDL_Renderer * renderer);
    bool loadBackgrounds(SDL_Renderer * renderer);
    bool loadJewels(SDL_Renderer * renderer);
    bool loadMusic();
    bool loadSounds();
    bool loadFonts();
    
    // gets a list of movable jewels
    list moveList();
    
    void addPoints(usint chainSizeX, usint chainSizeY);
    
    // shifts down column j
    bool shift(usint j);
    
    // swaps 2 adjacent jewels
    bool swap(usint ai, usint aj, usint bi, usint bj);
    
    string stringGrid();
    string stringMoveList(list moveList);
    
};

#endif /* defined(__GemsArr__Game__) */
