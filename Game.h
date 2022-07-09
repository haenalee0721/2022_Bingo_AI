#pragma once
#include<fstream>
#include<windows.h>

class Game
{
private:
	int** user=nullptr;
	int** com=nullptr;
	int num;
	CONSOLE_SCREEN_BUFFER_INFO presentCur;    // �ܼ� ���â�� ������ ��� ���ؼ� ������ ����ü 	 


public:
	Game(int num); // �迭 �ΰ� ������ֱ�
	Game();
	~Game();
	void Setting();
	void printU();
	void printC();
	void play();
	void foutU();  // �������� ���Ͽ� ����
	void foutC();  // ��ǻ�� ���� ���Ͽ� ����
	void saveU();
	void saveC();
	void AI(int& a, int& b); // ��ǻ�Ͱ� �¸� �˰����� �Ǵ��ϴ� �ڵ�
	void setCursorView(bool visible);
	void gotoxy(int x, int y);
	void replay();
	int winU();  // ������ �� ���� ���
	int winC();  // ������ �� ���� ���
	void Again();

};

