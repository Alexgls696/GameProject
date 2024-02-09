#pragma once
#include "../Library.h"
#include "../Players//PlayerPacMan.h"
#include "../Maps/Map.h"

class PacManMap: public Map
{
public:
    PacManMap()
    {
        countBonuses = 4;
        for(int i = 0; i < countBonuses; i++)
        {
            bonuses.push_back(new PacManBonus);
        }
        int Ax = rect.getPosition().x+75;
        int Ay = rect.getPosition().y+75;
        int Bx = rect.getPosition().x+rect.getSize().x-75;
        int By = rect.getPosition().y+rect.getSize().y-75;
        
        for(int i = 0; i < countBonuses; i++)
        {
            link:
            bonuses[i]->getSprite().setPosition(rand()%(Bx-Ax+1)+Ax,rand()%(By-Ay+1)+Ay);
            for(int j = 0; j < countBonuses; j++)
            {
                if(i!=j)
                {
                    if(bonuses[i]->getSprite().getGlobalBounds().intersects(bonuses[j]->getSprite().getGlobalBounds()))
                    {
                        i=0;
                        goto link;
                    }
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
    void drawBonuses(RenderWindow& window) override
    {
        for(int  i = 0; i < countBonuses; i++)
        {
            bonuses[i]->draw(window);
        }
    }
};
