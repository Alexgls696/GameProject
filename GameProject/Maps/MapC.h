#pragma once
#include "Map.h"

class MapC:public Map
{
public:
    MapC()
    {
        rect.setFillColor(Color::Blue);
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(rect);
    }
};
