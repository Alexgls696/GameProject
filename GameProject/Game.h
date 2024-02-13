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
    Map** maps;
    Players* player;
    Vector2f playerPosition; //перемещение между картами
    int score;
    time_t setPlayerTimer; 
    bool setPlayerFlag; //Для перехода ограничение времени
    
    bool game;
    bool gameMode;
    bool win ;
    bool loose ;
    
    int mapIndex; //Проверка контакта с препятствием только на одной карте
    int obstacleIndex; //Проверки контакта с последним препятствием
    int enemyIndex;
    int MaxCountBonuses; //Число бонусов для победы
    int totalCountBonuses; //текущее число бонусов

    Font timerFont;
    Text timerText;
    int minutes;
    int seconds;  
    Color timeColor = Color::Cyan;
    time_t timeTimer;
    time_t soundTimer;
    time_t timer;
    int indexLastMap;
    bool flagPacManMusic;
    bool flagCowboyMusic;
    string currentMapName;
    
    GameSound sound; //Класс в каталоге Sound. Поставьте нужную вам музыку. Если нужно вызвать звук здесь,
    //то добавляем в класс звук и тут воспроизводим.
    //Если нужно на вашей карте или при какои то действии вашего персонажа, то добавляем в свой класс звуки отдельно.

public:
    void start()
    {
        Map::positions[0]=1;
        Map::positions[1]=2;
        Map::positions[2]=3;
        Map::positions[3]=4;
        maps = nullptr;
        player = nullptr;
        soundTimer = clock();
        srand(time(0));
        maps = new Map*[MAPS_COUNT];
        maps[0] = new PacManMap;
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

        minutes=1;
        seconds = 31; //+1 от времени.
        flagPacManMusic = false;
        flagCowboyMusic = false;
        mapIndex = -1; 
        obstacleIndex = -1; 
        enemyIndex = -1;
        MaxCountBonuses = 0; 
        totalCountBonuses = 0;
        indexLastMap = -1;
        score = 0;
        game = true;
        gameMode = true;
        win = false;
        loose = false;
    }

    ~Game()
    {
        delete[]maps;
    }

    void timerWork()
    {
        string str;
        bool colorFlag = true;
        while (gameMode)
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
                    maps[i]->getBonusSoundPlay();
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
                            sound.pacManbreakSound.play();
                            sound.pacManSound.stop();
                            gameMode = false;
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
    
    void setPlayer() //Теперь универсально
    {
        if(setPlayerFlag)
        {
            if(clock()-setPlayerTimer>250)
            {
                setPlayerFlag=false;
                setPlayerTimer = clock();
            }
        }else{
            for (int i = 0; i < MAPS_COUNT; i++)
            {
                if (maps[i]->getRect().getGlobalBounds().contains(player->getSprite().getPosition()))
                {
                    if(indexLastMap!=i&&maps[i]->active==false)
                    {
                        setPassive(i);
                        maps[i]->active = true;
                        checkSound(maps[i]->get_name());
                        setPlayerFlag=true;
                        player = maps[i]->getPlayer();
                        player->getSprite().setPosition(playerPosition);
                        indexLastMap = i;
                    }
                }
            }
        }
    }
    
    void checkSound(string name)
    {
        if(name._Equal("RedDeadMap"))
        {
            sound.invSound.stop();
            sound.pacManSound.stop();
            sound.cowboySound.play();
        }
        if(name._Equal("PacManMap"))
        {
            sound.cowboySound.stop();
            sound.invSound.stop();
            sound.pacManSound.play();
        }
        if(name._Equal("InvisibilityMap"))
        {
            sound.cowboySound.stop();
            sound.pacManSound.stop();
            sound.invSound.play();
        }
    }
    
    void go()
    {
        RenderWindow window(VideoMode(WIDTH, HEIGHT), "Game");
        window.setFramerateLimit(60);
        
        link:
        start();
        player = new PlayerPacMan;
        setUpPlayerPosition(); //Устанавливаем позацию игрока
        calculateCountBonuses(); // считаем общее число бонусов
        //Второй поток с логикой игры
        thread logicThread([&]()
        {
            while (gameMode)
            {
                setPlayer();
                player->move();
                if(player->checkBounds())
                {
                    sound.pacManbreakSound.play();
                    gameMode=false;
                    sound.pacManSound.stop();
                }; //границы для пакмана
                checkBonuses();
                checkObstacles();
                playerPosition = player->getSprite().getPosition();
                checkTotalBonuses(); // условие победы
                this_thread::sleep_for(chrono::milliseconds(9));
            }
        });

        //ТАЙМЕР
        thread timerThread([&]()
        {
            if (gameMode)
            {
                timerWork();
            };
        });

        timerThread.detach();
        logicThread.detach();

        while (window.isOpen())
        {
            window.clear(Color(255, 255, 255));
            if(gameMode)
            {
                Event event;
                while (window.pollEvent(event))
                {
                    player->Direction(event);
                    if (event.type == Event::Closed)
                    {
                        gameMode = false;
                        window.close();
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Escape))
                    {
                        gameMode = false;
                        window.close();
                    }
                    if (Keyboard::isKeyPressed(Keyboard::R))
                    {
                        gameMode=false;
                        this_thread::sleep_for(chrono::milliseconds(1001));
                        Players::direction=STOP;
                        delete []maps;
                        delete player;
                        goto link;
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
            }else //Место для меню и остального
            {
                Event event;
                while (window.pollEvent(event))
                {
                    player->Direction(event);
                    if (event.type == Event::Closed)
                    {
                        window.close();
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Escape))
                    {
                        window.close();
                    }
                }
            }

            window.display();
        }
    }
};
