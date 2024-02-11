#pragma once
#include "../Library.h"
#include "../Obstacles/Obstacles.h"
using namespace sf;

class RedDeadObstacles : public Obstacles
{
public:
    RedDeadObstacles()
    {
        texture.loadFromFile("Textures/saloon.png");
        sprite.setTexture(texture);
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(sprite);
    }
};