// ctool.cpp
#include "ctool.h"
#include "Sound.h"

HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
HWND consoleWindow = GetConsoleWindow();
std::mutex ctool::mtx;

bool ctool::sound_is_open;
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

void ctool::Settings() {
    int option = 0;  // Mặc định chọn mục đầu tiên
    bool soundStatus = ctool::sound_is_open;  // Lưu trạng thái âm thanh (Bật/Tắt)

    while (true) {
        system("cls");  // Xóa màn hình
        std::cout << "-----AUDIO SETTINGS-----\n";

        // Vẽ các ô cho từng mục
        printRectangle(5, 5, 30, 3);  // Ô cho Sound
        printRectangle(5, 9, 30, 3);  // Ô cho Back to Main Menu

        // In các lựa chọn trong các ô chữ nhật
        for (int i = 0; i < 2; ++i) {
            // Nếu đang chọn mục này, tô màu xanh
            if (i == option) {
                setColor(BG_BLACK, BG_LIGHT_BLUE);  // Highlight in blue
            }
            else {
                setDefaultColor();  // Các mục còn lại dùng màu mặc định
            }

            // In các mục menu vào giữa các ô chữ nhật
            ctool::GotoXY(7, 6 + i * 4);  // Vị trí chữ trong ô
            switch (i) {
            case 0: std::cout << "Sound (" << (soundStatus ? "ON" : "OFF") << ")"; break;
            case 1: std::cout << "Back to Main Menu"; break;
            }
        }

        setDefaultColor();  // Reset lại màu sắc

        // Nhận đầu vào từ người dùng (phím mũi tên hoặc Enter)
        char ch = _getch();

        // Điều hướng lên/xuống
        if (ch == KEY_UP) {  // Di chuyển lên
            option = (option > 0) ? option - 1 : 1;
        }
        else if (ch == KEY_DOWN) {  // Di chuyển xuống
            option = (option + 1) % 2;  // Nếu ở cuối, quay lại đầu
        }
        else if (ch == KEY_ENTER) {  // Chọn
            if (option == 0) {  // Toggle âm thanh
                soundStatus = !soundStatus;  // Thay đổi trạng thái âm thanh
                ctool::sound_is_open = soundStatus;  // Cập nhật trạng thái âm thanh
                if (ctool::sound_is_open) {
                    Sound::playSound(BACKGROUND_SOUND);  // Phát nhạc nền nếu bật âm thanh
                }
                else {
                    Sound::stopSound();  // Dừng nhạc nền nếu tắt âm thanh
                }
            }
            else if (option == 1) {  // Quay lại Menu chính
                break;
            }
        }
        else if (ch == 27) {  // Phím ESC để quay lại
            break;
        }
    }
}



void ctool::printAbout() {
    system("cls");
    std::cout << "----- ABOUT THE GAME -----\n";
    setColor(BG_BLACK, BG_LIGHT_YELLOW);

    // Hiển thị thông tin về game
    std::cout << "\nTower Defense, also known as Tower Defense Game, is a subgenre of real-time strategy games.\n";
    std::cout << "In this game, players must defend a structure or area from waves of enemies\n";
    std::cout << "by placing defensive towers along their path. Each tower has different abilities\n";
    std::cout << "and can be upgraded to increase its effectiveness.\n";
    std::cout << "\nThe goal is to prevent the enemies from reaching your base while managing\n";
    std::cout << "resources to build stronger defenses.\n\n\n";
    std::cout << "\nPress ESC to go back to the main menu.\n\n\n";

    setDefaultColor();

    // Thêm thông tin về người viết code
    std::cout << "\n----- GROUP 4 -----\n";
    std::cout << "1. Dinh Anh Duong \n";
    std::cout << "2. Nguyen Van Hop\n";
    std::cout << "3. Tran So Vinh\n";
    std::cout << "4. Nguyen Nhat Hoang\n";

    // Thêm thông tin người hướng dẫn
    std::cout << "\n----- INSTRUCTOR -----\n";
    std::cout << "MR Truong Toan Thinh\n";

    setDefaultColor();

    // Chờ người dùng nhấn phím ESC để quay lại
    while (true) {
        char ch = _getch();
        if (ch == 27) {  // Phím ESC để quay lại
            break;
        }
    }
}

void ctool::printRectangle(int left, int top, int width, int height)
{
    ctool::GotoXY(left, top);
    putchar(218);
    for (int i = 0; i < width; i++) {
        putchar(196);
    }
    putchar(191);
    int i = 0;
    for (; i < height; i++)
    {
        ctool::GotoXY(left, top + i + 1);
        putchar(179);
        ctool::GotoXY(left + width + 1, top + i + 1);
        putchar(179);
    }

    ctool::GotoXY(left, top + i);
    putchar(192);
    for (i = 0; i < width; i++)
        putchar(196);
    putchar(217);
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

    int menu_option = 0; // Mặc định chọn mục đầu tiên

    while (true)
    {
        system("cls");

        // Hiển thị tiêu đề menu
        std::cout << "-----TOWER DEFENSE-----\n";

        // Vẽ các ô cho từng mục
        printRectangle(5, 5, 20, 3); // Cho mục 1: "PLAY"
        printRectangle(5, 9, 20, 3);  // Cho mục 2: "SAVE"
        printRectangle(5, 13, 20, 3); // Cho mục 3: "SETTING"
        printRectangle(5, 17, 20, 3); // Cho mục 4: "ABOUT"
        printRectangle(5, 21, 20, 3); // Cho mục 5: "EXIT"

        // In các lựa chọn menu trong các ô chữ nhật
        for (int i = 0; i < 5; ++i) {
            // Nếu đang chọn mục này, tô màu xanh
            if (i == menu_option) {
                setColor(BG_BLACK, BG_LIGHT_BLUE);  // Highlight in blue
            }
            else {
                setDefaultColor();  // Các mục còn lại dùng màu mặc định
            }

            // In các mục menu vào giữa các ô chữ nhật
            ctool::GotoXY(7, 6 + i * 4);
            switch (i) {
            case 0: std::cout << "1. PLAY"; break;
            case 1: std::cout << "2. SAVE"; break;
            case 2: std::cout << "3. SETTING"; break;
            case 3: std::cout << "4. ABOUT"; break;
            case 4: std::cout << "5. EXIT"; break;
            }
        }

        setDefaultColor(); // Reset lại màu sắc

        // Lấy đầu vào từ người dùng (phím mũi tên hoặc Enter)
        char menu_option_input = _getch();

        // Xử lý di chuyển lên/xuống
        if (menu_option_input == 'w' || menu_option_input == KEY_UP) {  // Di chuyển lên
            menu_option = (menu_option > 0) ? menu_option - 1 : 4;  // Nếu đã ở đầu, quay lại cuối
        }
        else if (menu_option_input == 's' || menu_option_input == KEY_DOWN) {  // Di chuyển xuống
            menu_option = (menu_option + 1) % 5;  // Nếu đã ở cuối, quay lại đầu
        }
        // Nếu nhấn phím Enter, mở ra màn hình tương ứng
        else if (menu_option_input == 13) {  // Enter key
            switch (menu_option) {
            case 0:
                system("cls");
                std::cout << "Starting game...\n";
                Sleep(200); // Delay 1 giây
                system("cls");
                std::cout << "Press any key to start demo: ";
                std::cin.get();
                ctool::ShowConsoleCursor(false);
                return;  // Đã chọn "PLAY", thoát menu
            case 1:
                system("cls");
                std::cout << "Loading save...\n";
                // Logic cho mục SAVE
                break;
            case 2:
                system("cls");
                ctool::Settings(); // Mở menu SETTINGS
                break;
            case 3:
                system("cls");
                ctool::printAbout();  // Mở ABOUT
                break;
            case 4:
                if (printExit()) {
                    Sleep(1000);  // Delay 1 giây
                    return;  // Thoát game khi chọn EXIT
                }
                break;
            default:
                break;
            }
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




