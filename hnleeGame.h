#pragma once
#include "Game.h"

class hnleeGame {

private:
	Game *now;
	CONSOLE_SCREEN_BUFFER_INFO presentCur;

public:
	hnleeGame();
	~hnleeGame();
	void play();
	void printIntro();
	void newGame();
	void Continue();
	void setCursorView(bool visible);
	void gotoxy(int x, int y);

};
