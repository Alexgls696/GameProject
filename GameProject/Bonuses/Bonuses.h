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
    bool flag_broke = true;
public:
    virtual void draw(sf::RenderWindow&window) = 0;
    Sprite&getSprite()
    {
        return sprite;
    }
    void setFlagBroke(bool flag_broke)
    {
        this->flag_broke = flag_broke;
    }
    bool getFlagBroke()
    {
        return flag_broke;
    }
};
