#pragma once

#include "cpoint.h"
#include <mutex>
#include "windows.h"
#include <conio.h>
#include <iostream>
#include "UI.h"
#include <fstream>
#include <string>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

using namespace std;

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
    /* static void  printSave();
     static void printLoad();*/
    static void printRectangle(int, int, int, int);
    //static bool saveGame(const string& playerName, const string& mapName, const vector<cenemy>& enemies);
    //static bool loadGame(string& playerName, string& mapName, vector<cenemy>& enemies);
};

void setUpWindow();
void setWindowSize();
void setColor(int background, int text);
void setDefaultColor();
void hideScrollBar();
void hideCursor();
void setTitle();

void playSound(int audio_pos, int volume);
void stopSound();
void adjustVolume();
