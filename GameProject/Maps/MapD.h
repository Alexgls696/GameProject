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
};
