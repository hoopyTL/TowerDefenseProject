﻿#pragma once
#include "cpoint.h"
#include "cenemy.h"

#define UP_LEFT     0
#define UP          1
#define UP_RIGHT    2
#define RIGHT       3
#define DOWN_RIGHT  4
#define DOWN        5
#define DOWN_LEFT   6
#define LEFT        7


struct Treach 
{
    cpoint point;  
    int index;     
    int step; 

    Treach(const cpoint& p, int idx, int stp)
        : point(p), index(idx), step(stp) {}
};

class ctower 
{
private:
    cpoint _tpos;
    vector<Treach> _treach;
public:
    ctower();
    ctower(cpoint tpos);

    cpoint getCurr() const;
    int getDamage() const;
    vector<Treach> getTreach() const;

    void setCurr(const cpoint& pos);
    void setDamage(int damage);

    void createTreach(const vector<cenemy>& enemies);

    int calculateShootDirection(const vector<cenemy>& enemiesList, int& pathIndex) const;
};
