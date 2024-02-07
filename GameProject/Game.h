#pragma once
#include "Library.h"
#include "Maps/GeometryDashMap.h"
#include "Maps/MapB.h"
#include "Maps/MapC.h"
#include "Maps/MapD.h"

class Game
{
private:
    Map **maps;
    Player **player;
    int score;
   
public:
    Game()
    {
        srand(time(0));
        maps = new Map*[MAPS_COUNT];
        maps[0]=new GeometryDashMap;
        maps[1]=new MapB;
        maps[2]=new MapC;
        maps[3]=new MapD;
        score = 0;
    }
    VertexArray DrawWeb()
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
    
    void go()
    {
        RenderWindow window(VideoMode(1920,1080),"Game",Style::Fullscreen);
        window.setFramerateLimit(60);
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
            }
            for(int i = 0; i < MAPS_COUNT; i++)
            {
                maps[i]->draw(window);
            }
            window.draw(DrawWeb());
            window.display();
        }
    }
    
};
