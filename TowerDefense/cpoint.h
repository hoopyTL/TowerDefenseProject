#pragma once
#include <cmath>
#include <vector>

using namespace std;

class cpoint {
public:
    // Constants and data
    const static int MAP_HEIGHT = 20; // Map matrix size
    const static int MAP_WIDTH = 47; // Map matrix size

    const static int MAP_LEFT = 3;      // Left-coordinates of the map screen
    const static int MAP_TOP = 0;       // Top-coordinates of the map screen

    // Constants for grid calculations
    const static int CELL_WIDTH = 3;
    const static int CELL_HEIGHT = 2;  // Vertical distance between rows
    const static int X_OFFSET = 2;      // Adjustment for X coordinate in grid
    const static int Y_OFFSET = 2;      // Adjustment for Y coordinate in grid

private:
    int x, y;    // Coordinates of the point
    int c;       // New integer attribute (you can use it as a "cost" or other data)

public:
    // Constructors
    cpoint() : x(0), y(0), c(0) {}          // Default constructor, initializing c to 0
    cpoint(int tx, int ty, int tc) : x(tx), y(ty), c(tc) {}  // Constructor with coordinates and c

    // Getter for c
    int getC() const { return c; }

    // Setter for c
    void setC(int tc) { c = tc; }

    // Getter for x and y
    int getX() const { return x; }
    int getY() const { return y; }

    // Setter for x and y
    void setX(int tx) { x = tx; }
    void setY(int ty) { y = ty; }

    // Assignment operator for cpoint
    cpoint& operator=(const cpoint& other);

    // Static methods for coordinate conversion
    static cpoint fromXYToRowCol(const cpoint& v);
    static cpoint fromRowColToXY(const cpoint& s);

    // New methods
    double distanceTo(const cpoint& other) const; // Calculate distance to another point
    int countSteps(cpoint other);

    // Operator overloading
    bool operator==(const cpoint& other) const;  // Compare two points
    bool operator!=(const cpoint& other) const;  // Check inequality of two points
};
