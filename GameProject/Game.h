#pragma once
#include "Library.h"
#include "Maps/PacManMap.h"
#include "Maps/RedDeadMap.h"
#include "Maps/MapC.h"
#include "Maps\InvisibilityMap.h"
#include "Players//RedPacMan.h"
#include "Players/PlayerCowboy.h"
#include "Players/PlayerInvisibility.h"
#include <thread>
#include <time.h>
//Изменения в Visual Studio
class Game
{
private:
    Map** maps = nullptr;
    Players* player = nullptr;
    //-------------------------------------------------
    //Добавляем сюда ваш новый объект Player
    Vector2f playerPosition;
    int score = 0;
    bool game = true;
    time_t setPlayerTimer;
    bool setPlayerFlag;
public:

    Game() //Добавление карт, не трогаем
    {
        srand(time(0));
        maps = new Map * [MAPS_COUNT];
        maps[0] = new PacManMap();
        maps[1] = new RedDeadMap;
        maps[2] = new MapC;
        maps[3] = new InvisibilityMap;
        score = 0;
        setPlayerFlag = clock();
    }
    ~Game()
    {
        delete[]maps;
    }

    VertexArray DrawWeb() //Сетка
    {
        VertexArray VertLine(Lines, 4);
        VertLine[0].position = Vector2f(WIDTH / 2, 0);
        VertLine[0].color = Color(0, 0, 0);
        VertLine[1].position = Vector2f(WIDTH / 2, HEIGHT);
        VertLine[1].color = Color(0, 0, 0);
        VertLine[2].position = Vector2f(0, HEIGHT / 2);
        VertLine[2].color = Color(0, 0, 0);
        VertLine[3].position = Vector2f(WIDTH, HEIGHT / 2);
        VertLine[3].color = Color(0, 0, 0);
        return VertLine;
    }

    void checkBonuses()
    {
        for (int i = 0; i < MAPS_COUNT; i++)
        {
            for (int j = 0; j < maps[i]->getBonuses().size(); j++)
            {
                if (maps[i]->getBonuses()[j]->getSprite()
                    .getGlobalBounds()
                    .intersects(player->getSprite().getGlobalBounds()))
                {
                    score += 100;
                    maps[i]->intersectBonuses(j);
                }
            }
        }
    }

    void checkObstacles()
    {
        for (int i = 0; i < MAPS_COUNT; i++)
        {
            for (int j = 0; j < maps[i]->getObstacles().size(); j++)
            {
                if (maps[i]->getObstacles()[j]->getSprite()
                    .getGlobalBounds()
                    .intersects(player->getSprite().getGlobalBounds()))
                {
                    player->setFlag(true);
                    if (maps[i]->get_name() == "PacManMap")
                    {
                        game = false;
                    }
                }
                else
                {
                    player->setFlag(false);
                }
            }
        }
    }

    void setUpPlayerPosition()
    {
        int number = rand() % MAPS_COUNT;
    link:
        playerPosition = Vector2f(maps[number]->getBoundsPosition()[0].x + rand() % ((WIDTH) / 2 - 100) + 100,
            maps[number]->getBoundsPosition()[0].y + rand() % ((HEIGHT) / 2) + 100 - 100);
        player->getSprite().setPosition(playerPosition);
        for (int i = 0; i < MAPS_COUNT; i++)
        {
            for (int j = 0; j < maps[i]->getBonuses().size(); j++)
            {
                if (maps[i]->getBonuses()[j]->getSprite()
                    .getGlobalBounds()
                    .intersects(player->getSprite().getGlobalBounds()))
                {
                    goto link;
                }
            }
        }
        for (int i = 0; i < MAPS_COUNT; i++)
        {
            for (int j = 0; j < maps[i]->getObstacles().size(); j++)
            {
                if (maps[i]->getObstacles()[j]->getSprite()
                    .getGlobalBounds()
                    .intersects(player->getSprite().getGlobalBounds()))
                {
                    goto link;
                }
            }
        }
    }

    void setPassive(int a)
    {
        for (int i = 0; i < MAPS_COUNT; i++)
        {
            if (i == a)
            {
                continue;
            }
            maps[i]->active = false;
        }
    }

    void setPlayer()
        //Добавляем для вашего персонажа аналогичное условие с его именем (name задается в карте Map,
        //устанавливаем его в конструкторе вашей карты)
    {
        if (setPlayerFlag)
        {
            for (int i = 0; i < MAPS_COUNT; i++)
            {
                if (maps[i]->getRect().getGlobalBounds().contains(player->getCenter()))
                {
                    if (maps[i]->get_name()._Equal("PacManMap") && maps[i]->active == false)
                    {
                        setPassive(i);
                        maps[i]->active = true;
                        setPlayerFlag = false;
                        player = new PlayerPacMan;
                        player->getSprite().setPosition(playerPosition);
                        continue;
                    }
                    if (maps[i]->get_name()._Equal("C") && maps[i]->active == false)
                    {
                        setPassive(i);
                        maps[i]->active = true;
                        setPlayerFlag = false;
                        player = new PlayerRedPacMan;
                        player->getSprite().setPosition(playerPosition);
                        continue;
                    }
                    if (maps[i]->get_name()._Equal("RedDeadMap") && maps[i]->active == false)
                    {
                        setPassive(i);
                        maps[i]->active = true;
                        setPlayerFlag = false;
                        player = new PlayerCowboy;
                        player->getSprite().setPosition(playerPosition);
                        continue;
                    }
                    if (maps[i]->get_name()._Equal("InvisibilityMap") && maps[i]->active == false && maps[3]->checking_transition(player))
                    {
                        setPassive(i);
                        maps[i]->active = true;
                        setPlayerFlag = false;
                        player = new PlayerInvisibility(maps[i]);
                        player->getSprite().setPosition(playerPosition);
                        continue;
                    }
                };
            }
        }
        else
        { //ОТ МЕРЦАНИЯ НА ГРАНИЦАХ, раз в пол секунды игроку разрешается измениться
            if (clock() - setPlayerTimer > 500)
            {
                setPlayerTimer = clock();
                setPlayerFlag = true;
            }
        }
    }

    time_t timer;
    void go()
    {
        RenderWindow window(VideoMode(WIDTH, HEIGHT), "Game");
        window.setFramerateLimit(60);
        player = new PlayerPacMan;
        setUpPlayerPosition();
        game = true;
        timer = clock();//Второй поток с логикой игры
        thread logicThread([&]()
            {
                while (game)
                {
                    if (clock() - timer > 9)
                    {
                        timer = clock();
                        setPlayer();
                        player->move();
                        player->checkBounds();
                        checkBonuses();
                        checkObstacles();
                        playerPosition = player->getSprite().getPosition();
                    }
                }
            });

        logicThread.detach();
        while (window.isOpen() && game)
        {
            window.clear(Color(255, 255, 255));
            Event event;
            while (window.pollEvent(event))
            {
                player->Direction(event);
                if (event.type == Event::Closed)
                {
                    game = false;
                    window.close();
                }
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    game = false;
                    window.close();
                }
            }
            for (int i = 0; i < MAPS_COUNT; i++)
            {
                maps[i]->draw(window);
            }
            for (int i = 0; i < MAPS_COUNT; i++)
            {
                for (int j = 0; j < maps[i]->getObstacles().size(); j++)
                {
                    maps[i]->getObstacles()[j]->draw(window);
                }
            }

            for (int i = 0; i < MAPS_COUNT; i++)
            {
                for (int j = 0; j < maps[i]->getBonuses().size(); j++)
                {
                    maps[i]->getBonuses()[j]->draw(window);
                }
            }

            for (int i = 0; i < MAPS_COUNT; i++)
                window.draw(DrawWeb());
            player->draw(window);
            window.display();
        }
    }
};
