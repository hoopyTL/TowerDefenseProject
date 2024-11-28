#include "cgame.h"
#include "ctool.h"

int main() {
    ctool::printMenu();
    cgame cg;
    cg.startGame();

    cg.processGame();  // All game logic is now handled in the cgame class

    // ctool::GotoXY(0, 54);  // Move to the last line before exiting
    return 0;
}
