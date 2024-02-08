#pragma once
#include "Library.h"
#include "Maps\PacManMap.h"
#include "Maps/MapB.h"
#include "Maps/MapC.h"
#include "Maps/MapD.h"
#include "Players//RedPacMan.h"

class Game
{
private:
    
    Map **maps=nullptr;
    Players* player=nullptr;
    //-------------------------------------------------
    //Добавляем сюда ваш новый объект Player
    
    Players*pacMan = new PlayerPacMan;
    Players*redPacMan = new PlayerRedPacMan;
    Vector2f playerPosition;
    int score;
public:
    Game() //Добавление карт, не трогаем
    {
        srand(time(0));
        maps = new Map*[MAPS_COUNT];
        maps[0]=new PacManMap;
        maps[1]=new MapB;
        maps[2]=new MapC;
        maps[3]=new MapD;
        score = 0;
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

    void setPlayer()
    //Добавляем для вашего персонажа аналогичное условие с его именем (name задается в карте Map,
    //устанавливаем его в конструкторе вашей карты)
    {
        for(int i = 0; i < MAPS_COUNT; i++)
        {
            if(player->getSprite().getGlobalBounds().intersects(maps[i]->getRect().getGlobalBounds())
               &&maps[i]->get_name()=="PacMan")
            {
                player=pacMan;
                player->getSprite().setPosition(playerPosition);
            };
            if(player->getSprite().getGlobalBounds().intersects(maps[i]->getRect().getGlobalBounds())
                &&maps[i]->get_name()=="B")
            {
                player=redPacMan;
                player->getSprite().setPosition(playerPosition);
            };
        }
    }
    
    void go()
    {
        RenderWindow window(VideoMode(1920,1080),"Game",Style::Fullscreen);
        window.setFramerateLimit(60);
        int number = rand() % MAPS_COUNT;
        player=pacMan; //Криво, но пусть так
        playerPosition = Vector2f(maps[number]->getBoundsPosition()->x+rand()%800,
            maps[number]->getBoundsPosition()->y+rand()%360); //позиция в карте рандом, карта рандом
        player->getSprite().setPosition(playerPosition);
        
        while(window.isOpen())
        {
            window.clear(Color(255,255,255));
            Event event;
            while(window.pollEvent(event))
            {
                if(event.type==Event::Closed)
                {
                    window.close();
                }
                if(Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    window.close();
                }
                player->Direction(event);
            }
            setPlayer();
            for(int i = 0; i < MAPS_COUNT; i++)
            {
                maps[i]->draw(window);
            }
            for (int i = 0; i < MAPS_COUNT; i++)
                window.draw(DrawWeb());
            player->draw(window);
            player->move();
            player->checkBounds();
            playerPosition=player->getSprite().getPosition();
            //Обновляет шлобальную позицию персонажа после изменения позиции спрайта
            
            window.display();
        }
    }
};
