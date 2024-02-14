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
    bool* fireEnemy;
    int health;
    int* lastSee;
    Clock clock2;
    float time2;
    float* EnemyFrame;
    time_t fireEnemyTimer;

    Image bulletImage;
    Texture bulletTexture;
    Sprite bulletSprite;
    Sprite* bulletEnemySprite;
    Direction bulletDirection;

    Image bottleImage;
    Texture bottleTexture;
    Sprite bottleSprite;

    Image healthImage;
    Texture healthTexture;
    Sprite healthSprite;

    SoundBuffer failSoundBuffer;
    Sound failSound;
    SoundBuffer winSoundBuffer;
    Sound winSound;

    SoundBuffer brokeBottleBuffer;
    Sound brokeBottleSound;

    SoundBuffer shootBuffer;
    Sound shootSound;

    SoundBuffer deathBuffer;
    Sound deathSound;

    SoundBuffer woundBuffer;
    Sound woundSound;

public:
    RedDeadMap()
    {
        woundBuffer.loadFromFile("Sound/wound.mp3");
        woundSound.setBuffer(woundBuffer);
        
        deathBuffer.loadFromFile("Sound/death.mp3");
        deathSound.setBuffer(deathBuffer);
        
        shootBuffer.loadFromFile("Sound/shoot.mp3");
        shootSound.setBuffer(shootBuffer);
        
        brokeBottleBuffer.loadFromFile("Sound/broke_bottle.mp3");
        brokeBottleSound.setBuffer(brokeBottleBuffer);
        bonusSoundBuffer.loadFromFile("Sound/bonus_RedDead.mp3");
        bonusSound.setBuffer(bonusSoundBuffer);
        failSoundBuffer.loadFromFile("Sound/sound_fail.mp3");
        failSound.setBuffer(failSoundBuffer);

        winSoundBuffer.loadFromFile("Sound/sound_win.mp3");
        winSound.setBuffer(failSoundBuffer);

        bulletImage.loadFromFile("Textures/fire.png");
        bulletImage.createMaskFromColor(Color::Black);
        bulletTexture.loadFromImage(bulletImage);
        bulletSprite.setTexture(bulletTexture);
        bulletSprite.setScale(0.75, 0.6);

        bottleTexture.loadFromFile("Textures/broken1.png");
        bottleSprite.setTexture(bottleTexture);
        bottleSprite.setTexture(bottleTexture);

        healthTexture.loadFromFile("Textures/health.png");
        healthSprite.setTexture(healthTexture);
        healthSprite.setTextureRect(IntRect(0, 0, 40, 8));

        countBonuses = 3;
        countObstacles = 2;
        countEnemies = 3;
        fireEnemyTimer = std::clock();

        EnemyFrame= new float[countEnemies];
        fireEnemy = new bool[countEnemies];
        lastSee = new int[countEnemies];
        bulletEnemySprite = new Sprite[countEnemies];

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
            fireEnemy[i] = false;
            bulletEnemySprite[i].setTexture(bulletTexture);
            bulletEnemySprite[i].setScale(0.75, 0.6);
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
        if (player != nullptr&&player->getHealth()>0)
        {
            if (std::clock()-fireEnemyTimer > 2000)
            {
                for(int i = 0; i < countEnemies; i++)
                {
                    player->flag_enemy_fire[i]=true;
                }
                fireEnemyTimer = std::clock();
            }
            
            if (player->getDirection() == UP)
            {
                healthSprite.setPosition(player->getSprite().getPosition().x - 15, player->getSprite().getPosition().y + 50);
            }
            else
            {
                healthSprite.setPosition(player->getSprite().getPosition().x - 15, player->getSprite().getPosition().y - 50);
            }
            switch (player->getHealth())
            {
            case 3: healthSprite.setTextureRect(IntRect(0, 0, 40, 8)); break;
            case 2: healthSprite.setTextureRect(IntRect(43, 0, 40, 8)); break;
            case 1: healthSprite.setTextureRect(IntRect(87, 0, 40, 8)); break;
            case 0: healthSprite.setTextureRect(IntRect(131, 0, 40, 8)); break;
            }

            if(player)
            {
                window.draw(healthSprite);
            }
            
            if (player->getFlagEnemyAnimation())
            {
                for (int i = 0; i < countEnemies; i++)
                {
                    if(!player->flag_enemy_fire[i])
                    {
                        if ((player->getSprite().getPosition().x < enemies[i]->getSprite().getPosition().x)
                            && ((enemies[i]->getSprite().getPosition().y < player->getCenter().y)
                                && (enemies[i]->getSprite().getPosition().y + enemies[i]->getSprite().getTextureRect().height > player->getCenter().y)))
                        {
                            enemies[i]->setRectTexture(15, 180, 50, 65);
                            enemies[i]->setSee(1);
                            continue;
                        }
                        if ((player->getSprite().getPosition().x > enemies[i]->getSprite().getPosition().x)
                            && ((enemies[i]->getSprite().getPosition().y < player->getCenter().y)
                                && (enemies[i]->getSprite().getPosition().y+enemies[i]->getSprite().getTextureRect().height > player->getCenter().y)))
                        {
                            enemies[i]->setRectTexture(30, 255, 55, 65);
                            enemies[i]->setSee(2);
                            continue;
                        }
                        if ((player->getSprite().getPosition().y > enemies[i]->getSprite().getPosition().y)
                            && ((enemies[i]->getSprite().getPosition().x < player->getSprite().getPosition().x + player->getSprite().getTextureRect().width)
                                && (enemies[i]->getSprite().getPosition().x + enemies[i]->getSprite().getTextureRect().width > player->getCenter().x)))
                        {
                            enemies[i]->setRectTexture(30, 10, 35, 70);
                            enemies[i]->setSee(3);
                            continue;
                        }
                        if ((player->getCenter().y < enemies[i]->getSprite().getPosition().y)
                            && ((enemies[i]->getSprite().getPosition().x < player->getCenter().x)
                                && (enemies[i]->getSprite().getPosition().x > player->getSprite().getPosition().x)))
                        {
                            enemies[i]->setRectTexture(30, 90, 35, 70);
                            enemies[i]->setSee(4);
                            continue;
                        }
                    }
                }
                player->setFlagEnemyAnimation(false);
            }
            time2 = clock2.getElapsedTime().asMicroseconds();
            clock2.restart();
            time2 = time2 / 800;
            for (int i = 0; i < countEnemies; i++)
            {
                if (player->flag_enemy_fire[i])
                {
                    if (enemies[i]->getSee() == 1)
                    {
                        EnemyFrame[i] += 0.01 * time2;
                        if (EnemyFrame[i] > 7) EnemyFrame[i] = 0;
                        enemies[i]->getSprite().setTextureRect(IntRect(100 * int(EnemyFrame[i]) + 15, 180, 50, 65));
                    }

                    if (enemies[i]->getSee() == 2)
                    {
                        EnemyFrame[i] += 0.01 * time2;
                        if (EnemyFrame[i] > 7) EnemyFrame[i] = 0;
                        enemies[i]->getSprite().setTextureRect(IntRect(100 * int(EnemyFrame[i]) + 30, 255, 55, 65));
                    }

                    if (enemies[i]->getSee() == 3)
                    {
                        EnemyFrame[i] += 0.01 * time2;
                        if (EnemyFrame[i] > 7) EnemyFrame[i] = 0;
                        enemies[i]->getSprite().setTextureRect(IntRect(100 * int(EnemyFrame[i]) + 30, 10, 35, 70));
                    }

                    if (enemies[i]->getSee() == 4)
                    {
                        EnemyFrame[i] += 0.01 * time2;
                        if (EnemyFrame[i] > 7) EnemyFrame[i] = 0;
                        enemies[i]->getSprite().setTextureRect(IntRect(100 * int(EnemyFrame[i]) + 30, 90, 35, 70));
                    }
                }
            }
            for (int i = 0; i < countEnemies; i++)
            {
                if(enemies[i]->getSprite().getPosition().x!=-100)
                {
                    if (EnemyFrame[i] > 4 && EnemyFrame[i] < 5)
                    {
                        if(!fireEnemy[i]) shootSound.play();
                        fireEnemy[i] = true;
                        switch (enemies[i]->getSee())
                        {
                        case 1:
                            bulletEnemySprite[i].setPosition(enemies[i]->getSprite().getPosition().x - 40,
                                enemies[i]->getSprite().getPosition().y - 25);
                            lastSee[i] = enemies[i]->getSee();
                            break;
                        case 2:
                            bulletEnemySprite[i].setPosition(enemies[i]->getSprite().getPosition().x + 30,
                                enemies[i]->getSprite().getPosition().y - 20);
                            lastSee[i] = enemies[i]->getSee();
                            break;
                        case 3:
                            bulletEnemySprite[i].setPosition(enemies[i]->getSprite().getPosition().x + 5,
                                enemies[i]->getSprite().getPosition().y + 60);
                            lastSee[i] = enemies[i]->getSee();
                            break;
                        case 4:
                            bulletEnemySprite[i].setPosition(enemies[i]->getSprite().getPosition().x + 5,
                                enemies[i]->getSprite().getPosition().y - 60);
                            lastSee[i] = enemies[i]->getSee();
                            break;
                        }
                    }
                }
            }
            for (int i = 0; i < countEnemies; i++)
            {
                if (fireEnemy[i] && rect.getGlobalBounds().intersects(bulletEnemySprite[i].getGlobalBounds()))
                {
                    for (int j = 0; j < countObstacles; j++)
                    {
                        if (obstacles[j]->getSprite().getGlobalBounds().intersects(bulletEnemySprite[i].getGlobalBounds()))
                        {
                            fireEnemy[i] = false; break;
                        }
                    }

                    for (int j = 0; j < countBonuses; j++)
                    {
                        if ((bonuses[j]->getSprite().getGlobalBounds().intersects(bulletEnemySprite[i].getGlobalBounds())) && bonuses[j]->getFlagBroke())
                        {
                            bonuses[j]->setFlagBroke(false);
                            brokeBottleSound.play();
                            bonuses[j]->getSprite().setTexture(bottleTexture);
                            bonuses[j]->getSprite().setTextureRect(bottleSprite.getTextureRect());
                            bonuses[j]->getSprite().setScale(0.7, 0.7);
                            fireEnemy[i] = false;
                        }
                    }

                    if (player->getSprite().getGlobalBounds().intersects(bulletEnemySprite[i].getGlobalBounds()))
                    {
                        health = player->getHealth();
                        health -= 1;
                        if(health!=0)
                        {
                            woundSound.play();
                        }
                        else
                        {
                            deathSound.play();
                            player->setHealth(health);
                            return;
                        }
                        player->setHealth(health);
                        fireEnemy[i] = false;
                    }

                    switch (lastSee[i])
                    {
                    case 1:
                        bulletEnemySprite[i].move(-25, 0);
                        bulletEnemySprite[i].setRotation(0);
                        break;
                    case 2:
                        bulletEnemySprite[i].move(25, 0);
                        bulletEnemySprite[i].setRotation(0);
                        break;
                    case 3:
                        bulletEnemySprite[i].move(0, 25);
                        bulletEnemySprite[i].setRotation(90);
                        break;
                    case 4:
                        bulletEnemySprite[i].move(0, -25);
                        bulletEnemySprite[i].setRotation(90);
                        break;
                    }
                    window.draw(bulletEnemySprite[i]);
                }
                else
                {
                    fireEnemy[i] = false;
                }
                for (int j = 0; j < countEnemies; j++)
                {
                    if (EnemyFrame[j] == 0)
                    {
                        player->flag_enemy_fire[j]=false;
                    }
                }
            }
            
            //-----------------------------------------------------------------------------
            if (player->getBullet() && player->getFrame() > 8 && player->getFrame() < 9)
            {
                player->getBullet() = false;
                fire = true;
                shootSound.play();
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
                    if (bonuses[i]->getSprite().getGlobalBounds().intersects(bulletSprite.getGlobalBounds()) && bonuses[i]->getFlagBroke())
                    {
                        bonuses[i]->setFlagBroke(false);
                        brokeBottleSound.play();
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
                                deathSound.play();
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
        bonusSound.play();
    }
};
