#include "cpoint.h"

cpoint cpoint::fromXYToRowCol(const cpoint& v) {
    return { (v.y - 1 - TOP) / 2, (v.x - 2 - LEFT) / 4};
}

cpoint cpoint::fromRowColToXY(const cpoint& s) {
    return { 4 * s.y + 2 + LEFT, 2 * s.x + 1 + TOP};
}

