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
    static bool sound_is_open;
    static void ShowConsoleCursor(bool showFlag);
    static void GotoXY(int x, int y);
    static void Draw(string str, int i, const vector<cpoint>& path, cpoint& _p);
    static void printLogo();
    static bool printExit();
    static void printMenu();
	static void Settings();
    static void printAbout();
    static void printRectangle(int, int, int, int);			
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
