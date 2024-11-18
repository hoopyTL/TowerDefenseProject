// MainPrg.cpp
#include "cgame.h"
#include <thread>
#include "ctool.h"
using namespace std;

void ThreadFunc2(cgame&);
void ThreadFunc1(cgame&);
int main() {
    ctool::printMenu();
    cgame cg;
    cg.startGame();
    thread t1(ThreadFunc1, std::ref(cg));
    thread t2(ThreadFunc2, std::ref(cg));
    t1.join();
    t2.join();
    ctool::GotoXY(0, 31); // Jump to the last line to exit the program
    return 0;
}
void ThreadFunc2(cgame& cg) {
    int i = 0;

    vector<cmap> mapList = cg.getMap();
    cmap map1 = mapList[0];

    vector<cenemy> ceList = map1.getEnemies(); // Get the list of cenemies
    cenemy ce1 = ceList[0]; // First enemy
    cenemy ce2 = ceList[1]; // Second enemy

    cpoint _ENEMY1;
    cpoint _ENEMY2;

    vector<ctower> ceTowerList = map1.getTowers();
    ctower ctw1 = ceTowerList[0]; // First tower
    ctower ctw2 = ceTowerList[1]; // Second tower

    cbullet& cb1 = ctw1.getBullet(); // Get bullet for first tower
    cbullet& cb2 = ctw2.getBullet(); // Get bullet for second tower

    int _SPEED1 = cb1.getSpeed(), _NBULLET1 = cb1.getN();
    int _SPEED2 = cb2.getSpeed(), _NBULLET2 = cb2.getN();

    cpoint* _BULLET1_P = cb1.getP();
    cpoint* _BULLET2_P = cb2.getP();
    cpoint _BULLET1 = cb1.getCurr();
    cpoint _BULLET2 = cb2.getCurr();

    // Bullet for the first tower
    while (!cg.getIsExist1()) {
        ctool::Draw((char*)"\033[34mo\033[0m", i, _BULLET1_P, _BULLET1);
        cb1.setCurr(_BULLET1);
        _ENEMY1 = ce1.getCurr();
        if (_BULLET1.getX() == _ENEMY1.getX() && _BULLET1.getY() == _ENEMY1.getY()) {
            ctool::Draw((char*)" ", i, _BULLET1_P, _BULLET1);
            cg.setIsExist1(true);
            break;
        }
        else i++;
        Sleep(1000 / _SPEED1);
        ctool::Draw((char*)" ", i - 1, _BULLET1_P, _BULLET1);
        if (i == _NBULLET1) i = 0;
    }

    // Bullet for the second tower
    i = 0; // Reset i for the second bullet
    while (!cg.getIsExist1()) {
        ctool::Draw((char*)"\033[35mo\033[0m", i, _BULLET2_P, _BULLET2);
        cb2.setCurr(_BULLET2);
        _ENEMY2 = ce2.getCurr();
        if (_BULLET2.getX() == _ENEMY2.getX() && _BULLET2.getY() == _ENEMY2.getY()) {
            ctool::Draw((char*)" ", i, _BULLET2_P, _BULLET2);
            cg.setIsExist1(true);
            break;
        }
        else i++;
        Sleep(1000 / _SPEED2);
        ctool::Draw((char*)" ", i - 1, _BULLET2_P, _BULLET2);
        if (i == _NBULLET2) i = 0;
    }

    cg.setIsExist2(true);
}

void ThreadFunc1(cgame& cg) {
    int i1 = 0, i2 = 0; // Separate indices for each enemy

    vector<cmap> mapList = cg.getMap();
    cmap map1 = mapList[0];

    vector<cenemy> ceList = map1.getEnemies(); // Get the list of cenemies
    cenemy ce1 = ceList[0]; // First enemy
    cenemy ce2 = ceList[1]; // Second enemy
    cpoint _ENEMY1 = ce1.getCurr(), _END1 = ce1.getEnd();
    cpoint _ENEMY2 = ce2.getCurr(), _END2 = ce2.getEnd();
    int SPEED1 = ce1.getSpeed();
    int SPEED2 = ce2.getSpeed();

    vector<ctower> ceTowerList = map1.getTowers();
    ctower ctw1 = ceTowerList[0]; // First tower
    ctower ctw2 = ceTowerList[1]; // Second tower

    cbullet& cb1 = ctw1.getBullet(); // Get the cbullet object for the first tower
    cbullet& cb2 = ctw2.getBullet(); // Get the cbullet object for the second tower

    cpoint _BULLET1 = cb1.getCurr();
    cpoint _BULLET2 = cb2.getCurr();

    while (!cg.getIsExist1()) {
        // Manage the first enemy
        ctool::Draw((char*)"\033[32mE\033[0m", i1, _P1, _ENEMY1);
        ce1.setCurr(_ENEMY1);
        if (_ENEMY1.getX() == _END1.getX() && _ENEMY1.getY() == _END1.getY()) {
            break;
        }
        else if (_ENEMY1.getX() == _BULLET1.getX() && _ENEMY1.getY() == _BULLET1.getY()) {
            ctool::Draw((char*)" ", i1, _P1, _ENEMY1);
            break;
        }
        else i1++;
        Sleep(1000 / SPEED1);
        ctool::Draw((char*)" ", i1 - 1, _P1, _ENEMY1);

        // Manage the second enemy
        ctool::Draw((char*)"\033[33mE\033[0m", i2, _P2, _ENEMY2);
        ce2.setCurr(_ENEMY2);
        if (_ENEMY2.getX() == _END2.getX() && _ENEMY2.getY() == _END2.getY()) {
            break;
        }
        else if (_ENEMY2.getX() == _BULLET2.getX() && _ENEMY2.getY() == _BULLET2.getY()) {
            ctool::Draw((char*)" ", i2, _P2, _ENEMY2);
            break;
        }
        else i2++;
        Sleep(1000 / SPEED2);
        ctool::Draw((char*)" ", i2 - 1, _P2, _ENEMY2);
    }
    cg.setIsExist1(true);
}