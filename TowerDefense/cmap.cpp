#include "cmap.h"
#include <cstdlib> // for rand()
#include <ctime>   // for time()

const int FREE_SPACE = 0;

cmap::cmap() {
    resetMapData();
    makeMapData();
}

void cmap::resetMapData() {
    // Khởi tạo lại các điểm trong bản đồ
    for (int i = 0; i < cpoint::MAP_SIZE; i++) {
        for (int j = 0; j < cpoint::MAP_SIZE; j++) {
            _m[i][j] = { 4 * j + cpoint::LEFT + 2, 2 * i + cpoint::TOP + 1 };
        }
    }
}

void cmap::makeMapData() {
    // Khởi tạo các đối tượng enemy
    cenemy enemy1, enemy2;

    // Đặt điểm xuất phát và kết thúc cho enemy1 và enemy2
    enemy1.setStart(_m[2][0]);
    enemy1.setEnd(_m[14][3]);
    enemy1.setCurr(_m[2][0]);

    // Lộ trình cố định
    const std::array<cpoint, 196> predefinedPath = {
        cpoint(1, 2), cpoint(1, 8), cpoint(11, 8), cpoint(11, 14)
    };

    // Cập nhật lộ trình cho cmap và enemy
    setPath(predefinedPath);  // Thiết lập lộ trình cho cmap
    enemy1.setPath(getPath()); // Thiết lập lộ trình cho enemy1
    enemy1.moveAlongPath();    // Di chuyển enemy1 theo lộ trình

    enemy2.setStart(_m[1][0]);
    enemy2.setEnd(_m[14][3]);
    enemy2.setCurr(_m[1][0]);
    enemy2.setPath(getPath()); // Thiết lập lộ trình cho enemy2
    enemy2.moveAlongPath();    // Di chuyển enemy2 theo lộ trình

    _ce.push_back(enemy1);
    _ce.push_back(enemy2);

    // Tạo và thiết lập các tháp (tower)
    ctower tower1, tower2;
    tower1.setLocation(_m[9][2]);  // Vị trí tháp 1
    tower1.setMapForBullet(_m);
    tower1.calcPathBullet();

    tower2.setLocation(_m[8][9]);  // Vị trí tháp 2
    tower2.setMapForBullet(_m);
    tower2.calcPathBullet();

    // Thêm các tháp vào danh sách
    _ctw.push_back(tower1);
    _ctw.push_back(tower2);
}

void cmap::drawMap() {
    // Vẽ dữ liệu bản đồ _m
    for (int i = 0; i < cpoint::MAP_SIZE; i++) {
        for (int j = 0; j < cpoint::MAP_SIZE; j++) {
            ctool::GotoXY(_m[i][j].getX(), _m[i][j].getY());
        }
    }

    // Vẽ các tháp trong _ctw
    for (const auto& tower : _ctw) {
        ctool::GotoXY(tower.getLocation().getX(), tower.getLocation().getY());
        std::cout << "\033[31mT\033[0m"; // 'T' in red for tower
    }

    // Vẽ các enemy trong _ce
    for (const auto& enemy : _ce) {
        ctool::GotoXY(enemy.getCurr().getX(), enemy.getCurr().getY());
        std::cout << "\033[32mE\033[0m"; // 'E' in green for enemy
    }
}
