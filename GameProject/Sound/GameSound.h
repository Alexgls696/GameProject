#include "../Library.h"
using namespace sf;
class GameSound
{
public:
    Music pacManSound;
    Music cowboySound;
    Music invSound;
    SoundBuffer winSoundBuffer;
    Sound winSound;
    SoundBuffer looseSoundBuffer;
    Sound looseSound;
    SoundBuffer pacManbreakBuffer;
    Sound pacManbreakSound;
    
    GameSound()
    {
        pacManSound.openFromFile("Sound/pacManStartSound.mp3");
        pacManSound.setVolume(0);
        pacManSound.setLoop(true);
        cowboySound.openFromFile("Sound/cowboyStartSound.mp3");
        cowboySound.setVolume(0);
        invSound.openFromFile("Sound/invStartSound.mp3");
        invSound.setVolume(0);
        pacManbreakBuffer.loadFromFile("Sound/pacManFail.mp3");
        pacManbreakSound.setBuffer(pacManbreakBuffer);
        
    }
};