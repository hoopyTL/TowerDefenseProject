#pragma once
#include "cpoint.h"
#include <vector>
#include <mutex>

using namespace std;

class cenemy 
{
private:
    int _speed;                   
    int _health;                  
    cpoint _epos;                 
    vector<cpoint> _epath;        
    int _index;                   
    bool _isAlive;                
    int _cntHit;

public:
    // Constructors
    cenemy();
    cenemy(int speed, int health, cpoint pos, vector<cpoint> path);

    int getSpeed() const;
    int getHealth() const;
    cpoint getCurr() const;
    vector<cpoint> getPath() const;
    int getIndex() const;
    bool isAlive() const;
    int getCntHit() const;

    void setSpeed(int tspeed);
    void setHealth(int thealth);
    void setCurr(cpoint pos);
    void setPath(const vector<cpoint>& path);
    void setIndex(int index);
    void setAlive(bool alive);
    void setCntHit(int hit);

    void decreaseHealth(int damage);
};
