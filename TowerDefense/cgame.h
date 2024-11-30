#pragma once
#include "cmap.h"
#include <thread>

class cgame 
{
private:
    vector<cmap> _map; 
    bool _ISEXIT1, _ISEXIT2;
    bool _isRunning;  

public:
    cgame() : _ISEXIT1(false), _ISEXIT2(false), _isRunning(true) {}

    bool getIsExist1() const { return _ISEXIT1; }
    void setIsExist1(bool b) { _ISEXIT1 = b; }

    bool getIsExist2() const { return _ISEXIT2; }
    void setIsExist2(bool b) { _ISEXIT2 = b; }

    void addMap(const cmap& map);

    vector<cmap>& getMap() { return _map; }

    void startGame();
    void processGame();

    void gameStateUpdate();
    void enemyMovement(cenemy& enemy, int mapIndex, int count);
    void bulletMovement(cbullet& bullet, vector<cpoint> path, int mapIndex, vector<bool>& bulletThreadStatus, int threadIndex, int enemySpeed);
};