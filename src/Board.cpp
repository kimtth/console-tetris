#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "Common.h"
#include "Board.h"

void Board::control_user_input() {
	char key;
	key = getch();

	switch (key) {
	case 'd': //right
		if (!is_collide(x + 1, y)) {
			move_block(x + 1, y);
		}
		break;
	case 'a': //left
		if (!is_collide(x - 1, y)) {
			move_block(x - 1, y);
		}
		break;
	case 's': //down
		if (!is_collide(x, y + 1)) {
			move_block(x, y + 1);
		}
		break;
	case 'w': //rotate
		rotate_block();
	}
}

// copy main_board data to main_cpy before making new block, this will save present data before add new_block.
// when re-draw, below line make new main_board data.
// main_board[i][x + j] = main_cpy[i][x + j] + mblock[i][j];
void Board::save_present_board_to_cpy() {
	for (size_t i = 0; i < HEIGHT - 1; i++) {
		for (size_t j = 0; j < WIDTH - 1; j++) {
			main_cpy[i][j] = main_board[i][j];
		}
	}
}

void Board::start() {
	size_t time_cnt = 0;
	size_t WAIT_MAX = 20000; //std::size_t is the unsigned integer type of the result of the sizeof operator

	while (is_game_over() == false) {
		if (kbhit()) { //kbhit returns a non-zero integer if a key is in the keyboard buffer.
			control_user_input();
		}

		//time check, then move block to down.
		if (time_cnt < WAIT_MAX) {
			time_cnt++;
		} else {
			processing_block(); //if time is consumed, block will be move to one row down
			time_cnt = 0;
		}
	}

	std::cout << "===============\n"
				 "~~~Game Over~~~\n"
				 "===============\n";

	exit(0);
}

void Board::clear_screen() {
	system("cls");
}

void Board::init_draw_main() {

	for (size_t i = 0; i <= HEIGHT - 2; i++) {
		for (size_t j = 0; j <= WIDTH - 2; j++) {
			//0 is down-side of border.
			if ((j == 0) || (j == WIDTH - 2) || (i == HEIGHT - 2)) {
				main_board[i][j] = POS_BORDER;
				main_cpy[i][j] = POS_BORDER;
			} else {
				main_board[i][j] = POS_FREE;
				main_cpy[i][j] = POS_FREE;
			}
		}
	}

	clear_line();
	new_block();
	re_draw_main();
}

void Board::re_draw_main() {
	clear_screen();

	for (size_t i = 0; i < HEIGHT - 1; i++) {
		for (size_t j = 0; j < WIDTH - 1; j++) {
			switch (main_board[i][j]) {
			case POS_FREE: //Empty
				std::cout << " " << std::flush;
				break;
			case POS_FILLED: //Block
				std::cout << "@" << std::flush;
				break;
			case POS_BORDER: //Border
				std::cout << "$" << std::flush;
				break;
			}
		}
		std::cout << std::endl;
	}
}

int Board::getRandom(int min, int max) {
	return rand() % (max - min + 1) + min;
}

void Board::new_block() {
	//initialize coordinates.
	x = 4;
	y = 0;

	Block m; //it will use stack and will only be keep alive until end of method.
	int blockType = getRandom(0, 6);
	int rotation = getRandom(0, 3);

	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			mblock[i][j] = POS_FREE;
			mblock[i][j] = m.GetBlockType(blockType, rotation, i, j);
		}
	}

	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			main_board[i][x + j] = main_cpy[i][x + j] + mblock[i][j];

			if (main_board[i][x + j] > 1) {
				isGameOver = true;
			}
		}
	}
}

void Board::move_block(int x2, int y2) {
	//Remove block
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			main_board[y + i][x + j] -= mblock[i][j];
		}
	}
	//Update coordinates
	x = x2;
	y = y2;

	// assign a block with the updated value
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			main_board[y + i][x + j] += mblock[i][j];
		}
	}

	re_draw_main();
}
void Board::rotate_block() {

	int tmp[4][4];

	for (size_t i = 0; i < 4; i++) { //Save temporarily block
		for (size_t j = 0; j < 4; j++) {
			tmp[i][j] = mblock[i][j];
		}
	}

	for (size_t i = 0; i < 4; i++) { //Rotate
		for (size_t j = 0; j < 4; j++) {
			mblock[i][j] = tmp[3 - j][i];
		}
	}

	if (is_collide(x, y)) { // And stop if it overlaps not be rotated
		for (size_t i = 0; i < 4; i++) {
			for (size_t j = 0; j < 4; j++) {
				mblock[i][j] = tmp[i][j]; //return back.
			}
		}
	}

	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			main_board[y + i][x + j] -= tmp[i][j]; //remove before changing
			main_board[y + i][x + j] += mblock[i][j]; //add new block data after rotation.
		}
	}

	re_draw_main();
}

void Board::clear_line() {

	for (int j = 0; j <= HEIGHT - 3; j++) {
		int i = 1;
		while (i <= WIDTH - 3) {
			if (main_board[j][i] == POS_FREE) {
				break;
			}
			i++;
		}

		if (i == WIDTH - 2) {
			// Moves all the upper lines one row down
			for (int k = j; k > 0; k--) {
				for (int idx = 1; idx <= WIDTH - 3; idx++) {
					main_board[k][idx] = main_board[k - 1][idx];
				}
			}
		}
	}
}

bool Board::is_collide(int x2, int y2) {
	//because every block definition array is 4 * 4 length array. i will traverse from 0 to 4.
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			if (mblock[i][j] && main_cpy[y2 + i][x2 + j] != 0) {
				return true;
			}
		}
	}
	return false;
}

bool Board::is_game_over() {
	return isGameOver;
}

void Board::processing_block() {
	if (!is_collide(x, y + 1)) {
		move_block(x, y + 1);
	} else { //if block cannot move to down anymore, make a new block.
		clear_line();
		save_present_board_to_cpy();
		new_block();
		re_draw_main();
	}
}

