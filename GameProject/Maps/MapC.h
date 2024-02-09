#pragma once
#include "Map.h"

class MapC:public Map
{
public:
    MapC()
    {
        name="C";
        rect.setFillColor(Color::Blue);
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
