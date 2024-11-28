#include "cmap.h"

// Constructor
cmap::cmap() {
    resetMapData();
    makeMapData();
}

// Reset map data
void cmap::resetMapData() {
    for (int i = 0; i < cpoint::MAP_HEIGHT; i++) {
        for (int j = 0; j < cpoint::MAP_WIDTH; j++) {
            _m[i][j] = cpoint(
                cpoint::MAP_LEFT + j * cpoint::CELL_WIDTH + cpoint::X_OFFSET,
                cpoint::MAP_TOP + i * cpoint::CELL_HEIGHT + cpoint::Y_OFFSET,
                0
            );
        }
    }
}

// Create map data
void cmap::makeMapData() {
    vector<cpoint> epath1;
    vector<cpoint> epath2;

    // Create enemy path
    for (int i = 0; i <= 8; ++i) 
    {
        epath1.push_back(_m[1][i]);
        _m[1][i].setC(1);
    }
    for (int i = 2; i <= 11; ++i) 
    {
        epath1.push_back(_m[i][8]);
        _m[i][8].setC(1);
    }
    for (int i = 9; i <= 13; ++i) 
    {
        epath1.push_back(_m[11][i]);
        _m[11][i].setC(1);
    }

    /*for (int i = 0; i <= 7; ++i) epath2.push_back(_m[1][i]);
    for (int i = 2; i <= 12; ++i) epath2.push_back(_m[i][7]);
    for (int i = 7; i <= 13; ++i) epath2.push_back(_m[12][i]);*/

    // Add enemy
    cenemy enemy1(2, 100, _m[1][0], epath1, 0, true);
    _ce.push_back(enemy1);

    cenemy enemy2(2, 100, _m[1][0], epath1, 0, true);
    _ce.push_back(enemy2);

    // Add tower
    ctower tower1(_m[6][3], 50, vector<Treach>{});
    tower1.createTreach(_ce);

    _ctw.push_back(tower1);

    // Add tower
    ctower tower2(_m[8][12], 50, vector<Treach>{});
    tower2.createTreach(_ce);

    _ctw.push_back(tower2);
}

// Draw map
void cmap::drawMap() {
    // Draw map grid
    for (int i = 0; i < cpoint::MAP_HEIGHT; i++) {
        for (int j = 0; j < cpoint::MAP_WIDTH; j++) {
            ctool::GotoXY(_m[i][j].getX(), _m[i][j].getY());
            if (_m[i][j].getC() == 0) cout << '+';
            else cout << ' ';
        }
    }

    // Draw towers
    for (const auto& tower : _ctw) {
        ctool::GotoXY(tower.getCurr().getX(), tower.getCurr().getY());
        cout << "\033[31mT\033[0m";
    }
}

// Create bullet path
vector<cpoint> cmap::createBulletPath(ctower tower, const vector<cenemy>& enemiesList) {
    int tReachIndex;
    int direction = tower.calculateShootDirection(enemiesList, tReachIndex);

    auto treachList = tower.getTreach();
    if (direction == -1 || tReachIndex < 0 || tReachIndex >= treachList.size())
        return {};

    vector<cpoint> bpath;
    Treach treach = treachList[tReachIndex];
    cpoint target = cpoint::fromXYToRowCol(treach.point);
    cpoint towerPos = cpoint::fromXYToRowCol(tower.getCurr());

    int rowTower = towerPos.getX(), colTower = towerPos.getY();
    int rowTarget = target.getX(), colTarget = target.getY();

    // bpath.push_back(_m[rowTower][colTower]);
    while (rowTower != rowTarget || colTower != colTarget) {
        switch (direction) {
        case UP_LEFT:     rowTower--; colTower--; break;
        case UP:          rowTower--; break;
        case UP_RIGHT:    rowTower--; colTower++; break;
        case RIGHT:       colTower++; break;
        case DOWN_RIGHT:  rowTower++; colTower++; break;
        case DOWN:        rowTower++; break;
        case DOWN_LEFT:   rowTower++; colTower--; break;
        case LEFT:        colTower--; break;
        }
        bpath.push_back(_m[rowTower][colTower]);
    }
    // bpath.push_back(_m[rowTower][colTower]);

    return bpath;
}

//// Add bullet
//bool cmap::addBullet(ctower& tower, const vector<cenemy>& enemiesList) {
//    auto path = createBulletPath(tower, enemiesList);
//    if (path.empty()) return false;
//
//    cbullet newBullet(1, tower.getCurr(), 50, path, 0, true);
//    _cb.push_back(newBullet);
//    return true;
//}

// Trong class cmap
void cmap::addBulletToList(const cbullet& newBullet) {
    _cb.push_back(newBullet);
}