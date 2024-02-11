#pragma once
#include "Obstacles.h"
class InvisibilityObstacles : public Obstacles
{
public:
    InvisibilityObstacles(Texture* name)
    {
        image.createMaskFromColor(Color::White);
        sprite.setTexture(*name);
    }
    void draw(sf::RenderWindow& window) override
    {

    }
};
