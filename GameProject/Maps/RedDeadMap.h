#pragma once
#include "../Library.h"
#include "../Players//PlayerCowboy.h"
#include "../Maps/Map.h"
#include "../Bonuses/RedDeadBonus.h"
#include "../Obstacles/RedDead_Obstacles.h"
#include "../Players/PlayerCowboy.h"

class RedDeadMap : public Map
{
private:
    bool fire = false;
    Image bulletImage;
    Texture bulletTexture;
    Sprite bulletSprite;
    Direction bulletDirection;

    Image bottleImage;
    Texture bottleTexture;
    Sprite bottleSprite;

public:
    RedDeadMap()
    {
        bulletImage.loadFromFile("Textures/fire.png");
        bulletImage.createMaskFromColor(Color::Black);
        bulletTexture.loadFromImage(bulletImage);
        bulletSprite.setTexture(bulletTexture);
        bulletSprite.setScale(0.75, 0.6);

        bottleTexture.loadFromFile("Textures/broken1.png");
        bottleSprite.setTexture(bottleTexture);
        bottleSprite.setTexture(bottleTexture);

        countBonuses = 3;
        countObstacles = 3;
        obstacles.push_back(new RedDeadObstacles);
        obstacles.push_back(new RedDeadObstacles2);
        obstacles.push_back(new RedDeadObstacles2);

        int Ax = rect.getPosition().x + 55;
        int Ay = rect.getPosition().y + 20;
        int Bx = rect.getPosition().x + rect.getSize().x - 340;
        int By = rect.getPosition().y + rect.getSize().y - 330;

        for (int i = 0; i < obstacles.size(); i++)
        {
        link1:
            obstacles[i]->getSprite().setPosition(rand() % (Bx - Ax + 1) + Ax, rand() % (By - Ay + 1) + Ay);
            for (int j = 0; j < obstacles.size(); j++)
            {
                if (i != j)
                {
                    if (obstacles[i]->getSprite().getGlobalBounds().intersects(
                        obstacles[j]->getSprite().getGlobalBounds()))
                    {
                        goto link1;
                    }
                }
            }
        }

        for (int i = 0; i < countBonuses; i++)
        {
            bonuses.push_back(new RedDeadBonus);
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

        name = "RedDeadMap";
        rect.setFillColor(Color::White);
        texture.loadFromFile("Textures/Fon_desert.jpg");
        rect.setTexture(&texture);
    }

    void draw(sf::RenderWindow& window) override
    {
        window.draw(rect);
        if (player != nullptr)
        {
            if (player->getBullet() && player->getFrame() > 8&&player->getFrame() < 9)
            {
                player->getBullet() = false;
                fire = true;
                switch (player->getDirection())
                {
                case LEFT:
                    bulletSprite.setPosition(player->getSprite().getPosition().x - 40,
                                             player->getSprite().getPosition().y - 25);
                    bulletDirection = LEFT;
                    break;
                case RIGHT:
                    bulletSprite.setPosition(player->getSprite().getPosition().x + 30,
                                             player->getSprite().getPosition().y - 20);
                    bulletDirection = RIGHT;
                    break;
                case DOWN:
                    bulletSprite.setPosition(player->getSprite().getPosition().x+5,
                                             player->getSprite().getPosition().y + 60);
                    bulletDirection = DOWN;
                    break;
                case UP:
                    bulletSprite.setPosition(player->getSprite().getPosition().x+5,
                                             player->getSprite().getPosition().y - 60);
                    bulletDirection = UP;
                    break;
                }
            }
            if (fire && rect.getGlobalBounds().intersects(bulletSprite.getGlobalBounds()))
            {
                for (int i = 0; i < countObstacles; i++)
                {
                    if (obstacles[i]->getSprite().getGlobalBounds().intersects(bulletSprite.getGlobalBounds()))
                    {
                        fire = false;
                    }
                }

                for (int i = 0; i < countBonuses; i++)
                {
                    if (bonuses[i]->getSprite().getGlobalBounds().intersects(bulletSprite.getGlobalBounds()))
                    {
                        bonuses[i]->getSprite().setTexture(bottleTexture);
                        bonuses[i]->getSprite().setTextureRect(bottleSprite.getTextureRect());
                        bonuses[i]->getSprite().setScale(0.7, 0.7);
                        fire = false;
                    }
                }
                switch (bulletDirection)
                {
                case LEFT:
                    bulletSprite.move(-25, 0);
                    bulletSprite.setRotation(0);
                    break;
                case RIGHT:
                    bulletSprite.move(25, 0);
                    bulletSprite.setRotation(0);
                    break;
                case DOWN:
                    bulletSprite.move(0, 25);
                    bulletSprite.setRotation(90);
                    break;
                case UP:
                    bulletSprite.move(0, -25);
                    bulletSprite.setRotation(90);
                    break;
                }
                window.draw(bulletSprite);
            }
            else
            {
                fire = false;
            }
        }
    }


    Players* getPlayer() override
    {
        player = new PlayerCowboy;
        return player;
    }
};
