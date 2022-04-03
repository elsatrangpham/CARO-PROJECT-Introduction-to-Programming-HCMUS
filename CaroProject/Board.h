#pragma once
#include"Header.h"
#include"Game.h"
#include"Menu.h"
#include"Point.h"

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void TextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void DrawBoard(int pSize) {
	GotoXY(0, 0);
	for (int i = 0; i <= LEFT + 4 * BOARD_SIZE + 3; i++)
	{
		if (i == 0) putchar(201);
		else if (i == LEFT + 4 * BOARD_SIZE + 3) putchar(187);
		else putchar(205);

	}
	for (int i = 1; i <= TOP + 2 * BOARD_SIZE; i++)
	{
		GotoXY(0, i); putchar(186);
		GotoXY(LEFT + 4 * BOARD_SIZE + 3, i); putchar(186);
	}
	GotoXY(0, TOP + 2 * BOARD_SIZE + 1);
	for (int i = 0; i <= LEFT + 4 * BOARD_SIZE + 3; i++)
	{
		if (i == 0) putchar(200);
		else if (i == LEFT + 4 * BOARD_SIZE + 3) putchar(188);
		else putchar(205);

	}
	for (int i = 0; i <= BOARD_SIZE; i++)
	{
		for (int j = 0; j <= BOARD_SIZE; j++)
		{
			GotoXY(LEFT + 4 * i, TOP + 2 * j);
			cout << ".";
		}
	}

	GotoXY(LEFT + 4 * BOARD_SIZE + 15, 1);
	cout << "XXX   XXX     OOOOOOO";
	GotoXY(LEFT + 4 * BOARD_SIZE + 15, 2);
	cout << " XXX XXX     OOO   OOO";
	GotoXY(LEFT + 4 * BOARD_SIZE + 15, 3);
	cout << "  XXXXX      OOO   OOO    ";
	GotoXY(LEFT + 4 * BOARD_SIZE + 15, 4);
	cout << " XXX XXX     OOO   OOO";
	GotoXY(LEFT + 4 * BOARD_SIZE + 15, 5);
	cout << "XXX   XXX     OOOOOOO";

	// Show player turn 
	GotoXY(LEFT + 6.5 * BOARD_SIZE + 15, 2);
	cout << "TURN: ";
	if (_TURN == 1) {
		GotoXY(LEFT + 6.3 * BOARD_SIZE + 15, 3);
		cout << "Player 1: X";
	}
	else {
		GotoXY(LEFT + 6.3 * BOARD_SIZE + 15, 3);
		cout << "Player 2: O";
	}

	// Show option 
	GotoXY(LEFT + 4 * BOARD_SIZE + 17, 8);
	cout << "N : New Game";
	GotoXY(LEFT + 4 * BOARD_SIZE + 17, 10);
	cout << "L : Save Game";
	GotoXY(LEFT + 4 * BOARD_SIZE + 37, 8);
	cout << "T : Load Game";
	GotoXY(LEFT + 4 * BOARD_SIZE + 37, 10);
	cout << "U : Undo Step";
	GotoXY(LEFT + 4 * BOARD_SIZE + 26, 12);
	cout << "ESC: Return Menu!";

	// Info player
	GotoXY(LEFT + 4 * BOARD_SIZE + 10, 14);
	cout << "Player 1: " << p1.name;
	GotoXY(LEFT + 4 * BOARD_SIZE + 10, 16);
	cout << "Player 2: " << p2.name;
	GotoXY(LEFT + 4 * BOARD_SIZE + 31, 14);
	cout << "Step: " << p1.step;
	GotoXY(LEFT + 4 * BOARD_SIZE + 31, 16);
	cout << "Step: " << p2.step;
	GotoXY(LEFT + 4 * BOARD_SIZE + 48, 14);
	cout << "W/L/D: " << p1.win << "/" << p1.lose << "/" << p1.draw;
	GotoXY(LEFT + 4 * BOARD_SIZE + 48, 16);
	cout << "W/L/D: " << p2.win << "/" << p2.lose << "/" << p2.draw;

	GotoXY(LEFT + 4 * BOARD_SIZE + 10, 0);
	for (int i = LEFT + 4 * BOARD_SIZE + 10; i <= LEFT + 4 * BOARD_SIZE + 60; i++)
	{
		if (i == LEFT + 4 * BOARD_SIZE + 10) putchar(201);
		else if (i == LEFT + 4 * BOARD_SIZE + 60) putchar(187);
		else putchar(205);
	}
	for (int i = 1; i <= 6; i++)
	{
		GotoXY(LEFT + 4 * BOARD_SIZE + 10, i); putchar(186);
		GotoXY(LEFT + 4 * BOARD_SIZE + 60, i); putchar(186);
	}
	GotoXY(LEFT + 4 * BOARD_SIZE + 10, 6);
	for (int i = LEFT + 4 * BOARD_SIZE + 10; i <= LEFT + 4 * BOARD_SIZE + 60; i++)
	{
		if (i == LEFT + 4 * BOARD_SIZE + 10) putchar(200);
		else if (i == LEFT + 4 * BOARD_SIZE + 60) putchar(188);
		else putchar(205);
	}

	GotoXY(_A[0][0].x, _A[0][0].y);
}

void MoveRight() {
	if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x) {
		_X += 4;
		GotoXY(_X, _Y);
	}
}

void MoveLeft() {
	if (_X > _A[0][0].x) {
		_X -= 4;
		GotoXY(_X, _Y);
	}
}

void MoveDown() {
	if (_Y < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y) {
		_Y += 2;
		GotoXY(_X, _Y);
	}
}

void MoveUp() {
	if (_Y > _A[0][0].y) {
		_Y -= 2;
		GotoXY(_X, _Y);
	}
}

void DrawLineWin(int x, int y) {
	int i = 0;
	int count = 0;

	while (x + i < BOARD_SIZE && _A[x][y].c == _A[x + i][y].c) {
		count++;
		i++;
	}

	if (count >= 5) {
		for (int j = 0; j < count; j++) {
			GotoXY(y * 4 + LEFT + 2, (x + j) * 2 + TOP + 1);
			cout << ((_A[x + j][y].c == 1) ? "O" : "X");
		}
		return;
	}

	i = 0; count = 0;
	while (y + i < BOARD_SIZE && _A[x][y].c == _A[x][y + i].c) {
		count++;
		i++;
	}

	if (count >= 5) {
		for (int j = 0; j < count; j++) {
			GotoXY((y + j) * 4 + LEFT + 2, x * 2 + TOP + 1);
			cout << ((_A[x][y + j].c == 1) ? "O" : "X");
		}
		return;
	}

	i = 0; count = 0;
	while (x + i < BOARD_SIZE && y + i < BOARD_SIZE && _A[x][y].c == _A[x + i][y + i].c) {
		count++;
		i++;
	}

	if (count >= 5) {
		for (int j = 0; j < count; j++) {
			GotoXY((y + j) * 4 + LEFT + 2, (x + j) * 2 + TOP + 1);
			cout << ((_A[x + j][y + j].c) == 1 ? "O" : "X");
		}
		return;
	}

	i = 0; count = 0;
	while (x - i >= 0 && y + i < BOARD_SIZE && _A[x][y].c == _A[x - i][y + i].c) {
		count++;
		i++;
	}

	if (count >= 5) {
		for (int j = 0; j < count; j++) {
			GotoXY((y + j) * 4 + LEFT + 2, (x - j) * 2 + TOP + 1);
			cout << ((_A[x - j][y + j].c) == 1) ? "O" : "X";
		}
		return;
	}
}

void DrawFireWorks(int key, int x, int y) {
	switch (key) {
	case 0:
		GotoXY(x, y + 10);
		printf("|");
		break;
	case 1:
		GotoXY(x, y + 10);
		printf(" ");
		GotoXY(x, y + 9);
		printf("|");
		break;
	case 2:
		GotoXY(x, y + 9);
		printf(" ");
		GotoXY(x, y + 8);
		printf("|");
		break;
	case 3:
		GotoXY(x, y + 8);
		printf(" ");
		GotoXY(x, y + 7);
		printf("|");
		break;
	case 4:
		GotoXY(x, y + 7);
		printf(" ");
		GotoXY(x, y + 6);
		printf("|");
		break;
	case 5:
		GotoXY(x, y + 6);
		printf(" ");
		GotoXY(x, y + 5);
		printf("|");
		break;
	case 6:
		GotoXY(x, y + 5);
		printf(" ");
		GotoXY(x, y + 4);
		printf("|");
		break;
	case 7:
		GotoXY(x, y + 4);
		printf(" ");
		GotoXY(x, y + 3);
		printf("|");
		break;
	case 8:
		GotoXY(x, y + 3);
		printf(" ");
		GotoXY(x, y + 2);
		printf("|");
		break;
	case 9:
		GotoXY(x, y + 0);
		printf(" ");
		GotoXY(x, y + 1);
		printf("|");
		break;
	case 10:
		GotoXY(x - 6, y - 3);
		printf("             ");
		GotoXY(x - 6, y - 2);
		printf("             ");
		GotoXY(x - 6, y - 1);
		printf("         	 ");
		GotoXY(x - 6, y);
		printf("      *      ");
		GotoXY(x - 6, y + 1);
		printf("             ");
		GotoXY(x - 6, y + 2);
		printf("             ");
		GotoXY(x - 6, y + 3);
		printf("             ");
		break;
	case 11:
		GotoXY(x - 6, y - 3);
		printf("             ");
		GotoXY(x - 6, y - 2);
		printf("             ");
		GotoXY(x - 6, y - 1);
		printf("      *  	 ");
		GotoXY(x - 6, y);
		printf("    * * *    ");
		GotoXY(x - 6, y + 1);
		printf("      *      ");
		GotoXY(x - 6, y + 2);
		printf("             ");
		GotoXY(x - 6, y + 3);
		printf("             ");
		break;
	case 12:
		GotoXY(x - 6, y - 3);
		printf("      *      ");
		GotoXY(x - 6, y - 2);
		printf("  *   *   *  ");
		GotoXY(x - 6, y - 1);
		printf("    *   *	 ");
		GotoXY(x - 6, y);
		printf("* *       * *");
		GotoXY(x - 6, y + 1);
		printf("    *   *    ");
		GotoXY(x - 6, y + 2);
		printf("  *   *   *  ");
		GotoXY(x - 6, y + 3);
		printf("      *      ");
		break;
	case 13:
		GotoXY(x - 6, y - 3);
		printf("      *      ");
		GotoXY(x - 6, y - 2);
		printf("  *       *  ");
		GotoXY(x - 6, y - 1);
		printf("             ");
		GotoXY(x - 6, y);
		printf("*           *");
		GotoXY(x - 6, y + 1);
		printf("             ");
		GotoXY(x - 6, y + 2);
		printf("  *       *  ");
		GotoXY(x - 6, y + 3);
		printf("      *      ");
		break;
	case 14:
		GotoXY(x - 6, y - 3);
		printf("             ");
		GotoXY(x - 6, y - 2);
		printf("             ");
		GotoXY(x - 6, y - 1);
		printf("             ");
		GotoXY(x - 6, y);
		printf("             ");
		GotoXY(x - 6, y + 1);
		printf("             ");
		GotoXY(x - 6, y + 2);
		printf("             ");
		GotoXY(x - 6, y + 3);
		printf("             ");
		break;
	}
}