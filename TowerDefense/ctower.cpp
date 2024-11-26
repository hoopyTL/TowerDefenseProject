#include "ctower.h"
#include <iostream>

ctower::ctower() : _tpos(0, 0, 0), _damage(0) {}

ctower::ctower(const cpoint& tpos, int damage, vector<Treach> treach) : _tpos(tpos), _damage(damage), _treach(treach) {}

cpoint ctower::getCurr() const {
    return _tpos;
}

void ctower::setCurr(const cpoint& pos) {
    _tpos = pos;
}

int ctower::getDamage() const {
    return _damage;
}

void ctower::setDamage(int damage) 
{
    _damage = damage;
}

vector<Treach> ctower::getTreach() const
{
    return _treach;
}

void ctower::createTreach(const cenemy& enemy) {
    _treach.clear();  // Clear the previous list of targets

    // Get the path of the first enemy (assuming all enemies have the same path)
    const auto& enemyPath = enemy.getPath();  // getPath() is assumed to return a vector of points

    // Convert tower's position to grid coordinates
    cpoint towerPoint = cpoint::fromXYToRowCol(_tpos);
    int rowTower = towerPoint.getX();
    int colTower = towerPoint.getY();

    // Iterate through the points on the enemy's path
    for (int i = 0; i < enemyPath.size(); ++i) {
        cpoint pathPoint = cpoint::fromXYToRowCol(enemyPath[i]);

        int rowPath = pathPoint.getX();
        int colPath = pathPoint.getY();

        
        // Check if the tower and the path point are aligned horizontally, vertically, or diagonally
        if (rowTower == rowPath || colTower == colPath || abs(rowTower - rowPath) == abs(colTower - colPath)) 
        {
            // Use the countSteps method from cpoint to calculate distance
            _treach.push_back({ enemyPath[i], i, towerPoint.countSteps(pathPoint) });
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
    for (Treach treachPoint : _treach)
    {
        treachIndex++;
        
        int pathIndex = treachPoint.index;

        // Lấy tọa độ của điểm trong hệ lưới
        cpoint reachPoint = cpoint::fromXYToRowCol(treachPoint.point);  // Chuyển đổi sang hệ lưới

        int rowReach = reachPoint.getX();
        int colReach = reachPoint.getY();

        // cout << "(" << rowReach << "," << colReach << ")";

        // Sử dụng trực tiếp 'step' từ Treach
        int bulletStep = treachPoint.step;


        // Kiểm tra sự trùng khớp của chỉ số trên đường đi của kẻ thù và bước viên đạn
        for (const auto& enemy : enemiesList)
        {
            int enemyIndex = enemy.getIndex();  // Lấy chỉ số của kẻ thù trong enemyPath
            // So sánh giữa chỉ số của ô ảnh hưởng và kẻ thù
            int enemyStep = pathIndex - enemyIndex;

            if (enemyStep < bulletStep)
            {
                continue;
            }
              

            // Nếu bước viên đạn và bước của kẻ thù trùng nhau, tìm hướng bắn
            if (enemyStep == bulletStep)
            {
                // cout << "(" << rowReach << "," << colReach << ")";
                // cout << bulletStep;
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





