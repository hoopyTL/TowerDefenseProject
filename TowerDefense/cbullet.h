#pragma once
#include "cpoint.h"
#include "cenemy.h"
#include <vector>

using namespace std;

class cbullet {
private:
    int _speed;
    cpoint _bpos;
    int _damage;
    vector<cpoint> _bpath;
    bool _isActive;

public:
    cbullet();
    cbullet(int speed, cpoint pos, int damage, vector<cpoint> path, bool isActive);

    cpoint getCurr() const;
    int getSpeed() const;
    int getDamage() const;
    bool isActive() const;

    void setCurr(cpoint pos);
    void setSpeed(int speed);
    void setDamage(int damage);
    void setIsActive(bool active);

    vector<cpoint>& getPath();
    void setPath(const vector<cpoint>& path);
};
