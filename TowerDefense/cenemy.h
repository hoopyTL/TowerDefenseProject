#pragma once
#include "cpoint.h"
#include <vector>
#include <mutex>

using namespace std;

class cenemy {
private:
    //std::mutex enemyMutex;
    int _speed;                   // Tốc độ di chuyển
    int _health;                  // Máu của enemy
    cpoint _epos;                 // Vị trí hiện tại
    vector<cpoint> _epath;        // Đường đi
    int _index;                   // Vị trí hiện tại trên đường đi
    bool _isAlive;                // Trạng thái sống/chết

public:
    // Constructors
    cenemy();
    cenemy(int speed, int health, cpoint pos, vector<cpoint> path, int index = 0, bool isAlive = true);

    // Getters
    int getSpeed() const;
    int getHealth() const;
    cpoint getCurr() const;
    vector<cpoint> getPath() const;
    int getIndex() const;
    bool isAlive() const;

    // Setters
    void setSpeed(int tspeed);
    void setHealth(int thealth);
    void setCurr(cpoint pos);
    void setPath(const vector<cpoint>& path);
    void setIndex(int index);
    void setAlive(bool alive);

    // Methods
    void decreaseHealth(int damage);
    //void updateStatus();

    //void move();
};
