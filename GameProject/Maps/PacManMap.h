#pragma once
#include "../Library.h"
#include "../Players//PlayerPacMan.h"
#include "../Maps/Map.h"
#include "../Obstacles/PacManObstacles.h"

class PacManMap : public Map
{
public:
    PacManMap()
    {
        countBonuses = 6;
        countObstacles = 6;

        for (int i = 0; i < countObstacles; i++)
        {
            obstacles.push_back(new PacManObstacles);
            int rotationAngle[] = {0,90};
            int A = 5; int B = 10;
            double scale = rand()%(B-A+1)+A;
            obstacles[i]->getSprite().setScale(scale/10,scale/10);
            obstacles[i]->getSprite().setOrigin(obstacles[i]->getSprite().getPosition().x+texture.getSize().x,obstacles[i]->getSprite().getPosition().y+texture.getSize().y);
            obstacles[i]->getSprite().setRotation(rotationAngle[rand()%2]);
        }
        
        int Ax = rect.getPosition().x + 120;
        int Ay = rect.getPosition().y + 200;
        int Bx = rect.getPosition().x + rect.getSize().x - 200;
        int By = rect.getPosition().y + rect.getSize().y - 200;

        for (int i = 0; i < countObstacles; i++)
        {
            link1:
            obstacles[i]->getSprite().setPosition(rand() % (Bx - Ax + 1) + Ax, rand() % (By - Ay + 1) + Ay);
            for (int j = 0; j < obstacles.size(); j++)
            {
                if (i != j)
                {
                    if (obstacles[i]->getSprite().getGlobalBounds().
                        intersects(obstacles[j]->getSprite().getGlobalBounds()))
                    {
                        i = 0;
                        goto link1;
                    }
                }
            }
            
        }
        
        for (int i = 0; i < countBonuses; i++)
        {
            bonuses.push_back(new PacManBonus);
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
