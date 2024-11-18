#pragma once
#include "cpoint.h"
#include <array>

class cbullet {
private:
    int _n, _speed;
    std::array<cpoint, cpoint::MAP_SIZE* cpoint::MAP_SIZE> _p;
    std::array<std::array<cpoint, cpoint::MAP_SIZE>, cpoint::MAP_SIZE> _m;
    cpoint _curr; // current position of the bullet

public:
    cbullet();

    void updateMap(int, int, cpoint);
    cpoint getCurr() const { return _curr; }
    void setCurr(cpoint tcurr) { _curr = tcurr; }
    cpoint* getP() { return _p.data(); }
    int getSpeed() const { return _speed; }
    int getN() const { return _n; }
    void setN(int tn) { _n = tn; }
    void setSpeed(int tspeed) { _speed = tspeed; }

    int queryCFromRowCol(int, int);
    int calcPathBullet(cpoint);
};
