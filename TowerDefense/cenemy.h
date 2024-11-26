#pragma once
#include "cpoint.h"
#include <vector>

using namespace std;

class cenemy
{
private:
    int _speed;
    int _health;
    cpoint _epos;
    vector<cpoint> _epath;
    int _index;                     

public:
    cenemy();
    cenemy(int speed, int health, cpoint pos, vector<cpoint> path, int index);

    int getSpeed() const { return _speed; }
    int getHealth() const { return _health; }
    cpoint getCurr() const { return _epos; }
    vector<cpoint> getPath() const { return _epath; }
    int getIndex() const { return _index; }  

    void setSpeed(int tspeed) { _speed = tspeed; }
    void setHealth(int thealth) { _health = thealth; }
    void setCurr(cpoint pos) { _epos = pos; }
    void setPath(const vector<cpoint>& path) { _epath = path; }
    void setIndex(int index) { _index = index; }

    void decreaseHealth(int damage);
};
