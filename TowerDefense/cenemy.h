#pragma once
#include "cpoint.h"
#include <vector>
#include <mutex>

using namespace std;

class cenemy 
{
private:
    int _speed;                   
    double _health;                  
    cpoint _epos;                 
    vector<cpoint> _epath;        
    int _index;                   
    bool _isAlive;                

public:
    // Constructors
    cenemy();
    cenemy(int speed, double health, cpoint pos, vector<cpoint> path);

    int getSpeed() const;
    double getHealth() const;
    cpoint getCurr() const;
    vector<cpoint> getPath() const;
    int getIndex() const;
    bool isAlive() const;

    void setSpeed(int speed);
    void setHealth(double health);
    void setCurr(cpoint pos);
    void setPath(const vector<cpoint>& path);
    void setIndex(int index);
    void setAlive(bool alive);

    void decreaseHealth(int damage);
};
