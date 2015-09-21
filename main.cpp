//
//  main.cpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 10/09/15.
//  Copyright (c) 2015 jrsc. All rights reserved.
//

#include "SDLApp.hpp"

int main( int argc, char * args[] )
{
    SDLApp * app = new SDLApp();
    
    if ( app->init() )
    {
        app->run();
    }
    
    app->close();
    
    return 0;
}