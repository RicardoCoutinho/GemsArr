//
//  Transform.hpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 16/09/15.
//  Copyright © 2015 jrsc. All rights reserved.
//

#ifndef __GemsArr__Transform__
#define __GemsArr__Transform__

#include <stdio.h>

class Transform
{
    
protected:
    
    float posX;
    float posY;
    
    float scaleX;
    float scaleY;
    
    float rotationZ;
    
    int width;
    int height;
    
public:
    
    Transform();
    Transform(float scaleX, float scaleY);
    
    float getPosX();
    float getPosY();
    float getScaleX();
    float getScaleY();
    float getRotationZ();
    int getWidth();
    int getHeight();
    
    void setPosX(float value);
    void setPosY(float value);
    void setScaleX(float value);
    void setScaleY(float value);
    void setRotationZ(float value);
    void setWidth(int value);
    void setHeight(int value);
};

#endif /* defined(__GemsArr__Transform__) */
