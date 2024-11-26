#include "cmap.h"
#include <cstdlib> // for rand()
#include <ctime>   // for time()

cmap::cmap() 
{
    resetMapData();
    makeMapData();
}

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

void cmap::makeMapData() 
{
    vector<cpoint> epath;

    for (int i = 0; i <= 8; ++i) 
    {
        epath.push_back(_m[0][i]);
    }

    for (int i = 1; i <= 12; ++i) {
        epath.push_back(_m[i][8]);
    }

    for (int i = 8; i <= 13; ++i) {
        epath.push_back(_m[12][i]);
    }
    
    cenemy enemy1(2, 100, _m[0][0], epath, 0);
    //cenemy enemy2(1, 100, _m[0][2], epath, 0);

    _ce.push_back(enemy1);
    //_ce.push_back(enemy2);


    ctower tower1(_m[3][3], 50, {});
    tower1.createTreach(_ce[0]);

   /* ctower tower2(_m[10][10], 50, {});
    tower2.createTreach(_ce[0]);*/

    _ctw.push_back(tower1);
    //_ctw.push_back(tower2);

}

//void cmap::drawMap() 
//{
//    for (const auto& tower : _ctw) 
//    {
//        ctool::GotoXY(tower.getCurr().getX(), tower.getCurr().getY());
//        cout << "\033[31mT\033[0m"; // 'T' in red
//    }
//}

void cmap::drawMap() 
{
    // Draw map data _m
    for (int i = 0; i < cpoint::MAP_SIZE; i++) {
        for (int j = 0; j < cpoint::MAP_SIZE; j++) {
            ctool::GotoXY(_m[i][j].getX(), _m[i][j].getY());

            // Check the value of c and draw the corresponding symbol
            if (_m[i][j].getC() == -1) {
                cout << '+';  // Draw '+' for c == -1
            }
            else if (_m[i][j].getC() == -2) {
                cout << 'U';  // Draw 'U' for c == -2
            }
            else {
                cout << '*';  // Default symbol for c == 0 (or other values)
            }
        }
    }

    // Draw _ctw (towers)
    for (const auto& tower : _ctw) {
        ctool::GotoXY(tower.getCurr().getX(), tower.getCurr().getY());
        cout << "\033[31mT\033[0m";  // Draw 'T' for towers
    }
}

vector<cpoint> cmap::createBulletPath(ctower tower)
{
    int direction = tower.calculateShootDirection(_ce).first;
    int tReachIndex = tower.calculateShootDirection(_ce).second;

    vector<cpoint> bpath;

    // Check if tReachIndex is valid
    if (tReachIndex < 0 || tReachIndex >= tower.getTreach().size()) {
        return {};  // Return empty path if invalid
    }

    Treach treach = tower.getTreach()[tReachIndex];
    cpoint target = cpoint::fromXYToRowCol(treach.point);  // Convert target to row/column coordinates
    cpoint towerPos = cpoint::fromXYToRowCol(tower.getCurr()); // Tower's position in row/col coordinates

    int dx = towerPos.getX();  // Row coordinate
    int dy = towerPos.getY();  // Column coordinate

    cout << dx << " " <<  dy << "\n";

    int diffx = abs(target.getX() - dx);  // Row difference
    int diffy = abs(target.getY() - dy);  // Column difference

    int steps = treach.step;

    // Loop to move according to calculated direction
    for (int i = 0; i <= steps; i++)  // Run from 0 to steps (inclusive)
    {
        // Update the coordinates based on the direction
        switch (direction) {
        case UP_LEFT:     dx--; dy--; break;
        case UP:          dy--; break;
        case UP_RIGHT:    dx++; dy--; break;
        case RIGHT:       dx++; break;
        case DOWN_RIGHT:  dx++; dy++; break;
        case DOWN:        dy++; break;
        case DOWN_LEFT:   dx--; dy++; break;
        case LEFT:        dx--; break;
        default:          break;
        }

        // Check if the coordinates are within valid bounds of the map
        if (dx >= 0 && dx < cpoint::MAP_SIZE && dy >= 0 && dy < cpoint::MAP_SIZE) 
        {
            bpath.push_back(_m[dy][dx]);  // Add to path if valid
        }
        else 
        {
            break;  // Break if out of bounds
        }
    }

    return bpath;
}






void cmap::addBullet(ctower tower)
{
    auto direction = tower.calculateShootDirection(_ce);

    vector<cpoint> path = createBulletPath(tower);

    if (path.empty())
    {
        // cout << "hello";
        return;
    }

    if (!path.empty() && direction.first != -1)
    { 
        cbullet newBullet(1, tower.getCurr(), 50, path, 0);

        _cb.push_back(newBullet);
    }
}


