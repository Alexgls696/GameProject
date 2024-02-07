#pragma once
#include "../Library.h"

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
