#include <stack>
#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include "Players/rabbitPlayer.h"
#include "Bonuses/rabbitBonuses.h"
#include "..\Obstacles\rabbitObstacles.h"
using namespace std;

class RabbitMap:public Map
{
private:
    Texture carrotTexture;
    Sprite carrotSprite;
    Texture fomTexture;
    Sprite cell;

public:
    RabbitMap()
    {
        bonusSoundBuffer.loadFromFile("Sound/rabbitEat.mp3");
        bonusSound.setBuffer(bonusSoundBuffer);
        countBonuses = 15;
        countObstacles = rand()%4;
        for(int i = 0; i < countBonuses; i++)
        {
            int type = rand()%3;
            if(type>=0&&type<2)
            {
                bonuses.push_back(new rabbitCarrotBonus);
            }
            if(type>=2)
            {
                bonuses.push_back(new rabbitCabbageBonus);
            }
        }
        for (int i = 0; i < countObstacles; i++)
        {
            obstacles.push_back(new rabbitObstacles);
            int rotationAngle[] = {0, 90};
            int A = 7;
            int B = 10;
            double scale = rand() % (B - A + 1) + A;
            obstacles[i]->getSprite().setOrigin(obstacles[i]->getSprite().getPosition().x + texture.getSize().x,
                                                obstacles[i]->getSprite().getPosition().y + texture.getSize().y);
        }

        int Ax = getBoundsPosition()[0].x + 50;
        int Ay = getBoundsPosition()[0].y + 20;
        int Bx = rect.getPosition().x + rect.getSize().x - 50;
        int By = rect.getPosition().y + rect.getSize().y - 50;

        for (int i = 0; i < countObstacles; i++)
        {
            link1:
                obstacles[i]->getSprite().setPosition(Ax, rand() % (By - Ay + 1) + Ay);
            for (int j = 0; j < obstacles.size(); j++)
            {
                if (i != j)
                {
                    if (abs(obstacles[i]->getSprite().getPosition().y-(obstacles[j]->getSprite().getPosition().y))<100)
                    {
                        goto link1;
                    }
                }
            }
        }
        for (int i = 0; i < countBonuses; i++)
        {
            link:
                bonuses[i]->getSprite().setPosition(rand() % (Bx - Ax + 1) + Ax, rand() % (By - Ay + 1) + Ay);
            for (int j = 0; j < countObstacles; j++)
            {
                if (bonuses[i]->getSprite().getGlobalBounds().intersects(obstacles[j]->getSprite().getGlobalBounds()))
                {
                    goto link;
                }
            }
            for (int j = 0; j < countBonuses; j++)
            {
                if (i != j)
                {
                    if (bonuses[i]->getSprite().getGlobalBounds().intersects(bonuses[j]->getSprite().getGlobalBounds()))
                    {
                        goto link;
                    }
                }
            }
        }
        texture.loadFromFile("Textures/rabbitFon.jpg");
        rect.setTexture(&texture);
        carrotTexture.loadFromFile("Textures/carrot.png");
        carrotSprite.setTexture(carrotTexture);
    }
    
    void draw(sf::RenderWindow& window) override
    {
        window.draw(rect);
    }
    Players* getPlayer() override
    {
        player = new rabbitPlayer(this);
        return player;
    }
    void getBonusSoundPlay() override
    {
        bonusSound.play();
    }
};



