#pragma once
#include "cpoint.h"
#include "cenemy.h"
#include "define.h"


struct Treach 
{
    cpoint pos;  
    int index;     
    int step; 

    Treach(const cpoint& p, int idx, int stp)
        : pos(p), index(idx), step(stp) {}
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
    vector<Treach> getTreach() const;

    void setCurr(const cpoint& pos);
    void createTreach(const vector<cenemy>& enemies);

    int calShootDirection(const vector<cenemy>& enemiesList, int& pathIndex) const;
};
