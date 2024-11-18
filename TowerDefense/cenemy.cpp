#include "cenemy.h"

cenemy::cenemy() : _speed(3), _start{ 0, 0 }, _end{ 0, 0 }, _curr{ 0, 0 }, _stepIndex(0) {
    _p.fill({ -1, -1 }); // Lộ trình ban đầu là rỗng
}

cenemy::cenemy(cpoint tstart, cpoint tend, cpoint tcurr)
    : cenemy() {
    _start = tstart;
    _end = tend;
    _curr = tcurr;
}

void cenemy::setPath(const std::array<cpoint, cpoint::MAP_SIZE* cpoint::MAP_SIZE>& path) {
    _p = path;
    _stepIndex = 0; // Bắt đầu từ bước đầu tiên của lộ trình
}


void cenemy::moveAlongPath() {
    if (_stepIndex < _p.size() && _p[_stepIndex].getX() != -1 && _p[_stepIndex].getY() != -1) {
        _curr = _p[_stepIndex]; // Cập nhật vị trí hiện tại
        _stepIndex++;           // Tiến tới bước tiếp theo
    }
    else {
        // Lộ trình đã hoàn thành hoặc không hợp lệ
        _stepIndex = 0; // Reset để bắt đầu lại nếu cần
    }
}
