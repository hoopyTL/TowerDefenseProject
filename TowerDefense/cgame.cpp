#include "cgame.h"
// #include <memory>
#include <mutex>
#include <thread>
//#include <vector>

// Mutex for synchronization
std::mutex printMtx;
std::mutex gameMutex; // Mutex for game state updates
std::mutex enemyMutex; // Mutex for enemies list access
std::mutex bulletMutex; // Mutex for bullet list access

void cgame::addMap(cmap map) {
    std::lock_guard<std::mutex> lock(gameMutex); // Protect the game state while adding a map
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
    vector<cenemy>& enemies = map.getEnemies(); // Get the list of enemies
    //vector<ctower>& towers = map.getTowers(); // Get the list of towers

    int count = 0; // Variable to manage delay between enemy movements

    // Launch threads for enemy movements
    std::vector<std::thread> enemyThreads;
    for (auto& enemy : enemies) {
        enemyThreads.emplace_back(&cgame::enemyMovement, this, std::ref(enemy), count);
        count++;
    }

    // Thread to update game state
    std::thread gameStateThread(&cgame::gameStateUpdate, this);

    // Wait for all enemy movement threads to finish
    for (auto& t : enemyThreads) {
        if (t.joinable()) {
            t.join();
        }
    }

    // Wait for the game state thread to finish
    if (gameStateThread.joinable()) {
        gameStateThread.join();
    }
}

void cgame::gameStateUpdate() {
    while (_isRunning && !_ISEXIT1) {
        if (getIsExist1()) {
            std::lock_guard<std::mutex> lock(printMtx); // Synchronize game state updates
            ctool::GotoXY(0, 35); // Update game state
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Use std::this_thread::sleep_for for better cross-platform compatibility
    }
}

void cgame::enemyMovement(cenemy& enemy, int count) {
    vector<cmap> mapList = getMap();
    cmap& map1 = mapList[0];

    auto& enemies = map1.getEnemies();
    auto& towers = map1.getTowers();

    vector<cpoint> path = enemy.getPath();
    int pathIndex = 0;
    int enemyIndex = enemy.getIndex();
    // cout << enemyIndex;
    cpoint ENEMY = enemy.getCurr();

    int delaySteps = 8;
    int delayTime = delaySteps * 500; // Delay between movements
    std::this_thread::sleep_for(std::chrono::milliseconds(count * delayTime));

    vector<thread> bullet_threads;
    vector<cbullet> bullets;
    while (!_ISEXIT1) {
        if (pathIndex < path.size()) {
            {
                std::lock_guard<std::mutex> lock(printMtx);
                ctool::Draw((char*)"\033[32mE\033[0m", pathIndex, path, ENEMY); // Draw enemy
            }
            
            enemy.setCurr(path[pathIndex]);
            enemy.setIndex(pathIndex++);

            ENEMY = enemy.getCurr();

            // Lock mutex to safely update the enemy's position in the list
            {
                std::lock_guard<std::mutex> lock(enemyMutex); // Lock to safely update the enemies list
                enemies[count] = enemy;

                

                for (auto& tower : towers)
                {
                    auto path = map1.createBulletPath(tower, enemies);
                    
                    // cout << path.size();
                    if (path.empty())
                    {
                        continue; // No valid path, cannot create bullet
                    }

                    //// Create a new bullet and add it to the map's bullet list
                    cbullet newBullet(1, path[0], 50, path, 0, true);

                    // Add the bullet to the map's list of bullets safely

                    //     // Lock for thread safety
                    map1.addBulletToList(newBullet);

                    //// Launch a thread to handle the bullet movement
                    bullet_threads.push_back(std::thread(&cgame::bulletMovement, this, ref(newBullet), newBullet.getPath()));
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            {
                std::lock_guard<std::mutex> lock(printMtx);
                ctool::Draw((char*)" ", pathIndex - 1, path, ENEMY); // Remove previous enemy from path
            }
        }
    }
    for (int i = 0; i < bullet_threads.size(); i++)
        bullet_threads[i].join();
}

void cgame::bulletMovement(cbullet& bullet, vector<cpoint> path) 
{
    vector<cmap> mapList = getMap();
    cmap& map1 = mapList[0];

    //vector<cpoint> bulletPath = bullet.getPath();
    cpoint BULLET = bullet.getCurr();
    int bulletIndex = 0;

    //cout << bulletPath.size();
    while (!_ISEXIT1 && bullet.isActive()) {
        if (bulletIndex < path.size() - 1) {
            {
                std::lock_guard<std::mutex> lock(printMtx);
                ctool::Draw((char*)"\033[34mo\033[0m", bulletIndex, path, BULLET); // Draw bullet
            }

            bullet.setCurr(path[bulletIndex++]);
            // bulletIndex++;
            BULLET = bullet.getCurr();

        //    // Check for collision with enemies
            {
                std::lock_guard<std::mutex> lock(enemyMutex); // Protect access to enemies list

                for (auto& enemy : map1.getEnemies()) {
                    if (BULLET == enemy.getCurr()) {
                        {
                            std::lock_guard<std::mutex> lock(printMtx);
                            
                            ctool::Draw((char*)" ", bulletIndex - 1, path, BULLET); // Remove bullet
                        }
                        setIsExist1(true); // Bullet hits an enemy
                        bullet.setIsActive(false); // Disable bullet
                        return;
                    }
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Clear bullet's previous position
            {
                std::lock_guard<std::mutex> lock(printMtx);
                ctool::Draw((char*)"+", bulletIndex - 1, path, BULLET);
            }
        }
        else {
            {
                std::lock_guard<std::mutex> lock(printMtx);
                ctool::Draw((char*)"+", bulletIndex - 1, path, BULLET); // Clear bullet's last position
            }
            bullet.setIsActive(false); // Bullet no longer active
            return;
        }
    }
}
