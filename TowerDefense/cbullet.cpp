#include "cbullet.h"

cbullet::cbullet() : cbullet(0, cpoint(), 0, {}, 0) {}

cbullet::cbullet(int speed, cpoint pos, int damage, vector<cpoint> bpath, int index) : _speed(speed), _bpos(pos), _damage(damage), _bpath(bpath), _index(index) {}

cpoint cbullet::getCurr() const { return _bpos; }
void cbullet::setCurr(cpoint pos) { _bpos = pos; }

int cbullet::getSpeed() const { return _speed; }
void cbullet::setSpeed(int speed) { _speed = speed; }

int cbullet::getDamage() const { return _damage; }
void cbullet::setDamage(int damage) { _damage = damage; }

int cbullet::getIndex()
{
	return _index;
}

void cbullet::setIndex(int index)
{
	_index = index;
}

vector<cpoint> cbullet::getPath() const { return _bpath; }

void cbullet::setPath(vector<cpoint> path)
{
	_bpath = path;
}

