#pragma once
#include "../Library.h"
#include "../Players//PlayerPacMan.h"
#include "../Maps/Map.h"

class PacManMap: public Map
{
public:
    PacManMap()
    {
        name="PacManMap";
        rect.setFillColor(Color::White);
        texture.loadFromFile("Textures//PacManMap.jpg");
        rect.setTexture(&texture);
    }
    void draw(RenderWindow& window) override
    {
        window.draw(rect);
    }
};
