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
    int _index;
    bool _isActive;

public:
    cbullet();
    cbullet(int speed, cpoint pos, int damage, vector<cpoint> path, int index, bool isActive);

    cpoint getCurr() const;
    void setCurr(cpoint pos);

    int getSpeed() const;
    void setSpeed(int speed);

    int getDamage() const;
    void setDamage(int damage);

    int getIndex() const;
    void setIndex(int index);

    bool isActive() const;
    void setIsActive(bool active);

    vector<cpoint> getPath() const;
    void setPath(const vector<cpoint>& path);

    void updateStatus();
    bool checkCollisionWithEnemy(const vector<cenemy>& enemies);
    void move(vector<cenemy>& enemies);
};
