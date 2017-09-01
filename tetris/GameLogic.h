//Author: Kevin Wilkinson
//Email: Willkillson@gmail.com

////HOTKEY INSTRUCTIONS FOR VISUAL STUDIO 15
////CTRL + K + U will uncomment selection.
////CTRL + K + C will comment selection
////CTRL + M + O will collapse all.
////CTRL + M + L will expand all. (in VS 2013 - Toggle All outlining)
////CTRL + M + P will expand all and disable outlining.
////CTRL + M + M will collapse / expand the current section.

#ifndef _GAMELOGIC_H
#define _GAMELOGIC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <windows.h>

#define bHEIGHT 26
#define bWIDTH 12

#define boarder '*'
#define empty ' '
#define block 'X'

typedef struct {
	int test1;
	int test2;

	int N;//prevent up movement
	int S;//prevent down movement
	int E;//prevent right movement
	int W;//prevent left movement
	int rr; //prevent rotate right if rotate right is blocked
	int rl; //prevent rotate left if rotate left is blocked

	int setdelay;
	int basedelay;
	int set;// setting a piece will then copy the array position into the array of the board
	int from_left;//x position to calculate bounds of a block
	int from_top;//y position to calculate bounds of a block
	int rotation;//Left and right 
	char type;//I,Q,S,Z,L,J,T
	int command;//0 move down 1 move left 2 move right 3 rotate left 4 rotate right 5 instant drop
	char position[bHEIGHT][bWIDTH];// position in board, but not the board

}piece;


void clearScreen();
void print_board(char board[bHEIGHT][bWIDTH], piece *x, int *score, int time, int line[bHEIGHT]);
void shift_stack(char board[][bWIDTH], int line[bHEIGHT]);
void score_board(char board[bHEIGHT][bWIDTH], piece *x, int *score, int line[bHEIGHT]);
void place_piece(char board[][bWIDTH], piece *x);
void test();
void command(piece *x);
void music();

void master_collision(piece *x, char board[][bWIDTH]);
void collision_I_rotation(piece *x, char board[][bWIDTH]);
void collision_S_rotation(piece *x, char board[][bWIDTH]);
void collision_Z_rotation(piece *x, char board[][bWIDTH]);
void collision_L_rotation(piece *x, char board[][bWIDTH]);
void collision_J_rotation(piece *x, char board[][bWIDTH]);
void collision_T_rotation(piece *x, char board[][bWIDTH]);
void collision_I(piece *x, char board[][bWIDTH]);
void collision_Q(piece *x, char board[][bWIDTH]);
void collision_S(piece *x, char board[][bWIDTH]);
void collision_Z(piece *x, char board[][bWIDTH]);
void collision_L(piece *x, char board[][bWIDTH]);
void collision_J(piece *x, char board[][bWIDTH]);
void collision_T(piece *x, char board[][bWIDTH]);

void move_I_rotate_right(piece *x);
void move_S_rotate_right(piece *x);
void move_Z_rotate(piece *x);
void move_T_rotate(piece *x);
void move_J_rotate(piece *x);
void move_L_rotate(piece *x);

void master_move(piece *x, char board[][bWIDTH]);
void move_I(piece *x);
void move_S(piece *x);
void move_Z(piece *x);
void move_Q(piece *x);
void move_L(piece *x);
void move_J(piece *x);
void move_T(piece *x);


#endif