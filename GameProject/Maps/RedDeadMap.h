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
    int health;
    Clock clock;
    float time;
    float* EnemyFrame;
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
        countObstacles = 2;
        countEnemies = 3;
        EnemyFrame= new float[countEnemies];
        obstacles.push_back(new RedDeadObstacles);
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

        for (int i = 0; i < countEnemies; i++)
        {
            enemies.push_back(new Enemy);
            EnemyFrame[i] = 0;
        }

        Ax = rect.getPosition().x + 55;
        Ay = rect.getPosition().y + 20;
        Bx = rect.getPosition().x + rect.getSize().x - 50;
        By = rect.getPosition().y + rect.getSize().y - 50;

        for (int i = 0; i < enemies.size(); i++)
        {
        link2:
            enemies[i]->getSprite().setPosition(rand() % (Bx - Ax + 1) + Ax, rand() % (By - Ay + 1) + Ay);
            for (int j = 0; j < enemies.size(); j++)
            {
                if (i != j)
                {
                    if (enemies[i]->getSprite().getGlobalBounds().intersects(
                        enemies[j]->getSprite().getGlobalBounds()))
                    {
                        goto link2;
                    }
                }
            }
            for (int j = 0; j < countObstacles; j++)
            {
                if (enemies[i]->getSprite().getGlobalBounds().intersects(obstacles[j]->getSprite().getGlobalBounds()))
                {
                    goto link2;
                }
            }
            for (int j = 0; j < countBonuses; j++)
            {
                if (i != j)
                {
                    if (enemies[i]->getSprite().getGlobalBounds().intersects(bonuses[j]->getSprite().getGlobalBounds()))
                    {
                        goto link2;
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
            if (player->getFlagEnemyAnimation())
            {
                for (int i = 0; i < countEnemies; i++)
                {
                    if ((player->getSprite().getPosition().x < enemies[i]->getSprite().getPosition().x)
                        && ((enemies[i]->getSprite().getPosition().y < player->getCenter().y)
                            && (enemies[i]->getSprite().getPosition().y + enemies[i]->getSprite().getTextureRect().height > player->getCenter().y)))
                    {
                        enemies[i]->setRectTexture(15, 180, 50, 65);
                        enemies[i]->setSee(1);
                    }
                    if ((player->getSprite().getPosition().x > enemies[i]->getSprite().getPosition().x)
                        && ((enemies[i]->getSprite().getPosition().y < player->getCenter().y)
                            && (enemies[i]->getSprite().getPosition().y+enemies[i]->getSprite().getTextureRect().height > player->getCenter().y)))
                    {
                        enemies[i]->setRectTexture(30, 255, 55, 65);
                        enemies[i]->setSee(2);
                    }
                    if ((player->getSprite().getPosition().y > enemies[i]->getSprite().getPosition().y)
                        && ((enemies[i]->getSprite().getPosition().x < player->getSprite().getPosition().x + player->getSprite().getTextureRect().width)
                            && (enemies[i]->getSprite().getPosition().x + enemies[i]->getSprite().getTextureRect().width > player->getCenter().x)))
                    {
                        enemies[i]->setRectTexture(30, 10, 35, 70);
                        enemies[i]->setSee(3);
                    }
                    if ((player->getCenter().y < enemies[i]->getSprite().getPosition().y)
                        && ((enemies[i]->getSprite().getPosition().x < player->getCenter().x)
                            && (enemies[i]->getSprite().getPosition().x > player->getSprite().getPosition().x)))
                    {
                        enemies[i]->setRectTexture(30, 90, 35, 70);
                        enemies[i]->setSee(4);
                    }
                }
                player->setFlagEnemyAnimation(false);
            }

            time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 800;
            if (player->getFlagEnemyFire())
            {
                
                for (int i = 0; i < countEnemies; i++)
                {
                    if (enemies[i]->getSee() == 1)
                    {
                        EnemyFrame[i] += 0.01 * time;
                        if (EnemyFrame[i] > 7) EnemyFrame[i] = 0;
                        enemies[i]->getSprite().setTextureRect(IntRect(100 * int(EnemyFrame[i]) + 15, 180, 50, 65));
                    }

                    if (enemies[i]->getSee() == 2)
                    {
                        EnemyFrame[i] += 0.01 * time;
                        if (EnemyFrame[i] > 7) EnemyFrame[i] = 0;
                        enemies[i]->getSprite().setTextureRect(IntRect(100 * int(EnemyFrame[i]) + 30, 255, 55, 65));
                    }

                    if (enemies[i]->getSee() == 3)
                    {
                        EnemyFrame[i] += 0.01 * time;
                        if (EnemyFrame[i] > 7) EnemyFrame[i] = 0;
                        enemies[i]->getSprite().setTextureRect(IntRect(100 * int(EnemyFrame[i]) + 30, 10, 35, 70));
                    }

                    if (enemies[i]->getSee() == 4)
                    {
                        EnemyFrame[i] += 0.01 * time;
                        if (EnemyFrame[i] > 7) EnemyFrame[i] = 0;
                        enemies[i]->getSprite().setTextureRect(IntRect(100 * int(EnemyFrame[i]) + 30, 90, 35, 70));
                    }
                }

                for (int i = 0; i < countEnemies; i++)
                {
                    if (EnemyFrame[i] != 0) break;

                    if (i == countEnemies - 1)
                    {
                        player->setFlagEnemyFire(false);
                    }
                }
            }

            if (player->getBullet() && player->getFrame() > 8 && player->getFrame() < 9)
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
                    bulletSprite.setPosition(player->getSprite().getPosition().x + 5,
                        player->getSprite().getPosition().y + 60);
                    bulletDirection = DOWN;
                    break;
                case UP:
                    bulletSprite.setPosition(player->getSprite().getPosition().x + 5,
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

                for (int i = 0; i < countEnemies; i++)
                {
                    if (enemies[i]->getSprite().getGlobalBounds().intersects(bulletSprite.getGlobalBounds()))
                    {
                        health = enemies[i]->getHealth();
                        health -= 1;
                        enemies[i]->setHealth(health);
                        if (enemies[i]->getHealth() == 0)
                        {
                            enemies[i]->getSprite().setPosition(-100, -100);
                        }
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
    
    void getBonusSoundPlay() override
    {
        
    }
};
