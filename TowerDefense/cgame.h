#pragma once
#include "cmap.h"

class cgame {
private:
    vector <cmap> _map;
    bool _ISEXIT1, _ISEXIT2;

public:
    cgame();

    bool getIsExist1() const { return _ISEXIT1; }
    void setIsExist1(bool b) { _ISEXIT1 = b; }
    bool getIsExist2() const { return _ISEXIT2; }
    void setIsExist2(bool b) { _ISEXIT2 = b; }

    void setMap(cmap map);
    vector <cmap>& getMap() { return _map; }
    void startGame();
};