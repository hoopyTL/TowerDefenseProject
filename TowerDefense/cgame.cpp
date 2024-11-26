#include "cgame.h"

cgame::cgame() : _ISEXIT1(false), _ISEXIT2(false) {}

void cgame::setMap(cmap map)
{
    _map.push_back(map);
}

void cgame::startGame() 
{
    system("cls");
    cmap map1;
    setMap(map1);
    _map[0].drawMap();
}
