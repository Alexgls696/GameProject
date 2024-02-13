#pragma once
#include "Obstacles.h"
class rabbitObstacles : public Obstacles
{
public:
    rabbitObstacles()
    {
        image.loadFromFile("Textures/barrierRabbit.png");
        image.createMaskFromColor(Color::White);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
       // sprite.setOrigin(sprite.getPosition().x+sprite.getTextureRect().width/2,sprite.getPosition().y+sprite.getTextureRect().height/2);
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(sprite);
    }
};
