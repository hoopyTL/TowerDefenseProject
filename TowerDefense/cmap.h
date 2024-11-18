#pragma once
#include "ctool.h"
#include "cenemy.h"
#include "ctower.h"
#include <vector>  // For handling multiple towers and enemies

using namespace std;

class cmap {
private:
    vector <cenemy> _ce;      // Vector to hold multiple enemies
    vector <ctower> _ctw;       // Vector to hold multiple towers
    cpoint _m[cpoint::MAP_SIZE][cpoint::MAP_SIZE];
    int _width;
    int _height;
    int _score;
    bool _isGameOver;
    
    array<cpoint, 196> _path;     // Thêm thuộc tính path lưu trữ lộ trình
public:
    cmap();

    void resetMapData();
    void makeMapData();
    void drawMap();

    vector <cenemy>& getEnemies() { return _ce; }
    vector <ctower>& getTowers() { return _ctw; }

    // Phương thức để thiết lập lộ trình
    void setPath(const std::array<cpoint, 196>& path) { _path = path; }

    // Phương thức để truy xuất lộ trình
    const std::array<cpoint, 196>& getPath() const { return _path; }

};