#pragma once
#include "../Library.h"
using namespace sf;
class Obstacles //Класс препятствий. Препятствия - наследники
{
protected:
    Texture texture;
    Sprite sprite;
    Image image;
    Vector2f position;
public:
    virtual void draw(sf::RenderWindow&window) = 0;
    Sprite&getSprite()
    {
        return sprite;
    }
};
