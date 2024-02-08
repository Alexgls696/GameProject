﻿#pragma once
#include "../Library.h"
using namespace sf;
class Object
{
public:
    Texture texture;
    Sprite sprite;
    RectangleShape rectangle_shape;
    Image image;
    Vector2f position;
public:
    virtual void draw(sf::RenderWindow&window) = 0;
    virtual void move(sf::RenderWindow&window) = 0;
    Sprite&getSprite()
    {
        return sprite;
    }
};
