#include "cenemy.h"

cenemy::cenemy() :_speed(0), _health(100), _epos(cpoint()), _epath({}), _index(0) {}

cenemy::cenemy(int speed, int health, cpoint pos, vector <cpoint> path, int index)
    : _speed(speed), _health(health), _epos(pos), _epath(path), _index(index) {}

void cenemy::decreaseHealth(int damage) 
{
    _health -= damage;
    if (_health < 0) _health = 0;
}


