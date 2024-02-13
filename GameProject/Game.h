#pragma once
#include "Library.h"
#include "Maps/PacManMap.h"
#include "Maps/RedDeadMap.h"
#include "Maps/MapC.h"
#include "Maps/InvisibilityMap.h"
#include "Players//RedPacMan.h"
#include "Players/PlayerCowboy.h"
#include "Players/PlayerInvisibility.h"

//Изменения в Visual Studio
class Game
{
private:
    Map** maps = nullptr;
    Players* player = nullptr;
    Vector2f playerPosition; //перемещение между картами
    int score = 0;
    time_t setPlayerTimer; 
    bool setPlayerFlag; //Против мерцания на границах карт
    
    bool game = true;
    bool win = false;
    bool loose = false;
    
    int mapIndex = -1; //Проверка контакта с препятствием только на одной карте
    int obstacleIndex = -1; //Проверки контакта с последним препятствием
    int enemyIndex = -1;
    int MaxCountBonuses = 0; //Число бонусов для победы
    int totalCountBonuses = 0; //текущее число бонусов

    Font timerFont;
    Text timerText;
    int minutes = 1;
    int seconds = 31;  //+1 сек
    Color timeColor = Color::Cyan;
    time_t timeTimer;

public:
    Game() //Добавление карт, не трогаем
    {
        srand(time(0));
        maps = new Map*[MAPS_COUNT];
        maps[0] = new PacManMap();
        maps[1] = new RedDeadMap;
        maps[2] = new MapC;
        maps[3] = new InvisibilityMap;
        score = 0;
        setPlayerFlag = clock();
        timerFont.loadFromFile("font2.ttf");
        timerText.setFont(timerFont);
        timerText.setFillColor(timeColor);
        timerText.setOutlineThickness(2);
        timerText.setCharacterSize(40);
        timerText.setPosition(WIDTH / 2 -34, 5);
        timerText.setOutlineColor(Color::Black);
        timeTimer = clock();
        timerText.setString(to_string(minutes) + ":" + to_string(seconds));
    }

    ~Game()
    {
        delete[]maps;
    }

    void timerWork()
    {
        string str;
        bool colorFlag = true;
        while (game)
        {
            if (minutes == 0 && seconds == 0) //Окончание игры
            {
                loose = true;
                game = false;
            }
            if (seconds > 0)
            {
                seconds--;
                timerText.setString(to_string(minutes) + ":" + to_string(seconds));
            }
            else
            {
                seconds = 59;
                timerText.setString(to_string(--minutes) + ":" + to_string(seconds));
            }
            if(minutes==0&&seconds<=10)
            {
                if(colorFlag)
                {
                    timerText.setFillColor(Color::Red);
                    colorFlag=false;
                }else
                {
                    timerText.setFillColor(timeColor);
                    colorFlag=true; 
                }
            }
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
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

    void calculateCountBonuses()
    {
        for (int i = 0; i < MAPS_COUNT; i++)
        {
            MaxCountBonuses += maps[i]->getBonuses().size();
        }
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
                    totalCountBonuses++;
                }
            }
        }
    }

    void checkTotalBonuses()
    {
        if (totalCountBonuses == MaxCountBonuses)
        {
            win = true;
            cout << "Game win!" << endl;
            //game = false; 
        }
    }

    void checkObstacles()
    {
        for (int i = 0; i < MAPS_COUNT; i++)
        {
            for (int j = 0; j < maps[i]->getObstacles().size(); j++)
            {
                if (mapIndex == -1)
                {
                    if (maps[i]->getObstacles()[j]->getSprite()
                                                  .getGlobalBounds()
                                                  .intersects(player->getSprite().getGlobalBounds()))
                    {
                        player->setFlag(true);
                        mapIndex = i;
                        obstacleIndex = j;
                        if (maps[i]->get_name() == "PacManMap")
                        {
                            game = false;
                        }
                    }
                }
                else
                {
                    if (i == mapIndex && obstacleIndex == j)
                    {
                        if (!maps[mapIndex]->getObstacles()[j]->getSprite()
                                                              .getGlobalBounds()
                                                              .intersects(player->getSprite().getGlobalBounds()))
                        {
                            player->setFlag(false);
                            mapIndex = -1;
                            obstacleIndex = -1;
                        }
                    }
                }
            }
        }
    }

    void checkEnemies()
    {
        for (int i = 0; i < MAPS_COUNT; i++)
        {
            for (int j = 0; j < maps[i]->getEnemies().size(); j++)
            {
                if (mapIndex == -1)
                {
                    if (maps[i]->getEnemies()[j]->getSprite()
                        .getGlobalBounds()
                        .intersects(player->getSprite().getGlobalBounds()))
                    {
                        player->setFlag(true);
                        mapIndex = i;
                        enemyIndex = j;
                    }
                }
                else
                {
                    if (i == mapIndex && enemyIndex == j)
                    {
                        if (!maps[mapIndex]->getEnemies()[j]->getSprite()
                            .getGlobalBounds()
                            .intersects(player->getSprite().getGlobalBounds()))
                        {
                            player->setFlag(false);
                            mapIndex = -1;
                            enemyIndex = -1;
                        }
                    }
                }
            }
        }
    }

    void setUpPlayerPosition()
    {
        int number = rand() % MAPS_COUNT;
        int Ax, Ay, Bx, By;
        Ax = maps[number]->getBoundsPosition()[0].x + 80;
        Ay = maps[number]->getBoundsPosition()[0].y + 80;
        Bx = maps[number]->getBoundsPosition()[3].x - 80;
        By = maps[number]->getBoundsPosition()[3].y - 80;

    link:
        playerPosition = Vector2f(rand() % (Bx - Ax + 1) + Ax, rand() % (By - Ay + 1) + Ay);
        player->getSprite().setPosition(playerPosition);
        for (int j = 0; j < maps[number]->getBonuses().size(); j++)
        {
            if (maps[number]->getBonuses()[j]->getSprite()
                                             .getGlobalBounds()
                                             .intersects(player->getSprite().getGlobalBounds()))
            {
                goto link;
            }
        }
        for (int j = 0; j < maps[number]->getObstacles().size(); j++)
        {
            if (maps[number]->getObstacles()[j]->getSprite()
                                               .getGlobalBounds()
                                               .intersects(player->getSprite().getGlobalBounds()))
            {
                goto link;
            }
        }
        for (int j = 0; j < maps[number]->getEnemies().size(); j++)
        {
            if (maps[number]->getEnemies()[j]->getSprite()
                .getGlobalBounds()
                .intersects(player->getSprite().getGlobalBounds()))
            {
                goto link;
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
                        player = maps[i]->getPlayer();
                        player->getSprite().setPosition(playerPosition);
                        continue;
                    }
                    if (maps[i]->get_name()._Equal("C") && maps[i]->active == false)
                    {
                        setPassive(i);
                        maps[i]->active = true;
                        setPlayerFlag = false;
                        player = maps[i]->getPlayer();
                        player->getSprite().setPosition(playerPosition);
                        continue;
                    }
                    if (maps[i]->get_name()._Equal("RedDeadMap") && maps[i]->active == false)
                    {
                        setPassive(i);
                        maps[i]->active = true;
                        setPlayerFlag = false;
                        player = maps[i]->getPlayer();
                        player->getSprite().setPosition(playerPosition);
                        continue;
                    }
                    if (maps[i]->get_name()._Equal("InvisibilityMap") && maps[i]->active == false)
                    {
                        setPassive(i);
                        maps[i]->active = true;
                        setPlayerFlag = false;
                        player = maps[i]->getPlayer();
                        player->getSprite().setPosition(playerPosition);
                        continue;
                    }
                };
            }
        }
        else
        {
            //ОТ МЕРЦАНИЯ НА ГРАНИЦАХ, раз в пол секунды игроку разрешается измениться
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
        setUpPlayerPosition(); //Устанавливаем позацию игрока
        calculateCountBonuses(); // считаем общее число бонусов
        game = true;

        //Второй поток с логикой игры
        thread logicThread([&]()
        {
            while (game)
            {
                timer = clock();
                setPlayer();
                player->move();
                player->checkBounds(); //общие границы
                player->checkBounds(game); //границы для пакмана
                checkBonuses();
                checkObstacles();
                checkEnemies();
                playerPosition = player->getSprite().getPosition();
                checkTotalBonuses(); // условие победы
                this_thread::sleep_for(chrono::milliseconds(9));
            }
        });

        //ТАЙМЕР
        thread timerThread([&]()
        {
            if (game)
            {
                timerWork();
            }
        });

        timerThread.detach();
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
                window.draw(DrawWeb());

            player->draw(window);

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
            {
                for (int j = 0; j < maps[i]->getEnemies().size(); j++)
                {
                    maps[i]->getEnemies()[j]->draw(window);
                }
            }
            window.draw(timerText);

            window.display();
        }
    }
};
