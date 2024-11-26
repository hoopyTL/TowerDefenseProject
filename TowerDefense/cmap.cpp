#include "cmap.h"
#include <iostream>
#include <vector>
#include <cstdlib> // for rand()
#include <ctime>   // for time()

using namespace std;

// Constructor
cmap::cmap()
{
    resetMapData();
    makeMapData();
}

// Đặt lại dữ liệu bản đồ
void cmap::resetMapData()
{
    for (int i = 0; i < cpoint::MAP_SIZE; i++)
    {
        for (int j = 0; j < cpoint::MAP_SIZE; j++)
        {
            _m[i][j] = cpoint(
                cpoint::MAP_LEFT + j * cpoint::CELL_WIDTH + cpoint::X_OFFSET,
                cpoint::MAP_TOP + i * cpoint::CELL_HEIGHT + cpoint::Y_OFFSET,
                0
            );
        }
    }
}

// Tạo dữ liệu bản đồ: Kẻ thù, tháp và đường đi
void cmap::makeMapData()
{
    vector<cpoint> epath;

    // Tạo đường đi cho kẻ thù
    for (int i = 0; i <= 8; ++i)
    {
        epath.push_back(_m[0][i]);
    }
    for (int i = 1; i <= 12; ++i)
    {
        epath.push_back(_m[i][8]);
    }
    for (int i = 8; i <= 13; ++i)
    {
        epath.push_back(_m[12][i]);
    }

    // Thêm kẻ thù
    cenemy enemy1(2, 100, _m[0][0], epath, 0);
    _ce.push_back(enemy1);

    // Thêm tháp
    ctower tower1(_m[6][3], 50, {});
    tower1.createTreach(_ce[0]);
    _ctw.push_back(tower1);
}

// Vẽ bản đồ
void cmap::drawMap()
{
    // Vẽ dữ liệu từ _m
    for (int i = 0; i < cpoint::MAP_SIZE; i++)
    {
        for (int j = 0; j < cpoint::MAP_SIZE; j++)
        {
            ctool::GotoXY(_m[i][j].getX(), _m[i][j].getY());
            if (_m[i][j].getC() == 0) {
                cout << '+'; // Ô trống
            }
        }
    }

    // Vẽ các tháp
    for (const auto& tower : _ctw)
    {
        ctool::GotoXY(tower.getCurr().getX(), tower.getCurr().getY());
        cout << "\033[31mT\033[0m"; // Ký hiệu tháp (màu đỏ)
    }
}

// Tạo đường đạn
vector<cpoint> cmap::createBulletPath(ctower tower, const vector<cenemy>& enemiesList)
{
    int tReachIndex;
    int direction = tower.calculateShootDirection(enemiesList, tReachIndex);

    // cout << direction;
    // cout << tReachIndex;
    // int directionInfo = tower.calculateShootDirection(enemiesList);

    vector<Treach> treachList = tower.getTreach();

    if (direction == -1 && tReachIndex < 0 || tReachIndex >= treachList.size())
    {
        return {};
    }

    vector<cpoint> bpath = {};

    Treach treach = tower.getTreach()[tReachIndex];

    cpoint target = cpoint::fromXYToRowCol(treach.point);
    int rowTarget = target.getX();
    int colTarget = target.getY();

    // cout << rowTarget;

    cpoint towerPos = cpoint::fromXYToRowCol(tower.getCurr());

    int rowTower = towerPos.getX();
    int colTower = towerPos.getY();

    while (true)
    {
        switch (direction)
        {
        case UP_LEFT:     rowTower--; colTower--; break;
        case UP:          rowTower--; break;
        case UP_RIGHT:    rowTower--; colTower++; break;
        case RIGHT:       colTower++; break;
        case DOWN_RIGHT:  rowTower++; colTower++; break;
        case DOWN:        rowTower++; break;
        case DOWN_LEFT:   rowTower++; colTower--; break;
        case LEFT:        colTower--; break;
        default:          break;
        }

        if (rowTower != rowTarget || colTower != colTarget)
        {
            
            bpath.push_back(_m[rowTower][colTower]);
        }
        else 
        {
            bpath.push_back(_m[rowTower][colTower]);
            break;
        }
    }

    return bpath;
}

// Thêm đạn vào bản đồ
bool cmap::addBullet(ctower tower, const vector<cenemy>& enemiesList)
{
    vector<cpoint> path = createBulletPath(tower, enemiesList);

    if (!path.empty())
    {
        cbullet newBullet(1, tower.getCurr(), 50, path, 0);
        _cb.push_back(newBullet);
        return true;
    }
    return false;
}


