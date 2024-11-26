#include "cpoint.h"

cpoint& cpoint::operator=(const cpoint& other) {
    if (this != &other) {
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}


// Convert screen coordinates (x, y) to grid indices (row, col)
cpoint cpoint::fromXYToRowCol(const cpoint& xyPoint) {
    return {
        (xyPoint.y - Y_OFFSET - MAP_TOP) / CELL_HEIGHT,
        (xyPoint.x - X_OFFSET - MAP_LEFT) / CELL_WIDTH,
        xyPoint.c
    };
}

// Convert grid indices (row, col) back to screen coordinates (x, y)
cpoint cpoint::fromRowColToXY(const cpoint& gridPoint) {
    return {
        CELL_WIDTH * gridPoint.y + X_OFFSET + MAP_LEFT,
        CELL_HEIGHT * gridPoint.x + Y_OFFSET + MAP_TOP,
        gridPoint.c
    };
}

// In cpoint class
double cpoint::distanceTo(const cpoint& other) const {
    // Calculate the difference in x and y coordinates
    int dx = (this->x - other.x);
    int dy = (this->y - other.y);

    // Adjust the distance based on the scaling factors, if necessary
    // If you're calculating in a grid with specific scaling (e.g., non-square cells),
    // you may need to account for `CELL_WIDTH` and `CELL_HEIGHT`
    double scaledDx = dx / (double)cpoint::CELL_WIDTH;
    double scaledDy = dy / (double)cpoint::CELL_HEIGHT;

    // Use the Euclidean distance formula
    return sqrt(scaledDx * scaledDx + scaledDy * scaledDy);
}

// Ph??ng th?c tính s? b??c t? ?i?m này ??n ?i?m khác trên l??i
int cpoint::countSteps(cpoint other) {
    // Ki?m tra n?u hai ?i?m trên cùng m?t ???ng ngang
    if (this->y == other.y) {
        return abs(this->x - other.x) / CELL_WIDTH;  // S? b??c trên cùng m?t ???ng ngang (chia theo CELL_WIDTH)
    }

    // Ki?m tra n?u hai ?i?m trên cùng m?t ???ng d?c
    if (this->x == other.x) {
        return abs(this->y - other.y) / CELL_HEIGHT;  // S? b??c trên cùng m?t ???ng d?c (chia theo CELL_HEIGHT)
    }

    // Ki?m tra n?u hai ?i?m trên cùng m?t ???ng chéo
    if (abs(this->x - other.x) == abs(this->y - other.y)) {
        // N?u ?i chéo, m?i b??c chéo s? tính là 1 b??c, m?c dù kho?ng cách th?c t? là CELL_WIDTH + CELL_HEIGHT
        return max(abs(this->x - other.x) / CELL_WIDTH, abs(this->y - other.y) / CELL_HEIGHT);
    }

    // N?u không cùng trên m?t ???ng, không th? ?i tr?c ti?p
    return -1;
}


bool cpoint::operator==(const cpoint& other) const {
    return x == other.x && y == other.y;
}

bool cpoint::operator!=(const cpoint& other) const {
    return !(*this == other);
}
