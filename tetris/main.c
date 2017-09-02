//Author: Kevin Wilkinson
//Email: Willkillson@gmail.com

////HOTKEY INSTRUCTIONS FOR VISUAL STUDIO 15
////CTRL + K + U will uncomment selection.
////CTRL + K + C will comment selection
////CTRL + M + O will collapse all.
////CTRL + M + L will expand all. (in VS 2013 - Toggle All outlining)
////CTRL + M + P will expand all and disable outlining.
////CTRL + M + M will collapse / expand the current section.


#include "GameLogic.h"






int main(void) {

	//initialization//////////////////////////

	int line[bHEIGHT];
	int i = 0;
	int j = 0;

	int score = 0;

	int time = clock();
	piece current;
	int level = 1;
	char board[bHEIGHT][bWIDTH];


	for (i = 0; i < bHEIGHT; i++) {
		for (j = 0; j < bWIDTH; j++) {
			if ((i == 0) | (j == 0) | (j == 11) | (i == 25)) {
				board[i][j] = boarder;
			}
			else {
				board[i][j] = empty;
			}
		}
	}
	place_piece(board, &current);

	//main game loop///////////////////////


	while (1) {

		while (!_kbhit()) {
			time++;
			if (current.set == 1) {
				place_piece(board, &current);
			}
			Sleep(15);
			time = (clock()*level);//simulates a tick rate of time

			if ((time % 1000) <= (25 * level)) {//force move
				Sleep(30);
				current.command = 0;
			}


			master_move(&current, board);
			score_board(board, &current, &score, line);
			print_board(board, &current, &score, time, line);
			current.command = 999;
		}
		command(&current);
	}
}


