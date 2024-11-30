#include "cenemy.h"

cenemy::cenemy() :_speed(0), _health(100), _epos(cpoint()), _epath({}), _index(0), _isAlive(true) {}

cenemy::cenemy(int speed, int health, cpoint pos, vector <cpoint> path, int index, bool isAlive)
    : _speed(speed), _health(health), _epos(pos), _epath(path), _index(index), _isAlive(isAlive) {}

// cenemy::cenemy(cenemy other) : cenemy(other.speed, other.health, other.pos, other.path, other.index, other.isAlive)

// Getters
int cenemy::getSpeed() const { return _speed; }
int cenemy::getHealth() const { return _health; }
cpoint cenemy::getCurr() const { return _epos; }
vector<cpoint> cenemy::getPath() const { return _epath; }
int cenemy::getIndex() const { return _index; }
bool cenemy::isAlive() const { return _isAlive; }

// Setters
void cenemy::setSpeed(int tspeed) 
{ 
    //std::lock_guard<std::mutex> lock(enemyMutex); 
    _speed = tspeed;
}
void cenemy::setHealth(int thealth) { //std::lock_guard<std::mutex> lock(enemyMutex);     
_health = thealth; }
void cenemy::setCurr(cpoint pos) { //std::lock_guard<std::mutex> lock(enemyMutex);   
_epos = pos; }
void cenemy::setPath(const vector<cpoint>& path) { //std::lock_guard<std::mutex> lock(enemyMutex);    
_epath = path; }
void cenemy::setIndex(int index) { //std::lock_guard<std::mutex> lock(enemyMutex);    
_index = index; }
void cenemy::setAlive(bool alive) { //std::lock_guard<std::mutex> lock(enemyMutex);   
_isAlive = alive; }

void cenemy::decreaseHealth(int damage) 
{
    //std::lock_guard<std::mutex> lock(enemyMutex);
    _health -= damage;
}

//void cenemy::updateStatus() 
//{
//    if (_health <= 0 || _index >= _epath.size()) 
//    {
//        _isAlive = false;
//    }
//}
//
//void cenemy::move() {
//    if (_isAlive) {
//        if (_index < _epath.size()) {
//            _epos = _epath[_index];
//            _index += _speed;
//
//            // Ensure index does not go beyond path size
//            if (_index >= _epath.size()) {
//                _index = _epath.size() - 1;  // Prevents going past the last position
//            }
//        }
//
//        // Update enemy status (alive or dead)
//        updateStatus();
//    }
//}




