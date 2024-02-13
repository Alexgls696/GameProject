#pragma once
#include "Bonuses.h"
class rabbitCarrotBonus : public Bonuses
{
public:
    rabbitCarrotBonus()
    {
        image.loadFromFile("Textures/carrot.png");
        image.createMaskFromColor(Color::White);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        //sprite.setOrigin(sprite.getPosition().x+sprite.getTextureRect().width/2,sprite.getPosition().y+sprite.getTextureRect().height/2);
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(sprite);
    }
    
};
class rabbitCabbageBonus : public Bonuses
{
public:
    rabbitCabbageBonus()
    {
        image.loadFromFile("Textures/cabbage.png");
        image.createMaskFromColor(Color::White);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        //sprite.setOrigin(sprite.getPosition().x+sprite.getTextureRect().width/2,sprite.getPosition().y+sprite.getTextureRect().height/2);
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(sprite);
    }
    
};
