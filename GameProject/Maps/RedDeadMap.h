﻿#pragma once
#include "../Library.h"
#include "../Players//PlayerCowboy.h"
#include "../Maps/Map.h"
#include "../Bonuses/RedDeadBonus.h"
#include "../Obstacles/RedDead_Obstacles.h"

class RedDeadMap : public Map
{
public:
    RedDeadMap()
    {
        countBonuses = 3;
        countObstacles = 1;
        for (int i = 0; i < countBonuses; i++)
        {
            bonuses.push_back(new RedDeadBonus);
        }
        int Ax = rect.getPosition().x + 55;
        int Ay = rect.getPosition().y + 20;
        int Bx = rect.getPosition().x + rect.getSize().x - 55;
        int By = rect.getPosition().y + rect.getSize().y - 20;

        for (int i = 0; i < countBonuses; i++)
        {
        link:
            bonuses[i]->getSprite().setPosition(rand() % (Bx - Ax + 1) + Ax, rand() % (By - Ay + 1) + Ay);
            for (int j = 0; j < countBonuses; j++)
            {
                if (i != j)
                {
                    if (bonuses[i]->getSprite().getGlobalBounds().intersects(bonuses[j]->getSprite().getGlobalBounds()))
                    {
                        i = 0;
                        goto link;
                    }
                }
            }
        }

        for (int i = 0; i < countObstacles; i++)
        {
            obstacles.push_back(new RedDeadObstacles);
        }

        Ax = rect.getPosition().x + 55;
        Ay = rect.getPosition().y + 20;
        Bx = rect.getPosition().x + rect.getSize().x - 276;
        By = rect.getPosition().y + rect.getSize().y - 160;

        for (int i = 0; i < countObstacles; i++)
        {
            link1:
                obstacles[i]->getSprite().setPosition(rand() % (Bx - Ax + 1) + Ax, rand() % (By - Ay + 1) + Ay);
            for (int j = 0; j < countBonuses; j++)
            {
                if (i != j)
                {
                    if (obstacles[i]->getSprite().getGlobalBounds().intersects(bonuses[j]->getSprite().getGlobalBounds()))
                    {
                        i = 0;
                        goto link1;
                    }
                }
            }
        }

        name="RedDeadMap";
        rect.setFillColor(Color::White);
        texture.loadFromFile("Textures/Fon_desert.jpg");
        rect.setTexture(&texture);
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(rect);
    }
    
    void drawBonuses(RenderWindow& window) override
    {
        for(int  i = 0; i < countBonuses; i++)
        {
            bonuses[i]->draw(window);
        }
    }
};
