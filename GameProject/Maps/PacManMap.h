#pragma once
#include "../Library.h"
#include "../Players//PlayerPacMan.h"
#include "../Maps/Map.h"

class PacManMap: public Map
{
public:
    PacManMap()
    {
        name="PacMan";
        rect.setFillColor(Color::Magenta);
        rect.setTexture(&texture);
    }
    void draw(RenderWindow& window) override
    {
        window.draw(rect);
    }
};
