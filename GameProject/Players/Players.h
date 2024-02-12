#pragma once
#include "../Library.h"
using namespace std;
using namespace sf;



class Players
{
protected:
    static Direction direction;
    Texture texture;
    Sprite sprite;
    RectangleShape rectangle_shape;
    Image image;
    bool fail = false; //проигрыш
    bool pressed = false;
    bool obstacle = false;
    bool flag_bullet=false;
    bool flag_bullet_animation=false;
    float CurrentFrame = 0;
public:
    virtual void setFlag(bool flag)
    {
        this->obstacle=flag;
    }

    virtual void draw(RenderWindow& window) = 0; //Рисуем вашего персонажа так, как нужно
    virtual void move() = 0; //Движение с помощью объекта direction - класс PlayerPacMan как пример
    virtual void Direction(Event&event) = 0; //Направление движения, пример тоже в классе PlayerPacMan
    virtual Vector2f getCenter()
    {
        return Vector2f(sprite.getPosition().x + sprite.getTextureRect().width / 2, sprite.getPosition().y+sprite.getTextureRect().height/2);
    }
    Sprite&getSprite() 
    {
        return sprite;
    }
    virtual void checkBounds() //переопределите в наследнике
    {
       
    }

    virtual void checkBounds(bool&game)
    {
        
    }

    bool&getBullet()
    {
        return flag_bullet;
    }

    virtual enum Direction getDirection()
    {
        return direction;
    }

    virtual void setBullet(bool flag_bullet)
    {
        this->flag_bullet = flag_bullet;
    }
    float getFrame()
    {
        return CurrentFrame;
    }
};
