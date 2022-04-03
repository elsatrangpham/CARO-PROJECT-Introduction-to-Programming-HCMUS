#pragma once
#include"Header.h"
#include"Board.h"
#include"Game.h"
#include"Menu.h"

struct _POINT {
	int x, y, c;
};

struct Player {
	string name;
	int step = 0;
	int win = 0, lose = 0, draw = 0;
};

_POINT _A[BOARD_SIZE][BOARD_SIZE]; // matrix board
bool _TURN; // true: 1st player's turn; false: 2nd player's turn0
int _COMMAND; // variable that receives the user-entered key value
int _X, _Y; // coordinate on board
Player p1, p2;
string MENU[MAX_MENU] = { " NEW GAME ", "LOAD  GAME", "   ABOUT  ", "   HELP   ", "   EXIT   " };