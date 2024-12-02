#include "cgame.h"
#include "ctool.h"

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


void cgame::processGame() {
    if (_map.empty()) {
        return;
    }

    int option = 0;  // Mặc định chọn bản đồ đầu tiên
    int choice = 0;  // Lựa chọn bản đồ cuối cùng (để sử dụng sau)
    std::cout << "-----CHOOSE MAP-----\n";
    while (true) {
        //system("cls");  // Xóa màn hình
        system("color E3");  // Đặt màu nền và màu chữ


        // Vẽ các ô cho từng bản đồ (1-4)
        ctool::printRectangle(5, 5, 30, 3);  // Ô cho Map 1
        ctool::printRectangle(5, 9, 30, 3);  // Ô cho Map 2
        ctool::printRectangle(5, 13, 30, 3); // Ô cho Map 3
        ctool::printRectangle(5, 17, 30, 3); // Ô cho Map 4

        // In các lựa chọn vào các ô chữ nhật
        for (int i = 0; i < 4; ++i) {
            // Nếu đang chọn mục này, tô màu xanh
            if (i == option) {
                setColor(13, 3);  // Highlight in blue
            }
            else {
                setColor(14, 3);  // Các mục còn lại dùng màu mặc định
            }

            // In các lựa chọn bản đồ vào giữa các ô chữ nhật
            ctool::GotoXY(7, 6 + i * 4);  // Vị trí chữ trong ô
            std::cout << "Map " << (i + 1);  // In "Map 1", "Map 2", ...
        }

        setColor(12, 3);  // Reset lại màu sắc

        // Nhận đầu vào từ người dùng (phím mũi tên hoặc Enter)
        char ch = _getch();

        // Điều hướng lên/xuống
        if (ch == KEY_UP) {  // Di chuyển lên
            option = (option > 0) ? option - 1 : 3;  // Nếu ở đầu, quay lại cuối
        }
        else if (ch == KEY_DOWN) {  // Di chuyển xuống
            option = (option + 1) % 4;  // Nếu ở cuối, quay lại đầu
        }
        else if (ch == KEY_ENTER) {  // Chọn
            choice = option + 1;  // Chọn bản đồ (Map 1, Map 2, ...)
            break;  // Thoát vòng lặp sau khi chọn
        }
        else if (ch == 27) {  // Phím ESC để quay lại
            return;  // Quay lại nếu nhấn ESC
        }
    }

    // Sau khi chọn xong, bạn có thể sử dụng lựa chọn cho bản đồ
    system("cls");
    system("color E3");  // Đặt màu nền và màu chữ
    setColor(14, 0);
    int mapIndex = choice - 1;  // Xác định chỉ mục bản đồ

    // Vẽ và hiển thị bản đồ đã chọn
    _map[mapIndex].drawMap();

    auto& map = _map[mapIndex];  // Lấy bản đồ đã chọn
    vector<cenemy>& enemies = map.getEnemies();

    int indexEnemy = 0;

    // Khởi tạo các luồng để di chuyển kẻ địch
    vector<thread> enemyThreads;
    for (auto& enemy : enemies) {
        enemyThreads.emplace_back(&cgame::enemyMovement, this, std::ref(enemy), mapIndex, indexEnemy);
        indexEnemy++;
    }

    // Thread để cập nhật trạng thái game
    std::thread gameStateThread(&cgame::gameStateUpdate, this);

    // Đợi tất cả các thread di chuyển kẻ địch kết thúc
    for (auto& t : enemyThreads) {
        if (t.joinable()) {
            t.join();
        }
    }

    // Đợi thread cập nhật trạng thái game kết thúc
    if (gameStateThread.joinable()) {
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
            cout << "END GAME";
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

    while (enemyIndex < path.size())
    {
        if (enemy.isAlive() == true)
        {
            {
                lock_guard<mutex> lock(printMtx);
                if (enemy.getCntHit() == 0)
                    cout << TEXT_GREEN_BG_LIGHT_YELLOW;
                else if (enemy.getCntHit() == 1)
                    cout << TEXT_YELLOW_BG_LIGHT_YELLOW;
                else if (enemy.getCntHit() == 2)
                    cout << TEXT_RED_BG_LIGHT_YELLOW;
                else
                    cout << TEXT_PURPLE_BG_LIGHT_YELLOW;

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
                cout << TEXT_PURPLE_BG_LIGHT_YELLOW;
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
