#pragma once
#include "Bonuses.h"
class PacMoney : public Bonuses
{
public:
    void draw(sf::RenderWindow& window) override
    {
        window.draw(sprite);
    }
};
