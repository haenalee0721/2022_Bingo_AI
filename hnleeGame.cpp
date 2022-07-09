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
	cout << "202111356 ���س� \n";
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
			cout << "������������������������������������������������������������������������������������������������\n";
			cout << "��        �ݢ�    �� ��  �� Ÿ Ʈ    �ܢ�       ��\n";
			cout << "������������������������������������������������������������������������������������������������\n";
			newGame();
			break;
		case 2:
			cout << "������������������������������������������������������������������������������������������������\n";
			cout << "��        �ݢ�    �� ��  �� Ÿ Ʈ    �ܢ�       ��\n";
			cout << "������������������������������������������������������������������������������������������������\n";
			Continue();
			break;
		case 3:
			return;
		default:
			cout << "�޴� �ȿ��� �������ּ���\n";
			break;
		}


	}

}

void hnleeGame::printIntro()
{

	cout << "������������������������������������������������������������������������������������������������\n";
	cout << "��        �ݢ�     B I N G   G O     �ܢ�       ��\n";
	cout << "������������������������������������������������������������������������������������������������\n";
	cout << "1) ������ \n2) �̾��ϱ� \n3) ���� \n";

}

void hnleeGame::newGame()
{

	int num ;
	cout << "����Ͻ� �������� ũ�⸦ �Է����ּ���(3~9)\n(ex. 5 �Է� �� 5X5 ������ ����) ->  ";

	cin >> num;
	if (num > 2 && num < 10) {
		now = new Game(num);
		now->Setting();
		now->play();
	}
	else {
		cout << "3���� 9 ������ ���ڸ� �Է����ּ���..!\n"; return;
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
