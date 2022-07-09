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
	ofstream fout("bing.txt", ios::out);  // ���� �ʱ�ȭ
	fout << "";
	fout.close();

	int a = 1; //������� �־��ֱ� ���� �ӽù���
	for (int i = 0; i < num; i++) {  // 1���� n�������� �־��ֱ�
		for (int j = 0; j < num; j++) {
			user[i][j] = a;
			com[i][j] = a;
			a++;
		}
	}

	srand(time(NULL)); // �Ϻ��� ������ �ǵ���

	for (int i = 0; i < 50; ++i) // ����
	{
		// �÷��̾ ����
		int idx1 = rand() % (num); 
		int idx2 = rand() % (num);
		int idx3 = rand() % (num);
		int idx4 = rand() % (num);

		int temp = user[idx1][idx2];
		user[idx1][idx2] =  user[idx3][idx4];
		user[idx3][idx4] = temp;

		// ��ǻ�Ͳ� ����
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
	cout << "-------------�����------------\n";
	for (int i = 0; i < num; i++) {  
		for (int j = 0; j < num; j++) {
			if (user[i][j] == 0)
				cout << "��" << "\t";
			else if (user[i][j] == -1)
				cout << "��" << "\t";
			else
				cout << user[i][j] << "\t";
		} cout << "\n";
	} cout << "\n";
}

void Game::printC() 
{  // ����� 0 ( �� ), ��ǻ�� -1 ( �� )
	cout << "-------------��ǻ��------------\n";
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (com[i][j] == 0)
				cout << "��" << "\t";
			else if (com[i][j] == -1)
				cout << "��" << "\t";
			else
				cout << com[i][j] << "\t";
		} cout << "\n";
	} cout << "\n";
}

void Game::play()  // ������ �����ϴ� �Լ�
{
	cout << "\n��ȣ�� �ƴ� ���� �����ϸ� �������� ���ư��ϴ�.\n";
	foutU();  //�����丮����
	foutC();
	saveU();  // ���� ������ ���� ���� ����
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
			cout << "\n�̹� ���õƴ� ��ȣ �Դϴ�. �ٽ� �������ּ���! \n";
			continue;
		}
		int what = user[xx][yy];
		user[xx][yy] = 0;

		for (int i = 0; i < num; i++) {  // ��ǻ�Ϳ��� what ã�� 
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

		for (int i = 0; i < num; i++) {  //  �������� what ã�� 
			for (int j = 0; j < num; j++) {
				if (what == user[i][j]) {
					user[i][j] = -1; break;
				}
			}
		}
		
		//���Ͽ� ����, ��ǻ�� ���� �����ֱ�
		foutU();  //�����丮����
 		foutC();
		saveU();  // ���� ������ ���� ���� ����
		saveC();

		int U = winU();
		int C = winC();

		if (U == C) {
			if (U > 0) {
				if (U == (num + num + 2)) {
					cout << "������������������������������������������������������������������������������������������������\n";
					cout << "��        �ݢ�    �� �� ��  �� ��    �ܢ�       ��\n";
					cout << "������������������������������������������������������������������������������������������������\n";
					printU(); printC();
					return;
				}
				cout << "�����̾ ������ ��� �����մϴ�. \n";
				continue;
			}
			continue;
		}
		else {
			if (U > C) {
				cout << "������������������������������������������������������������������������������������������������\n";
				cout << "��        �ݢ�    �� �� ��  �� ��    �ܢ�       ��\n";
				cout << "������������������������������������������������������������������������������������������������\n\n";
				printU(); printC();
				break;
			}
			else if(U < C){
				cout << "������������������������������������������������������������������������������������������������\n";
				cout << "��        �ݢ�    �� ǻ ��  �� ��    �ܢ�       ��\n";
				cout << "������������������������������������������������������������������������������������������������\n\n";
				printU(); printC();
				break;
			}
		}
	}

	cout << "������������������������������������������������������������������������������������������������\n";
	cout << "��        �ݢ�      R e p l a y      �ܢ�       ��\n";
	cout << "������������������������������������������������������������������������������������������������\n";
	replay();
}

void Game::foutU()
{
	
	ofstream fout("bing.txt", ios::app);  // �ؽ�Ʈ ���� ����
	if (!fout) {
		cout << "������ ã�� �� ����\n";
		return;
	}
	fout << "-------------�����------------\n";
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (user[i][j] == 0)
				fout << "��" << "\t";
			else if (user[i][j] == -1)
				fout << "��" << "\t";
			else
				fout << user[i][j] << "\t";
		} fout << "\n";
	}
	fout.close();
}

void Game::foutC()
{
	ofstream fout("bing.txt", ios::app);  // �ؽ�Ʈ ���� ����
	if (!fout) {
		cout << "������ ã�� �� ����\n";
		return;
	}
	fout << "-------------��ǻ��------------\n";
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (com[i][j] == 0)
				fout << "��" << "\t";
			else if (com[i][j] == -1)
				fout << "��" << "\t";
			else
				fout << com[i][j] << "\t";
		} fout << "\n";
	}

	fout.close();
}

void Game::saveU()
{
	ofstream fout("go.txt", ios::out);  // �ؽ�Ʈ ���� ����
	if (!fout) {
		cout << "������ ã�� �� ����\n";
		return;
	}
	fout << num << "\n"; // ù���� n�� �ֱ�
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
				fout << user[i][j] << "\n";
		} 
	}
	fout.close();
}

void Game::saveC()
{
	ofstream fout("go.txt", ios::app);  // �ؽ�Ʈ ���� ����
	if (!fout) {
		cout << "������ ã�� �� ����\n";
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
	int* fre = new int[num + num + 2];  // ������, ������, ���� ����������, ���� ����������

	for (int i = 0; i < (num + num + 2); i++) {
		fre[i] = 0;
	}

	//�밢�� Ȯ��
	for (int i = 0; i < num; i++) {
		if (com[i][i] < 1) {
			fre[0]++; // ���Ͼ�
		}
	}
	for (int i = 0; i < num; i++) {
		if (com[i][num - 1 - i] < 1) {
			fre[1]++;  // �����
		}
	}


	//����
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (com[i][j] < 1) {
				fre[i + 2]++;
			}
		}
	}

	//����
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (com[j][i] < 1) {
				fre[i + 2 + num]++;
			}
		}
	}

	//�ִ밪ã��
	max = 0;
	for (int i = 0; i < (num + num + 2); i++) {
		if ((max < fre[i])&&(fre[i]<num)) {
			max = fre[i];
			index = i;
		}
	}

	// �ε��� ã��
	if (index == 0) {  // �������� �ִ� 

		for (int i = 0; i < num; i++) {
			if (com[i][i] > 0) {
				a = i;
				b = i;
				
			}
		}

	}
	else if (index == 1) { // ������� �ִ� 
		for (int i = 0; i < num; i++) {
			if (com[i][num - 1 - i] > 0) {
				a = i;
				b = num - 1 - i;
			
			}
		}
	}
	else if (1 < index && index < (num + 2)) {  // ����
		for (int j = 0; j < num; j++) {
			if (com[index - 2][j] > 0) {
				a = (index - 2);
				b = j;
				
			}
		}
	}
	else {  //����
		for (int j = 0; j < num; j++) {
			if (com[j][index - num - 2] > 0) {
				a = j;
				b = index - num - 2;
				
			}
		}
	}
	delete[]fre;  //�����Ҵ� ����
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

	//����Ȯ��
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (user[i][j] < 1)sum++;
		}
		if (sum == num) binggo++;
		sum = 0;
	}
	//����Ȯ��
	sum = 0;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (user[j][i] < 1)sum++;
		}
		if (sum == num) binggo++;
		sum = 0;
	}
	//�밢��Ȯ��

	sum = 0;
	for (int i = 0; i < num; i++) {
		if (user[i][i] < 1) {
			sum++; // ���Ͼ�
		}
	}
	if (sum == num) 
		binggo++;
	sum = 0;

	for (int i = 0; i < num; i++) {
		if (user[i][num - 1 - i] < 1) {
			sum++;  // �����
		}
	}if (sum == num) 
		binggo++;

	return binggo;
}

int Game::winC()
{

	int sum = 0;
	int binggo = 0;

	//����Ȯ��
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (com[i][j] < 1)
				sum++;
		}
		if (sum == num) 
			binggo++;
		sum = 0;
	}
	//����Ȯ��
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
	//�밢��Ȯ��

	sum = 0;
	for (int i = 0; i < num; i++) {
		if (com[i][i] < 1) {
			sum++; // ���Ͼ�
		}
	}
	if (sum == num) 
		binggo++;
	sum = 0;

	for (int i = 0; i < num; i++) {
		if (com[i][num - 1 - i] < 1) {
			sum++;  // �����
		}
	}if (sum == num) 
		binggo++;

	return binggo;
}

void Game::Again()  // �����о ������ �����ϱ�
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
