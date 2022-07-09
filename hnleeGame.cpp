#include<iostream>
#include<fstream>
#include"hnleeGame.h"
#include <string>
#include<windows.h>
#include<conio.h>

using namespace std;

hnleeGame::hnleeGame()
{

}

hnleeGame::~hnleeGame()
{
	delete now;

}

void hnleeGame::play()
{
	int choice=0;
	cout << "202111356 이해나 \n";
	while(1){

		int choice;

		printIntro();
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
		int x = presentCur.dwCursorPosition.X;
		int y = presentCur.dwCursorPosition.Y;
		y = y - 3;
		int b = y;
		gotoxy(x, y);
		int keycode;
		while (1) {
			if (_kbhit()) {
				keycode = _getch();
				if (keycode == 224) {
					keycode = _getch();
					switch (keycode) {
					case 72: y -= 1; break;
					case 80: y += 1; break;
					}gotoxy(x, y);
				}
				else if (keycode == 13) {
					GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
					y = presentCur.dwCursorPosition.Y;
					if (b == y) choice = 1;
					else if(b==(y-1))choice = 2;
					else if (b == (y - 2))choice = 3;
					else choice = 4;
					y = y + 3;
					gotoxy(x, y);
					break;
				}
			}
		}

		switch (choice)
		{
		case 1:
			cout << "┏──────────────────────────────────────────────┓\n";
			cout << "┃        ♬♪    게 임  스 타 트    ♪♬       ┃\n";
			cout << "┗──────────────────────────────────────────────┛\n";
			newGame();
			break;
		case 2:
			cout << "┏──────────────────────────────────────────────┓\n";
			cout << "┃        ♬♪    게 임  스 타 트    ♪♬       ┃\n";
			cout << "┗──────────────────────────────────────────────┛\n";
			Continue();
			break;
		case 3:
			return;
		default:
			cout << "메뉴 안에서 선택해주세요\n";
			break;
		}


	}

}

void hnleeGame::printIntro()
{

	cout << "┏──────────────────────────────────────────────┓\n";
	cout << "┃        ♬♪     B I N G   G O     ♪♬       ┃\n";
	cout << "┗──────────────────────────────────────────────┛\n";
	cout << "1) 새게임 \n2) 이어하기 \n3) 종료 \n";

}

void hnleeGame::newGame()
{

	int num ;
	cout << "사용하실 빙고판의 크기를 입력해주세요(3~9)\n(ex. 5 입력 시 5X5 빙고판 생성) ->  ";

	cin >> num;
	if (num > 2 && num < 10) {
		now = new Game(num);
		now->Setting();
		now->play();
	}
	else {
		cout << "3부터 9 사이의 숫자를 입력해주세요..!\n"; return;
	}
	//N.printC();
	//N.printU();
	
}

void hnleeGame::Continue()
{
	ifstream fin("go.txt");
	string N;
	getline(fin, N);
	fin.close();
	int num = stoi(N);
	now = new Game(num);
	now->Again();
	now->play();
}

void hnleeGame::setCursorView(bool visible)
{
	CONSOLE_CURSOR_INFO cursor = { 1, visible };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void hnleeGame::gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
