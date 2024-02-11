﻿#pragma once
#include "../Library.h"
#include "../Obstacles/Obstacles.h"
#include "Bonuses/Bonuses.h"
#include "Bonuses/PacManBonus.h"

#define ONE sf::Vector2f(0,0)
#define TWO sf::Vector2f(WIDTH/2,0)
#define THREE sf::Vector2f(0,HEIGHT/2)
#define FOUR sf::Vector2f(WIDTH/2,HEIGHT/2)

/*----------------------------------------------
Этот класс не трогаем!
----------------------------------------------
*/

class Map //abstract class
{
protected:
    static std::vector<int>positions;
    sf::RectangleShape rect;
    static int index;
    sf::Texture texture;
    string name;
    vector<Bonuses*>bonuses;
    vector<Obstacles*>obstacles;;
    int countBonuses = 0;
    int countObstacles = 0;
public:
    bool active = false;
    //index 0 - левый верхний угол
    //index 1 - левый нижний угол
    //index 2 - правый нижний угол
    //index 3 - правый верхний угол
    virtual sf::Vector2f*getBoundsPosition()
    {
        sf::Vector2f one(rect.getPosition());
        sf::Vector2f two(rect.getPosition().x,rect.getPosition().y+rect.getSize().y);
        sf::Vector2f three(rect.getPosition().x+rect.getSize().x,rect.getPosition().y+rect.getSize().y);;
        sf::Vector2f four(rect.getPosition().x+rect.getSize().x,rect.getPosition().y);
        sf::Vector2f array[4];
        array[0]=one;
        array[1]=two;
        array[2]=three;
        array[3]=four;
        return array;
    }
    Map()
    {
        rect.setSize(sf::Vector2f(WIDTH/2,HEIGHT/2));
        rect.setFillColor(sf::Color::White);
        int random;
        sf::Vector2f pos;
        while(true)
        {
            random = rand()%index;
            switch (random)
            {
            case 0:
                pos = ONE; break;
            case 1:
                pos = TWO; break;
            case 2:
                pos = THREE; break;
            case 3:
                pos = FOUR; break;
            }
            if(positions[random]!=0)
            {
                rect.setPosition(pos);
                positions[random]=0;
                break;
            }
        }
    }
    
    virtual void draw(sf::RenderWindow&window)=0;
    
    virtual sf::RectangleShape&getRect()
    {
        return rect;
    }
    
    virtual string get_name() const
    {
        return name;
    }
    
    virtual void drawBonuses(RenderWindow&window) = 0;

    virtual void intersectBonuses(int index)
    {
        bonuses.at(index)->getSprite().setPosition(-500,-500);
    }
    
    vector<Bonuses*>getBonuses() 
    {
        return bonuses;
    }
    vector<Obstacles*>getObstacles()
    {
        return obstacles;
    }
};

