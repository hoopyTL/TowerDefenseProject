#pragma once
#include "cpoint.h"
#include "ctower.h"
#include "cenemy.h"
#include <vector>

class ctower;

class cbullet 
{
private:
    int _speed;                  
    cpoint _bpos;               
    int _damage;                 
    vector<cpoint> _bpath;   
    int _index;
public:
    cbullet();
    cbullet(int, cpoint, int, vector <cpoint>, int);

    cpoint getCurr() const;
    void setCurr(cpoint pos);

    int getSpeed() const;
    void setSpeed(int speed);

    int getDamage() const;
    void setDamage(int damage);

    int getIndex();
    void setIndex(int);

    vector<cpoint> getPath() const;
    void setPath(vector<cpoint> path);
};
