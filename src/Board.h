#ifndef BOARD_H_
#define BOARD_H_

#include "Block.h"

class Board
{

public:

	void control_user_input();
	void save_present_board_to_cpy();
	void processing_block();
	void start();

	void clear_screen();
	void init_draw_main();
	void re_draw_main();
	int getRandom(int min, int max);
	void new_block();
	void move_block(int x, int y);
	void rotate_block();
	void clear_line();
	bool is_collide(int x, int y);
	bool is_game_over();

	enum {
		POS_FREE, POS_FILLED, POS_BORDER
	};

private:
	bool isGameOver;
};

#endif
