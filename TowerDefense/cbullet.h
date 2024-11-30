#pragma once
#include "cpoint.h"
#include "cenemy.h"
#include <vector>

using namespace std;

class cbullet {
private:
    cpoint _bpos;
    int _damage;
    vector<cpoint> _bpath;
    bool _isActive;

public:
    cbullet();
    cbullet(cpoint pos, int damage, vector<cpoint> path);

    cpoint getCurr() const;
    int getDamage() const;
    bool isActive() const;

    void setCurr(cpoint pos);
    void setDamage(int damage);
    void setActive(bool active);

    vector<cpoint>& getPath();
    void setPath(const vector<cpoint>& path);
};
