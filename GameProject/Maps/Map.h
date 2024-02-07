#pragma once
#include "../Library.h"

#define ONE sf::Vector2f(0,0)
#define TWO sf::Vector2f(960,0)
#define THREE sf::Vector2f(0,550)
#define FOUR sf::Vector2f(960,550)

class Map //abstract class
{
protected:
    static std::vector<int>positions;
    sf::RectangleShape rect;
    static int index;
    sf::Texture texture;
public:
    Map()
    {
        rect.setSize(sf::Vector2f(960,550));
        rect.setFillColor(sf::Color::Black);
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
    
};

