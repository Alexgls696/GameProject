#pragma once
#include "Map.h"
#include "../Players/RedPacMan.h"
class MapC:public Map
{
public:
    MapC()
    {
        player = new PlayerRedPacMan;
        name="C";
        rect.setFillColor(Color::Blue);
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(rect);
    }
    Players*getPlayer() override
    {
        player = new PlayerRedPacMan();
        return  player;
    }
    void getBonusSoundPlay() override
    {
        
    }
};
