#pragma once
#include "../Library.h"
class Bonuses
{
protected:
    Texture texture;
    Sprite sprite;
    RectangleShape rectangle_shape;
    Image image;
    Vector2f position;
public:
    virtual void draw(sf::RenderWindow&window) = 0;
    Sprite&getSprite()
    {
        return sprite;
    }
};
