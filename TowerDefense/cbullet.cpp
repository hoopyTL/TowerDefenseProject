#include "cbullet.h"

cbullet::cbullet() {
    _n = 0;
    _speed = 4;
    _curr = { 0, 0};
    // Initialize the bullet path array
    for (int i = 0; i < cpoint::MAP_SIZE * cpoint::MAP_SIZE; i++) {
        _p[i] = { 0, 0};
    }
    // Initialize the map matrix
    for (int i = 0; i < cpoint::MAP_SIZE; i++) {
        for (int j = 0; j < cpoint::MAP_SIZE; j++) {
            _m[i][j] = { 0, 0};
        }
    }
}

void cbullet::updateMap(int i, int j, cpoint v) {
    // Ensure i and j are within bounds of the map
    if (i >= 0 && i < cpoint::MAP_SIZE && j >= 0 && j < cpoint::MAP_SIZE) {
        _m[i][j] = v;
    }
}

int cbullet::queryCFromRowCol(int row, int col) {
    // Check for out-of-bounds coordinates
    if (row < 0 || row >= cpoint::MAP_SIZE || col < 0 || col >= cpoint::MAP_SIZE) {
        return -2;
    }

    // Search the map for the corresponding point
    for (int i = 0; i < cpoint::MAP_SIZE; i++) {
        for (int j = 0; j < cpoint::MAP_SIZE; j++) {
            cpoint tmp = cpoint::fromXYToRowCol(_m[i][j]);
        }
    }
    return -1;  // Return -1 if the point was not found
}

int cbullet::calcPathBullet(cpoint tower) {
    // Convert tower's coordinates from XY to RowCol
    cpoint tmp = cpoint::fromXYToRowCol(tower);
    int row = tmp.getX(), col = tmp.getY(), i = 0;

    // Path calculation loop
    do {
        col++;  // Move right
        row--;  // Move up

        // Check if the current location is an empty space (i.e., query returns 0)
        if (queryCFromRowCol(row, col) == 0) {
            _p[i] = cpoint::fromRowColToXY({ row, col});  // Add to path
            i += 2;  // Move in steps of 2
        }
        else {
            break;  // Stop if the path is blocked
        }
    } while (i < cpoint::MAP_SIZE);

    _n = i;  // Update the number of points in the path

    // Adjust the points for smoother movement
    for (i = 1; i < _n; i += 2) {
        _p[i] = { _p[i - 1].getX() + 2, _p[i - 1].getY() - 1};
    }

    // Set the current position to the first point in the path
    _curr = { _p[0].getX(), _p[0].getY()};

    return _n;  // Return the number of points in the calculated path
}
