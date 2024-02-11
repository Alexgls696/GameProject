#pragma once
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

        for (int i = 0; i < countObstacles; i++)
        {
            obstacles.push_back(new RedDeadObstacles);
        }
        
        int Ax = rect.getPosition().x + 55;
        int Ay = rect.getPosition().y + 20;
        int Bx = rect.getPosition().x + rect.getSize().x - 340;
        int By = rect.getPosition().y + rect.getSize().y - 330;

        for (int i = 0; i < countObstacles; i++)
        {
            link1:
            obstacles[i]->getSprite().setPosition(rand() % (Bx - Ax + 1) + Ax, rand() % (By - Ay + 1) + Ay);
            for (int j = 0; j < obstacles.size(); j++)
            {
                if (i != j)
                {
                    if (obstacles[i]->getSprite().getGlobalBounds().intersects(obstacles[j]->getSprite().getGlobalBounds()))
                    {
                        i = 0;
                        goto link1;
                    }
                }
            }
            
        }
        
        for (int i = 0; i < countBonuses; i++)
        {
            bonuses.push_back(new RedDeadBonus);
        }
        Ax = rect.getPosition().x + 55;
        Ay = rect.getPosition().y + 40;
        Bx = rect.getPosition().x + rect.getSize().x - 55;
        By = rect.getPosition().y + rect.getSize().y - 40;

        for (int i = 0; i < countBonuses; i++)
        {
            link:
                bonuses[i]->getSprite().setPosition(rand() % (Bx - Ax + 1) + Ax, rand() % (By - Ay + 1) + Ay);
            for (int j = 0; j < countObstacles; j++)
            {
                if (bonuses[i]->getSprite().getGlobalBounds().intersects(obstacles[j]->getSprite().getGlobalBounds()))
                {
                    i = 0;
                    goto link;
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
    
};
