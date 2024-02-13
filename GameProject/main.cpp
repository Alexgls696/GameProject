#include "Game.h"

int Map::index = MAPS_COUNT;
vector<int> Map::positions = {1,2,3,4};
Direction Players::direction = STOP; //Изначально персонаж неподвижен


int main() {
    srand(time(0));
    Game game;
    game.go();
}