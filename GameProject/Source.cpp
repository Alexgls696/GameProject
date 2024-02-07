#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

int main() {
    RenderWindow window(VideoMode(1920, 1080), "Game");
    window.setFramerateLimit(60);
    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type==Event::Closed)
            {
                window.clear();
            }
        }
        window.display();
    }
    
}