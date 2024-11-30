#pragma once
#include "ctool.h"
#include "cenemy.h"
#include "ctower.h"
#include "cbullet.h"
#include <algorithm>
#include <chrono>

class cmap
{
private:
    vector<cenemy> _ce;
    vector<ctower> _ctw;
    vector<cbullet> _cb;

    int _height;
    int _width;
    vector<vector<cpoint>> _m;
    int _level;

public:
    cmap(int);
    void resetMapData();
    void makeMapData();
    void drawMap();

    int getHeight() const;
    int getWidth() const;
    int getLevel() const;

    void setHeight(int height);
    void setWidth(int width);
    void setLevel(int level);

    void addEnemy(const cenemy& enemy);
    void addTower(const ctower& tower);
    void addBullet(const cbullet& bullet);

    vector<cenemy>& getEnemies();
    vector<ctower>& getTowers();
    vector<cbullet>& getBullets();
    vector<vector<cpoint>>& getRealMap();

    vector<cpoint> createBulletPath(const ctower& tower, const vector<cenemy>& enemiesList);
};
