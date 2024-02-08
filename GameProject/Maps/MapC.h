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
};
