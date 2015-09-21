//
//  Transform.cpp
//  GemsArr
//
//  Created by José Ricardo de Sousa Coutinho on 16/09/15.
//  Copyright © 2015 jrsc. All rights reserved.
//

#include "Transform.hpp"

Transform::Transform()
{
    posX = 0.0;
    posY = 0.0;
    
    scaleX = 1.0;
    scaleY = 1.0;
    
    rotationZ = 0.0;
    
    width  = 0.0;
    height = 0.0;
}

float Transform::getPosX()
{
    return posX;
}
float Transform::getPosY()
{
    return posY;
}
float Transform::getScaleX()
{
    return scaleX;
}
float Transform::getScaleY()
{
    return scaleY;
}
float Transform::getRotationZ()
{
    return rotationZ;
}
int Transform::getWidth()
{
    return width;
}
int Transform::getHeight()
{
    return height;
}

void Transform::setPosX(float value)
{
    posX = value;
}
void Transform::setPosY(float value)
{
    posY = value;
}
void Transform::setScaleX(float value)
{
    scaleX = value;
}
void Transform::setScaleY(float value)
{
    scaleY = value;
}
void Transform::setRotationZ(float value)
{
    rotationZ = value;
}
void Transform::setWidth(int value)
{
    width = value;
}
void Transform::setHeight(int value)
{
    height = value;
}