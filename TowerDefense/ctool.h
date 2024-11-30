#pragma once

#include "cpoint.h"
#include "UI.h"
#include <mutex>
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <mmsystem.h>

class ctool 
{
public:
    static mutex mtx;

    static void ShowConsoleCursor(bool showFlag);
    static void GotoXY(int x, int y);
    static void Draw(string str, int i, const vector<cpoint>& path, cpoint& _p);
    static void printLogo();
    static bool printExit();
    static void printMenu();
};

void setUpWindow();
void setWindowSize();
void setColor(int background, int text);
void setDefaultColor();
void hideScrollBar();
void hideCursor();
void setTitle();

// Sound setting
// void playSound(int audio_pos);
