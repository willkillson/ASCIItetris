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



void clearScreen() {

	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);


	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void print_board(char board[bHEIGHT][bWIDTH], piece *x, int *score, int time, int line[bHEIGHT]) {

	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int scorees = *score;

	clearScreen();
	////////ui///////////
	int m = 1;
	if (x->set == 0) {
		while (m <= 25) {
			printf("\n");
			//if (m == 1) {
			//	printf("\t\t\t Controls   |Left a|  |Right d|  |Down s|  |Instant Drop w|  |Rotate 1| ");
			//}
			if (m == 2) {
				printf("\t\t\t *DEGBUG*  check |W = %d|E =  %d|S =  %d| |SETDELAY = %d", x->W, x->E, x->S, x->setdelay);
			}
			if (m == 3) {
				printf("\t\t\t Time | %d|", (time / 1000));
			}
			if (m == 4) {
				printf("\t\t\t Score = %d", *score);
			}

			if (m == 5) {
				printf("\t\t\tRotate Left Collision - %d\t\t\t\t\t\t", x->rl);
			}
			if (m == 6) {
				printf("\t\t\tRotate Right Collision - %d\t\t\t\t\t\t", x->rr);
			}
			if (m == 7) {
				printf("\t\t\tRotation Position - %d\t\t\t\t\t", x->rotation);
			}
			if (m == 8) {
				printf("\t\t\tTEST 1 - %d\t\t\t\t\t\t", x->test1);
			}
			if (m == 9) {
				printf("\t\t\tTEST 2 - %d\t\t\t\t\t", x->test2);
			}
		
			m++;
		}
	}




	//copy position of piece x into the board

	clearScreen();

	for (i = 0; i < bHEIGHT; i++) {
		for (j = 0; j < bWIDTH; j++) {
			//playable area is 0i to 25i  and 0j to 11j
			if (x->position[i][j] == block) {
				printf("%c ", x->position[i][j]);
			}
			else {
				printf("%c ", board[i][j]);

			}
			//printf("[%d][%d]-%c    ",i,j, board[i][j]);
		}
		printf("\n");

	}

}
void shift_stack(char board[][bWIDTH], int line[bHEIGHT]) {
	int i = 0;
	int j = 0;
	int k = 0;
	int zero = 0;
	int one = 1;

	for (i = 0; i < 25; i++) {
		if (line[i] == 10) {
			k = i;
			k = k - 4;
			while (k != 0) {
				for (j = 1; j < 11; j++) {
					if ((i - zero) < 4) {
						break;
					}
					board[i - zero][j] = board[i - one][j];
					board[i - one][j] = empty;
				}
				zero++;
				one++;
				k--;

			}
		}
	}

}
void score_board(char board[bHEIGHT][bWIDTH], piece *x, int *score, int line[bHEIGHT]) {

	int i = 0;
	int j = 0;
	int c = 0;

	while (x->set == 1) {// copy x->position into board
		for (i = 0; i < bHEIGHT; i++) {
			for (j = 0; j < bWIDTH; j++) {
				if (x->position[i][j] == block) {
					board[i][j] = block;
					x->position[i][j] = empty;
				}
			}
		}
		break;
	}

	for (i = 24; i > 4; i--) {
		for (j = 1; j < 11; j++) {
			if (board[i][j] == block) {		//clear line array 10- = things are in there
				c++;
			}
		}
		line[i] = c;
		c = 0;
	}

	shift_stack(board, line);

}
void place_piece(char board[][bWIDTH], piece *x) {

	int type = 99;


	type = (rand() % 7);

	if (type == 0) {
		//drawing an I piece in vertical poistion 0
		x->set = 0;
		x->S = 0;
		x->E = 0;
		x->W = 0;
		x->rl = 0;
		x->rr = 0;
		x->rotation = 0;
		x->type = 'I';
		x->from_left = 6;
		x->from_top = 4;
		x->position[4][4] = block;
		x->position[4][5] = block;
		x->position[4][6] = block;
		x->position[4][7] = block;
	}
	if (type == 1) {
		//drawing a Q square piece
		x->set = 0;
		x->S = 0;
		x->E = 0;
		x->W = 0;
		x->rotation = 0;
		x->type = 'Q';
		x->from_left = 5;
		x->from_top = 4;
		x->position[3][5] = block;
		x->position[3][6] = block;
		x->position[4][5] = block;
		x->position[4][6] = block;
	}
	if (type == 2) {
		//drawing a S piece
		x->set = 0;
		x->S = 0;
		x->E = 0;
		x->W = 0;
		x->rotation = 0;
		x->type = 'S';
		x->from_left = 5;
		x->from_top = 4;
		x->position[4][4] = block;
		x->position[4][5] = block;
		x->position[3][5] = block;
		x->position[3][6] = block;
	}
	if (type == 3) {
		//drawing a T piece
		x->set = 0;
		x->S = 0;
		x->E = 0;
		x->W = 0;
		x->rotation = 0;
		x->type = 'T';
		x->from_left = 5;
		x->from_top = 3;
		x->position[3][4] = block;
		x->position[3][5] = block;
		x->position[3][6] = block;
		x->position[4][5] = block;
	}
	if (type == 4) {
		//drawing a L piece
		x->set = 0;
		x->S = 0;
		x->E = 0;
		x->W = 0;
		x->rotation = 0;
		x->type = 'L';
		x->from_left = 4;
		x->from_top = 4;
		x->position[4][4] = block;
		x->position[3][4] = block;
		x->position[3][5] = block;
		x->position[3][6] = block;
	}
	if (type == 5) {
		//drawing a J piece
		x->set = 0;
		x->S = 0;
		x->E = 0;
		x->W = 0;
		x->rotation = 0;
		x->type = 'J';
		x->from_left = 6;
		x->from_top = 4;
		x->position[3][5] = block;
		x->position[3][4] = block;
		x->position[3][6] = block;
		x->position[4][6] = block;

	}
	if (type == 6) {
		//drawing a Z piece
		x->set = 0;
		x->S = 0;
		x->E = 0;
		x->W = 0;
		x->rotation = 0;
		x->type = 'Z';
		x->from_left = 5;
		x->from_top = 4;
		x->position[4][5] = block;
		x->position[3][5] = block;
		x->position[3][4] = block;
		x->position[4][6] = block;

	}

	//GLOBAL
	x->basedelay = 8;
	x->setdelay = x->basedelay;

}

void music() {
	Beep(658, 125);
	Beep(1320, 500);
	Beep(990, 250);
	Beep(1056, 250);
	Beep(1188, 250);
	Beep(1320, 125);
	Beep(1188, 125);
	Beep(1056, 250);
	Beep(990, 250);
	Beep(880, 500);
	Beep(880, 250);
	Beep(1056, 250);
	Beep(1320, 500);
	Beep(1188, 250);
	Beep(1056, 250);
	Beep(990, 750);
	Beep(1056, 250);
	Beep(1188, 500);
	Beep(1320, 500);
	Beep(1056, 500);
	Beep(880, 500);
	Beep(880, 500);
	Sleep(250);
	Beep(1188, 500);
	Beep(1408, 250);
	Beep(1760, 500);
	Beep(1584, 250);
	Beep(1408, 250);
	Beep(1320, 750);
	Beep(1056, 250);
	Beep(1320, 500);
	Beep(1188, 250);
	Beep(1056, 250);
	Beep(990, 500);
	Beep(990, 250);
	Beep(1056, 250);
	Beep(1188, 500);
	Beep(1320, 500);
	Beep(1056, 500);
	Beep(880, 500);
	Beep(880, 500);
	Sleep(500);
	Beep(1320, 500);
	Beep(990, 250);
	Beep(1056, 250);
	Beep(1188, 250);
	Beep(1320, 125);
	Beep(1188, 125);
	Beep(1056, 250);
	Beep(990, 250);
	Beep(880, 500);
	Beep(880, 250);
	Beep(1056, 250);
	Beep(1320, 500);
	Beep(1188, 250);
	Beep(1056, 250);
	Beep(990, 750);
	Beep(1056, 250);
	Beep(1188, 500);
	Beep(1320, 500);
	Beep(1056, 500);
	Beep(880, 500);
	Beep(880, 500);
	Sleep(250);
	Beep(1188, 500);
	Beep(1408, 250);
	Beep(1760, 500);
	Beep(1584, 250);
	Beep(1408, 250);
	Beep(1320, 750);
	Beep(1056, 250);
	Beep(1320, 500);
	Beep(1188, 250);
	Beep(1056, 250);
	Beep(990, 500);
	Beep(990, 250);
	Beep(1056, 250);
	Beep(1188, 500);
	Beep(1320, 500);
	Beep(1056, 500);
	Beep(880, 500);
	Beep(880, 500);
	Sleep(500);
	Beep(660, 1000);
	Beep(528, 1000);
	Beep(594, 1000);
	Beep(495, 1000);
	Beep(528, 1000);
	Beep(440, 1000);
	Beep(419, 1000);
	Beep(495, 1000);
	Beep(660, 1000);
	Beep(528, 1000);
	Beep(594, 1000);
	Beep(495, 1000);
	Beep(528, 500);
	Beep(660, 500);
	Beep(880, 1000);
	Beep(838, 2000);
	Beep(660, 1000);
	Beep(528, 1000);
	Beep(594, 1000);
	Beep(495, 1000);
	Beep(528, 1000);
	Beep(440, 1000);
	Beep(419, 1000);
	Beep(495, 1000);
	Beep(660, 1000);
	Beep(528, 1000);
	Beep(594, 1000);
	Beep(495, 1000);
	Beep(528, 500);
	Beep(660, 500);
	Beep(880, 1000);
	Beep(838, 2000);
}
void test() {

	//This function is for automating gameplay, for testing, or to just have fun.  Perhaps this will become AI at some point.

	//Move down = 0
	//Move left = 1
	//Move right = 2
	//rotate right = 3

	//board of commands
	//,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

	//Test I block position 0
	int test1[10000] = { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	//Test I block position 1
	int test2[10000] = { 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,3, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,3, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,3, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,3, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	//TEST Q block position 0
	int test3[10000] = { 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	//TEST S block position 0

	//TEST S block position 1

	//TEST Z block position 0

	//TEST Z block position 1

	//TEST T block position 0

	//TEST T block position 1

	//TEST T block position 2

	//TEST T block position 3

	//TEST J block position 0

	//TEST J block position 1

	//TEST J block position 2

	//TEST J block position 3

	//TEST L block position 0

	//TEST L block position 1

	//TEST L block position 2

	//TEST L block position 3

}
void command(piece *x) {

	//This function converts a keypress into a decimal value to be used to move,drop, and rotate pieces through x->command typedef

	x->command = _getch();

	if (x->command == 's') {
		x->command = 0;
	}
	if (x->command == 'a') {
		x->command = 1;
	}
	if (x->command == 'd') {
		x->command = 2;
	}
	if (x->command == 'w') {
		x->command = 5;
	}
	if (x->command == 'j') {
		x->command = 3;
	}
	if (x->command == 'k') {
		x->command = 4;
	}

}

//Move functions first checks collision off the pieces, before they are moved, and then set into the board[][] array.


void master_collision(piece *x, char board[][bWIDTH]) {

	if (x->S == 0) {//reset delay 
		x->setdelay = x->basedelay;
	}

	if (x->type == 'I') {
		collision_I(x, board);
	}
	if (x->type == 'Q') {
		collision_Q(x, board);
	}
	if (x->type == 'L') {
		collision_L(x, board);
	}
	if (x->type == 'Z') {
		collision_Z(x, board);
	}
	if (x->type == 'S') {
		collision_S(x, board);
	}
	if (x->type == 'J') {
		collision_J(x, board);
	}
	if (x->type == 'T') {
		collision_T(x, board);
	}

	///////for all pieces



}
void master_move(piece *x, char board[][bWIDTH]) {


	//999 prevents further movement
	if (x->command == 999) {
		return;
	}

	if (x->type == 'I') {
		if (x->command == 5) {
			x->command = 0;
			while (x->set != 1) {
				master_collision(x, board);
				move_I(x);
				master_collision(x, board);


			}
		}
		else {
			if (x->S == 0) {//reset delay 
				x->setdelay = x->basedelay;
			}
			master_collision(x, board);
			move_I(x);
			master_collision(x, board);
		}



	}
	if (x->type == 'Q') {
		if (x->command == 5) {
			x->command = 0;
			while (x->set != 1) {
				master_collision(x, board);
				move_Q(x);
				master_collision(x, board);


			}
		}
		else {
			if (x->S == 0) {//reset delay 
				x->setdelay = x->basedelay;
			}
			master_collision(x, board);
			move_Q(x);
			master_collision(x, board);
		}

	}
	if (x->type == 'S') {
		if (x->command == 5) {
			x->command = 0;
			while (x->set != 1) {
				master_collision(x, board);
				move_S(x);
				master_collision(x, board);


			}
		}
		else {
			if (x->S == 0) {//reset delay 
				x->setdelay = x->basedelay;
			}
			master_collision(x, board);
			move_S(x);
			master_collision(x, board);
		}
	}
	if (x->type == 'L') {
		if (x->command == 5) {
			x->command = 0;
			while (x->set != 1) {
				master_collision(x, board);
				move_L(x);
				master_collision(x, board);


			}
		}
		else {
			if (x->S == 0) {//reset delay 
				x->setdelay = x->basedelay;
			}
			master_collision(x, board);
			move_L(x);
			master_collision(x, board);
		}
	}
	if (x->type == 'J') {
		if (x->command == 5) {
			x->command = 0;
			while (x->set != 1) {
				master_collision(x, board);
				move_J(x);
				master_collision(x, board);


			}
		}
		else {
			if (x->S == 0) {//reset delay 
				x->setdelay = x->basedelay;
			}
			master_collision(x, board);
			move_J(x);
			master_collision(x, board);
		}
	}
	if (x->type == 'Z') {
		if (x->command == 5) {
			x->command = 0;
			while (x->set != 1) {
				master_collision(x, board);
				move_Z(x);
				master_collision(x, board);


			}
		}
		else {
			if (x->S == 0) {//reset delay 
				x->setdelay = x->basedelay;
			}
			master_collision(x, board);
			move_Z(x);
			master_collision(x, board);
		}
	}
	if (x->type == 'T') {
		if (x->command == 5) {
			x->command = 0;
			while (x->set != 1) {
				master_collision(x, board);
				move_T(x);
				master_collision(x, board);


			}
		}
		else {
			if (x->S == 0) {//reset delay 
				x->setdelay = x->basedelay;
			}
			master_collision(x, board);
			move_T(x);
			master_collision(x, board);
		}
	}






}

//I Piece type = 0
void collision_I_rotation(piece *x, char board[][bWIDTH]) {
	x->rr = 0;
	x->rl = 0;


	//I only has two rotation positions, and so we only need to check the top in position one.
	if (((x->command == 3) || (x->command == 4)) && (x->rotation == 0)) {

		if ((board[x->from_top - 1][x->from_left] != empty) || (board[x->from_top - 2][x->from_left] != empty) || (board[x->from_top + 1][x->from_left] != empty)) {// check top
			x->rr = 1;
			x->rl = 1;
		}
		return;
	}
	if ((x->command == 3 | 4) && (x->rotation == 1)) {

		if ((board[x->from_top][x->from_left + 1] != empty)) {// check right
			x->rr = 1;
			x->rl = 1;
		}
		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top][x->from_left - 2] != empty)) {// check left
			x->rr = 1;
			x->rl = 1;
		}
		return;
	}

}
void collision_I(piece *x, char board[][bWIDTH]) {

	if (x->command == 3) {
		collision_I_rotation(x, board);
		return;
	}
	if (x->command == 4) {
		collision_I_rotation(x, board);
		return;
	}



	////Rotation = 0

	if (((x->command == 0) || (x->command == 1) || (x->command == 2)) && (x->rotation == 0)) {

		if (board[x->from_top][x->from_left - 3] != empty) {// check left
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if (board[x->from_top][x->from_left + 2] != empty) {// check right
			x->E = 1;
		}
		else {
			x->E = 0;
		}
		if ((board[x->from_top + 1][x->from_left] != empty) || (board[x->from_top + 1][x->from_left - 1] != empty) || (board[x->from_top + 1][x->from_left - 2] != empty) || (board[x->from_top + 1][x->from_left + 1] != empty)) {// check south
			x->S = 1;
		}
		else {
			x->S = 0;
		}
	}

	//Rotation = 1 

	if (((x->command == 0) || (x->command == 1) || (x->command == 2)) && (x->rotation == 1)) {
		//check left
		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty) || (board[x->from_top - 2][x->from_left - 1] != empty) || (board[x->from_top + 1][x->from_left - 1] != empty)) {
			x->W = 1;

		}
		else {
			x->W = 0;
		}
		//check right
		if ((board[x->from_top][x->from_left + 1] != empty) || (board[x->from_top - 1][x->from_left + 1] != empty) || (board[x->from_top - 2][x->from_left + 1] != empty) || (board[x->from_top + 1][x->from_left + 1] != empty)) {
			x->E = 1;

		}
		else {
			x->E = 0;
		}
		//check south
		if (board[x->from_top + 2][x->from_left] != empty) {
			x->S = 1;

		}
		else {
			x->S = 0;
		}

	}

	////Type = I Rotation from 0 to 1

	if ((x->command == 3) && (x->rotation == 0)) {

		if ((board[x->from_top - 1][x->from_left] != empty) && (board[x->from_top - 2][x->from_left] != empty)) {// check north
			x->N = 1;
		}
		else {
			x->N = 0;
		}
		if (board[x->from_top + 1][x->from_left] != empty) {// check south
			x->S = 1;
			//prevent set returning now, set should only activate on downward motion;
			return;
		}
		else {
			x->S = 0;
		}
		x->W = 0;
		x->E = 0;



	}

	////Type = I Rotation from 1 to 0

	if ((x->command == 3) && (x->rotation == 1)) {
		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top][x->from_left - 2] != empty)) {// check west
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if (board[x->from_top][x->from_left + 1] != empty) {// check east
			x->E = 1;

		}
		else {
			x->E = 0;
		}


	}

	//This checks if the piece should be set or not, so that it can become apart of the board

	if (x->S == 0) {
		x->setdelay = x->basedelay;
	}

	if (x->S == 1) {
		x->setdelay--;
	}
	if ((x->setdelay == 0) && (x->S == 1)) {
		x->set = 1;
	}

}
void move_I_rotate_right(piece *x) {


	if ((x->rotation == 0) && ((x->rr == 0) && (x->rl == 0))) {//clear if rotation is 0
															   //erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top][x->from_left - 2] = empty;
		x->position[x->from_top][x->from_left + 1] = empty;

		//set new rotation
		x->rotation = 1;
		//draw new rotation
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top + 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;
		return;
	}

	if ((x->rotation == 1) && ((x->rr == 0) && (x->rl == 0))) {
		//erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top + 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
		//set new rotation
		x->rotation = 0;
		//draw new rotation
		x->position[x->from_top][x->from_left] = block;
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top][x->from_left - 2] = block;
		x->position[x->from_top][x->from_left + 1] = block;
		return;
	}

}
void move_I(piece *x) {

	if ((x->command == 4) || (x->command == 3)) {
		move_I_rotate_right(x);
		return;
	}


	// Rotation = 0 Movement =  down
	if ((x->command == 0) && (x->rotation == 0) && (x->S == 0) && (x->S == 0)) {
		x->from_top++;

		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left - 1] = empty;
		x->position[x->from_top - 1][x->from_left - 2] = empty;
		x->position[x->from_top - 1][x->from_left + 1] = empty;

		x->position[x->from_top][x->from_left] = block; // middle block
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top][x->from_left - 2] = block;
		x->position[x->from_top][x->from_left + 1] = block;



	}
	// Rotation = 0 Movement =  left
	if ((x->command == 1) && (x->rotation == 0) && (x->W == 0)) {
		x->from_left--;


		x->position[x->from_top][x->from_left] = empty; // middle block
		x->position[x->from_top][x->from_left - 1] = empty; // middle block
		x->position[x->from_top][x->from_left + 1] = empty; // middle block
		x->position[x->from_top][x->from_left + 2] = empty; // middle block

		x->position[x->from_top][x->from_left] = block; // middle block
		x->position[x->from_top][x->from_left - 1] = block; // middle block
		x->position[x->from_top][x->from_left - 2] = block; // middle block
		x->position[x->from_top][x->from_left + 1] = block; // middle block

	}
	//Rotation = 0 Movement =  right
	if ((x->command == 2) && (x->rotation == 0) && (x->E == 0)) {
		x->from_left++;

		x->position[x->from_top][x->from_left] = empty; // middle block
		x->position[x->from_top][x->from_left - 1] = empty; // middle block
		x->position[x->from_top][x->from_left - 2] = empty; // middle block
		x->position[x->from_top][x->from_left - 3] = empty; // middle block

		x->position[x->from_top][x->from_left] = block; // middle block
		x->position[x->from_top][x->from_left - 1] = block; // middle block
		x->position[x->from_top][x->from_left - 2] = block; // middle block
		x->position[x->from_top][x->from_left + 1] = block; // middle block

	}
	//Rotation = 1 Movement = down
	if ((x->command == 0) && (x->rotation == 1) && (x->S == 0)) {
		x->from_top++;

		x->position[x->from_top][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;
		x->position[x->from_top + 1][x->from_left] = block;

		x->position[x->from_top - 4][x->from_left] = empty;
		x->position[x->from_top - 3][x->from_left] = empty;





	}
	//Rotation = 1 Movement =  left
	if ((x->command == 1) && (x->rotation == 1) && (x->W == 0)) {
		x->from_left--;
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top + 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;

		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top + 1][x->from_left + 1] = empty;
		x->position[x->from_top - 2][x->from_left + 1] = empty;
		x->position[x->from_top - 1][x->from_left + 1] = empty;

	}
	//Rotation = 1 Movement =  right
	if ((x->command == 2) && (x->rotation == 1) && (x->E == 0)) {
		x->from_left++;
		x->position[x->from_top][x->from_left] = block;
		x->position[x->from_top + 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;

		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top - 1][x->from_left - 1] = empty;
		x->position[x->from_top - 2][x->from_left - 1] = empty;
		x->position[x->from_top + 1][x->from_left - 1] = empty;

	}
	//Rotation = 0 Movement = rotate
	//
	//
	//
	//if ((x->command == 3) && (x->rotation == 0) && (x->W == 0) && (x->E == 0)) {

	//	x->position[x->from_top][x->from_left] = empty;
	//	x->position[x->from_top][x->from_left - 1] = empty;
	//	x->position[x->from_top][x->from_left - 2] = empty;
	//	x->position[x->from_top][x->from_left + 1] = empty;

	//	x->position[x->from_top][x->from_left] = block;//middle block
	//	x->position[x->from_top + 1][x->from_left] = block;
	//	x->position[x->from_top - 1][x->from_left] = block;
	//	x->position[x->from_top - 2][x->from_left] = block;

	//	// set new rotation position
	//	x->rotation = 1;
	//	return;
	//	//void command so it doesn't interact anymore
	//	x->command = NULL;
	//}
	//Rotation = 1 Movement = rotate

	//
	//
	//
	//if ((x->command == 3) && (x->rotation == 1) && (x->W == 0) && (x->E == 0)) {

	//	x->position[x->from_top][x->from_left] = empty;
	//	x->position[x->from_top - 1][x->from_left] = empty;
	//	x->position[x->from_top - 2][x->from_left] = empty;
	//	x->position[x->from_top + 1][x->from_left] = empty;

	//	x->position[x->from_top][x->from_left] = block;
	//	x->position[x->from_top][x->from_left - 1] = block;
	//	x->position[x->from_top][x->from_left - 2] = block;
	//	x->position[x->from_top][x->from_left + 1] = block;

	//	// set new rotation position
	//	x->rotation = 0;
	//	//void command so it doesn't interact anymore
	//	x->command = NULL;

	//}



}

//Q Piece type = 1
void collision_Q(piece *x, char board[][bWIDTH]) {

	//Type = Q doesn't rotate


	if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty)) {// check left 
		x->W = 1;
	}
	else {
		x->W = 0;
	}


	if ((board[x->from_top][x->from_left + 2] != empty) || (board[x->from_top - 1][x->from_left + 2] != empty)) {// check right
		x->E = 1;
	}
	else {
		x->E = 0;
	}
	if (((board[x->from_top + 1][x->from_left] != empty)) || ((board[x->from_top + 1][x->from_left + 1] != empty))) {// check south
		x->S = 1;
	}
	else {
		x->S = 0;
	}



	//This checks if the piece should be set or not, so that it can become apart of the board
	if (x->S == 0) {
		x->setdelay = x->basedelay;
	}
	if (x->S == 1) {
		x->setdelay--;
	}
	if ((x->setdelay == 0) && (x->S == 1)) {
		x->set = 1;
	}

}
void move_Q(piece *x) {



	//prevent Q from rotating because Q doesn't rotate
	//if ((x->type == 'Q') && ((x->command == 3) || (x->command == 4))) {
	//	x->command = 0;
	//}
	// Movement =  down
	if ((x->type == 'Q') && (x->command == 0) && (x->S == 0)) {
		x->from_top++;

		x->position[x->from_top][x->from_left] = block;
		x->position[x->from_top][x->from_left + 1] = block;

		x->position[x->from_top - 2][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left + 1] = empty;


	}

	// Movement =  left
	if ((x->type == 'Q') && (x->W == 0) && (x->command == 1)) {
		x->from_left--;

		x->position[x->from_top][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left] = block;


		x->position[x->from_top - 1][x->from_left + 2] = empty;
		x->position[x->from_top][x->from_left + 2] = empty;



	}

	// Movement =  right
	if ((x->type == 'Q') && (x->command == 2) && (x->E == 0)) {
		x->from_left++;


		x->position[x->from_top][x->from_left + 1] = block;
		x->position[x->from_top - 1][x->from_left + 1] = block;

		x->position[x->from_top - 1][x->from_left - 1] = empty;
		x->position[x->from_top][x->from_left - 1] = empty;


	}
}

//S Piece type = 2
void collision_S(piece *x, char board[][bWIDTH]) {


	if (x->command == 3) {
		collision_S_rotation(x, board);
		return;
	}
	if (x->command == 4) {
		collision_S_rotation(x, board);
		return;
	}






	////Rotation = 0

	if (((x->command == 0) || (x->command == 1) || (x->command == 2) || (x->command == 3)) && (x->rotation == 0)) {

		if ((board[x->from_top][x->from_left - 2] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty)) {// check left
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if ((board[x->from_top - 1][x->from_left + 2] != empty) || (board[x->from_top][x->from_left + 1] != empty)) {// check right
			x->E = 1;
		}
		else {
			x->E = 0;
		}
		if ((board[x->from_top + 1][x->from_left] != empty) || (board[x->from_top + 1][x->from_left - 1] != empty) || (board[x->from_top][x->from_left + 1] != empty)) {// check south
			x->S = 1;
		}
		else {
			x->S = 0;
		}
	}


	if (((x->command == 0) || (x->command == 1) || (x->command == 2) || (x->command == 3)) && (x->rotation == 1)) {

		if ((board[x->from_top][x->from_left - 2] != empty) || (board[x->from_top - 1][x->from_left - 2] != empty) || (board[x->from_top + 1][x->from_left - 1] != empty)) {// check left
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if ((board[x->from_top][x->from_left + 1] != empty) || (board[x->from_top + 1][x->from_left + 1] != empty)) {// check right
			x->E = 1;
		}
		else {
			x->E = 0;
		}
		if ((board[x->from_top + 2][x->from_left] != empty) || (board[x->from_top + 1][x->from_left - 1] != empty)) {// check south
			x->S = 1;
		}
		else {
			x->S = 0;
		}
	}





	//This checks if the piece should be set or not, so that it can become apart of the board
	if (x->S == 0) {
		x->setdelay = x->basedelay;
	}
	if (x->S == 1) {
		x->setdelay--;
	}
	if ((x->setdelay == 0) && (x->S == 1)) {
		x->set = 1;
	}

}
void collision_S_rotation(piece *x, char board[][bWIDTH]) {
	x->rr = 0;
	x->rl = 0;


	//S only has two rotation positions, and so we only need to check the top in position one.
	if ((x->rotation == 0)) {

		if ((board[x->from_top - 2][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty) || (board[x->from_top + 1][x->from_left] != empty)) {// check top
			x->rr = 1;
			x->rl = 1;
		}
		return;
	}
	if ((x->rotation == 1)) {

		if ((board[x->from_top - 1][x->from_left + 1] != empty) || (board[x->from_top - 1][x->from_left] != empty)) {// check right
			x->rr = 1;
			x->rl = 1;
		}
		if ((board[x->from_top + 1][x->from_left - 1] != empty)) {// check below
			x->rr = 1;
			x->rl = 1;
		}
		return;
	}


}
void move_S_rotate_right(piece *x) {

	if ((x->rotation == 0) && ((x->rr == 0) && (x->rl == 0))) {//clear if rotation is 0
															   //erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left + 1] = empty;

		//set new rotation
		x->from_top--;
		x->rotation = 1;
		//draw new rotation
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top + 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left - 1] = block;
		return;
	}

	if ((x->rotation == 1) && ((x->rr == 0) && (x->rl == 0))) {
		//erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top + 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left - 1] = empty;
		//set new rotation
		x->from_top++;
		x->rotation = 0;
		//draw new rotation
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left + 1] = block;
		return;
	}




}
void move_S(piece *x) {

	if ((x->command == 3) || (x->command == 4)) {
		move_S_rotate_right(x);
	}




	// Rotation = 0 Movement =  down
	if ((x->command == 0) && (x->rotation == 0) && (x->S == 0) && (x->S == 0)) {
		x->from_top++;

		x->position[x->from_top][x->from_left] = block;
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top - 1][x->from_left + 1] = block;


		x->position[x->from_top - 1][x->from_left - 1] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left + 1] = empty;




	}

	// Rotation = 0 Movement =  right
	if ((x->E == 0) && (x->command == 2) && (x->rotation == 0) && (x->E == 0)) {
		x->from_left++;

		x->position[x->from_top][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left + 1] = block;

		x->position[x->from_top][x->from_left - 2] = empty;
		x->position[x->from_top - 1][x->from_left - 1] = empty;


	}

	// Rotation = 0 Movement =  left
	if ((x->W == 0) && (x->command == 1) && (x->rotation == 0) && (x->W == 0)) {
		x->from_left--;

		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top - 1][x->from_left] = block;

		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top - 1][x->from_left + 2] = empty;


	}

	// Rotation = 1 Movement =  down
	if ((x->command == 0) && (x->rotation == 1) && (x->S == 0) && (x->S == 0)) {
		x->from_top++;

		x->position[x->from_top - 1][x->from_left] = empty;//middle
		x->position[x->from_top - 1][x->from_left - 1] = empty;
		x->position[x->from_top - 2][x->from_left - 1] = empty;
		x->position[x->from_top][x->from_left] = empty;

		x->position[x->from_top][x->from_left] = block;//middle
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top - 1][x->from_left - 1] = block;
		x->position[x->from_top + 1][x->from_left] = block;



	}

	// Rotation = 1 Movement =  left
	if ((x->command == 1) && (x->rotation == 1) && (x->W == 0)) {
		x->from_left--;

		x->position[x->from_top][x->from_left - 1] = block;//middle
		x->position[x->from_top - 1][x->from_left - 1] = block;
		x->position[x->from_top + 1][x->from_left] = block;

		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top + 1][x->from_left + 1] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;

	}

	// Rotation = 1 Movement =  right
	if ((x->command == 2) && (x->rotation == 1) && (x->E == 0)) {
		x->from_left++;

		x->position[x->from_top][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left - 1] = block;
		x->position[x->from_top + 1][x->from_left] = block;

		x->position[x->from_top][x->from_left - 2] = empty;
		x->position[x->from_top - 1][x->from_left - 2] = empty;
		x->position[x->from_top + 1][x->from_left - 1] = empty;




	}



}

//T Piece type = 3
void collision_T_rotation(piece * x, char board[][bWIDTH]) {
	x->rr = 0;
	x->rl = 0;

	if (x->rotation == 0) {

		if ((board[x->from_top - 1][x->from_left] != empty)) {
			x->rl = 1;
			x->rr = 1;
		}
		return;
	}
	if (x->rotation == 1) {

		if ((board[x->from_top][x->from_left + 1] != empty)) {
			x->rl = 1;
		}
		if ((board[x->from_top + 1][x->from_left - 1] != empty) || (board[x->from_top + 1][x->from_left + 1] != empty)) {
			x->rr = 1;
		}
		return;
	}
	if (x->rotation == 2) {

		if ((board[x->from_top][x->from_left + 1] != empty) || (board[x->from_top][x->from_left - 1] != empty)) {
			x->rl = 1;
		}
		if ((board[x->from_top + 1][x->from_left - 1] != empty) || (board[x->from_top + 1][x->from_left + 1] != empty)) {
			x->rr = 1;
		}
		return;
	}
	if (x->rotation == 3) {

		if ((board[x->from_top + 1][x->from_left - 1] != empty) || (board[x->from_top + 1][x->from_left + 1] != empty)) {
			x->rl = 1;
		}
		if (board[x->from_top][x->from_left - 1] != empty) {
			x->rr = 1;
		}
		return;
	}

}
void collision_T(piece *x, char board[][bWIDTH]) {


	if (x->command == 3) {
		collision_T_rotation(x, board);
		return;
	}
	if (x->command == 4) {
		collision_T_rotation(x, board);
		return;
	}

	////Rotation = 0
	if (x->rotation == 0) {

		if ((board[x->from_top][x->from_left - 2] != empty) || (board[x->from_top + 1][x->from_left - 1] != empty)) {// check left
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if ((board[x->from_top][x->from_left + 2] != empty) || (board[x->from_top + 1][x->from_left + 1] != empty)) {// check right
			x->E = 1;
		}
		else {
			x->E = 0;
		}
		if ((board[x->from_top + 2][x->from_left] != empty) || (board[x->from_top + 1][x->from_left - 1] != empty) || (board[x->from_top + 1][x->from_left + 1] != empty)) {// check south
			x->S = 1;
		}
		else {
			x->S = 0;
		}

	}

	////Rotation = 1
	if (x->rotation == 1) {

		if ((board[x->from_top][x->from_left - 2] != empty) || (board[x->from_top + 1][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty)) {// check left
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if ((board[x->from_top - 1][x->from_left + 1] != empty) || (board[x->from_top][x->from_left + 1] != empty) || (board[x->from_top + 1][x->from_left + 1] != empty)) {// check right
			x->E = 1;
		}
		else {
			x->E = 0;
		}
		if ((board[x->from_top + 2][x->from_left] != empty) || (board[x->from_top + 1][x->from_left - 1] != empty)) {// check south
			x->S = 1;
		}
		else {
			x->S = 0;
		}

	}

	////Rotation = 2
	if (((x->command == 0) || (x->command == 1) || (x->command == 2) || (x->command == 3)) && (x->rotation == 2)) {

		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top + 1][x->from_left - 2] != empty)) {// check left
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if ((board[x->from_top][x->from_left + 1] != empty) || (board[x->from_top + 1][x->from_left + 2] != empty)) {// check right
			x->E = 1;
		}
		else {
			x->E = 0;
		}
		if ((board[x->from_top + 2][x->from_left] != empty) || (board[x->from_top + 2][x->from_left + 1] != empty) || (board[x->from_top + 2][x->from_left - 1] != empty)) {// check south
			x->S = 1;
		}
		else {
			x->S = 0;
		}

	}

	////Rotation = 3
	if (((x->command == 0) || (x->command == 1) || (x->command == 2) || (x->command == 3)) && (x->rotation == 3)) {

		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top + 1][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty)) {// check left
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if ((board[x->from_top][x->from_left + 2] != empty) || (board[x->from_top - 1][x->from_left + 1] != empty) || (board[x->from_top + 1][x->from_left + 1] != empty)) {// check right
			x->E = 1;
		}
		else {
			x->E = 0;
		}
		if ((board[x->from_top + 2][x->from_left] != empty) || (board[x->from_top + 1][x->from_left + 1] != empty)) {// check south
			x->S = 1;
		}
		else {
			x->S = 0;
		}

	}



	//This checks if the piece should be set or not, so that it can become apart of the board
	if (x->S == 0) {
		x->setdelay = x->basedelay;
	}
	if (x->S == 1) {
		x->setdelay--;
	}
	if ((x->setdelay == 0) && (x->S == 1)) {
		x->set = 1;
	}

}
void move_T(piece *x) {

	if ((x->command == 3) || (x->command == 4)) {
		move_T_rotate(x);
		return;
	}

	// Rotation = 0 Movement =  down
	if ((x->command == 0) && (x->rotation == 0) && (x->S == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top + 1][x->from_left] = empty;

		x->from_top++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top][x->from_left + 1] = block;
		x->position[x->from_top + 1][x->from_left] = block;

	}
	// Rotation = 0 Movement =  right
	if ((x->command == 2) && (x->rotation == 0) && (x->E == 0)) {
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top + 1][x->from_left] = empty;

		x->from_left++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top][x->from_left + 1] = block;
		x->position[x->from_top + 1][x->from_left] = block;

	}
	// Rotation = 0 Movement =  left
	if ((x->command == 1) && (x->rotation == 0) && (x->W == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top + 1][x->from_left] = empty;

		x->from_left--;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top][x->from_left + 1] = block;
		x->position[x->from_top + 1][x->from_left] = block;

	}


	// Rotation = 1 Movement =  down
	if ((x->command == 0) && (x->rotation == 1) && (x->S == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top + 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;

		x->from_top++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top + 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left] = block;

	}
	// Rotation = 1 Movement =  right
	if ((x->command == 2) && (x->rotation == 1) && (x->E == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top + 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;

		x->from_left++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top + 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left] = block;

	}
	// Rotation = 1 Movement =  left
	if ((x->command == 1) && (x->rotation == 1) && (x->W == 0)) {
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top + 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;

		x->from_left--;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top + 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left] = block;
	}

	// Rotation = 2 Movement =  down
	if ((x->command == 0) && (x->rotation == 2) && (x->S == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top + 1][x->from_left] = empty;
		x->position[x->from_top + 1][x->from_left - 1] = empty;
		x->position[x->from_top + 1][x->from_left + 1] = empty;

		x->from_top++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top + 1][x->from_left] = block;
		x->position[x->from_top + 1][x->from_left - 1] = block;
		x->position[x->from_top + 1][x->from_left + 1] = block;

	}
	// Rotation = 2 Movement =  right
	if ((x->command == 2) && (x->rotation == 2) && (x->E == 0)) {
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top + 1][x->from_left] = empty;
		x->position[x->from_top + 1][x->from_left - 1] = empty;
		x->position[x->from_top + 1][x->from_left + 1] = empty;

		x->from_left++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top + 1][x->from_left] = block;
		x->position[x->from_top + 1][x->from_left - 1] = block;
		x->position[x->from_top + 1][x->from_left + 1] = block;

	}
	// Rotation = 2 Movement =  left
	if ((x->command == 1) && (x->rotation == 2) && (x->W == 0)) {
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top + 1][x->from_left] = empty;
		x->position[x->from_top + 1][x->from_left - 1] = empty;
		x->position[x->from_top + 1][x->from_left + 1] = empty;

		x->from_left--;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top + 1][x->from_left] = block;
		x->position[x->from_top + 1][x->from_left - 1] = block;
		x->position[x->from_top + 1][x->from_left + 1] = block;

	}

	// Rotation = 3 Movement =  down
	if ((x->command == 0) && (x->rotation == 3) && (x->S == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top + 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top][x->from_left + 1] = empty;

		x->from_top++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top + 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top][x->from_left + 1] = block;

	}
	// Rotation = 3 Movement =  right
	if ((x->command == 2) && (x->rotation == 3) && (x->E == 0)) {
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top + 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top][x->from_left + 1] = empty;

		x->from_left++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top + 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top][x->from_left + 1] = block;


	}
	// Rotation = 3 Movement =  left
	if ((x->command == 1) && (x->rotation == 3) && (x->W == 0)) {
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top + 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top][x->from_left + 1] = empty;

		x->from_left--;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top + 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top][x->from_left + 1] = block;

	}








	//// Rotation = 0 Movement =  rotateright
	//if ((x->command == 3) && (x->rotation == 0)) {

	//	x->position[x->from_top - 1][x->from_left] = block;

	//	x->position[x->from_top][x->from_left - 1] = empty;

	//	x->rotation = 1;
	//	return;

	//}
	//// Rotation = 1 Movement =  rotateright
	//if ((x->command == 3) && (x->rotation == 1)) {

	//	x->position[x->from_top][x->from_left - 1] = block;

	//	x->position[x->from_top + 1][x->from_left] = empty;

	//	x->rotation = 2;
	//	return;

	//}
	//// Rotation = 2 Movement =  rotateright
	//if ((x->command == 3) && (x->rotation == 2)) {

	//	x->position[x->from_top + 1][x->from_left] = block;

	//	x->position[x->from_top][x->from_left + 1] = empty;

	//	x->rotation = 3;
	//	return;

	//}
	//// Rotation = 3 Movement =  rotateright
	//if ((x->command == 3) && (x->rotation == 3)) {

	//	x->position[x->from_top][x->from_left + 1] = block;

	//	x->position[x->from_top - 1][x->from_left] = empty;

	//	x->rotation = 0;
	//	return;

	//}



}
void move_T_rotate(piece * x) {

	int i = x->rotation;

	if ((x->command == 3) && (x->rl == 1)) {
		return;
	}
	if ((x->command == 4) && (x->rr == 1)) {
		return;
	}

	if (x->command == 3) {
		x->rotation--;
		if (x->rotation == -1) {
			x->rotation = 3;
		}
	}
	if (x->command == 4) {
		x->rotation++;
		if (x->rotation == 4) {
			x->rotation = 0;
		}
	}


	if (i == 0) { //clear if rotation is 0
				  //erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top + 1][x->from_left] = empty;
	}
	if (i == 1) { //clear if rotation is 0
				  //erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top + 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;
	}
	if (i == 2) { //clear if rotation is 0
				  //erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top + 1][x->from_left] = empty;
		x->position[x->from_top + 1][x->from_left - 1] = empty;
		x->position[x->from_top + 1][x->from_left + 1] = empty;
	}
	if (i == 3) { //clear if rotation is 0
				  //erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top + 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top][x->from_left + 1] = empty;
	}


	if (x->rotation == 3) {
		//draw new rotation
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top + 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top][x->from_left + 1] = block;
	}
	if (x->rotation == 2) {
		//draw new rotation
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top + 1][x->from_left] = block;
		x->position[x->from_top + 1][x->from_left - 1] = block;
		x->position[x->from_top + 1][x->from_left + 1] = block;
	}
	if (x->rotation == 1) {
		//draw new rotation
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top + 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left] = block;
	}
	if (x->rotation == 0) {
		//draw new rotation
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top][x->from_left + 1] = block;
		x->position[x->from_top + 1][x->from_left] = block;
	}



}

//L Piece type = 4
void collision_L_rotation(piece *x, char board[][bWIDTH]) {
	x->rr = 0;
	x->rl = 0;

	if (x->rotation == 0) {

		if ((board[x->from_top - 2][x->from_left] != empty) || (board[x->from_top][x->from_left + 1] != empty) || (board[x->from_top][x->from_left + 2] != empty)) {
			x->rl = 1;
		}
		if ((board[x->from_top][x->from_left + 1] != empty) || (board[x->from_top - 2][x->from_left + 1] != empty) || (board[x->from_top - 2][x->from_left] != empty)) {
			x->rr = 1;
		}
		return;
	}
	if (x->rotation == 1) {

		if ((board[x->from_top - 1][x->from_left + 1] != empty) || (board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty)) {
			x->rl = 1;
		}
		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left + 1] != empty) || (board[x->from_top][x->from_left + 1] != empty)) {
			x->rr = 1;
		}
		return;
	}
	if (x->rotation == 2) {

		if ((board[x->from_top - 1][x->from_left] != empty) || (board[x->from_top - 2][x->from_left - 1] != empty) || (board[x->from_top - 2][x->from_left] != empty)) {
			x->rl = 1;
		}
		if ((board[x->from_top - 1][x->from_left] != empty) || (board[x->from_top - 2][x->from_left] != empty)) {
			x->rr = 1;
		}
		return;
	}
	if (x->rotation == 3) {

		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left + 1] != empty)) {
			x->rl = 1;
		}
		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left + 1] != empty)) {
			x->rr = 1;
		}
		return;
	}


}
void collision_L(piece *x, char board[][bWIDTH]) {

	if (x->command == 3) {
		collision_L_rotation(x, board);
		return;
	}
	if (x->command == 4) {
		collision_L_rotation(x, board);
		return;
	}


	////Rotation = 0

	if (x->rotation == 0) {

		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty)) {// check left
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if ((board[x->from_top][x->from_left + 1] != empty) || (board[x->from_top - 1][x->from_left + 3] != empty)) {// check right
			x->E = 1;
		}
		else {
			x->E = 0;
		}
		if ((board[x->from_top + 1][x->from_left] != empty) || (board[x->from_top][x->from_left + 1] != empty) || (board[x->from_top][x->from_left + 2] != empty)) {// check south
			x->S = 1;
		}
		else {
			x->S = 0;
		}
	}

	if (x->rotation == 1) {

		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty) || (board[x->from_top - 2][x->from_left - 2] != empty)) {// check left
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if ((board[x->from_top][x->from_left + 1] != empty) || (board[x->from_top - 1][x->from_left + 1] != empty) || (board[x->from_top - 2][x->from_left + 1] != empty)) {// check right
			x->E = 1;
		}
		else {
			x->E = 0;
		}
		if ((board[x->from_top + 1][x->from_left] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty)) {// check south
			x->S = 1;
		}
		else {
			x->S = 0;
		}
	}

	if (x->rotation == 2) {

		if ((board[x->from_top][x->from_left - 2] != empty) || (board[x->from_top - 1][x->from_left] != empty)) {// check left
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if ((board[x->from_top][x->from_left + 2] != empty) || (board[x->from_top - 1][x->from_left + 2] != empty)) {// check right
			x->E = 1;
		}
		else {
			x->E = 0;
		}
		if ((board[x->from_top + 1][x->from_left] != empty) || (board[x->from_top + 1][x->from_left - 1] != empty) || (board[x->from_top + 1][x->from_left + 1] != empty)) {// check south
			x->S = 1;
		}
		else {
			x->S = 0;
		}
	}

	if (x->rotation == 3) {

		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty) || (board[x->from_top - 2][x->from_left - 1] != empty)) {// check left
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if ((board[x->from_top][x->from_left + 2] != empty) || (board[x->from_top - 1][x->from_left + 1] != empty) || (board[x->from_top - 2][x->from_left + 1] != empty)) {// check right
			x->E = 1;
		}
		else {
			x->E = 0;
		}
		if ((board[x->from_top + 1][x->from_left] != empty) || (board[x->from_top + 1][x->from_left + 1] != empty)) {// check south
			x->S = 1;
		}
		else {
			x->S = 0;
		}
	}








	//This checks if the piece should be set or not, so that it can become apart of the board
	if (x->S == 0) {
		x->setdelay = x->basedelay;
	}
	if (x->S == 1) {
		x->setdelay--;
	}
	if ((x->setdelay == 0) && (x->S == 1)) {
		x->set = 1;
	}

}
void move_L(piece *x) {

	if ((x->command == 3) || (x->command == 4)) {
		move_L_rotate(x);
		return;
	}

	// Rotation = 0 Movement =  down
	if ((x->command == 0) && (x->rotation == 0) && (x->S == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left + 1] = empty;
		x->position[x->from_top - 1][x->from_left + 2] = empty;

		x->from_top++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left + 1] = block;
		x->position[x->from_top - 1][x->from_left + 2] = block;
	}
	// Rotation = 0 Movement =  right
	if ((x->command == 2) && (x->rotation == 0) && (x->E != 1)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left + 1] = empty;
		x->position[x->from_top - 1][x->from_left + 2] = empty;

		x->from_left++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left + 1] = block;
		x->position[x->from_top - 1][x->from_left + 2] = block;
	}
	// Rotation = 0 Movement =  left
	if ((x->command == 1) && (x->rotation == 0) && (x->W != 1)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left + 1] = empty;
		x->position[x->from_top - 1][x->from_left + 2] = empty;

		x->from_left--;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left + 1] = block;
		x->position[x->from_top - 1][x->from_left + 2] = block;
	}
	// Rotation = 1 Movement =  left
	if ((x->command == 1) && (x->rotation == 1) && (x->W != 1)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left - 1] = empty;

		x->from_left--;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left - 1] = block;
	}
	// Rotation = 1 Movement =  down
	if ((x->command == 0) && (x->rotation == 1) && (x->S == 0)) {
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left - 1] = empty;

		x->from_top++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left - 1] = block;
	}
	// Rotation = 1 Movement =  right
	if ((x->command == 2) && (x->rotation == 1) && (x->E != 1)) {
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left - 1] = empty;

		x->from_left++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left - 1] = block;
	}
	// Rotation = 2 Movement =  left
	if ((x->command == 1) && (x->rotation == 2) && (x->W != 1)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top - 1][x->from_left + 1] = empty;
		x->position[x->from_top][x->from_left - 1] = empty;

		x->from_left--;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left + 1] = block;
		x->position[x->from_top - 1][x->from_left + 1] = block;
		x->position[x->from_top][x->from_left - 1] = block;
	}
	// Rotation = 2 Movement =  right
	if ((x->command == 2) && (x->rotation == 2) && (x->E != 1)) {
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top - 1][x->from_left + 1] = empty;
		x->position[x->from_top][x->from_left - 1] = empty;

		x->from_left++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left + 1] = block;
		x->position[x->from_top - 1][x->from_left + 1] = block;
		x->position[x->from_top][x->from_left - 1] = block;
	}
	// Rotation = 2 Movement =  down
	if ((x->command == 0) && (x->rotation == 2) && (x->S == 0)) {
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top - 1][x->from_left + 1] = empty;
		x->position[x->from_top][x->from_left - 1] = empty;

		x->from_top++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left + 1] = block;
		x->position[x->from_top - 1][x->from_left + 1] = block;
		x->position[x->from_top][x->from_left - 1] = block;
	}
	// Rotation = 3 Movement =  down
	if ((x->command == 0) && (x->rotation == 3) && (x->S == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
		x->from_top++;
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left + 1] = block;
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;
	}
	// Rotation = 3 Movement =  right
	if ((x->command == 2) && (x->rotation == 3) && (x->E != 1)) {
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
		x->from_left++;
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left + 1] = block;
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;
	}
	// Rotation = 3 Movement =  left
	if ((x->command == 1) && (x->rotation == 3) && (x->W != 1)) {
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
		x->from_left--;
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left + 1] = block;
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;
	}









}
void move_L_rotate(piece *x) {
	int i = x->rotation;

	if ((x->command == 3) && (x->rl == 1)) {
		return;
	}
	if ((x->command == 4) && (x->rr == 1)) {
		return;
	}

	if (x->command == 3) {
		x->rotation--;
		if (x->rotation == -1) {
			x->rotation = 3;
		}
	}
	if (x->command == 4) {
		x->rotation++;
		if (x->rotation == 4) {
			x->rotation = 0;
		}
	}


	if (i == 0) { //clear if rotation is 0
				  //erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left + 1] = empty;
		x->position[x->from_top - 1][x->from_left + 2] = empty;
	}
	if (i == 1) { //clear if rotation is 0
				  //erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left - 1] = empty;
	}
	if (i == 2) { //clear if rotation is 0
				  //erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top - 1][x->from_left + 1] = empty;
		x->position[x->from_top][x->from_left - 1] = empty;
	}
	if (i == 3) { //clear if rotation is 0
				  //erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
	}

	//Sets proper rotation so the pieces don't run away!
	if ((i == 0) && (x->rotation == 1)) {
		x->from_left++;
	}
	if ((i == 3) && (x->rotation == 0)) {
		x->from_left--;
	}
	if ((i == 0) && (x->rotation == 3)) {
		x->from_left++;
	}
	if ((i == 1) && (x->rotation == 0)) {
		x->from_left--;
	}
	//

	if (x->rotation == 3) {
		//draw new rotation
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left + 1] = block;
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;
	}
	if (x->rotation == 2) {
		//draw new rotation
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left + 1] = block;
		x->position[x->from_top - 1][x->from_left + 1] = block;
		x->position[x->from_top][x->from_left - 1] = block;
	}
	if (x->rotation == 1) {
		//draw new rotation
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left - 1] = block;
	}
	if (x->rotation == 0) {
		//draw new rotation
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left + 1] = block;
		x->position[x->from_top - 1][x->from_left + 2] = block;
	}



}

//J Piece  type = 5
void collision_J_rotation(piece *x, char board[][bWIDTH]) {
	x->rr = 0;
	x->rl = 0;

	if (x->rotation == 0) {

		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top - 2][x->from_left - 1] != empty) || (board[x->from_top - 2][x->from_left] != empty)) {
			x->rl = 1;
		}
		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top][x->from_left - 2] != empty)) {
			x->rr = 1;
		}
		return;
	}
	if (x->rotation == 1) {

		if ((board[x->from_top - 1][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left + 1] != empty) || (board[x->from_top][x->from_left + 1] != empty)) {
			x->rl = 1;
		}
		if ((board[x->from_top - 1][x->from_left - 1] != empty) || (board[x->from_top][x->from_left + 1] != empty)) {
			x->rr = 1;
		}
		return;
	}
	if (x->rotation == 2) {

		if ((board[x->from_top - 1][x->from_left] != empty) || (board[x->from_top - 2][x->from_left] != empty)) {
			x->rl = 1;
		}
		if ((board[x->from_top - 1][x->from_left] != empty) || (board[x->from_top - 2][x->from_left] != empty) || (board[x->from_top - 2][x->from_left + 1] != empty)) {
			x->rr = 1;
		}
		return;
	}
	if (x->rotation == 3) {

		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty) || (board[x->from_top][x->from_left + 1] != empty)) {
			x->rl = 1;
		}
		if ((board[x->from_top][x->from_left + 1] != empty) || (board[x->from_top - 1][x->from_left + 1] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty)) {
			x->rr = 1;
		}
		return;
	}
}
void collision_J(piece *x, char board[][bWIDTH]) {

	if (x->command == 3) {
		collision_J_rotation(x, board);
		return;
	}
	if (x->command == 4) {
		collision_J_rotation(x, board);
		return;
	}

	////////////////
	////Rotation = 0
	////////////////

	if (x->rotation == 0) {
		if ((board[x->from_top + 1][x->from_left] != empty) || (board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top][x->from_left - 2] != empty)) {// check down
			x->S = 1;
		}
		else {
			x->S = 0;
		}
		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left - 3] != empty)) {// check left
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if ((board[x->from_top][x->from_left + 1] != empty) || (board[x->from_top - 1][x->from_left + 1] != empty)) {// check right
			x->E = 1;
		}
		else {
			x->E = 0;
		}

	}

	////////////////
	////Rotation = 1
	////////////////

	if (x->rotation == 1) {
		if ((board[x->from_top + 1][x->from_left] != empty) || (board[x->from_top + 1][x->from_left - 1] != empty)) {// check down
			x->S = 1;
		}
		else {
			x->S = 0;
		}
		if ((board[x->from_top][x->from_left - 2] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty) || (board[x->from_top - 2][x->from_left - 1] != empty)) {// check left
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if ((board[x->from_top][x->from_left + 1] != empty) || (board[x->from_top - 1][x->from_left + 1] != empty) || (board[x->from_top - 2][x->from_left + 1] != empty)) {// check right
			x->E = 1;
		}
		else {
			x->E = 0;
		}

	}

	////////////////
	////Rotation = 2
	////////////////

	if (x->rotation == 2) {//DOWN
		if ((board[x->from_top + 1][x->from_left] != empty) || (board[x->from_top + 1][x->from_left + 1] != empty) || (board[x->from_top + 1][x->from_left - 1] != empty)) {// check down
			x->S = 1;
		}
		else {
			x->S = 0;
		}
		if ((board[x->from_top][x->from_left - 2] != empty) || (board[x->from_top - 1][x->from_left - 2] != empty)) {// check left
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if ((board[x->from_top][x->from_left + 2] != empty) || (board[x->from_top - 1][x->from_left] != empty)) {// check right
			x->E = 1;
		}
		else {
			x->E = 0;
		}

	}
	////////////////
	////Rotation = 3
	////////////////

	if (x->rotation == 3) {//DOWN
		if ((board[x->from_top + 1][x->from_left] != empty) || (board[x->from_top - 1][x->from_left + 1] != empty)) {// check down
			x->S = 1;
		}
		else {
			x->S = 0;
		}
		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty) || (board[x->from_top - 2][x->from_left - 1] != empty)) {// check left
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if ((board[x->from_top][x->from_left + 1] != empty) || (board[x->from_top - 1][x->from_left + 1] != empty) || (board[x->from_top - 2][x->from_left + 2] != empty)) {// check right
			x->E = 1;
		}
		else {
			x->E = 0;
		}

	}



}
void move_J(piece *x) {

	if ((x->command == 3) || (x->command == 4)) {
		move_J_rotate(x);
		return;
	}

	// Rotation = 0 Movement =  down
	if ((x->command == 0) && (x->rotation == 0) && (x->S == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left - 1] = empty;
		x->position[x->from_top - 1][x->from_left - 2] = empty;

		x->from_top++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left - 1] = block;
		x->position[x->from_top - 1][x->from_left - 2] = block;

	}
	// Rotation = 0 Movement =  right
	if ((x->command == 2) && (x->rotation == 0) && (x->E == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left - 1] = empty;
		x->position[x->from_top - 1][x->from_left - 2] = empty;

		x->from_left++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left - 1] = block;
		x->position[x->from_top - 1][x->from_left - 2] = block;

	}
	// Rotation = 0 Movement =  left
	if ((x->command == 1) && (x->rotation == 0) && (x->W == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left - 1] = empty;
		x->position[x->from_top - 1][x->from_left - 2] = empty;

		x->from_left--;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left - 1] = block;
		x->position[x->from_top - 1][x->from_left - 2] = block;

	}

	////////////////////////

	// Rotation = 1 Movement =  down
	if ((x->command == 0) && (x->rotation == 1) && (x->S == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
		x->from_top++;
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;
	}
	// Rotation = 1 Movement =  right
	if ((x->command == 2) && (x->rotation == 1) && (x->E == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
		x->from_left++;
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;

	}
	// Rotation = 1 Movement =  left
	if ((x->command == 1) && (x->rotation == 1) && (x->W == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
		x->from_left--;
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;

	}

	////////////////////////

	// Rotation = 2 Movement =  down
	if ((x->command == 0) && (x->rotation == 2) && (x->S == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top - 1][x->from_left - 1] = empty;

		x->from_top++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left + 1] = block;
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top - 1][x->from_left - 1] = block;


	}
	// Rotation = 2 Movement =  right
	if ((x->command == 2) && (x->rotation == 2) && (x->E == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top - 1][x->from_left - 1] = empty;

		x->from_left++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left + 1] = block;
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top - 1][x->from_left - 1] = block;


	}
	// Rotation = 2 Movement =  left
	if ((x->command == 1) && (x->rotation == 2) && (x->W == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top - 1][x->from_left - 1] = empty;

		x->from_left--;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left + 1] = block;
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top - 1][x->from_left - 1] = block;


	}


	////////////////////////

	// Rotation = 3 Movement =  down
	if ((x->command == 0) && (x->rotation == 3) && (x->S == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left + 1] = empty;

		x->from_top++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left + 1] = block;


	}
	// Rotation = 3 Movement =  left
	if ((x->command == 1) && (x->rotation == 3) && (x->W == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left + 1] = empty;

		x->from_left--;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left + 1] = block;


	}
	// Rotation = 3 Movement =  right
	if ((x->command == 2) && (x->rotation == 3) && (x->E == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left + 1] = empty;

		x->from_left++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left + 1] = block;


	}

	////////////////////////Loops rotation back to 0


	//This checks if the piece should be set or not, so that it can become apart of the board

	if (x->S == 0) {
		x->setdelay = x->basedelay;
	}

	if (x->S == 1) {
		x->setdelay--;
	}
	if ((x->setdelay == 0) && (x->S == 1)) {
		x->set = 1;
	}


}
void move_J_rotate(piece *x) {
	int i = x->rotation;

	if ((x->command == 3) && (x->rl == 1)) {
		return;
	}
	if ((x->command == 4) && (x->rr == 1)) {
		return;
	}

	if (x->command == 3) {
		x->rotation--;
		if (x->rotation == -1) {
			x->rotation = 3;
		}
	}
	if (x->command == 4) {
		x->rotation++;
		if (x->rotation == 4) {
			x->rotation = 0;
		}
	}

	if (i == 0) { //clear if rotation is 0
				  //erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left - 1] = empty;
		x->position[x->from_top - 1][x->from_left - 2] = empty;
	}
	if (i == 1) { //clear if rotation is 0
				  //erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
	}
	if (i == 2) { //clear if rotation is 0
				  //erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top][x->from_left + 1] = empty;
		x->position[x->from_top][x->from_left - 1] = empty;
		x->position[x->from_top - 1][x->from_left - 1] = empty;
	}
	if (i == 3) { //clear if rotation is 0
				  //erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left] = empty;
		x->position[x->from_top - 2][x->from_left + 1] = empty;
	}

	//Sets proper rotation so the pieces don't run away!
	if ((i == 0) && (x->rotation == 1)) {
		x->from_left--;
	}
	if ((i == 3) && (x->rotation == 0)) {
		x->from_left++;
	}
	if ((i == 0) && (x->rotation == 3)) {
		x->from_left--;
	}
	if ((i == 1) && (x->rotation == 0)) {
		x->from_left++;
	}


	if (x->rotation == 3) {
		//draw new rotation

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left + 1] = block;
	}
	if (x->rotation == 2) {
		//draw new rotation
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left + 1] = block;
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top - 1][x->from_left - 1] = block;
	}
	if (x->rotation == 1) {
		//draw new rotation
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top][x->from_left - 1] = block;
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 2][x->from_left] = block;
	}
	if (x->rotation == 0) {
		//draw new rotation
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left - 1] = block;
		x->position[x->from_top - 1][x->from_left - 2] = block;
	}
}

//Z Piece type = 6
void collision_Z_rotation(piece *x, char board[][bWIDTH]) {
	x->rr = 0;
	x->rl = 0;

	if (x->rotation == 0) {

		if ((board[x->from_top - 1][x->from_left + 1] != empty) || (board[x->from_top - 2][x->from_left + 1] != empty)) {
			x->rl = 1;
			x->rr = 1;
		}
		return;
	}
	if (x->rotation == 1) {

		if ((board[x->from_top - 1][x->from_left - 1] != empty) || (board[x->from_top][x->from_left + 1] != empty)) {
			x->rl = 1;
			x->rr = 1;
		}
		return;
	}
}
void collision_Z(piece *x, char board[][bWIDTH]) {

	if (x->command == 3) {
		collision_Z_rotation(x, board);
		return;
	}
	if (x->command == 4) {
		collision_Z_rotation(x, board);
		return;
	}

	////////////////
	////Rotation = 0
	////////////////

	if (x->rotation == 0) {//DOWN
		if ((board[x->from_top + 1][x->from_left] != empty) || (board[x->from_top + 1][x->from_left + 1] != empty) || (board[x->from_top][x->from_left - 1] != empty)) {// check down
			x->S = 1;
		}
		else {
			x->S = 0;
		}
		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left - 2] != empty)) {// check left
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if ((board[x->from_top][x->from_left + 2] != empty) || (board[x->from_top - 1][x->from_left + 1] != empty)) {// check right
			x->E = 1;
		}
		else {
			x->E = 0;
		}

	}

	////////////////
	////Rotation = 1
	////////////////

	if (x->rotation == 1) {//DOWN
		if ((board[x->from_top + 1][x->from_left] != empty) || (board[x->from_top][x->from_left + 1] != empty)) {// check down
			x->S = 1;
		}
		else {
			x->S = 0;
		}
		if ((board[x->from_top][x->from_left - 1] != empty) || (board[x->from_top - 1][x->from_left - 1] != empty) || (board[x->from_top - 2][x->from_left] != empty)) {// check left
			x->W = 1;
		}
		else {
			x->W = 0;
		}
		if ((board[x->from_top][x->from_left + 1] != empty) || (board[x->from_top - 1][x->from_left + 2] != empty) || (board[x->from_top - 2][x->from_left + 2] != empty)) {// check right
			x->E = 1;
		}
		else {
			x->E = 0;
		}

	}


	//This checks if the piece should be set or not, so that it can become apart of the board

	if (x->S == 0) {
		x->setdelay = x->basedelay;
	}

	if (x->S == 1) {
		x->setdelay--;
	}
	if ((x->setdelay == 0) && (x->S == 1)) {
		x->set = 1;
	}




}
void move_Z(piece *x) {

	if ((x->command == 3) || (x->command == 4)) {
		move_Z_rotate(x);
		return;
	}


	// Rotation = 0 Movement =  down
	if ((x->command == 0) && (x->rotation == 0) && (x->S == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left - 1] = empty;
		x->position[x->from_top][x->from_left + 1] = empty;

		x->from_top++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left - 1] = block;
		x->position[x->from_top][x->from_left + 1] = block;

	}
	// Rotation = 0 Movement =  right
	if ((x->command == 2) && (x->rotation == 0) && (x->E == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left - 1] = empty;
		x->position[x->from_top][x->from_left + 1] = empty;

		x->from_left++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left - 1] = block;
		x->position[x->from_top][x->from_left + 1] = block;

	}
	// Rotation = 0 Movement =  left
	if ((x->command == 1) && (x->rotation == 0) && (x->W == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left - 1] = empty;
		x->position[x->from_top][x->from_left + 1] = empty;

		x->from_left--;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left - 1] = block;
		x->position[x->from_top][x->from_left + 1] = block;
	}

	////////////////////////

	// Rotation = 1 Movement =  down
	if ((x->command == 0) && (x->rotation == 1) && (x->S == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left + 1] = empty;
		x->position[x->from_top - 2][x->from_left + 1] = empty;

		x->from_top++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left + 1] = block;
		x->position[x->from_top - 2][x->from_left + 1] = block;


	}
	// Rotation = 1 Movement =  left
	if ((x->command == 1) && (x->rotation == 1) && (x->W == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left + 1] = empty;
		x->position[x->from_top - 2][x->from_left + 1] = empty;

		x->from_left--;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left + 1] = block;
		x->position[x->from_top - 2][x->from_left + 1] = block;


	}
	// Rotation = 1 Movement =  right
	if ((x->command == 2) && (x->rotation == 1) && (x->E == 0)) {

		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left + 1] = empty;
		x->position[x->from_top - 2][x->from_left + 1] = empty;

		x->from_left++;

		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left + 1] = block;
		x->position[x->from_top - 2][x->from_left + 1] = block;

	}



	//This checks if the piece should be set or not, so that it can become apart of the board

	if (x->S == 0) {
		x->setdelay = x->basedelay;
	}

	if (x->S == 1) {
		x->setdelay--;
	}
	if ((x->setdelay == 0) && (x->S == 1)) {
		x->set = 1;
	}



}
void move_Z_rotate(piece *x) {
	int i = x->rotation;

	if ((x->command == 3) && (x->rl == 1)) {
		return;
	}
	if ((x->command == 4) && (x->rr == 1)) {
		return;
	}

	if (x->command == 3) {
		x->rotation--;
		if (x->rotation == -1) {
			x->rotation = 1;
		}
	}
	if (x->command == 4) {
		x->rotation++;
		if (x->rotation == 2) {
			x->rotation = 0;
		}
	}


	if (i == 0) { //clear if rotation is 0
				  //erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left - 1] = empty;
		x->position[x->from_top][x->from_left + 1] = empty;
	}
	if (i == 1) { //clear if rotation is 0
				  //erase old rotation
		x->position[x->from_top][x->from_left] = empty;//middle block
		x->position[x->from_top - 1][x->from_left] = empty;
		x->position[x->from_top - 1][x->from_left + 1] = empty;
		x->position[x->from_top - 2][x->from_left + 1] = empty;
	}
	if (x->rotation == 1) {
		//draw new rotation
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left + 1] = block;
		x->position[x->from_top - 2][x->from_left + 1] = block;
	}
	if (x->rotation == 0) {
		//draw new rotation
		x->position[x->from_top][x->from_left] = block;//middle block
		x->position[x->from_top - 1][x->from_left] = block;
		x->position[x->from_top - 1][x->from_left - 1] = block;
		x->position[x->from_top][x->from_left + 1] = block;
	}






}
