﻿#pragma once
#include "Map.h"

class MapB : public Map
{
public:
    MapB()
    {
        rect.setFillColor(Color::Red);
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(rect);
    }
};
