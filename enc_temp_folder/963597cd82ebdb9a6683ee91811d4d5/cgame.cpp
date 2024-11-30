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

void cgame::addMap(const cmap& map) 
{
    _map.push_back(map);
}

void cgame::startGame() 
{
    system("cls");

    cmap map1(1);
    addMap(map1);

    cmap map2(2);
    addMap(map2);

    cmap map3(3);
    addMap(map3);

    cmap map4(4);
    addMap(map4);
}


void cgame::processGame() 
{
    if (_map.empty()) 
    {
        return;
    }

    system("cls");

    int choice;
    cout << "Choose map (1-4): ";
    cin >> choice;

    system("cls");

    int mapIndex = choice - 1;

    _map[mapIndex].drawMap();

    auto& map = _map[mapIndex]; 
    vector<cenemy>& enemies = map.getEnemies();

    int count = 0;

    // Launch threads for enemy movements
    std::vector<std::thread> enemyThreads;
    for (auto& enemy : enemies) 
    {
        enemyThreads.emplace_back(&cgame::enemyMovement, this, std::ref(enemy), mapIndex, count);
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
    if (gameStateThread.joinable()) 
    {
        gameStateThread.join();
    }
}

void cgame::gameStateUpdate() {
    while (_isRunning && !_ISEXIT1) 
    {
        if (getIsExist1()) 
        {
            system("cls");
            std::lock_guard<std::mutex> lock(printMtx); // Synchronize game state updates
            ctool::GotoXY(0, 20);
            // cout << "END GAME";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Use std::this_thread::sleep_for for better cross-platform compatibility
    }
}

void cgame::enemyMovement(cenemy& enemy, int mapIndex, int count) {
    vector<cmap>& mapList = getMap();
    cmap& map = mapList[mapIndex];

    auto& enemies = map.getEnemies();
    auto& towers = map.getTowers();

    vector<cpoint> path = enemy.getPath();
    cpoint ENEMY = enemy.getCurr();

    int delaySteps = 3;
    int delayTime = delaySteps * 500; 
    std::this_thread::sleep_for(std::chrono::milliseconds(count * delayTime));

    vector<thread> bullet_threads;

    // vector<cbullet> bullets;

    for (int enemyIndex = 0; enemyIndex < path.size();)
    {
        {
            std::lock_guard<std::mutex> lock(printMtx);
            ctool::Draw((char*)"\033[32mE\033[0m", enemyIndex, path, ENEMY); // Draw enemy
        }
            
        enemy.setCurr(path[enemyIndex]);
        enemy.setIndex(enemyIndex++);

        ENEMY = enemy.getCurr();

        {
            std::lock_guard<std::mutex> lock(enemyMutex);
            enemies[count] = enemy;

                

            for (auto& tower : towers)
            {
                auto path = map.createBulletPath(tower, enemies);
                    
                if (path.empty())
                {
                    continue; 
                }

                cbullet newBullet(1, path[0], 50, path, true);


                map.addBullet(newBullet);

                bullet_threads.push_back(std::thread(&cgame::bulletMovement, this, ref(newBullet), newBullet.getPath(), mapIndex));
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        {
            std::lock_guard<std::mutex> lock(printMtx);
            ctool::Draw((char*)" ", enemyIndex - 1, path, ENEMY);
        }
    }


    for (int i = 0; i < bullet_threads.size(); i++)
    {
        bullet_threads[i].join();
    }
}

void cgame::bulletMovement(cbullet& bullet, vector<cpoint> path, int mapIndex)
{
    vector<cmap> mapList = getMap();
    cmap& map = mapList[mapIndex];

    cpoint BULLET = bullet.getCurr();
    int bulletIndex = 0;

    // vector<vector<cpoint>>& _m = map.getRealMap();
    if (bullet.isActive())
    {
        for (int bulletIndex = 0; bulletIndex < path.size() - 1;)
        {
            {
                std::lock_guard<std::mutex> lock(printMtx);
                ctool::Draw((char*)"\033[34mo\033[0m", bulletIndex, path, BULLET);
            }

            bullet.setCurr(path[bulletIndex++]);

            BULLET = bullet.getCurr();

            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            {
                std::lock_guard<std::mutex> lock(printMtx);
                cpoint bulletPos = cpoint::fromXYToRowCol(BULLET);
                if (bulletPos.getC() == 0)
                    ctool::Draw((char*)"+", bulletIndex - 1, path, BULLET);
                if (bulletPos.getC() == 1)
                    ctool::Draw((char*)" ", bulletIndex - 1, path, BULLET);
            }
        }
    }
    
    bullet.setIsActive(false);
}
