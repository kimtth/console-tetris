#include <iostream>
#include <conio.h>
#include <stdlib.h>

#include "Common.h"
#include "Board.h"

using namespace std;

//extern variables
int y;
int x;
int main_board[HEIGHT][WIDTH]; //X, Y
int main_cpy[HEIGHT][WIDTH];
int mblock[4][4];

int main() {

	Board m;

	//initialize coordinates
	x = 4;
	y = 0;

	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			mblock[i][j] = m.POS_FREE;
		}
	}

	//start
	std::cout << "==================\n"
				"Press 1: Start Game\n"
				"==================\n";

	int select_num = 0;
	std::cin >> select_num; //get input

	switch (select_num) {
	case 1:
		m.clear_screen(); //clear screen
		m.init_draw_main(); //initialize board

		//In C++ you are supposed to declare functions before you can use them.
		m.start(); //start game
		break;
	default:
		exit(0);
		break;
	}
}
