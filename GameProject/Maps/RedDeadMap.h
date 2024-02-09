#pragma once
#include "Map.h"

class RedDeadMap : public Map
{
public:
    RedDeadMap()
    {
        name="RedDeadMap";
        rect.setFillColor(Color::White);
        texture.loadFromFile("Textures/Fon_desert.jpg");
        rect.setTexture(&texture);
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(rect);
    }
};
