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
        //sprite.setOrigin(sprite.getPosition().x + sprite.getTextureRect().width / 2, sprite.getPosition().y+sprite.getTextureRect().height/2); //изм
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(sprite);
    }
};