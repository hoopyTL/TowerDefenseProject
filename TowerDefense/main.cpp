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

    ctool::GotoXY(0, 33); // Di chuyển đến dòng cuối trước khi thoát
    return 0;
}

void ThreadFunc2(cgame& cg) 
{
    int i1 = 0;
    vector<cmap> mapList = cg.getMap();
    cmap map1 = mapList[0];

    vector<cenemy> ceList = map1.getEnemies();
    if (ceList.empty()) return;

    cenemy ce1 = ceList[0]; // Kẻ thù đầu tiên

    vector<ctower> ctowerList = map1.getTowers();
    if (ctowerList.empty()) return;

    ctower ctw1 = ctowerList[0]; // Tháp đầu tiên

    while (!cg.getIsExist1()) 
    {
        map1.addBullet(ctw1);
        vector<cbullet> cbulletList = map1.getBullets();
        if (cbulletList.empty())
        {
            continue;
        }

        cbullet cb1 = cbulletList[0];
        vector<cpoint> bulletPath = cb1.getPath();
        if (bulletPath.empty())
            continue;
        // cout << bulletPath.size();
        // cpoint _BULLET1 = bulletPath[i1];

        // cout << _BULLET1.getX() << "," << _BULLET1.getY() << "\n";
        cpoint _BULLET1 = cb1.getCurr();
        if (i1 < bulletPath.size()) 
        {
            cout << i1;
            ctool::Draw((char*)"\033[34mo\033[0m", i1, bulletPath, _BULLET1);
            cb1.setCurr(_BULLET1);

            // Kiểm tra va chạm
            if (_BULLET1 == ce1.getCurr()) {
                ctool::Draw((char*)" ", i1, bulletPath, _BULLET1);
                cg.setIsExist1(true);
                break;
            }
            else {
                i1++;
                Sleep(1000 / cb1.getSpeed());
                ctool::Draw((char*)" ", i1 - 1, bulletPath, _BULLET1);
            }
        }
    }

    cg.setIsExist2(true);
}

void ThreadFunc1(cgame& cg) {
    vector<cmap> mapList = cg.getMap();
    cmap map1 = mapList[0];

    vector<cenemy> ceList = map1.getEnemies();
    if (ceList.empty()) return;

    cenemy ce1 = ceList[0]; // Enemy đầu tiên
    vector<cpoint> path = ce1.getPath();

    if (path.empty()) return;

    int pathIndex1 = 0;
    cpoint _ENEMY1 = ce1.getCurr();

    while (!cg.getIsExist1()) 
    {
        if (pathIndex1 < path.size()) 
        {
            ctool::Draw((char*)"\033[32mE\033[0m", pathIndex1, path, _ENEMY1);
            pathIndex1++;
            ce1.setCurr(_ENEMY1);

            // Kiểm tra Enemy đạt đích
            if (_ENEMY1 == path.back()) {
                ctool::Draw((char*)" ", pathIndex1 - 1, path, _ENEMY1);
                break;
            }

            Sleep(1000 / ce1.getSpeed());
            ctool::Draw((char*)" ", pathIndex1 - 1, path, _ENEMY1);
        }
    }

    cg.setIsExist1(true);
}
