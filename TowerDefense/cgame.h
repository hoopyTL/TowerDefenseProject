#pragma once
#include "cmap.h"
#include <thread>

class cgame 
{
private:
    vector<cmap> _map; 
    bool _ISEXIT;

public:
    cgame() : _ISEXIT(false) {}

    bool getIsExist() const { return _ISEXIT; }
    void setIsExist(bool b) { _ISEXIT = b; }

    /*bool getIsExist2() const { return _ISEXIT2; }
    void setIsExist2(bool b) { _ISEXIT2 = b; }*/

    void addMap(const cmap& map);

    vector<cmap>& getMap() { return _map; }

    void startGame();
    void processGame();

    void gameStateUpdate();
    void enemyMovement(cenemy& enemy, int mapIndex, int count);
    void bulletMovement(cbullet& bullet, vector<cpoint> path, int mapIndex, vector<bool>& bulletThreadStatus, int threadIndex, int enemySpeed);
};