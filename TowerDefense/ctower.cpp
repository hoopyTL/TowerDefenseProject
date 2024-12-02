#include "ctower.h"
#include <iostream>

ctower::ctower() : _tpos(0, 0, 0), _treach({}) {}

ctower::ctower(cpoint pos) : _tpos(pos) {}

cpoint ctower::getCurr() const 
{
    return _tpos;
}

void ctower::setCurr(const cpoint& pos) 
{
    _tpos = pos;
}


vector<Treach> ctower::getTreach() const
{
    return _treach;
}

void ctower::createTreach(const vector<cenemy>& enemies) 
{
    _treach.clear();

    if (enemies.empty()) return; // Không có enemy nào thì thoát sớm

    // Vị trí của tháp (được chuyển sang tọa độ lưới)
    cpoint towerPoint = cpoint::fromXYToRowCol(_tpos);
    int rowTower = towerPoint.getX();
    int colTower = towerPoint.getY();

    // Duyệt qua từng enemy trong danh sách
    for (const auto& enemy : enemies) {
        const auto& enemyPath = enemy.getPath(); // Lấy đường đi của enemy hiện tại

        // Duyệt qua từng điểm trên đường đi của enemy
        for (int i = 0; i < enemyPath.size(); ++i) {
            cpoint pathPoint = cpoint::fromXYToRowCol(enemyPath[i]);

            int rowPath = pathPoint.getX();
            int colPath = pathPoint.getY();

            // Kiểm tra nếu điểm này có nằm trong phạm vi của tháp
            if (rowTower == rowPath || colTower == colPath || abs(rowTower - rowPath) == abs(colTower - colPath)) {
                bool exists = false;
                for (const auto& target : _treach) 
                {
                    if (target.point == enemyPath[i]) 
                    { 
                        exists = true;
                        break;
                    }
                }

                // Nếu chưa tồn tại, thêm vào _treach
                if (!exists) {
                    _treach.push_back({ enemyPath[i], i, towerPoint.countSteps(pathPoint) });
                }
            }
        }
    }
}


int ctower::calculateShootDirection(const vector<cenemy>& enemiesList, int &treachIndex) const
{
    // Lấy tọa độ của tháp trong hệ lưới
    cpoint towerPoint = cpoint::fromXYToRowCol(_tpos);  // Chuyển đổi sang hệ lưới
    int rowTower = towerPoint.getX();
    int colTower = towerPoint.getY();

    treachIndex = -1;
    for (const Treach &treachPoint : _treach)
    {
        treachIndex++;
        
        int pathIndex = treachPoint.index;
        cpoint reachPoint = cpoint::fromXYToRowCol(treachPoint.point);  

        int rowReach = reachPoint.getX();
        int colReach = reachPoint.getY();

        int bulletStep = treachPoint.step;

        for (const auto& enemy: enemiesList)
        {
            int enemyIndex = enemy.getIndex();  // Lấy chỉ số của kẻ thù trong enemyPath
            // So sánh giữa chỉ số của ô ảnh hưởng và kẻ thù
            int enemyStep = pathIndex - enemyIndex + 1;

            // Nếu bước viên đạn và bước của kẻ thù trùng nhau, tìm hướng bắn
            if (enemyStep == bulletStep)
            {
                
                // Determine shooting direction based on coordinate difference
                if (rowReach < rowTower && colReach < colTower)
                    return UP_LEFT;  // Diagonal Up-Left
                if (rowReach < rowTower && colReach == colTower)
                    return UP;       // Vertical Up
                if (rowReach < rowTower && colReach > colTower)
                    return UP_RIGHT; // Diagonal Up-Right
                if (rowReach == rowTower && colReach > colTower)
                    return RIGHT;    // Horizontal Right
                if (rowReach > rowTower && colReach > colTower)
                    return DOWN_RIGHT; // Diagonal Down-Right
                if (rowReach > rowTower && colReach == colTower)
                    return DOWN;     // Vertical Down
                if (rowReach > rowTower && colReach < colTower)
                    return DOWN_LEFT; // Diagonal Down-Left
                if (rowReach == rowTower && colReach < colTower)
                    return LEFT;     // Horizontal Left
            }
        }
    }

    treachIndex = -1;
     
    return - 1;
}





