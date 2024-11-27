#include "cgame.h"
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

// Mutex for synchronization
std::mutex gameMutex;
std::mutex ceListMutex;

void cgame::addMap(cmap map) {
    _map.push_back(map); // Add map to the list
}

void cgame::startGame() {
    system("cls");
    cmap map1; // Create a new map
    addMap(map1); // Add it to the game

    // Draw the map
    _map[0].drawMap();
}

void cgame::processGame() {
    if (_map.empty()) {
        startGame();
    }

    auto& map = _map[0]; // Access the first map

    std::vector<std::thread> enemyThreads;
    std::vector<std::thread> bulletThreads;

    vector<cenemy>& listCe = map.getEnemies(); // Tham chiếu danh sách enemies

    for (auto& enemy : listCe) 
    {
        enemyThreads.push_back(std::thread([this, &enemy, &listCe]() 
        {
            enemyMovement(enemy, listCe);
            }));
    }

    for (auto& tower : map.getTowers()) 
    {
        std::lock_guard<std::mutex> lock(ceListMutex);
        if (map.addBullet(tower, listCe)) {
            for (auto& bullet : map.getBullets())
                    bulletThreads.push_back(std::thread([this, &bullet, &listCe]() {
                        bulletMovement(bullet, listCe);
                        }));
        }
    }

    std::thread gameStateThread([this]() {
        gameStateUpdate();
        });

    for (auto& t : enemyThreads) {
        if (t.joinable()) {
            t.join();
        }
    }

    for (auto& t : bulletThreads) {
        if (t.joinable()) {
            t.join();
        }
    }

    if (gameStateThread.joinable()) {
        gameStateThread.join();
    }
}



void cgame::gameStateUpdate() {
    while (_isRunning && !_ISEXIT1) {
        if (getIsExist1()) {
            std::lock_guard<std::mutex> lock(gameMutex); // Synchronize game state updates
            ctool::GotoXY(0, 35); // Update game state
        }

        Sleep(100); // Allow time for game processing
    }
}

void cgame::enemyMovement(cenemy& enemy, vector<cenemy>& ceList) {
    vector<cmap> mapList = getMap();
    cmap& map1 = mapList[0];

    if (ceList.empty()) return;

    vector<cpoint> path = enemy.getPath();
    int pathIndex = 0;
    int enemyIndex = enemy.getIndex();
    cpoint _ENEMY = enemy.getCurr();

    while (!getIsExist1()) {
        {
            std::lock_guard<std::mutex> lock(ceListMutex);
            // Move enemy along the path
            if (pathIndex < path.size()) {
                ctool::Draw((char*)"\033[32mE\033[0m", pathIndex, path, _ENEMY);
                pathIndex++;
                enemy.setCurr(path[pathIndex]);
                enemy.setIndex(enemyIndex++); 

                // Tìm enemy trong danh sách theo ID hoặc chỉ số, sau đó cập nhật
                for (auto& e : ceList) 
                {
                    cout << e.getIndex();
                    if (e.getIndex() == enemy.getIndex()) 
                    { // So sánh bằng ID để tìm đúng enemy
                        cout << e.getIndex();

                        e = enemy;
                        cout << "?";
                        break;
                    }
                    // cout << e.getIndex() << enemy.getIndex();

                }

                _ENEMY = enemy.getCurr();

                // Check if the enemy reached the destination
                if (enemy.getCurr() == path.back()) {
                    ctool::Draw((char*)" ", pathIndex - 1, path, _ENEMY);
                    break;
                }

                Sleep(400 / enemy.getSpeed());
                ctool::Draw((char*)" ", pathIndex - 1, path, _ENEMY);
            }
        }
    }
}


void cgame::bulletMovement(cbullet& bullet, vector<cenemy>& enemies) {
    vector<cmap> mapList = getMap();
    cmap& map1 = mapList[0];

    // Get the bullet's path and initial state
    vector<cpoint> bulletPath = bullet.getPath();
    cpoint bulletPos = bullet.getCurr();
    int bulletIndex = bullet.getIndex();

    while (!getIsExist1()) {
        if (!bullet.isActive()) {
            return; // Nếu viên đạn không còn hoạt động, dừng việc vẽ
        }

        // Move bullet along the path
        if (bulletIndex < bulletPath.size()) {
            ctool::Draw((char*)"\033[34mo\033[0m", bulletIndex, bulletPath, bulletPos);
            bullet.setCurr(bulletPath[bulletIndex]);
            bullet.setIndex(++bulletIndex);

            // Check for collision with enemies (the updated list)
            for (auto& enemy : enemies) {
                std::lock_guard<std::mutex> lock(ceListMutex);
                if (bulletPos == enemy.getCurr()) {
                    ctool::Draw((char*)" ", bulletIndex - 1, bulletPath, bulletPos);
                    setIsExist1(true); // Bullet hits enemy
                    bullet.setIsActive(false); // Dừng vẽ viên đạn
                    return; // Bullet hit an enemy, so exit the loop
                }
            }

            Sleep(200 / bullet.getSpeed());
            ctool::Draw((char*)" ", bulletIndex - 1, bulletPath, bulletPos); // Clear previous bullet
        }
        else {
            // Bullet path finished
            ctool::Draw((char*)" ", bulletIndex - 1, bulletPath, bulletPos);
            bullet.setIsActive(false); // Dừng vẽ viên đạn khi đi hết path
            return; // Bullet out of path, exit
        }
    }
}


