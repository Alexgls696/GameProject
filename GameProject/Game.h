#pragma once
#include "Library.h"
#include "Maps/PacManMap.h"
#include "Maps/RedDeadMap.h"
#include "Maps/MapC.h"
#include "Maps/MapD.h"
#include "Players//RedPacMan.h"
#include "Players/PlayerCowboy.h"
#include <thread>
#include <time.h>

class Game
{
private:
    Map **maps=nullptr;
    Players* player=nullptr;
    //-------------------------------------------------
    //Добавляем сюда ваш новый объект Player
    Vector2f playerPosition;
    int score = 0;
    
public:
    Game() //Добавление карт, не трогаем
    {
        srand(time(0));
        maps = new Map*[MAPS_COUNT];
        maps[0]=new PacManMap;
        maps[1]=new RedDeadMap;
        maps[2]=new MapC;
        maps[3]=new MapD;
        score = 0;
    }
    ~Game()
    {
        delete []maps;
    }
    
    VertexArray DrawWeb() //Сетка
    {
        VertexArray VertLine(Lines,4);
        VertLine[0].position = Vector2f(960,0);
        VertLine[0].color=Color(0,0,0);
        VertLine[1].position = Vector2f(960,1080);
        VertLine[1].color=Color(0,0,0);
        VertLine[2].position = Vector2f(0,540);
        VertLine[2].color=Color(0,0,0);
        VertLine[3].position = Vector2f(1920,540);
        VertLine[3].color=Color(0,0,0);
        return VertLine;
    }

    void checkBonuses()
    {
        for(int i = 0; i < MAPS_COUNT; i++)
        {
            for(int j = 0; j < maps[i]->getBonuses().size() ;j++)
            {
                if(maps[i]->getBonuses()[j]->getSprite()
                    .getGlobalBounds()
                    .intersects(player->getSprite().getGlobalBounds()))
                {
                    score+=100;
                    maps[i]->getBonuses().at(j)->getSprite().setPosition(-500,-500);
                }
            }
        }
    }

    void setUpPlayerPosition()
    {
        int number = rand() % MAPS_COUNT;
        link:
        playerPosition = Vector2f(maps[number]->getBoundsPosition()->x+rand()%800+50,
            maps[number]->getBoundsPosition()->y+rand()%360+50);
        player->getSprite().setPosition(playerPosition);
        for(int i = 0; i < MAPS_COUNT ; i++)
        {
            for(int j = 0; j < maps[i]->getBonuses().size() ;j++)
            {
                if(maps[i]->getBonuses()[j]->getSprite()
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
        for(int i = 0; i < MAPS_COUNT ;i++)
        {
            if(i==a)
            {
                continue;
            }
            maps[i]->active=false;
        }
    }
    void setPlayer()
    //Добавляем для вашего персонажа аналогичное условие с его именем (name задается в карте Map,
    //устанавливаем его в конструкторе вашей карты)
    {
        for(int i = 0; i < MAPS_COUNT; i++)
        {
            if(maps[i]->getRect().getGlobalBounds().intersects(player->getSprite().getGlobalBounds()))
            {
                if(maps[i]->get_name()._Equal("PacManMap")&&maps[i]->active==false)
                {
                    setPassive(i);
                    maps[i]->active=true;
                    player=new PlayerPacMan;
                    player->getSprite().setPosition(playerPosition);
                    continue;
                }
                if(maps[i]->get_name()._Equal("C")&&maps[i]->active==false)
                {
                    setPassive(i);
                    maps[i]->active=true;
                    player=new PlayerRedPacMan;
                    player->getSprite().setPosition(playerPosition);
                    continue;
                }
                if(maps[i]->get_name()._Equal("RedDeadMap")&&maps[i]->active==false)
                {
                    setPassive(i);
                    maps[i]->active=true;
                    player=new PlayerCowboy;
                    player->getSprite().setPosition(playerPosition);
                    continue;;
                }
            };
        }
       
    }

    void go()
    {
        RenderWindow window(VideoMode(1920,1080),"Game",Style::Fullscreen);
        window.setFramerateLimit(60);
        player=new PlayerPacMan;
        setUpPlayerPosition();
        
        while(window.isOpen())
        {
            window.clear(Color(255,255,255));
            
            Event event;
            setPlayer();
            player->move();
            player->checkBounds();
            checkBonuses();
            
            while(window.pollEvent(event))
            {
                player->Direction(event);
                if(event.type==Event::Closed)
                {
                    window.close();
                }
                if(Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    window.close();
                }
            }
            playerPosition=player->getSprite().getPosition();
            for(int i = 0; i < MAPS_COUNT; i++)
            {
                maps[i]->draw(window);
            }
            for(int i = 0; i < MAPS_COUNT; i++)
            {
                maps[i]->drawBonuses(window);
            }
            for (int i = 0; i < MAPS_COUNT; i++)
                window.draw(DrawWeb());
            player->draw(window);
            window.display();
        }
    }
};
