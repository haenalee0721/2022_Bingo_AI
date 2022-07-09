#include "Game.h"
#include<iostream>
#include <stdlib.h>
#include <time.h>
#include<windows.h>
#include<fstream>
#include<string>
#include<conio.h>

using namespace std;

Game::Game(int num)
	:num(num)
{
	user = new int*[num];
	com = new int*[num];
	for (int i = 0; i < num; i++) {
		user[i] = new int[num];
		com[i] = new int[num];
	}


}

Game::Game()
	:num(0)
{

}

Game::~Game()
{
	for (int i = 0; i < num; i++) {
		delete[]user[i];
		delete[]com[i];
	}
	delete[]user;
	delete[]com;
}

void Game::Setting()
{
	ofstream fout("bing.txt", ios::out);  // 파일 초기화
	fout << "";
	fout.close();

	int a = 1; //순서대로 넣어주기 위한 임시문자
	for (int i = 0; i < num; i++) {  // 1부터 n제곱까지 넣어주기
		for (int j = 0; j < num; j++) {
			user[i][j] = a;
			com[i][j] = a;
			a++;
		}
	}

	srand(time(NULL)); // 완벽한 랜덤이 되도록

	for (int i = 0; i < 50; ++i) // 섞기
	{
		// 플레이어꺼 섞기
		int idx1 = rand() % (num); 
		int idx2 = rand() % (num);
		int idx3 = rand() % (num);
		int idx4 = rand() % (num);

		int temp = user[idx1][idx2];
		user[idx1][idx2] =  user[idx3][idx4];
		user[idx3][idx4] = temp;

		// 컴퓨터꺼 섞기
		idx1 = rand() % num; 
		idx2 = rand() % num;
		idx3 = rand() % num;
		idx4 = rand() % num;

		temp = com[idx1][idx2];
		com[idx1][idx2] = com[idx3][idx4];
		com[idx3][idx4] = temp;
	}

}

void Game::printU()
{
	cout << "-------------사용자------------\n";
	for (int i = 0; i < num; i++) {  
		for (int j = 0; j < num; j++) {
			if (user[i][j] == 0)
				cout << "□" << "\t";
			else if (user[i][j] == -1)
				cout << "■" << "\t";
			else
				cout << user[i][j] << "\t";
		} cout << "\n";
	} cout << "\n";
}

void Game::printC() 
{  // 사용자 0 ( □ ), 컴퓨터 -1 ( ■ )
	cout << "-------------컴퓨터------------\n";
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (com[i][j] == 0)
				cout << "□" << "\t";
			else if (com[i][j] == -1)
				cout << "■" << "\t";
			else
				cout << com[i][j] << "\t";
		} cout << "\n";
	} cout << "\n";
}

void Game::play()  // 게임을 진행하는 함수
{
	cout << "\n번호가 아닌 곳을 선택하면 메인으로 돌아갑니다.\n";
	foutU();  //히스토리저장
	foutC();
	saveU();  // 다음 게임을 위한 내용 저장
	saveC();
	while (1) {
		cout << "\n";
		printU();

		int xx, yy;

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
		int x = presentCur.dwCursorPosition.X;
		int y = presentCur.dwCursorPosition.Y;
		int a = x;
		y = y - num-1;
		int b = y;
		gotoxy(x, y);
		//int keycode;
		while (1) {
			if (_kbhit()) {
				int keycode = _getch();
				if (keycode == 224) {
					keycode = _getch();
					switch (keycode) {
					case 72: y -= 1; break;
					case 75: x -= 8; break;
					case 77: x += 8; break;
					case 80: y += 1; break;
					}gotoxy(x, y);
				}
				else if (keycode == 13) {
					GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
					x = presentCur.dwCursorPosition.X;
					y = presentCur.dwCursorPosition.Y;
					if (x == a) yy = 0;
					else yy = (x - a) / 8;
					xx = (y - b) ;
					x = 0;
					y = b + num+1;
					gotoxy(x, y);
					break;
				}
			}
		}

		if ((0 > xx) || (num <= xx) || (0 > yy) || (num <= yy)) return;

		if (user[xx][yy] < 1) {
			cout << "\n이미 선택됐던 번호 입니다. 다시 선택해주세요! \n";
			continue;
		}
		int what = user[xx][yy];
		user[xx][yy] = 0;

		for (int i = 0; i < num; i++) {  // 컴퓨터에서 what 찾기 
			for (int j = 0; j < num; j++) {
				if (what == com[i][j]) {
					com[i][j] = 0; break;
				}
			}
		}

		int aa, bb;
		AI(aa, bb);

		what = com[aa][bb];
		com[aa][bb] = -1;

		for (int i = 0; i < num; i++) {  //  유저에서 what 찾기 
			for (int j = 0; j < num; j++) {
				if (what == user[i][j]) {
					user[i][j] = -1; break;
				}
			}
		}
		
		//파일에 유저, 컴퓨터 내용 적어주기
		foutU();  //히스토리저장
 		foutC();
		saveU();  // 다음 게임을 위한 내용 저장
		saveC();

		int U = winU();
		int C = winC();

		if (U == C) {
			if (U > 0) {
				if (U == (num + num + 2)) {
					cout << "┏──────────────────────────────────────────────┓\n";
					cout << "┃        ♬♪    비 겼 습  니 다    ♪♬       ┃\n";
					cout << "┗──────────────────────────────────────────────┛\n";
					printU(); printC();
					return;
				}
				cout << "동점이어서 게임을 계속 진행합니다. \n";
				continue;
			}
			continue;
		}
		else {
			if (U > C) {
				cout << "┏──────────────────────────────────────────────┓\n";
				cout << "┃        ♬♪    사 용 자  승 리    ♪♬       ┃\n";
				cout << "┗──────────────────────────────────────────────┛\n\n";
				printU(); printC();
				break;
			}
			else if(U < C){
				cout << "┏──────────────────────────────────────────────┓\n";
				cout << "┃        ♬♪    컴 퓨 터  승 리    ♪♬       ┃\n";
				cout << "┗──────────────────────────────────────────────┛\n\n";
				printU(); printC();
				break;
			}
		}
	}

	cout << "┏──────────────────────────────────────────────┓\n";
	cout << "┃        ♬♪      R e p l a y      ♪♬       ┃\n";
	cout << "┗──────────────────────────────────────────────┛\n";
	replay();
}

void Game::foutU()
{
	
	ofstream fout("bing.txt", ios::app);  // 텍스트 파일 연결
	if (!fout) {
		cout << "파일을 찾을 수 없음\n";
		return;
	}
	fout << "-------------사용자------------\n";
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (user[i][j] == 0)
				fout << "□" << "\t";
			else if (user[i][j] == -1)
				fout << "■" << "\t";
			else
				fout << user[i][j] << "\t";
		} fout << "\n";
	}
	fout.close();
}

void Game::foutC()
{
	ofstream fout("bing.txt", ios::app);  // 텍스트 파일 연결
	if (!fout) {
		cout << "파일을 찾을 수 없음\n";
		return;
	}
	fout << "-------------컴퓨터------------\n";
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (com[i][j] == 0)
				fout << "□" << "\t";
			else if (com[i][j] == -1)
				fout << "■" << "\t";
			else
				fout << com[i][j] << "\t";
		} fout << "\n";
	}

	fout.close();
}

void Game::saveU()
{
	ofstream fout("go.txt", ios::out);  // 텍스트 파일 연결
	if (!fout) {
		cout << "파일을 찾을 수 없음\n";
		return;
	}
	fout << num << "\n"; // 첫줄은 n값 넣기
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
				fout << user[i][j] << "\n";
		} 
	}
	fout.close();
}

void Game::saveC()
{
	ofstream fout("go.txt", ios::app);  // 텍스트 파일 연결
	if (!fout) {
		cout << "파일을 찾을 수 없음\n";
		return;
	}
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
				fout << com[i][j] << "\n";
		} 
	}
	fout.close();
}

void Game::AI(int& a, int& b)
{

	int max, index = 0;
	int* fre = new int[num + num + 2];  // 우하향, 좌하향, 가로 위에서부터, 세로 위에서부터

	for (int i = 0; i < (num + num + 2); i++) {
		fre[i] = 0;
	}

	//대각선 확인
	for (int i = 0; i < num; i++) {
		if (com[i][i] < 1) {
			fre[0]++; // 우하양
		}
	}
	for (int i = 0; i < num; i++) {
		if (com[i][num - 1 - i] < 1) {
			fre[1]++;  // 우상향
		}
	}


	//가로
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (com[i][j] < 1) {
				fre[i + 2]++;
			}
		}
	}

	//세로
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (com[j][i] < 1) {
				fre[i + 2 + num]++;
			}
		}
	}

	//최대값찾기
	max = 0;
	for (int i = 0; i < (num + num + 2); i++) {
		if ((max < fre[i])&&(fre[i]<num)) {
			max = fre[i];
			index = i;
		}
	}

	// 인덱스 찾기
	if (index == 0) {  // 우하향이 최대 

		for (int i = 0; i < num; i++) {
			if (com[i][i] > 0) {
				a = i;
				b = i;
				
			}
		}

	}
	else if (index == 1) { // 우상향이 최대 
		for (int i = 0; i < num; i++) {
			if (com[i][num - 1 - i] > 0) {
				a = i;
				b = num - 1 - i;
			
			}
		}
	}
	else if (1 < index && index < (num + 2)) {  // 가로
		for (int j = 0; j < num; j++) {
			if (com[index - 2][j] > 0) {
				a = (index - 2);
				b = j;
				
			}
		}
	}
	else {  //세로
		for (int j = 0; j < num; j++) {
			if (com[j][index - num - 2] > 0) {
				a = j;
				b = index - num - 2;
				
			}
		}
	}
	delete[]fre;  //동적할당 해제
	return;
}

void Game:: setCursorView(bool visible) {
	CONSOLE_CURSOR_INFO cursor = { 1, visible }; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
void Game:: gotoxy(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void Game::replay()
{
	ifstream fin("bing.txt");
	string line;
	int a = 0;
	while (!fin.eof())
	{
		for (int i = 0; i < (num + 1); i++) {
			getline(fin, line);
			cout << line << endl;
			
			a++;
		}
		Sleep(1000);
	}
	fin.close();

}

int Game::winU()
{
	int sum = 0;
	int binggo = 0;

	//가로확인
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (user[i][j] < 1)sum++;
		}
		if (sum == num) binggo++;
		sum = 0;
	}
	//세로확인
	sum = 0;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (user[j][i] < 1)sum++;
		}
		if (sum == num) binggo++;
		sum = 0;
	}
	//대각선확인

	sum = 0;
	for (int i = 0; i < num; i++) {
		if (user[i][i] < 1) {
			sum++; // 우하양
		}
	}
	if (sum == num) 
		binggo++;
	sum = 0;

	for (int i = 0; i < num; i++) {
		if (user[i][num - 1 - i] < 1) {
			sum++;  // 우상향
		}
	}if (sum == num) 
		binggo++;

	return binggo;
}

int Game::winC()
{

	int sum = 0;
	int binggo = 0;

	//가로확인
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (com[i][j] < 1)
				sum++;
		}
		if (sum == num) 
			binggo++;
		sum = 0;
	}
	//세로확인
	sum = 0;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (com[j][i] < 1)
				sum++;
		}
		if (sum == num) 
			binggo++;
		sum = 0;
	}
	//대각선확인

	sum = 0;
	for (int i = 0; i < num; i++) {
		if (com[i][i] < 1) {
			sum++; // 우하양
		}
	}
	if (sum == num) 
		binggo++;
	sum = 0;

	for (int i = 0; i < num; i++) {
		if (com[i][num - 1 - i] < 1) {
			sum++;  // 우상향
		}
	}if (sum == num) 
		binggo++;

	return binggo;
}

void Game::Again()  // 파일읽어서 빙고판 세팅하기
{
	ifstream fin("go.txt");
	string N;
	getline(fin, N);
	for (int i = 0; i < num; i++){
		for (int j = 0; j < num; j++) {
			getline(fin, N);
			int a = stoi(N);
			user[i][j] = a;
		}
	}

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			getline(fin, N);
			int a = stoi(N);
			com[i][j] = a;
		}
	}
	
	fin.close();
}
