#pragma once
#include"Header.h"
#include"Board.h"
#include"Menu.h"
#include"Point.h"

void ResetData() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			_A[i][j].x = 4 * j + LEFT + 2;
			_A[i][j].y = 2 * i + TOP + 1;
			_A[i][j].c = 0;
		}
	}
	_TURN = true;
	_COMMAND = -1;
	_X = _A[0][0].x;
	_Y = _A[0][0].y;
	p1.step = 0; p2.step = 0;
}

void StartGame() {
	system("cls");
	ResetData(); // original data initialization
	DrawBoard(BOARD_SIZE); // Draw board game
}

int Undo(int pX, int pY)
{
	int res;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_TURN == true) {
				// if that position is already checked
				if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == -1)
				{
					res = _A[i][j].c;
					_A[i][j].c = 0;
					return res;
				}
			}
			else {
				// if that position is already checked
				if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 1)
				{
					res = _A[i][j].c;
					_A[i][j].c = 0;
					return res;
				}
			}
			
		}
	}
	return 0;
}

int CheckBoard(int pX, int pY) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0) {
				if (_TURN == true) {
					_A[i][j].c = -1; // current turn is true: c = -1
					p1.step++;
					PlaySound(TEXT("step.wav"), NULL, SND_FILENAME | SND_ASYNC);
				}
				else {
					_A[i][j].c = 1; // current turn is false: c = 1
					p2.step++;
					PlaySound(TEXT("step.wav"), NULL, SND_FILENAME | SND_ASYNC);
				}
				return
					_A[i][j].c;
			}
		}
	}
	return 0;
}

void ShowWin(int win) {
	char key = -1;
	int count = 0, count1 = 0, count2 = 0, count3 = 0, count4 = 0;
	int step = 0, flag = 1;
	string name = "";
	PlaySound(TEXT("cheer.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	for (int i = 0; i < 30; i++) {
		GotoXY(55, i);
		for (int j = 0; j < 65; j++)
			cout << " ";
	}

	while (key == -1) {
		TextColor(rand() % 15 + 1);
		DrawLineWin(_X, _Y);
		TextColor(default_ColorCode);
		int x = 70, y = 19;

		//FireWorks
		if (step >= 0) {
			TextColor(rand() % 15 + 1);
			DrawFireWorks(count % 15, x, y);
			TextColor(default_ColorCode);
			count++;
		}

		if (step >= 5) {
			TextColor(rand() % 15 + 1);
			x = 90; y = 19;
			DrawFireWorks(count1 % 15, x, y);
			TextColor(default_ColorCode);
			count1++;
		}

		if (step >= 8) {
			TextColor(rand() % 15 + 1);
			x = 110; y = 19;
			DrawFireWorks(count2 % 15, x, y);
			TextColor(default_ColorCode);
			count2++;
		}

		if (step >= 11) {
			TextColor(rand() % 15 + 1);
			x = 80; y = 19;
			DrawFireWorks(count3 % 15, x, y);
			TextColor(default_ColorCode);
			count3++;
		}

		if (step >= 14) {
			TextColor(rand() % 15 + 1);
			x = 100; y = 19;
			DrawFireWorks(count4 % 15, x, y);
			TextColor(default_ColorCode);
			count4++;
		}
		step++;

		GotoXY(62, 3);
		for (int i = 0; i <= 50; i++) {
			if (i == 0) putchar(201);
			else if (i == 50) putchar(187);
			else putchar(205);
		}

		for (int i = 1; i <= 10; i++) {
			GotoXY(62, i + 3); putchar(186);
			GotoXY(112, i + 3); putchar(186);
		}

		GotoXY(62, 13);
		for (int i = 0; i <= 50; i++) {
			if (i == 0) putchar(200);
			else if (i == 50) putchar(188);
			else putchar(205);
		}

		if (win == -1)
			name = p1.name;
		else if (win == 1)
			name = p2.name;
		else {
			GotoXY(70, 5);
			cout << "\t" << p1.name << " VA " << p2.name << " HOA NHAU !\t";
			GotoXY(70, 7);
			cout << "Yes[Y] \t\t\t: New Game";
			GotoXY(70, 9);
			cout << "No[N/press any key] : Back to Menu";
			GotoXY(70, 11);
			cout << "You Choose: ";

			if (_kbhit())
			{
				key = getchar();
				cin.ignore();
				_COMMAND = toupper(key);
			}
			return;
		}
		GotoXY(70, 5);
		cout << "\tCHUC MUNG " << name << " CHIEN THANG !\t";
		GotoXY(70, 7);
		cout << "Yes[Y] \t\t\t: New Game";
		GotoXY(70, 9);
		cout << "No[N/press any key] \t: Back to Menu";
		GotoXY(70, 11);
		cout << "You Choose: ";

		if (_kbhit())
		{
			key = _getch();
			cin.ignore();
			_COMMAND = toupper(key);
		}
		Sleep(100);
	}

	PlaySound(NULL, NULL, SND_ASYNC);
	if (_COMMAND == 'Y') {
		TextColor(6);
		StartGame();
	}
	else
		Menu(); // return to menu
}

int ProcessFinish(int pWhoWin) {
	switch (pWhoWin) {
	case -1:
		p1.win++;
		p2.lose++;
		ShowWin(-1);
		break;
	case 1:
		p2.win++;
		p1.lose++;
		ShowWin(1);
		break;
	case 0:
		p1.draw++;
		p2.draw++;
		ShowWin(2);
		break;
	case 2:
		_TURN = !_TURN; // Change turn if nothing happen
		break;
	}

	GotoXY(_X, _Y); // Return the current position of pointer on board
	return pWhoWin;
}

bool CheckDraw() {
	bool check = true;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			// if there is a position that haven't checked -> not draw
			if (_A[i][j].c == 0) {
				check = false;
				break;
			}
		}
	}
	return check;
}

bool CheckWin(int bingo) {
	bool win = false;
	int cnt, tmp, k, l;
	if (_TURN == true) {
		// check row
		for (int i = 0; i < BOARD_SIZE; i++) {
			cnt = 0;
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (_A[i][j].c == -1) {		// if there is an X then check if 4 consecutive cells in a row
					cnt++;
					for (int k = j + 1; k < j + 5; k++)
						if (_A[i][k].c == -1)
							cnt++;
				}
				if (cnt == bingo) {		// if there is 5 consecutive cells in a row is X
					win = true;
					break;
				}
				else {
					cnt = 0;
				}
			}
		}

		// check column 
		for (int i = 0; i < BOARD_SIZE; i++) {
			cnt = 0;
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (_A[j][i].c == -1) {		// if there is an X then check if 4 consecutive cells in a column
					cnt++;
					for (int k = j + 1; k < j + 5; k++)
						if (_A[k][i].c == -1)
							cnt++;
				}
				if (cnt == bingo) {		// if there is 5 consecutive cells in a column is X
					win = true;
					break;
				}
				else {
					cnt = 0;
				}
			}
		}

		// check main diagonal 
		cnt = 0;
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (_A[i][j].c == -1) {		// if there is an X then check if 4 consecutive cells in a main diagonal
					cnt++;
					tmp = bingo;
					k = i; l = j;
					while (tmp > 1) {
						k++, l++;
						if (_A[k][l].c == -1)
							cnt++;
						else
							break;
						tmp--;
					}
				}
				if (cnt == bingo) {		// if there is 5 consecutive cells in a main diagonal is X
					win = true;
					break;
				}
				else {
					cnt = 0;
				}
			}
		}

		// check auxiliary diagonal
		cnt = 0;
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (_A[i][j].c == -1) {		// if there is an X then check if 4 consecutive cells in a auxiliary diagonal
					cnt++;
					tmp = bingo;
					k = i; l = j;
					while (tmp > 1) {
						k++, l--;
						if (_A[k][l].c == -1)
							cnt++;
						else
							break;
						tmp--;
					}
				}
				if (cnt == bingo) {		// if there is 5 consecutive cells in a auxiliary diagonal is X
					win = true;
					break;
				}
				else {
					cnt = 0;
				}
			}
		}
	}
	else if (_TURN == false) {
		// check row
		for (int i = 0; i < BOARD_SIZE; i++) {
			cnt = 0;
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (_A[i][j].c == 1) {		// if there is an O then check if 4 consecutive cells in a row
					cnt++;
					for (int k = j + 1; k < j + 5; k++)
						if (_A[i][k].c == 1)
							cnt++;
				}
				if (cnt == bingo) {		// if there is 5 consecutive cells in a row is O
					win = true;
					break;
				}
				else {
					cnt = 0;
				}
			}
		}

		// check column 
		for (int i = 0; i < BOARD_SIZE; i++) {
			cnt = 0;
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (_A[j][i].c == 1) {		// if there is an O then check if 4 consecutive cells in a column
					cnt++;
					for (int k = j + 1; k < j + 5; k++)
						if (_A[k][i].c == 1)
							cnt++;
				}
				if (cnt == bingo) {		// if there is 5 consecutive cells in a column is O
					win = true;
					break;
				}
				else {
					cnt = 0;
				}
			}
		}

		// check main diagonal 
		cnt = 0;
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (_A[i][j].c == 1) {		// if there is an O then check if 4 consecutive cells in a main diagonal
					cnt++;
					tmp = bingo;
					k = i; l = j;
					while (tmp > 1) {
						k++, l++;
						if (_A[k][l].c == 1)
							cnt++;
						else
							break;
						tmp--;
					}
				}
				if (cnt == bingo) {		// if there is 5 consecutive cells in a main diagonal is O
					win = true;
					break;
				}
				else {
					cnt = 0;
				}
			}
		}

		// check auxiliary diagonal
		cnt = 0;
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (_A[i][j].c == 1) {		// if there is an O then check if 4 consecutive cells in a auxiliary diagonal
					cnt++;
					tmp = bingo;
					k = i; l = j;
					while (tmp > 1) {
						k++, l--;
						if (_A[k][l].c == 1)
							cnt++;
						else
							break;
						tmp--;
					}
				}
				if (cnt == bingo) {		// if there is 5 consecutive cells in a auxiliary diagonal is O
					win = true;
					break;
				}
				else {
					cnt = 0;
				}
			}
		}
	}
	return win;
}

int TestBoard(int level) {
	// Show player turn in real time
	if (_TURN == 0) {
		GotoXY(LEFT + 6.3 * BOARD_SIZE + 15, 3);
		cout << "Player 1: X";
	}
	else {
		GotoXY(LEFT + 6.3 * BOARD_SIZE + 15, 3);
		cout << "Player 2: O";
	}

	// Show steps of each player in real time
	GotoXY(LEFT + 4 * BOARD_SIZE + 31, 14);
	cout << "Step: " << p1.step;
	GotoXY(LEFT + 4 * BOARD_SIZE + 31, 16);
	cout << "Step: " << p2.step;

	if (CheckDraw() == true)
		return 0; // Draw
	else {
		if (CheckWin(level) == true)
			return (_TURN == true ? -1 : 1); // -1: true win
		else
			return 2; // 2: no one win
	}
}

void GabageCollect() {}

void ExitGame(int& flag) {
	flag = 0;
	system("cls");
	GabageCollect();
}

bool ExistFilename(string filename) {
	fstream file(filename + ".txt");
	if (!file)		// cannot open file
		return false; // no exist
	file.close();
	return true; // exist
}

void UpdateBoardFromFile(string filename) {
	string line[BOARD_SIZE + 5], temp;
	int i = 0, j = 0;
	ifstream file(filename + ".txt");

	// Read each line in file and add it in a string array
	while (!file.eof()) {
		getline(file, temp);
		line[i] = temp;
		i++;
	}

	for (int i = 0; i < BOARD_SIZE + 5; i++) {
		stringstream ss(line[i]);
		j = 0;
		// Read line board
		if (i >= 0 && i < BOARD_SIZE) {
			while (j < BOARD_SIZE) {
				getline(ss, temp, ' ');
				_A[i][j].c = stoi(temp);
				j++;
			}
		}
		// Read line player name
		else if (i == BOARD_SIZE) {
			while (j < 2) {
				getline(ss, temp, ' ');
				if (j == 0)
					p1.name = temp;
				else
					p2.name = temp;
				j++;
			}
		}
		// Read line player step
		else if (i == BOARD_SIZE + 1) {
			while (j < 2) {
				getline(ss, temp, ' ');
				if (j == 0)
					p1.step = stoi(temp);
				else
					p2.step = stoi(temp);
				j++;
			}
		}
		// Read line player 1 W/L/D
		else if (i == BOARD_SIZE + 2) {
			while (j < 3) {
				getline(ss, temp, '/');
				if (j == 0)
					p1.win = stoi(temp);
				else if (j == 1)
					p1.lose = stoi(temp);
				else
					p1.draw = stoi(temp);
				j++;
			}
		}
		// Read line player 2 W/L/D
		else if (i == BOARD_SIZE + 3) {
			while (j < 3) {
				getline(ss, temp, '/');
				if (j == 0)
					p2.win = stoi(temp);
				else if (j == 1)
					p2.lose = stoi(temp);
				else
					p2.draw = stoi(temp);
				j++;
			}
		}
		// Read line turn
		else if (i == BOARD_SIZE + 4)
			_TURN = stoi(line[i]);

	}

	system("cls");
	DrawBoard(BOARD_SIZE); // Draw board game

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[j][i].c == -1) {
				GotoXY(_A[j][i].x, _A[j][i].y);
				cout << "X";
			}
			else if (_A[j][i].c == 1) {
				GotoXY(_A[j][i].x, _A[j][i].y);
				cout << "O";
			}
		}

		file.close();
	}
}

void InsertInfoPlayer() {
	system("cls");
	GotoXY(45, 13);
	cout << "Please enter name player 1: ";
	cin >> p1.name;
	GotoXY(45, 15);
	cout << "Please enter name player 2: ";
	cin >> p2.name;
}

void SaveGame() {
	string filename;
	int i = 18;
	char replace;

	do {
		GotoXY(LEFT + 4 * BOARD_SIZE + 10, i);
		cout << "Please enter file name to save: ";
		cin >> filename;

		if (ExistFilename(filename) == true) {
			i++;
			GotoXY(LEFT + 4 * BOARD_SIZE + 10, i);
			cout << "This name already exist. Do you want to replace? (y/n): ";
			cin >> replace;
			if (replace == 'Y' || replace == 'y') {
				i++;
				break;
			}
		}
		else {
			i++;
			break;
		}
		i++;
	} while (true);

	GotoXY(LEFT + 4 * BOARD_SIZE + 10, i);
	cout << "Save success" << endl;
	Sleep(500);

	// write board game into file
	ofstream file(filename + ".txt");
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			file << _A[i][j].c << " ";
		}
		file << "\n";
	}

	// write info of player into file
	file << p1.name << " " << p2.name << endl;
	file << p1.step << " " << p2.step << endl;
	file << p1.win << "/" << p1.lose << "/" << p1.draw << endl;
	file << p2.win << "/" << p2.lose << "/" << p2.draw << endl;
	file << _TURN;

	file.close();

	UpdateBoardFromFile(filename);
}