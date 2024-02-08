#pragma once
#include "../Library.h"
using namespace std;
using namespace sf;

enum Direction //НАПРАВЛЕНИЯ ДВИЖЕНИЯ
{
    STOP,LEFT,RIGHT,UP,DOWN
};

class Players
{
protected:
    static Direction direction;
    Texture texture;
    Sprite sprite;
    RectangleShape rectangle_shape;
    Image image;
public:
    virtual void draw(RenderWindow& window) = 0; //Рисуем вашего персонажа так, как нужно
    virtual void move() = 0; //Движение с помощью объекта direction - класс PlayerPacMan как пример
    virtual void Direction(Event&event) = 0; //Направление движения, пример тоже в классе PlayerPacMan
    Sprite&getSprite() 
    {
        return sprite;
    }
    virtual void checkBounds() //переопределите в наследнике, если нужно
    {
        if(sprite.getPosition().x-texture.getSize().x/2 <0 ||sprite.getPosition().x+texture.getSize().x/2>1920)
        {
            direction=STOP;
        }
        if(sprite.getPosition().y-texture.getSize().y/2 <0 ||sprite.getPosition().y+texture.getSize().y/2>1080)
        {
            direction=STOP;
        }
    }
    
};
