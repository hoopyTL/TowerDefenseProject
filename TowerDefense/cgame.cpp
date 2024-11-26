#include "cgame.h"


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

#include <thread>
#include <vector>
#include <mutex>

std::mutex gameMutex; // Mutex for thread synchronization

void cgame::processGame() {
    vector<cmap> mapList = getMap();
    cmap map = mapList[0];

    vector<cenemy> ceList = map.getEnemies();
    vector<ctower> ctowerList = map.getTowers();

    // Create threads for handling enemy movement and bullet movement
    std::thread enemyThread(&cgame::enemyMovement, this, std::ref(ceList));
    std::thread bulletThread(&cgame::bulletMovement, this, std::ref(ctowerList), std::ref(ceList));

    // Game state update thread
    std::thread gameStateThread(&cgame::gameStateUpdate, this);

    // Wait for all threads to finish
    enemyThread.join();
    bulletThread.join();
    gameStateThread.join();
}

// Enemy movement logic with mutex for synchronization
void cgame::enemyMovement(std::vector<cenemy>& ceList) {
    while (_isRunning && !_ISEXIT1) {
        bool allEnemiesFinished = true;

        for (auto& ce : ceList) {
            vector<cpoint> path = ce.getPath();
            int pathIndex = 0;
            cpoint _ENEMY = ce.getCurr();

            while (pathIndex < path.size() && !_ISEXIT1) {
                ctool::Draw((char*)"\033[32mE\033[0m", pathIndex, path, _ENEMY);
                ce.setCurr(_ENEMY);
                ce.setIndex(pathIndex);
                pathIndex++;

                if (_ENEMY == path.back()) {
                    ctool::Draw((char*)" ", pathIndex - 1, path, _ENEMY);
                    break;
                }

                Sleep(400 / ce.getSpeed());
                ctool::Draw((char*)" ", pathIndex - 1, path, _ENEMY);
            }

            // If this enemy hasn't finished its path, game should continue
            if (pathIndex < path.size()) {
                allEnemiesFinished = false;
            }
        }

        // If all enemies have finished, stop the game or update game state
        if (allEnemiesFinished) {
            std::lock_guard<std::mutex> lock(gameMutex);
            setIsExist1(true);  // This could be a condition for the game to end
        }
    }
}

// Bullet movement logic with mutex for synchronization
void cgame::bulletMovement(vector<ctower>& ctowerList, vector<cenemy>& ceList) {
    vector<cbullet> activeBullets;
    vector<cmap> mapList = getMap();
    cmap map = mapList[0];

    while (_isRunning && !_ISEXIT1) {
        for (auto& tower : ctowerList) {
            if (map.addBullet(tower, ceList)) {
                vector<cbullet> newBullets = map.getBullets();
                activeBullets.insert(activeBullets.end(), newBullets.begin(), newBullets.end());
            }
        }

        // Move bullets and check for collisions
        for (size_t i = 0; i < activeBullets.size();) {
            cbullet& bullet = activeBullets[i];
            vector<cpoint> bulletPath = bullet.getPath();
            cpoint _BULLET = bullet.getCurr();
            int bulletIndex = bullet.getIndex();

            if (bulletIndex < bulletPath.size()) {
                ctool::Draw((char*)"\033[34mo\033[0m", bulletIndex, bulletPath, _BULLET);
                bullet.setCurr(bulletPath[bulletIndex]);
                bullet.setIndex(++bulletIndex);

                // Check collision with enemies
                for (auto& ce : ceList) {
                    if (_BULLET == ce.getCurr()) {
                        ctool::Draw((char*)" ", bulletIndex - 1, bulletPath, _BULLET);
                        setIsExist1(true);
                        activeBullets.erase(activeBullets.begin() + i);
                        break;
                    }
                }

                Sleep(200 / bullet.getSpeed());
                ctool::Draw((char*)" ", bulletIndex - 1, bulletPath, _BULLET);
                i++;
            }
            else {
                ctool::Draw((char*)" ", bulletIndex - 1, bulletPath, _BULLET);
                activeBullets.erase(activeBullets.begin() + i);
            }
        }
    }
}

// Game state update logic with periodic checking
void cgame::gameStateUpdate() {
    while (_isRunning && !_ISEXIT1) {
        if (getIsExist1()) {
            std::lock_guard<std::mutex> lock(gameMutex);
            ctool::GotoXY(0, 35); // Update game state display
        }

        Sleep(100); // This sleep gives time for the game to process and check conditions
    }
}


