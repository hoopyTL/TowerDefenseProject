#pragma once
#include "cmap.h"
#include <thread>
#include <vector>

class cgame {
private:
    vector <cmap> _map;
    bool _ISEXIT1, _ISEXIT2;
    bool _isRunning;  // Flag to manage game state

public:
    cgame() : _ISEXIT1(false), _ISEXIT2(false), _isRunning(true) {}

    bool getIsExist1() const { return _ISEXIT1; }
    void setIsExist1(bool b) { _ISEXIT1 = b; }

    bool getIsExist2() const { return _ISEXIT2; }
    void setIsExist2(bool b) { _ISEXIT2 = b; }

    void setMap(cmap map);
    vector <cmap>& getMap() { return _map; }

    void startGame();
    // Process the game logic including multi-threaded parts
    void processGame();

    // Enemy movement logic
    void enemyMovement(std::vector<cenemy>& ceList);

    // Bullet movement logic
    void bulletMovement(std::vector<ctower>& ctowerList, std::vector<cenemy>& ceList);

    // Game state update logic (win/loss checking)
    void gameStateUpdate();
};