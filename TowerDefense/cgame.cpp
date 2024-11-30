#include "cgame.h"

mutex printMtx;
// mutex gameMtx; // Mutex for game state updates
mutex enemyMtx; // Mutex for enemies list access

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

    // SetConsoleTextAttribute(consoleOutput);

    int mapIndex = choice - 1;

    _map[mapIndex].drawMap();

    auto& map = _map[mapIndex]; 
    vector<cenemy>& enemies = map.getEnemies();

    int indexEnemy = 0;

    // Launch threads for enemy movements
    vector<thread> enemyThreads;
    for (auto& enemy : enemies) 
    {
        enemyThreads.emplace_back(&cgame::enemyMovement, this, std::ref(enemy), mapIndex, indexEnemy);
        indexEnemy++;
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
            lock_guard<mutex> lock(printMtx); // Synchronize game state updates
            ctool::GotoXY(0, 20);
            // cout << "END GAME";
        }
        this_thread::sleep_for(std::chrono::milliseconds(100)); // Use std::this_thread::sleep_for for better cross-platform compatibility
    }
}

void cgame::enemyMovement(cenemy& enemy, int mapIndex, int indexEnemy) {
    vector<cmap>& mapList = getMap();
    cmap& map = mapList[mapIndex];

    auto& enemies = map.getEnemies();
    auto copyEnemies = enemies;

    auto& towers = map.getTowers();

    vector<cpoint> path = enemy.getPath();
    cpoint ENEMY = enemy.getCurr();
    int cntHit = enemy.getCntHit();
    int enemySpeed = enemy.getSpeed();

    int enemyIndex = 0;

    int step = 5;
    int timeDelay = indexEnemy * step * 500;

    this_thread::sleep_for(chrono::milliseconds(timeDelay));

    vector<thread> bullet_threads;
    vector<bool> bulletThreadStatus;

    int damage = 30;
    int threadIndex = 0;

    string tmp;

    while(enemyIndex < path.size())
    {
        if (enemy.isAlive() == true)
        {
            for (int i = 0; i < bullet_threads.size(); i++)
            {
                if (bulletThreadStatus[i] == true)
                {
                    bulletThreadStatus[i] = false;
                    cntHit++;

                    enemy.decreaseHealth(damage);

                    enemy.setCntHit(cntHit);
                    if (enemy.getHealth() <= 0)
                    {
                        enemy.setAlive(false);
                        break;
                    }
                }
            }
            {
                lock_guard<mutex> lock(printMtx);
                if (enemy.getCntHit() == 0)
                    cout << TEXT_GREEN;
                else if (enemy.getCntHit() == 1)
                    cout << TEXT_YELLOW;
                else if (enemy.getCntHit() == 2)
                    cout << TEXT_RED;
                else
                    cout << TEXT_PURPLE;

                string tmp = "E";
                ctool::Draw(tmp, enemyIndex, path, ENEMY);
            }

            enemy.setCurr(path[enemyIndex]);
            enemy.setIndex(enemyIndex++);

            ENEMY = enemy.getCurr();

            {
                lock_guard<mutex> lock(enemyMtx);
                copyEnemies[indexEnemy] = enemy;

                for (auto& tower : towers)
                {
                    auto path = map.createBulletPath(tower, copyEnemies);

                    if (path.empty())
                    {
                        continue;
                    }

                    

                    cbullet newBullet(path[0], damage, path);


                    map.addBullet(newBullet);

                    bulletThreadStatus.push_back(false);
                    bullet_threads.emplace_back(thread(&cgame::bulletMovement, this, ref(newBullet), newBullet.getPath(), mapIndex, ref(bulletThreadStatus), threadIndex, enemySpeed));
                    threadIndex++;

                }
            }

            timeDelay = 650 / sqrt(enemySpeed);

            this_thread::sleep_for(chrono::milliseconds(timeDelay));
            {
                lock_guard<mutex> lock(printMtx);
                tmp = " ";
                ctool::Draw(tmp, enemyIndex - 1, path, ENEMY);
            }
        }
        else
        {
            break;
        }
    }

    {
        lock_guard<mutex> lock(printMtx);
        tmp = " ";
        ctool::Draw(tmp, enemyIndex, path, ENEMY);
    }

    for (auto& t : bullet_threads) 
    {
        if (t.joinable()) {
            t.join();
        }
    }
}

void cgame::bulletMovement(cbullet& bullet, vector<cpoint> path, int mapIndex, vector<bool>& bulletThreadStatus, int threadIndex, int enemySpeed)
{
    // finished = false;
    vector<cmap> mapList = getMap();
    cmap& map = mapList[mapIndex];

    cpoint BULLET = bullet.getCurr();
    int damage = bullet.getDamage();
    int bulletIndex = 0;

    string tmp;
    if (bullet.isActive())
    {
        while (bulletIndex < path.size() - 1)
        {
            {
                std::lock_guard<std::mutex> lock(printMtx);
                cout << TEXT_BRIGHT_BLUE;
                string tmp = "o";
                ctool::Draw(tmp, bulletIndex, path, BULLET);
            }

            bullet.setCurr(path[bulletIndex++]);

            BULLET = bullet.getCurr();

            int timeDelay = 700 / sqrt(enemySpeed);

            this_thread::sleep_for(chrono::milliseconds(timeDelay));

            {
                lock_guard<std::mutex> lock(printMtx);
                cpoint bulletPos = cpoint::fromXYToRowCol(BULLET);

                if (bulletPos.getC() == 0)
                    tmp = "+";

                else
                    tmp = " ";

                ctool::Draw(tmp, bulletIndex - 1, path, BULLET);
            }

            if (bulletIndex == path.size() - 2)
            {
                bulletThreadStatus[threadIndex] = true;
            }
        }
    }

    bullet.setActive(false);
}
