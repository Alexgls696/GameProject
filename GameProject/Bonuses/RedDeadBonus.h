#pragma once
#include "Bonuses.h"
class RedDeadBonus : public Bonuses
{
public:
    RedDeadBonus()
    {
        image.loadFromFile("Textures/bonus_cowboy.png");
        image.createMaskFromColor(Color::White);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
       // sprite.setOrigin(sprite.getPosition().x + sprite.getTextureRect().width / 2, sprite.getPosition().y + sprite.getTextureRect().height / 2);
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(sprite);
    }
};
