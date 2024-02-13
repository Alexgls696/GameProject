#pragma once
#include "../Library.h"
#include "../Obstacles/Obstacles.h"
using namespace sf;

class RedDeadObstacles : public Obstacles
{
public:
    RedDeadObstacles()
    {
        texture.loadFromFile("Textures/saloon2.png");
        sprite.setTexture(texture);
        //sprite.setOrigin(sprite.getPosition().x + sprite.getTextureRect().width / 2, sprite.getPosition().y+sprite.getTextureRect().height/2); //изм
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(sprite);
    }
};

class RedDeadObstacles2 : public Obstacles
{
public:
    RedDeadObstacles2()
    {
        texture.loadFromFile("Textures/Cactus.png");
        sprite.setTexture(texture);
        //sprite.setOrigin(sprite.getPosition().x + sprite.getTextureRect().width / 2, sprite.getPosition().y+sprite.getTextureRect().height/2); //изм
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(sprite);
    }
};

class Enemy
{
private:
    Texture texture;
    Sprite sprite;
    Image image;
    Vector2f position;
    int health = 2;
    int see=0;
public:
    Enemy()
    {
        texture.loadFromFile("Textures/enemy.png");
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(25, 0, 40, 80));
        sprite.setOrigin(sprite.getPosition().x + sprite.getTextureRect().width / 2, sprite.getPosition().y+sprite.getTextureRect().height/2);
    }
    void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }
    Sprite& getSprite()
    {
        return sprite;
    }
    int getHealth()
    {
        return health;
    }
    void setHealth(int health)
    {
        this->health = health;;
    }
    int getSee()
    {
        return see;
    }
    void setSee(int see)
    {
        this->see = see;
    }
    void setRectTexture(int x, int y, int w, int h)
    {
        sprite.setTextureRect(IntRect(x, y, w, h));
    }
};