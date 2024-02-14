#include "../Library.h"
using namespace sf;
class GameSound
{
public:
    Music pacManSound;
    Music cowboySound;
    Music rabbitSound;
    Music invSound;
    SoundBuffer winSoundBuffer;
    Sound winSound;
    SoundBuffer looseSoundBuffer;
    Sound looseSound;
    SoundBuffer pacManbreakBuffer;
    Sound pacManbreakSound;
    GameSound()
    {
        rabbitSound.openFromFile("Sound/rabbitStartSound.mp3");
        winSoundBuffer.loadFromFile("Sound/sound_win.mp3");
        winSound.setBuffer(winSoundBuffer);
        looseSoundBuffer.loadFromFile("Sound/sound_fail.mp3");
        looseSound.setBuffer(looseSoundBuffer);
        pacManSound.openFromFile("Sound/pacManStartSound.mp3");
        pacManSound.setVolume(35);
        pacManSound.setLoop(true);
        cowboySound.openFromFile("Sound/cowboyStartSound.mp3");
        cowboySound.setVolume(75);
        invSound.openFromFile("Sound/invStartSound.mp3");
        invSound.setVolume(75);
        pacManbreakBuffer.loadFromFile("Sound/pacManFail.mp3");
        pacManbreakSound.setBuffer(pacManbreakBuffer);
    }
};