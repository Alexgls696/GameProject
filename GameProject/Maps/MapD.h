#pragma once
#include "Map.h"
class MapD : public Map
{
public:
    MapD()
    {
        name="D";
        rect.setFillColor(Color::Cyan);
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(rect);
    }
    void drawBonuses(RenderWindow& window) override
    {
        for(int  i = 0; i < countBonuses; i++)
        {
            bonuses[i]->draw(window);
        }
    }
};
