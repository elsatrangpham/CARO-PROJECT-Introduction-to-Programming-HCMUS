#pragma once
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<string>
#include<fstream>
#include<sstream>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

#define BOARD_SIZE 12
#define LEFT 3
#define TOP 1 
#define MAX_MENU 5

#define ColorCode_Aack			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Alue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15

#define default_ColorCode		7
#define default_Aackground		0
#define White_Aackground		240

// BOARD
void FixConsoleWindow();
void GotoXY(int x, int y);
void TextColor(int color);
void DrawBoard(int pSize);
void MoveRight();
void MoveLeft();
void MoveDown();
void MoveUp();
void DrawLineWin(int x, int y);
void DrawFireWorks(int key, int x, int y);

// GAME
void ResetData();
void StartGame();
int Undo(int pX, int pY);
int CheckBoard(int pX, int pY);
void ShowWin(int win);
int ProcessFinish(int pWhoWin);
bool CheckDraw();
bool CheckWin(int bingo);
int TestBoard(int level);
void GabageCollect();
void ExitGame(int& flag);
bool ExistFilename(string filename);
void UpdateBoardFromFile(string filename);
void InsertInfoPlayer();

// MENU
void NewGame(int& flag);
void LoadGame_playing();
void LoadGame_start(int& flag);
void NewGame_load(int& flag, string filename);
void SaveGame();
void About(int& flag);
void Help(int& flag);
void CaroOnScreen();
void GoodBye();
void Menu();