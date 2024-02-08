#pragma once
#include "../Library.h"
#include "../Objects/PlayerPacMan.h"
#include "../Maps/Map.h"

class GeometryDashMap: public Map
{
public:
    GeometryDashMap()
    {
        texture.loadFromFile("Textures/good.png");
        rect.setFillColor(Color::White);
        rect.setTexture(&texture);
    }
    void draw(RenderWindow& window) override
    {
        window.draw(rect);
    }
};
