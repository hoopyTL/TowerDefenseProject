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
    cpoint _m[cpoint::MAP_SIZE][cpoint::MAP_SIZE];


public:
    cmap();
    void resetMapData();
    void makeMapData();
    void drawMap();

    int getHeight() { return _height; }
    int getWidth() { return _width; }

    vector<cenemy>& getEnemies() { return _ce; }
    vector<ctower>& getTowers() { return _ctw; }
    vector<cbullet>& getBullets() { return _cb; }

    vector<cpoint> createBulletPath(ctower tower, const vector<cenemy>& enemiesList);
    bool addBullet(ctower&, const vector<cenemy>& enemiesList);

    // void updateEnemies();
    // void updateBullets();
};
