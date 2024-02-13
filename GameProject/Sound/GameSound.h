#include "../Library.h"

class GameSound
{
public:
    sf::Music pacManSound;
    sf:: Music cowboySound;
    sf::Music invSound;
    GameSound()
    {
        pacManSound.openFromFile("Sound/pacManStartSound.mp3");
        cowboySound.openFromFile("Sound/cowboyStartSound.mp3");
        invSound.openFromFile("Sound/invStartSound.mp3");
    }
};