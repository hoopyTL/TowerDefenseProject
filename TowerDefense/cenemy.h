#pragma once
#include "cpoint.h"
#include <array>

class cenemy {
private:
    int _speed;
    cpoint _start, _end, _curr;
    std::array<cpoint, cpoint::MAP_SIZE* cpoint::MAP_SIZE> _p; // Lộ trình cố định
    int _stepIndex; // Chỉ số hiện tại trong lộ trình

public:
    cenemy();
    cenemy(cpoint tstart, cpoint tend, cpoint tcurr);

    cpoint getStart() const { return _start; }
    cpoint getEnd() const { return _end; }
    int getSpeed() const { return _speed; }
    cpoint getCurr() const { return _curr; }

    void setSpeed(int tspeed) {
        if (tspeed > 0 && tspeed < 10) _speed = tspeed;
    }
    void setStart(cpoint tstart) { _start = tstart; }
    void setEnd(cpoint tend) { _end = tend; }
    void setCurr(cpoint tcurr) { _curr = tcurr; }

    void setPath(const std::array<cpoint, cpoint::MAP_SIZE* cpoint::MAP_SIZE>& path); // Đặt lộ trình cố định
    void moveAlongPath(); // Di chuyển theo lộ trình
};
