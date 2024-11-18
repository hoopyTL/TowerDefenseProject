// ctower.h
#pragma once

#include "cbullet.h"

class ctower {
private:
    cpoint _location;
    cbullet _cb;

public:
    ctower() : _location{ 0, 0} {}

    cpoint getLocation() const { return _location; }
    void setLocation(cpoint tl) { _location = tl; }

    void setMapForBullet(cpoint[][cpoint::MAP_SIZE]);
    void calcPathBullet() { _cb.calcPathBullet(_location); }

    cbullet& getBullet() { return _cb; }
};
