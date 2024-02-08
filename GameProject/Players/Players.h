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
    virtual Sprite&getSprite() 
    {
        return sprite;
    }
};
