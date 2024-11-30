// ctool.cpp
#include "ctool.h"

HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
HWND consoleWindow = GetConsoleWindow();
std::mutex ctool::mtx;

void ctool::ShowConsoleCursor(bool showFlag) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleOutput, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(consoleOutput, &cursorInfo);
}

void ctool::GotoXY(int x, int y) {
    COORD crd = { x, y };
    SetConsoleCursorPosition(consoleOutput, crd);
}

void ctool::Draw(string str, int i, const vector<cpoint>& p, cpoint& _p) {
    std::lock_guard<std::mutex> lock(mtx);
    _p = p[i];
    ctool::GotoXY(_p.getX(), _p.getY());
    cout << str << RESET_COLOR;
}


void ctool::printLogo() {
    system("cls");

    std::ifstream logo_file("./images/logo.txt");
    if (!logo_file) {
        std::cout << "Cannot open file!\n";
        return;
    }

    
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(consoleOutput, &csbi);

    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    
    setColor(BG_WHITE, BG_RED);

   
    int yPosStart = (consoleHeight / 2) - 5;

    std::string line;
    int lineIndex = 0;
    while (getline(logo_file, line)) {
        int xPos = (consoleWidth - line.length()) / 2;
        int yPos = yPosStart + lineIndex;
        GotoXY(xPos, yPos);
        std::cout << line;
        lineIndex++;
        Sleep(100); 
    }

    setDefaultColor(); 
    logo_file.close();
}

bool ctool::printExit()
{
    std::cout << "Do you wish to exit?: [0 == yes / 1 == no]\n";
    int option = _getch();

    while (option != '0' && option != '1')
    {
        std::cout << "Please type 0 or 1.\n";
        option = _getch();
    }

    if (option == '0')
    {
        system("cls");
        std::cout << "Thank you for playing this game.\n";
PlaySound(TEXT("exit.wav", NULL, SND_FILENAME | SND_ASYNC));
        return true;
    }

    system("cls");
    std::cout << "Returning...\n";

    return false;
}

void ctool::printMenu()
{
    
    SetConsoleTextAttribute(consoleOutput, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);

  
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(consoleOutput, &csbi);
    DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;

   
    DWORD written;
    FillConsoleOutputAttribute(consoleOutput, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED, consoleSize, { 0, 0 }, &written);
    printLogo();
    Sleep(500);

    system("cls");
    std::cout << "Loading menu...\n";
    Sleep(200);

    int menu_option;

    while (true)
    {
        system("cls");

        std::cout << "-----PRESS A NUMBER TO CONTINUE-----\n";
        setColor(BG_BLACK, BG_LIGHT_YELLOW);
        std::cout << "  1.PLAY\n";
        std::cout << "  2.SAVE\n";
        std::cout << "  3.SETTING\n";
        std::cout << "  4.EXIT\n";
        setDefaultColor();
PlaySound(TEXT("background.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP));
        menu_option = _getch();

        if (menu_option == '1')
        {
PlaySound(0,0,0);
PlaySound(TEXT("mapSound.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP));
            system("cls");
            std::cout << "Starting game...\n";
            Sleep(200); // delay 1 second
            system("cls");
            cout << "Press any key to start demo: ";
            cin.get();
            ctool::ShowConsoleCursor(false);
            break;
        }

        else if (menu_option == '2')
        {
            system("cls");

        }

        else if (menu_option == '3')
        {
            system("cls");

        }

        else if (menu_option == '4')
        {
            if (printExit())
            {
                Sleep(1000);  // delay 1 second  
                break;
            }
        }
        else
        {
            std::cout << "Please choose the correct option.\n";
PlaySound(TEXT("error.wav", NULL, SND_FILENAME | SND_ASYNC));
            Sleep(1000); // delay 1 second
        }
    }
}

void setUpWindow()
{
    setWindowSize();
    setTitle();
    hideCursor();
    hideScrollBar();
}

void setWindowSize()
{
    RECT desktop;

    GetWindowRect(GetDesktopWindow(), &desktop);

    MoveWindow(consoleWindow, 0, 0, desktop.right, desktop.bottom, TRUE);
}

void setColor(int background, int text)
{
    SetConsoleTextAttribute(consoleOutput, background * 16 + text);
}

void setDefaultColor()
{
    SetConsoleTextAttribute(consoleOutput, 15);
}

void hideScrollBar()
{
    ShowScrollBar(consoleWindow, SB_BOTH, 0);
}

void hideCursor()
{
    CONSOLE_CURSOR_INFO ConCurInf;

    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = false;

    SetConsoleCursorInfo(consoleOutput, &ConCurInf);
}

void setTitle()
{
    SetConsoleTitleA("TOEWER-DEFENSE");
}

//void playSound(int audio_pos) {
//    std::string soundFile[] = { "background.wav", "button.wav", "collison.wav", "end.wav", "exit.wav"};
//    std::wstring path = L"./sounds/" + std::wstring(soundFile[audio_pos].begin(), soundFile[audio_pos].end());
//    PlaySound(path.c_str(), NULL, SND_FILENAME | SND_ASYNC);
//}



