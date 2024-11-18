#include "cgame.h"

cgame::cgame() : _ISEXIT1(false), _ISEXIT2(false) {}

void cgame::setMap()
{
    cmap _map1;
    _map.push_back(_map1);
}

void cgame::startGame() {
    system("cls");
    setMap();
    _map[0].drawMap();
}
