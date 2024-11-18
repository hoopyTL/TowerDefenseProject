#pragma once

#include "cpoint.h"
#include <mutex>
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <mmsystem.h>

using namespace std;

class ctool 
{
public:
    static std::mutex mtx;

    static void ShowConsoleCursor(bool showFlag);
    static void GotoXY(int x, int y);
    static void Draw(const char* str, int i, cpoint p[], cpoint& _p);
    static void printLogo();
    static bool printExit();
    static void printMenu();
};

// Colors
#define BLACK 0      
#define BLUE 1       
#define GREEN 2      
#define AQUA 3       
#define RED 4        
#define PURPLE 5     
#define YELLOW 6     
#define WHITE 7   
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

// Keyboard values
#define SPACE_KEY 32
#define ESC 27
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

// SOUNDTRACK
#define BACKGROUND_SOUND 0
#define BUTTON_SOUND 1
#define COLLISION_SOUND 3
#define SAVE_SOUND 3
#define END_SOUND 4
#define EXIT_SOUND 5


void setUpWindow();
void setWindowSize();
void setColor(int background, int text);
void setDefaultColor();
void hideScrollBar();
void hideCursor();
void setTitle();

// Sound setting
// void playSound(int audio_pos);
