#pragma once
#include "cmap.h"

class cgame 
{
private:
    vector<cmap> _map; // Sử dụng unique_ptr cho cmap
    bool _ISEXIT1, _ISEXIT2;
    bool _isRunning;  // Flag to manage game state

public:
    cgame() : _ISEXIT1(false), _ISEXIT2(false), _isRunning(true) {}

    bool getIsExist1() const { return _ISEXIT1; }
    void setIsExist1(bool b) { _ISEXIT1 = b; }

    bool getIsExist2() const { return _ISEXIT2; }
    void setIsExist2(bool b) { _ISEXIT2 = b; }

    void addMap(cmap map);

    vector<cmap> getMap() { return _map; }

    void startGame();
    // Process the game logic including multi-threaded parts
    void processGame();

    // Game state update logic (win/loss checking)
    void gameStateUpdate();
    void enemyMovement(cenemy& enemy, vector<cenemy>& ceList);
    void bulletMovement(cbullet& bullet, vector<cenemy>& enemies);
};