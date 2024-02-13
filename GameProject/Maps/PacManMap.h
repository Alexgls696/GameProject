#pragma once
#include "../Library.h"
#include "../Players//PlayerPacMan.h"
#include "../Maps/Map.h"
#include "../Obstacles/PacManObstacles.h"
#include "../Players/PlayerPacMan.h"

class PacManMap : public Map
{
public:
    PacManMap()
    {
        countBonuses = rand() % (10 - 4 + 1) + 4;
        countObstacles = rand() % (10 - 6 + 1) + 6;;
        for (int i = 0; i < countObstacles; i++)
        {
            obstacles.push_back(new PacManObstacles);
            int rotationAngle[] = {0, 90};
            int A = 7;
            int B = 10;
            double scale = rand() % (B - A + 1) + A;
            obstacles[i]->getSprite().setOrigin(obstacles[i]->getSprite().getPosition().x + texture.getSize().x,
                                                obstacles[i]->getSprite().getPosition().y + texture.getSize().y);
            obstacles[i]->getSprite().setScale(scale / 10, scale / 10);
            obstacles[i]->getSprite().setRotation(rotationAngle[rand() % 2]);
        }

        int Ax = getBoundsPosition()[0].x + 20;
        int Ay = getBoundsPosition()[0].y + 20;
        int Bx = rect.getPosition().x + rect.getSize().x - 200;
        int By = rect.getPosition().y + rect.getSize().y - 200;

        for (int i = 0; i < countObstacles; i++)
        {
        link1:
            obstacles[i]->getSprite().setPosition(rand() % (Bx - Ax + 1) + Ax, rand() % (By - Ay + 1) + Ay);
            for (int j = 0; j < obstacles.size(); j++)
            {
                if (i != j)
                {
                    if (obstacles[i]->getSprite().getGlobalBounds().
                                      intersects(obstacles[j]->getSprite().getGlobalBounds()))
                    {
                        goto link1;
                    }
                }
            }
        }

        for (int i = 0; i < countBonuses; i++)
        {
            bonuses.push_back(new PacManBonus);
        }
        Ax = getBoundsPosition()[0].x + 20;
        Ay = getBoundsPosition()[0].y + 20;
        Bx = getBoundsPosition()[3].x - 60;
        By = getBoundsPosition()[1].y - 60;

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
        
        name = "PacManMap";
        bonusSoundBuffer.loadFromFile("Sound/PacManEat.mp3");
        bonusSound.setBuffer(bonusSoundBuffer);
        rect.setFillColor(Color::White);
        texture.loadFromFile("Textures//PacManMap.jpg");
        rect.setTexture(&texture);
    }

    void draw(RenderWindow& window) override
    {
        window.draw(rect);
    }

    Players* getPlayer() override
    {
        player = new PlayerPacMan();
        return player;
    }
    void getBonusSoundPlay() override
    {
        bonusSound.play();
    }
};
