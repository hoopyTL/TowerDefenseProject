#include "cmap.h"

cmap::cmap(int level) 
{
    setLevel(level);
    setHeight(cpoint::MAP_HEIGHT + (level - 1));
    setWidth(cpoint::MAP_WIDTH + 3 * (level - 1));

    _m.resize(_height);

    for (int i = 0; i < _height; i++)
    {
        _m[i].resize(_width);
    }

    resetMapData();
    makeMapData();
}

int cmap::getHeight() const { return _height; }
int cmap::getWidth() const { return _width; }
int cmap::getLevel() const { return _level; }

void cmap::setHeight(int height) {  _height = height; }
void cmap::setWidth(int width) { _width = width; }
void cmap::setLevel(int level)  {  _level = level; }

void cmap::addEnemy(const cenemy& enemy)
{
    _ce.push_back(enemy);
}

void cmap::addTower(const ctower& tower)
{
    _ctw.push_back(tower);
}

void cmap::addBullet(const cbullet& bullet)
{
    _cb.push_back(bullet);
}

vector<cenemy>& cmap::getEnemies() { return _ce; }
vector<ctower>& cmap::getTowers() { return _ctw; }
vector<cbullet>& cmap::getBullets() { return _cb; }

vector<vector<cpoint>>& cmap::getRealMap()
{
    return _m;
}

void cmap::resetMapData() 
{
    for (int i = 0; i < _height; i++) 
    {
        for (int j = 0; j < _width; j++) 
        {
            _m[i][j] = cpoint(
                cpoint::MAP_LEFT + j * cpoint::CELL_WIDTH + cpoint::X_OFFSET,
                cpoint::MAP_TOP + i * cpoint::CELL_HEIGHT + cpoint::Y_OFFSET,
                1
            );
        }
    }
}

void cmap::makeMapData() 
{
    switch(_level)
    {
        case 1:
        {
            vector<cpoint> epath1;

            for (int i = 0; i <= 8; ++i)
            {
                epath1.push_back(_m[2][i]);
                _m[2][i].setC(0);
            }
            for (int i = 3; i <= 9; ++i)
            {
                epath1.push_back(_m[i][8]);
                _m[i][8].setC(0);
            }
            for (int i = 9; i < _width; ++i)
            {
                epath1.push_back(_m[9][i]);
                _m[9][i].setC(0);
            }

            cenemy enemy1(2, 100, _m[2][0], epath1);
            cenemy enemy2(2, 100, _m[2][0], epath1);

            addEnemy(enemy1);
            addEnemy(enemy2);

            ctower tower1(_m[5][3]);
            tower1.createTreach(_ce);

            ctower tower2(_m[4][15]);
            tower2.createTreach(_ce);

            addTower(tower1);
            addTower(tower2);

            break;
        }
        case 2:
        {
            vector<cpoint> epath1;

            for (int i = 0; i <= 9; ++i) {
                epath1.push_back(_m[2][i]);
                _m[2][i].setC(0);
            }
            for (int i = 3; i <= 10; ++i) {
                epath1.push_back(_m[i][9]);
                _m[i][9].setC(0);
            }
            for (int i = 10; i < _width; ++i) {
                epath1.push_back(_m[10][i]);
                _m[10][i].setC(0);
            }
            
            for (int i = 4; i >= 1; i--)
            {
                cenemy enemy(i, 100, _m[2][0], epath1);
                addEnemy(enemy);
            }

            ctower tower1(_m[6][2]);
            tower1.createTreach(_ce);

            ctower tower2(_m[7][16]);
            tower2.createTreach(_ce);

            ctower tower3(_m[1][13]);
            tower3.createTreach(_ce);

            ctower tower4(_m[11][4]);
            tower4.createTreach(_ce);

            addTower(tower1);
            addTower(tower2);
            addTower(tower3);
            addTower(tower4);

            break;
        }
        case 3:
        {
            vector<cpoint> epath1;

            for (int i = 0; i <= 7; ++i) {
                epath1.push_back(_m[3][i]);
                _m[3][i].setC(0);
            }
            for (int i = 4; i <= 10; ++i) {
                epath1.push_back(_m[i][7]);
                _m[i][7].setC(0);
            }
            for (int i = 8; i < _width; ++i) {
                epath1.push_back(_m[10][i]);
                _m[10][i].setC(0);
            }

            cenemy enemy1(3, 100, _m[3][0], epath1);
            addEnemy(enemy1);

            cenemy enemy2(3, 100, _m[3][0], epath1);
            addEnemy(enemy2);

            ctower tower1(_m[5][16]);
            tower1.createTreach(_ce);

            ctower tower2(_m[12][11]);
            tower2.createTreach(_ce);

            addTower(tower1);
            addTower(tower2);

            break;
        }
        default:
        {
            vector<cpoint> epath1;
            vector<cpoint> epath2;

            for (int i = 0; i <= 6; ++i) {
                epath1.push_back(_m[4][i]);
                _m[4][i].setC(0);
            }
            for (int i = 5; i <= 10; ++i) {
                epath1.push_back(_m[i][6]);
                _m[i][6].setC(0);
            }
            for (int i = 7; i < _width; ++i) {
                epath1.push_back(_m[10][i]);
                _m[10][i].setC(0);
            }

            cenemy enemy1(4, 100, _m[4][0], epath1);
            cenemy enemy2(4, 100, _m[4][0], epath1);

            addEnemy(enemy1);
            addEnemy(enemy2);

            ctower tower1(_m[6][4]);
            tower1.createTreach(_ce);

            ctower tower2(_m[9][13]);
            tower2.createTreach(_ce);

            addTower(tower1);
            addTower(tower2);
        }       
    }
}

void cmap::drawMap() {
    for (int i = 0; i < _height; i++) 
    {
        for (int j = 0; j < _width; j++) 
        {
            ctool::GotoXY(_m[i][j].getX(), _m[i][j].getY());
            if (_m[i][j].getC() == 1) cout << '+';
        }
    }

    for (const auto& tower : _ctw) 
    {   
        ctool::GotoXY(tower.getCurr().getX(), tower.getCurr().getY());
        cout << TEXT_BLUE_BG_LIGHT_YELLOW << "T";
    }
}

vector<cpoint> cmap::createBulletPath(const ctower& tower, const vector<cenemy>& enemiesList) {
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

    while (rowTower != rowTarget || colTower != colTarget) 
    {
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

    return bpath;
}