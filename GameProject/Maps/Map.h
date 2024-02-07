#pragma once
#include "../Library.h"

#define ONE sf::Vector2f(0,0)
#define TWO sf::Vector2f(960,0)
#define THREE sf::Vector2f(0,540)
#define FOUR sf::Vector2f(960,540)

class Map //abstract class
{
protected:
    static std::vector<int>positions;
    sf::RectangleShape rect;
    static int index;
    sf::Texture texture;
public:
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
public:
    Map()
    {
        rect.setSize(sf::Vector2f(960,540));
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

