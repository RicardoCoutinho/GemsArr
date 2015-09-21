//
//  Game.cpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 10/09/15.
//  Copyright © 2015 jrsc. All rights reserved.
//

#include "Game.hpp"

Game::Game()
{
    currentState = IDLE;
    
    score = 0;
    combo = 0;
    level = 1;
    
    init();
    //testInit();
    
    backgrounds.clear();
    jewels.clear();
    music.clear();
    sounds.clear();
    fonts.clear();
    
    isJewelSelected = false;
    jewelSelected = make_pair(0,0);
}
Game::~Game()
{
    close();
}

usint Game::get(usint i, usint j)
{
    return grid[i][j];
}

unsigned int Game::getScore()
{
    return score;
}

void Game::set(usint i, usint j, usint value)
{
    grid[i][j] = value;
}

void Game::set(usint ai, usint aj, usint bi, usint bj)
{
    usint temp = grid[ai][aj];
    grid[ai][aj] = grid[bi][bj];
    grid[bi][bj] = temp;
}

void Game::resetCombo()
{
    this->combo = 0;
}

void Game::init()
{
    for (int i=0; i<GRIDSIZE; i++)
        for (int j=0; j<GRIDSIZE; j++)
            grid[i][j] = GRIDSIZE;
        
    build();
}

// pre-built board for testing
void Game::testInit()
{
    grid[0][0] =3;
    grid[0][1] =1;
    grid[0][2] =4;
    grid[0][3] =5;
    grid[0][4] =1;
    grid[0][5] =2;
    grid[0][6] =2;
    grid[0][7] =4;
    
    grid[1][0] =4;
    grid[1][1] =4;
    grid[1][2] =2;
    grid[1][3] =2;
    grid[1][4] =5;
    grid[1][5] =4;
    grid[1][6] =1;
    grid[1][7] =1;
    
    grid[2][0] =5;
    grid[2][1] =1;
    grid[2][2] =2;
    grid[2][3] =1;
    grid[2][4] =5;
    grid[2][5] =2;
    grid[2][6] =3;
    grid[2][7] =5;
    
    grid[3][0] =5;
    grid[3][1] =2;
    grid[3][2] =5;
    grid[3][3] =5;
    grid[3][4] =1;
    grid[3][5] =5;
    grid[3][6] =2;
    grid[3][7] =1;
    
    grid[4][0] =4;
    grid[4][1] =1;
    grid[4][2] =4;
    grid[4][3] =2;
    grid[4][4] =5;
    grid[4][5] =3;
    grid[4][6] =1;
    grid[4][7] =3;
    
    grid[5][0] =4;
    grid[5][1] =2;
    grid[5][2] =1;
    grid[5][3] =5;
    grid[5][4] =1;
    grid[5][5] =5;
    grid[5][6] =1;
    grid[5][7] =5;
    
    grid[6][0] =3;
    grid[6][1] =3;
    grid[6][2] =4;
    grid[6][3] =4;
    grid[6][4] =3;
    grid[6][5] =1;
    grid[6][6] =3;
    grid[6][7] =3;
    
    grid[7][0] =1;
    grid[7][1] =3;
    grid[7][2] =5;
    grid[7][3] =1;
    grid[7][4] =5;
    grid[7][5] =4;
    grid[7][6] =5;
    grid[7][7] =1;
}

// cleaning all the vectors
void Game::close()
{
    for (auto it = backgrounds.begin(); it != backgrounds.end(); ++it)
    {
        delete *it;
    }
    backgrounds.clear();
    
    for (auto it = jewels.begin(); it != jewels.end(); ++it)
    {
        delete *it;
    }
    jewels.clear();
    
    for (auto it = music.begin(); it != music.end(); ++it)
    {
        delete *it;
    }
    music.clear();
    
    for (auto it = sounds.begin(); it != sounds.end(); ++it)
    {
        delete *it;
    }
    sounds.clear();
    
    for (auto it = fonts.begin(); it != fonts.end(); ++it)
    {
        delete *it;
    }
    fonts.clear();
}

// building board with difficulty relative to randomness and level
void Game::build()
{
    srand((unsigned int) time(0));
    usint minMoves, maxMoves, nMoves;
    
    minMoves = 3;
    maxMoves = 30 - level;
    
    do
    {
        for (usint i=0; i<GRIDSIZE; i++)
        {
            for (usint j=0; j<GRIDSIZE; j++)
            {
                do
                {
                    grid[i][j] = generate();
                }
                while ( isChain(grid[i][j],i,j) );
            }
        }
        
        nMoves = (usint) moveList().size();
    }
    while ( !(nMoves >= minMoves && nMoves <= maxMoves) );
}


bool Game::move(usint ai, usint aj, usint bi, usint bj)
{
    bool success = false;
    
    if ( swap(ai,aj,bi,bj) )
    {
        if ( isChain(grid[ai][aj], ai, aj) )
        {
            chain(ai, aj);
            success = true;
        }
    
        if ( isChain(grid[bi][bj], bi, bj) )
        {
            chain(bi, bj);
            success = true;
        }
    
        if (!success)
        {
            swap(ai,aj,bi,bj);
        }
    }
    
    return success;
}


// bottom up from affected cells
// from left-right to bot-up
bool Game::chain(usint i, usint j)
{
    bool success = false;
    
    usint
        chainSizeX, chainSizeY,
        type  = grid[i][j],
        left  = check(type, LEFT,  i, j),
        right = check(type, RIGHT, i, j);
    
    chainSizeX = left + right - 1;
    
    if ( chainSizeX >= 3 )
    {
        clear(type, LEFT,  i, j-1);
        clear(type, RIGHT, i, j+1);
        
        success = true;
    }
    
    usint
        top    = check(type, TOP,    i, j),
        bottom = check(type, BOTTOM, i, j);
    
    chainSizeY = top + bottom - 1;
    
    if ( chainSizeY >= 3 )
    {
        clear(type, TOP,    i-1, j);
        clear(type, BOTTOM, i+1, j);
        
        success = true;
    }
    
    if ( success )
    {
        set(i, j, 0);
        addPoints( chainSizeX, chainSizeY );
        
        cout << "Score: " << score << endl;
    }
    
    return success;
}

// checks the size of a chain
usint Game::check(usint type, direction dir, usint i, usint j)
{
    if ( i >= GRIDSIZE || j >= GRIDSIZE || grid[i][j] != type )
    {
        return 0;
    }
    
    switch ( dir )
    {
        case direction::LEFT:
            return check(type,dir,i,j-1) + 1;
            break;
            
        case direction::RIGHT:
            return check(type,dir,i,j+1) + 1;
            break;
            
        case direction::TOP:
            return check(type,dir,i-1,j) + 1;
            break;
            
        case direction::BOTTOM:
            return check(type,dir,i+1,j) + 1;
            break;
    }
    
    return 0;
}


// clear chained cells
void Game::clear(usint type, direction dir, usint i, usint j)
{
    if ( i < 0 || i >= GRIDSIZE || j < 0 || j >= GRIDSIZE || grid[i][j] != type )
    {
        return;
    }
    
    grid[i][j]=0;
    
    switch ( dir )
    {
        case direction::LEFT:
            clear(type,dir,i,j-1);
            break;
            
        case direction::RIGHT:
            clear(type,dir,i,j+1);
            break;
            
        case direction::TOP:
            clear(type,dir,i-1,j);
            break;
            
        case direction::BOTTOM:
            clear(type,dir,i+1,j);
            break;
    }
    
}

void Game::shiftAll()
{
    usint column;
    
    for (int j=0; j<GRIDSIZE; j++)
    {
        column = shift(j);
        //cout << "Shifted column: " << j << " = " << column << endl;
    }
}

// generates an object in range of [1,TYPE]
usint Game::generate()
{
    return rand() % JEWELTYPES + 1;
}


// verifies if there's a chain of at least 3
bool Game::isChain(usint type, usint i, usint j)
{
    return ( type>0 && type<=JEWELTYPES && i<GRIDSIZE && j<GRIDSIZE &&
            (
            (check(type,LEFT,i,j) + check(type,RIGHT, i,j) - 1) > 2 ||
            (check(type,TOP, i,j) + check(type,BOTTOM,i,j) - 1) > 2
            )
           );
}

// verifies if there's at least one chain
bool Game::isThereAChain(usint & pI, usint & pJ)
{
    for (int i=GRIDSIZE-1; i>=0; i--)
    {
        for (int j=0; j<GRIDSIZE; j++)
        {
            if ( isChain(grid[i][j],i,j) )
            {
                pI = i;
                pJ = j;
                return true;
            }
        }
    }
    
    return false;
}

bool Game::isValidType(usint i, usint j)
{
    return ( i<GRIDSIZE && j<GRIDSIZE && grid[i][j] > 0 && grid[i][j] <= JEWELTYPES );
}

// adds points to score relative to chainSize
void Game::addPoints(usint chainSizeX, usint chainSizeY)
{
    combo++;
    usint
        pointsX    = (chainSizeX > 2) ? (chainSizeX-2): 0,
        pointsY    = (chainSizeY > 2) ? (chainSizeY-2): 0,
        multiplier = (pointsX + pointsY > 5) ? 2 : 1;
    
    score += ( (pointsX + pointsY) * BASEVALUE) * multiplier /* * combo * COMBVALUE*/;
}


bool Game::shift(usint j)
{
    if (j>=GRIDSIZE)
    {
        return false;
    }
    
    usint target;
    
    for (target=GRIDSIZE-1; isValidType(target, j); target--) ;
    
    if ( target>=GRIDSIZE )
    {
        return false;
    }
    
    usint gap = 1, next;
    
    for (next=target-1; next<GRIDSIZE && !isValidType(next, j); next--, gap++) ;
    
    if ( isValidType(next,j) )
    {
        // shift existing cells down
        for ( ; next<GRIDSIZE && target<GRIDSIZE; next--, target--)
        {
            grid[target][j] = grid[next][j];
            // add to animation queue, (target -> i , j) of type grid[target][j]
        }
    }
    
    // fill left over empty cells
    for ( ; gap<GRIDSIZE; gap--)
    {
        grid[gap][j] = generate();
        // add to animation queue, (outsidebox -> gap , j) of type grid[gap][j]
    }
    
    return true;
}

// swaps adjacent elements if they make a chain
bool Game::swap(usint ai, usint aj, usint bi, usint bj)
{
    if ( ai<GRIDSIZE && aj<GRIDSIZE && bi<GRIDSIZE && bj<GRIDSIZE &&
        ((ai == bi && abs(aj-bj) == 1) || (aj == bj && abs(ai-bi) == 1)) )
    {
        set(ai, aj, bi, bj);
        
        return true;
    }
    
    return false;
}

bool Game::fetchMedia()
{
    return
        fetchBackgrounds() &&
        fetchJewels() &&
        fetchMusic() &&
        fetchSounds() &&
        fetchFonts();
}

bool Game::fetchBackgrounds()
{
    cout << "Fetching backgrounds...";
    
    bool success = true;
    Texture * tex = NULL;
    
    regex regexp { REGEX_TEXTURE , regex_constants::ECMAScript };
    
    ostringstream path;
    
    DIR *     dir;
    dirent *  pdir;
    
    dir = opendir( "./media/background/" );     // open current directory
    
    while ( (pdir = readdir(dir)) )
    {
        // clean path ss
        path.clear();
        path.str( string() );
        
        path << "media/background/" << pdir->d_name;
        
        if ( regex_match( pdir->d_name, regexp ) )
        {
            tex = new Texture( path.str() );
            
            if ( tex == NULL )
            {
                success = false;
            }
            else
            {
                backgrounds.push_back( tex );
            }
            
        }
    }
    
    closedir(dir);
    
    cout << ((success) ? " ok." : " woops! ") << endl ;
    
    return success;
}

bool Game::fetchJewels()
{
    cout << "Fetching jewels...";
    
    bool success = true;
    Texture * tex = NULL;
    
    regex regexp { REGEX_TEXTURE , regex_constants::ECMAScript };
    
    ostringstream path;
    
    DIR *     dir;
    dirent *  pdir;
    
    dir = opendir( "./media/jewel/" );     // open current directory
    
    while ( (pdir = readdir(dir)) )
    {
        // clean path ss
        path.clear();
        path.str( string() );
        
        path << "media/jewel/" << pdir->d_name;
        
        if ( regex_match( pdir->d_name, regexp ) )
        {
            tex = new Texture( path.str() );
            
            if ( tex == NULL )
            {
                success = false;
            }
            else
            {
                tex->setScaleX( 0.5 );
                tex->setScaleY( 0.5 );
                jewels.push_back( tex );
            }
            
        }
    }
    
    closedir(dir);
    
    cout << ((success) ? " ok." : " woops! ") << endl ;
    
    return success;
}

bool Game::fetchMusic()
{
    cout << "Fetching music...";
    
    bool success = true;
    Music * mus = NULL;
    
    regex regexp { REGEX_MUSIC , regex_constants::ECMAScript };
    
    ostringstream path;
    
    DIR *     dir;
    dirent *  pdir;
    
    dir = opendir( "./media/music/" );     // open current directory
    
    while ( (pdir = readdir(dir)) )
    {
        // clean path ss
        path.clear();
        path.str( string() );
        
        path << "media/music/" << pdir->d_name;
        
        if ( regex_match( pdir->d_name, regexp ) )
        {
            mus = new Music( path.str() );
            
            if ( mus == NULL )
            {
                success = false;
            }
            else
            {
                music.push_back( mus );
            }
            
        }
    }
    
    closedir(dir);
    
    cout << ((success) ? " ok." : " woops! ") << endl ;
    
    return success;
}

bool Game::fetchSounds()
{
    cout << "Fetching sounds...";
    
    bool success = true;
    Sound * sound = NULL;
    
    regex regexp { REGEX_SOUND , regex_constants::ECMAScript };
    
    ostringstream path;
    
    DIR *     dir;
    dirent *  pdir;
    
    dir = opendir( "./media/sound/" );     // open current directory
    
    while ( (pdir = readdir(dir)) )
    {
        // clean path ss
        path.clear();
        path.str( string() );
        
        path << "media/sound/" << pdir->d_name;
        
        if ( regex_match( pdir->d_name, regexp ) )
        {
            sound = new Sound( path.str() );
            
            if ( sound == NULL )
            {
                success = false;
            }
            else
            {
                sounds.push_back( sound );
            }
            
        }
    }
    
    closedir(dir);
    
    cout << ((success) ? " ok." : " woops! ") << endl ;
    
    return success;
}

bool Game::fetchFonts()
{
    cout << "Fetching fonts...";
    
    bool success = true;
    Font * font = NULL;
    
    regex regexp { REGEX_FONT , regex_constants::ECMAScript };
    
    ostringstream path;
    
    DIR *     dir;
    dirent *  pdir;
    
    dir = opendir( "./media/font/" );     // open current directory
    
    while ( (pdir = readdir(dir)) )
    {
        // clean path ss
        path.clear();
        path.str( string() );
        
        path << "media/font/" << pdir->d_name;
        
        if ( regex_match( pdir->d_name, regexp ) )
        {
            font = new Font( path.str() );
            
            if ( font == NULL )
            {
                success = false;
            }
            else
            {
                fonts.push_back( font );
            }
            
        }
    }
    
    closedir(dir);
    
    cout << ((success) ? " ok." : " woops! ") << endl ;
    
    return success;
}

bool Game::loadMedia(SDL_Renderer * renderer)
{
    return
        loadBackgrounds(renderer) &&
        loadJewels(renderer) &&
        loadMusic() &&
        loadSounds() &&
        loadFonts();
}

bool Game::loadBackgrounds(SDL_Renderer * renderer)
{
    cout << "Loading backgrounds...";
    
    bool success = true;
    
    vector<Texture *>::iterator it,ite;
    it  = backgrounds.begin();
    ite = backgrounds.end();
    
    for( ; it != ite; ++it)
    {
        if ( (*it)->load( renderer ) == false )
        {
            success = false;
        }
    }
    
    cout << ((success) ? " ok." : " woops! ") << endl ;
    
    return success;
}
bool Game::loadJewels(SDL_Renderer * renderer)
{
    cout << "Loading jewels...";
    
    bool success = true;
    
    vector<Texture *>::iterator it,ite;
    it  = jewels.begin();
    ite = jewels.end();
    
    for( ; it != ite; ++it)
    {
        if ( (*it)->load( renderer ) == false )
        {
            success = false;
        }
    }
    
    cout << ((success) ? " ok." : " woops! ") << endl ;
    
    return success;
}
bool Game::loadMusic()
{
    cout << "Loading music...";
    
    bool success = true;
    
    vector<Music *>::iterator it,ite;
    it  = music.begin();
    ite = music.end();
    
    for( ; it != ite; ++it)
    {
        if ( (*it)->load() == false )
        {
            success = false;
        }
    }
    
    cout << ((success) ? " ok." : " woops! ") << endl ;
    
    return success;
}
bool Game::loadSounds()
{
    cout << "Loading sounds...";
    
    bool success = true;
    
    vector<Sound *>::iterator it,ite;
    it  = sounds.begin();
    ite = sounds.end();
    
    for( ; it != ite; ++it)
    {
        if ( (*it)->load() == false )
        {
            success = false;
        }
    }
    
    cout << ((success) ? " ok." : " woops! ") << endl ;
    
    return success;
}

bool Game::loadFonts()
{
    cout << "Loading fonts...";
    
    bool success = true;
    
    vector<Font *>::iterator it,ite;
    it  = fonts.begin();
    ite = fonts.end();
    
    for( ; it != ite; ++it)
    {
        if ( (*it)->load() == false )
        {
            success = false;
        }
    }
    
    cout << ((success) ? " ok." : " woops! ") << endl ;
    
    return success;
}

// get movable cells
list Game::moveList()
{
    list moveList;
    moveList.clear();
    
    for (usint i=0; i < GRIDSIZE; i++)
    {
        for (usint j=0; j < GRIDSIZE; j++)
        {
            
            // Swap UP
            if ( swap(i,j,i-1,j) )
            {
                if ( isChain(grid[i][j],i,j) || isChain(grid[i-1][j],i-1,j) )
                {
                    moveList.insert( make_pair(i,j) );
                    moveList.insert( make_pair(i-1,j) );
                    //cout << "movable : (" << i << "," << j << ") -> (" << i-1 << "," << j << ")\n";
                }
                
                swap(i,j,i-1,j);
            }
            
            // Swap DOWN
            if ( swap(i,j,i+1,j) )
            {
                if ( isChain(grid[i][j],i,j) || isChain(grid[i+1][j],i+1,j) )
                {
                    moveList.insert( make_pair(i,j) );
                    moveList.insert( make_pair(i+1,j) );
                    //cout << "movable : (" << i << "," << j << ") -> (" << i+1 << "," << j << ")\n";
                }
                
                swap(i,j,i+1,j);
            }
            
            // Swap LEFT
            if ( swap(i,j,i,j-1) )
            {
                if ( isChain(grid[i][j],i,j) || isChain(grid[i][j-1],i,j-1) )
                {
                    moveList.insert( make_pair(i,j) );
                    moveList.insert( make_pair(i,j-1) );
                    //cout << "movable : (" << i << "," << j << ") -> (" << i << "," << j-1 << ")\n";
                }
                
                swap(i,j,i,j-1);
            }
            
            // Swap RIGHT
            if ( swap(i,j,i,j+1) )
            {
                if ( isChain(grid[i][j],i,j) || isChain(grid[i][j+1],i,j+1) )
                {
                    moveList.insert( make_pair(i,j) );
                    moveList.insert( make_pair(i,j+1) );
                    //cout << "movable : (" << i << "," << j << ") -> (" << i << "," << j+1 << ")\n";
                }
                
                swap(i,j,i,j+1);
            }
            
        }
    }
    
    //cout << "Moves left: " << moveList.size() << endl;
    
    return moveList;
}

// grid to string
string Game::stringGrid()
{
    ostringstream oss;
    
    oss << "  \\j";
    
    for (usint j=0; j<GRIDSIZE; j++)
    {
        oss << " " << j;
    }
    
    oss << "\n i \\";
    
    for (usint j=0; j<GRIDSIZE; j++)
    {
        oss << " ■";
    }
    
    oss << endl;
    
    for (usint i=0; i<GRIDSIZE; i++)
    {
        oss << " " << i << " ■";
        
        for (usint j=0; j<GRIDSIZE; j++)
        {
            //oss << "grid(" << i << "," << j << ") <- " << grid[i][j] << endl;
            oss << " " << grid[i][j];
        }
        
        oss << endl;
    }
    
    oss << endl;
    
    return oss.str();
}

// movable cells in string
string Game::stringMoveList(list moveList)
{
    ostringstream oss;
    
    oss << "Found " << moveList.size() << " movable cells:\n";
    
    list::iterator
        it  = moveList.begin(),
        ite = moveList.end();
    
    for(; it != ite; ++it)
    {
        oss << "(" << it->first << "," << it->second << ") , ";
    }
    
    oss << endl << endl;
    
    return oss.str();
}
