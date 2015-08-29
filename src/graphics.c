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

// ---------------- Constant definitions
//
// // ---------------- Macro definitions
//
// // ---------------- Structures/Types


/*
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
*/

void create_border(int w, int h){

		init_pair(1, COLOR_GREEN, COLOR_BLACK);
		attron(COLOR_PAIR(1));
		//top		
		int i;
		move(0,0);
                for (i=0;i<(2*w);i++){
                        addch('-');
                }

		//bottom
                move(2*h, 0);
                for (i=0; i<2*w; i++){
                        addch('-');
                }

		//left
                for (i=1;i<2*h;i++){
                        move(i,0);
                        addch('|');
                }

		//right
                for (i=1;i<2*h-1;i++){
                        move(i, 2*w);
                        addch('|');
                }
		attroff(COLOR_PAIR(1));

}

void draw_avatar(int avatar_y, int avatar_x){
	
	init_pair(3, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(3));	
	move(avatar_y, avatar_x);
	addch('A');
	attroff(COLOR_PAIR(3));

}

void draw_inside(Maze* maze_list){
	
	int i;
	int j;
	
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
        attron(COLOR_PAIR(2));
	
	//loop through all the maze nodes
	for (i=0; i<maze_list->num_row; i++){
		for (j=0; j<maze_list->num_col; j++){

			//if the node has an east wall and south wall
			if (maze_list->maze[i][j].east_wall == 1){
				//make east wall
				move(2*i+1, 2*(j+1));
				addch('|');

				if (maze_list->maze[i][j].south_wall==1){
					//make south wall
					move(2*(i+1),2*j+1); 
					addch('-');
					//make corner
					move(2*(i+1), 2*(j+1));
					addch('*');
				}
			}
			//if the node has just a south wall
			if (maze_list->maze[i][j].east_wall !=1){
				if (maze_list->maze[i][j].south_wall==1){
					//make south wall
					move(2*(i+1), 2*j+1);
					addch('-');
				
				}
			}
		}
	}
	attroff(COLOR_PAIR(2));
}

void draw_fakes(Maze* maze_list){

        int i;
        int j;

        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
        attron(COLOR_PAIR(5));


        for (i=0; i<maze_list->num_row; i++){
                for (j=0; j<maze_list->num_col; j++){
			//east
                        if (maze_list->maze[i][j].east_wall == 2){ 
                                move(2*i+1, 2*(j+1));
                                addch('|');
		                           
                        }                        
			//south
                        if (maze_list->maze[i][j].east_wall !=2){
                                if (maze_list->maze[i][j].south_wall==2){                                
                                        move(2*(i+1), 2*j+1);
                                        addch('-');
                                }
                        }
                }
        }
        attroff(COLOR_PAIR(5));
}
