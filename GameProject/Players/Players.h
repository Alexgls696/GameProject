#pragma once
#include "../Library.h"
using namespace std;
using namespace sf;

class Players
{
protected:
    Texture texture;
    Sprite sprite;
    RectangleShape rectangle_shape;
    Image image;
    bool fail = false; //проигрыш
    bool pressed = false;
    bool obstacle = false;
    bool flag_bullet=false;
    bool flag_bullet_animation=false;
    bool flag_enemy_animation = false;
    float CurrentFrame = 0;
    int health = 3;
public:
    bool flag_enemy_fire[3] = {true,true,true};
    static Direction direction;
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
    
    virtual bool checkBounds()
    {
        return false;
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
    bool& getFlagEnemyAnimation()
    {
        return flag_enemy_animation;
    }
    void setFlagEnemyAnimation(bool flag_enemy_animation)
    {
        this->flag_enemy_animation = flag_enemy_animation;
    }


    
    int getHealth()
    {
        return health;
    }
    void setHealth(int health)
    {
        this->health = health;
    }

    
};
