/*  graphics.c
 *
 *
 *    Project name: Amazing Project
 *      Component name:  graphics
 *
 *        Prints ascii representation of maze and avatars
 *
 *          Primary Author: James Jia
 *            Date Created: Aug 2015
 *
 *              Special considerations:
 *                  (e.g., special compilation options, platform limitations, etc.)
 *
 *                  ======================================================================*/

// // ---------------- Open Issues
//
// // ---------------- System includes e.g., <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
// ---------------- Local includes  e.g., "file.h"
#include "amazing.h"
#include "maze.h"

//function prototypes
void create_border(int w, int h);
void draw_avatars(Avatar** avatar_list);

// ---------------- Constant definitions
//
// // ---------------- Macro definitions
//
// // ---------------- Structures/Types



//main for testing movement
int main (int argc, char *argv[]){
		
	int h=20;
	int w=20;
	int avatar_x = 1;
	int avatar_y = 10;

	while(avatar_x<2*w+1){

		clear();	
		initscr();
		raw();
		
		//make outside walls
		create_border(w,h);

		move(avatar_y, avatar_x);
		addch('*');
		avatar_x = avatar_x +1;

		refresh();	
		getch();
		endwin();
		}
	
	return 0;
}

void create_border(int w, int h){
		//top		
		int i;
		move(0,0);
                for (i=0;i<(2*w+1);i++){
                        addch('-');
                }

		//bottom
                move(2*h+1, 0);
                for (i=0; i<2*w+1; i++){
                        addch('-');
                }

		//left
                for (i=1;i<2*h+1;i++){
                        move(i,0);
                        addch('|');
                }

		//right
                for (i=1;i<2*h+1;i++){
                        move(i, 2*w+1);
                        addch('|');
                }
}

void draw_avatars(Avatar** avatar_list){
	
	int i=0;
	int avatar_x;
	int avatar_y;

	while(i<4){
		avatar_x = avatar_list[i]->pos.x;
		avatar_y = avatar_list[i]->pos.y;
		move(avatar_y, avatar_x);
		addch('*');
	}
}



	  
