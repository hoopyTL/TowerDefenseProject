#include "ctower.h"

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
    int xTower = towerPoint.getX();
    int yTower = towerPoint.getY();

    // Iterate through the points on the enemy's path
    for (int i = 0; i < enemyPath.size(); ++i) {
        cpoint pathPoint = cpoint::fromXYToRowCol(enemyPath[i]);

        int xPath = pathPoint.getX();
        int yPath = pathPoint.getY();

        // Check if the path point is valid on the map
        if (xPath >= 0 && xPath < cpoint::MAP_SIZE && yPath >= 0 && yPath < cpoint::MAP_SIZE) {
            // Check if the tower and the path point are aligned horizontally, vertically, or diagonally
            if (xTower == xPath || yTower == yPath || abs(xTower - xPath) == abs(yTower - yPath)) {
                // Use the countSteps method from cpoint to calculate distance
                _treach.push_back({ pathPoint, i, _tpos.countSteps(pathPoint) });
            }
        }
    }
}




pair<int, int> ctower::calculateShootDirection(const vector<cenemy>& enemiesList) const
{
    int xTower = _tpos.getX();
    int yTower = _tpos.getY();

    // Lấy tọa độ của tháp trong hệ lưới
    cpoint towerPoint = cpoint::fromXYToRowCol(_tpos);  // Chuyển đổi sang hệ lưới

    for (const Treach& treachPoint : _treach)
    {
        cpoint point = treachPoint.point;
        int pathIndex = treachPoint.index;

        // Lấy tọa độ của điểm trong hệ lưới
        cpoint reachPoint = cpoint::fromXYToRowCol(point);  // Chuyển đổi sang hệ lưới

        int xReach = reachPoint.getX();
        int yReach = reachPoint.getY();

        // Sử dụng trực tiếp 'step' từ Treach
        int bulletStep = treachPoint.step;

        // Kiểm tra sự trùng khớp của chỉ số trên đường đi của kẻ thù và bước viên đạn
        for (const auto& enemy : enemiesList)
        {
            int enemyIndex = enemy.getIndex();  // Lấy chỉ số của kẻ thù trong enemyPath

            // So sánh giữa chỉ số của ô ảnh hưởng và kẻ thù
            int enemyStep = pathIndex - enemyIndex;

            // Nếu bước viên đạn và bước của kẻ thù trùng nhau, tìm hướng bắn
            if (enemyStep == bulletStep)
            {
                // Xác định hướng bắn dựa trên chênh lệch tọa độ
                if (xTower > xReach && yTower > yReach)
                    return make_pair(UP_LEFT, pathIndex);  // Diagonal Up-Left
                if (xTower == xReach && yTower > yReach)
                    return make_pair(UP, pathIndex);      // Vertical Up
                if (xTower < xReach && yTower > yReach)
                    return make_pair(UP_RIGHT, pathIndex); // Diagonal Up-Right
                if (xTower < xReach && yTower == yReach)
                    return make_pair(RIGHT, pathIndex);   // Horizontal Right
                if (xTower < xReach && yTower < yReach)
                    return make_pair(DOWN_RIGHT, pathIndex); // Diagonal Down-Right
                if (xTower == xReach && yTower < yReach)
                    return make_pair(DOWN, pathIndex);    // Vertical Down
                if (xTower > xReach && yTower < yReach)
                    return make_pair(DOWN_LEFT, pathIndex); // Diagonal Down-Left
                if (xTower > xReach && yTower == yReach)
                    return make_pair(LEFT, pathIndex);    // Horizontal Left
            }
        }
    }

    return make_pair(-1, -1); // Không tìm được hướng
}





