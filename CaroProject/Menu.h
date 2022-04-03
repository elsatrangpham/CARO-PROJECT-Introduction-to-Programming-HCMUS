#pragma once
#include"Header.h"
#include"Board.h"
#include"Game.h"
#include"Point.h"

void NewGame(int& flag) {
	PlaySound(TEXT("nen.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	InsertInfoPlayer();
	system("cls");
	PlaySound(NULL, NULL, SND_ASYNC);
	StartGame();
	bool validEnter = true;
	int level = 5;

	while (1) {
		_COMMAND = toupper(_getch());
		if (_COMMAND == 27) {
			ExitGame(flag);
			break;
		}
		else {
			if (_COMMAND == 'A')
				MoveLeft();
			else if (_COMMAND == 'W')
				MoveUp();
			else if (_COMMAND == 'S')
				MoveDown();
			else if (_COMMAND == 'D')
				MoveRight();
			else if (_COMMAND == 'L')
				SaveGame();
			else if (_COMMAND == 'T')
				LoadGame_playing();
			else if (_COMMAND == 'N')
				StartGame();
			else if (_COMMAND == 'U') {
				switch (Undo(_X, _Y)) {
				case -1:
					if (_TURN == false)
						_TURN = !_TURN;
					cout << " ";

					GotoXY(LEFT + 6.3 * BOARD_SIZE + 15, 3);
					cout << "Player 1: X";
					GotoXY(_X, _Y);
					break;
				case 1:
					if (_TURN == true)
						_TURN = !_TURN;
					cout << " ";

					GotoXY(LEFT + 6.3 * BOARD_SIZE + 15, 3);
					cout << "Player 2: O";
					GotoXY(_X, _Y);
					break;
				case 0:
					validEnter = false;
					break;
				}
			}
			else if (_COMMAND == 13) {
				switch (CheckBoard(_X, _Y)) {
				case -1:
					cout << "X";
					GotoXY(_X, _Y);
					break;
				case 1:
					cout << "O";
					GotoXY(_X, _Y);
					break;
				case 0:
					validEnter = false;
					break;
				}
				if (validEnter == true) {
					switch (ProcessFinish(TestBoard(level))) {
					case -1: case 1: case 0:
						break;
					}
				}
				validEnter = true;
			}
		}
	}
}

void LoadGame_playing() {
	string filename;
	int i = 18;
	char create;

	do {
		GotoXY(LEFT + 4 * BOARD_SIZE + 10, i);
		cout << "Please enter file name to load: ";
		cin >> filename;

		if (ExistFilename(filename) == false) {
			i++;
			GotoXY(LEFT + 4 * BOARD_SIZE + 10, i);
			cout << "This file doesn't exist. Please enter another name" << endl;
		}
		i++;
	} while (ExistFilename(filename) == false);

	GotoXY(LEFT + 4 * BOARD_SIZE + 10, i);
	cout << "Load success" << endl;
	Sleep(500);

	UpdateBoardFromFile(filename);
	GotoXY(_A[0][0].x, _A[0][0].y);
}

void LoadGame_start(int& flag) {
	PlaySound(TEXT("nen.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	string filename;

	system("cls");
	GotoXY(35, 13);
	cout << "Please enter file name to load: ";
	getline(cin, filename);
	if (ExistFilename(filename) == false) {
		GotoXY(35, 14);
		cout << "This file doesn't exist" << endl;
		Sleep(3000);
	}

	if (ExistFilename(filename) == false)
		flag = 0;
	else
		NewGame_load(flag, filename);
}

void NewGame_load(int& flag, string filename) {
	system("cls");
	PlaySound(NULL, NULL, SND_ASYNC);
	StartGame();
	UpdateBoardFromFile(filename);
	GotoXY(_A[0][0].x, _A[0][0].y);
	bool validEnter = true;
	int level = 5;

	while (1) {
		_COMMAND = toupper(_getch());
		if (_COMMAND == 27) {
			ExitGame(flag);
			break;
		}
		else {
			if (_COMMAND == 'A')
				MoveLeft();
			else if (_COMMAND == 'W')
				MoveUp();
			else if (_COMMAND == 'S')
				MoveDown();
			else if (_COMMAND == 'D')
				MoveRight();
			else if (_COMMAND == 'L')
				SaveGame();
			else if (_COMMAND == 'T')
				LoadGame_playing();
			else if (_COMMAND == 'N')
				StartGame();
			else if (_COMMAND == 'U') {
				switch (Undo(_X, _Y)) {
				case -1:
					if (_TURN == false)
						_TURN = !_TURN;
					cout << " ";

					GotoXY(LEFT + 6.3 * BOARD_SIZE + 15, 3);
					cout << "Player 1: X";
					GotoXY(_X, _Y);
					break;
				case 1:
					if (_TURN == true)
						_TURN = !_TURN;
					cout << " ";

					GotoXY(LEFT + 6.3 * BOARD_SIZE + 15, 3);
					cout << "Player 2: O";
					GotoXY(_X, _Y);
					break;
				case 0:
					validEnter = false;
					break;
				}
			}
			else if (_COMMAND == 13) {
				switch (CheckBoard(_X, _Y)) {
				case - 1:
					cout << "X";
					GotoXY(_X, _Y);
					break;
				case 1:
					cout << "O";
					GotoXY(_X, _Y);
					break;
				case 0:
					validEnter = false;
					break;
				}
				if (validEnter == true) {
					switch (ProcessFinish(TestBoard(level))) {
					case -1: case 1: case 0:
						break;
					}
				}
				validEnter = true;
			}
		}
	}
}

void About(int& flag) {
	system("cls");
	PlaySound(TEXT("nen.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	TextColor(11);
	GotoXY(50, 10);
	cout << "NHOM 8 _ NMLT" << endl;
	GotoXY(45, 11);
	cout << "Giang vien: Truong Toan Thinh" << endl;
	GotoXY(50, 12);
	cout << "Cac thanh vien: " << endl;
	GotoXY(45, 13);
	cout << "20127175 - Do Nguyen Hung" << endl;
	GotoXY(45, 14);
	cout << "20127362 - Pham Hien Doan Trang" << endl;
	GotoXY(45, 15);
	cout << "20127639 - Nguyen Thanh Thuan" << endl;
	GotoXY(0, 29);
	system("pause");
	system("cls");
	flag = 0;
}

void Help(int& flag) {
	system("cls");
	PlaySound(TEXT("nen.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	TextColor(13);
	GotoXY(55, 7);
	cout << "RULES: " << endl;
	GotoXY(52, 10);
	cout << "Player 1: X" << endl;
	GotoXY(52, 11);
	cout << "Player 2: O" << endl;
	GotoXY(34, 12);
	cout << "If you want to win, try to get your sign (X or O): " << endl;
	GotoXY(46, 13);
	cout << "5 consecutive cells on 1 row" << endl;
	GotoXY(44, 14);
	cout << "5 consecutive cells on 1 column" << endl;
	GotoXY(44, 15);
	cout << "5 consecutive cells on 1 diagonal" << endl;
	GotoXY(31, 16);
	cout << "If no one win when the board is full, then 2 players draw" << endl;
	GotoXY(0, 29);
	system("pause");
	system("cls");
	flag = 0;
}

void CaroOnScreen() {
	TextColor(6);
	GotoXY(20, 5);
	cout << " .----------------.  .----------------.  .----------------.  .----------------. " << endl;
	GotoXY(20, 6);
	cout << "| .--------------. || .--------------. || .--------------. || .--------------. |" << endl;
	GotoXY(20, 7);
	cout << "| |     ______   | || |      __      | || |  ________    | || |     ____     | |" << endl;
	GotoXY(20, 8);
	cout << "| |   .' ___  |  | || |     |  |     | || | |_   __  |   | || |   .'    `.   | |" << endl;
	GotoXY(20, 9);
	cout << "| |  | .'   |_|  | || |    | || |    | || |   | |__)_|   | || |  |  .--.  |  | |" << endl;
	GotoXY(20, 10);
	cout << "| |  | |         | || |   | ____ |   | || |   |  __ /    | || |  | |    | |  | |" << endl;
	GotoXY(20, 11);
	cout << "| |  | `.___.'|  | || | _| |    | |_ | || |  _| |  |`|_  | || |  |  `--'  |  | |" << endl;
	GotoXY(20, 12);
	cout << "| |   `._____.'  | || ||____|  |____|| || | |____| |___| | || |   `.____.'   | |" << endl;
	GotoXY(20, 13);
	cout << "| |              | || |              | || |              | || |              | |" << endl;
	GotoXY(20, 14);
	cout << "| '--------------' || '--------------' || '--------------' || '--------------' |" << endl;
	GotoXY(20, 15);
	cout << " '----------------'  '----------------'  '----------------'  '----------------' " << endl;
}

void GoodBye() {
	system("cls");
	PlaySound(TEXT("bye.wav"), NULL, SND_FILENAME | SND_ASYNC);
	for (int i = 0; i < 24; i++) {
		int n = rand() % 16;
		TextColor(n);
		GotoXY(27, 12);
		cout << " XXXXXX   XXXXXX   XXXXXX  XXXXXX      YYYYYY YY    YY YYYYYYY " << endl;
		GotoXY(27, 13);
		cout << "XX       XX    XX XX    XX XX   XX     YY   YY YY  YY  YY      " << endl;
		GotoXY(27, 14);
		cout << "XX  XXX  XX    XX XX    XX XX    XX    YYYYYY   YYYY   YYYYYYY " << endl;
		GotoXY(27, 15);
		cout << "XX    XX XX    XX XX    XX XX   XX     YY   YY   YY    YY      " << endl;
		GotoXY(27, 16);
		cout << " XXXXX    XXXXXX   XXXXXX  XXXXXX      YYYYYY    YY    YYYYYYY " << endl;
		Sleep(200);
		system("cls");
	}
}

void Menu() {
	system("cls");
	int flag;
	do {
		flag = 1;
		PlaySound(TEXT("main.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		CaroOnScreen();
		int pointer = 0;
		while (true) {
			TextColor(6);
			for (int i = 0; i < MAX_MENU; i++) {
				if (pointer == i) {
					TextColor(3);
					GotoXY(54, i + 20);
					cout << "> " << MENU[i] << " <" << endl;
					TextColor(6);
				}
				else {
					GotoXY(54, i + 20);
					cout << "[ " << MENU[i] << " ]" << endl;
				}
			}

			// Work with keyboard
			while (true) {
				if (_kbhit()) { // Function get input from keyboard
					char key = _getch();
					if (key == 72) { // Up
						if (pointer > 0) {
							--pointer;
						}
						else {
							pointer = MAX_MENU - 1;
						}
						break;
					}
					if (key == 80) { // Down
						if (pointer < (MAX_MENU - 1)) {
							++pointer;
						}
						else {
							pointer = 0;
						}
						break;
					}
					if (key == 13) { // Enter
						switch (pointer) {
						case 0:
							PlaySound(NULL, NULL, SND_ASYNC);
							NewGame(flag);
							break;
						case 1:
							PlaySound(NULL, NULL, SND_ASYNC);
							LoadGame_start(flag);
							break;
						case 2:
							PlaySound(NULL, NULL, SND_ASYNC);
							About(flag);
							break;
						case 3:
							PlaySound(NULL, NULL, SND_ASYNC);
							Help(flag);
							break;
						case 4:
							flag = -1;
							break;
						}
					}
				}
				if (flag == -1 || flag == 0)
					break;
			}
			if (flag == -1 || flag == 0)
				break;
		}
		PlaySound(NULL, NULL, SND_ASYNC);
	} while (flag == 0);
	GoodBye();
}