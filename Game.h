#pragma once
#include<fstream>
#include<windows.h>

class Game
{
private:
	int** user=nullptr;
	int** com=nullptr;
	int num;
	CONSOLE_SCREEN_BUFFER_INFO presentCur;    // 콘솔 출력창의 정보를 담기 위해서 정의한 구조체 	 


public:
	Game(int num); // 배열 두개 만들어주기
	Game();
	~Game();
	void Setting();
	void printU();
	void printC();
	void play();
	void foutU();  // 유저정보 파일에 적기
	void foutC();  // 컴퓨터 정보 파일에 적기
	void saveU();
	void saveC();
	void AI(int& a, int& b); // 컴퓨터가 승리 알고리즘을 판단하는 코드
	void setCursorView(bool visible);
	void gotoxy(int x, int y);
	void replay();
	int winU();  // 빙고인 줄 개수 출력
	int winC();  // 빙고인 줄 개수 출력
	void Again();

};

