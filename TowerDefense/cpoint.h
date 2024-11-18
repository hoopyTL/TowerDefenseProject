#pragma once

class cpoint {
public:
    // Constants and data
    const static int MAP_SIZE = 14; // Map matrix size
    const static int LEFT = 3;      // Left–coordinates of the map screen
    const static int TOP = 1;       // Top-coordinates of map screen

private:
    int x, y;

public:
    cpoint() : x(0), y(0){}
    cpoint(int tx, int ty) : x(tx), y(ty) {}

    int getX() const { return x; }
    int getY() const { return y; }
    /*int getC() const { return c; }
    void setC(int tc) { c = tc; }*/

    static cpoint fromXYToRowCol(const cpoint& v);
    static cpoint fromRowColToXY(const cpoint& s);
};
