#include"hnleeGame.h"
#include <crtdbg.h>
#include <iostream>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new(_NORMAL_BLOCK,__FILE__,__LINE__)
#define new DBG_NEW
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif // !DBG_NEW
#endif

using namespace std;

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	hnleeGame newGame;
	newGame.play();
	
	return 0;

}