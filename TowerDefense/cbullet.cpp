#include "cbullet.h"

cbullet::cbullet()
    : _speed(1), _bpos(cpoint()), _damage(0), _bpath({}), _index(0), _isActive(true) {}

cbullet::cbullet(int speed, cpoint pos, int damage, vector<cpoint> path, int index, bool isActive)
    : _speed(speed), _bpos(pos), _damage(damage), _bpath(path), _index(index), _isActive(isActive) {}

cpoint cbullet::getCurr() const { return _bpos; }
void cbullet::setCurr(cpoint pos) { _bpos = pos; }

int cbullet::getSpeed() const { return _speed; }
void cbullet::setSpeed(int speed) { _speed = speed; }

int cbullet::getDamage() const { return _damage; }
void cbullet::setDamage(int damage) { _damage = damage; }

int cbullet::getIndex() const { return _index; }
void cbullet::setIndex(int index) { _index = index; }

bool cbullet::isActive() const { return _isActive; }
void cbullet::setIsActive(bool active) { _isActive = active; }

vector<cpoint> cbullet::getPath() const { return _bpath; }
void cbullet::setPath(const vector<cpoint>& path) { _bpath = path; }

//void cbullet::updateStatus() 
//{
//    if (_index >= _bpath.size()) {
//        _isActive = false; // Đạn không còn hoạt động nếu đã ra khỏi đường bay
//    }
//}

//bool cbullet::checkCollisionWithEnemy(const vector<cenemy>& enemies) {
//    for (const auto& enemy : enemies) {
//        if (_bpos == enemy.getCurr() && enemy.isAlive()) {
//            return true; // Nếu đạn va chạm với kẻ thù, trả về true
//        }
//    }
//    return false; // Nếu không có va chạm
//}
//
//void cbullet::move(vector<cenemy>& enemies) {
//    if (_isActive) {
//        if (_index < _bpath.size()) {
//            _bpos = _bpath[_index];
//            _index += _speed;
//
//            if (_index >= _bpath.size()) {
//                _index = _bpath.size();
//            }
//
//            // Check collision and apply damage
//            if (checkCollisionWithEnemy(enemies)) {
//                for (auto& enemy : enemies) {
//                    if (_bpos == enemy.getCurr() && enemy.isAlive()) {
//                        enemy.decreaseHealth(_damage);  // Apply damage to the enemy
//                        _isActive = false;  // Deactivate the bullet after collision
//                        break;
//                    }
//                }
//            }
//        }
//        updateStatus();
//    }
//}

