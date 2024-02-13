#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>
#include <thread>
#include <time.h>
#include <vector>
#include <iostream>
#include <string>
#include "chrono"
#include "Sound/GameSound.h"

using namespace sf;

enum Direction //НАПРАВЛЕНИЯ ДВИЖЕНИЯ
{
    STOP,LEFT,RIGHT,UP,DOWN
};

#define MAPS_COUNT 4
#define WIDTH 1920
#define HEIGHT 1080

using namespace std;
using namespace sf;


