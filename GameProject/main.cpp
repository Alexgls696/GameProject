#include "Game.h"

int Map::index = MAPS_COUNT;

vector<int> Map::positions = {1,2,3,4};

int main() {
    srand(time(0));
    Game game;
    game.go();
}