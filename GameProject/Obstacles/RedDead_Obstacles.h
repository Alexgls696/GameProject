#pragma once
#include "../Library.h"
#include "../Obstacles/Obstacles.h"
using namespace sf;

class RedDeadObstacles : public Obstacles
{
public:
    RedDeadObstacles()
    {
        texture.loadFromFile("Textures/saloon2.png");
        sprite.setTexture(texture);
        //sprite.setOrigin(sprite.getPosition().x + sprite.getTextureRect().width / 2, sprite.getPosition().y+sprite.getTextureRect().height/2); //изм
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(sprite);
    }
};

//class RedDeadObstacles2 : public Obstacles
//{
//public:
//    RedDeadObstacles2()
//    {
//        texture.loadFromFile("Textures/Cactus.png");
//        sprite.setTexture(texture);
//        //sprite.setOrigin(sprite.getPosition().x + sprite.getTextureRect().width / 2, sprite.getPosition().y+sprite.getTextureRect().height/2); //изм
//    }
//    void draw(sf::RenderWindow& window) override
//    {
//        window.draw(sprite);
//    }
//};