#pragma once
#include "Obstacles.h"
class PacManObstacles : public Obstacles
{
public:
    PacManObstacles()
    {
        image.loadFromFile("Textures/Barrier.png");
        image.createMaskFromColor(Color::White);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(sprite);
    }
};
