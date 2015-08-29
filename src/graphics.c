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
#include "graphics.h"

//function prototypes

// ---------------- Constant definitions
//
// // ---------------- Macro definitions
//
// // ---------------- Structures/Types

//draw outside border in green
void create_border(int w, int h){
		
		//initialize green
		init_pair(1, COLOR_GREEN, COLOR_BLACK);
		attron(COLOR_PAIR(1));

		//top		
		int i;
		move(0,0);
                for (i=0;i<(2*w);i++){
                  if(i%2 == 0) addch('*');
                  else addch('-');
                }
		//bottom
                move(2*h, 0);
                for (i=0; i<2*w; i++){
                  if(i%2 == 0) addch('*');
                  else addch('-');
                }
		//left
                for (i=1;i<2*h;i++){               
                  if(i%2 == 0) mvaddch(i, 0, '*');
			            else mvaddch(i,0,'|');
                }
		//right
                for (i=1;i<2*h-1;i++){
               		if (i%2 == 0) mvaddch(i, 2*w, '*');
                  else mvaddch(i,2*w,'|');
                }
		//turn off green
		attroff(COLOR_PAIR(1));

}
//draws avatars given their coordinates
void draw_avatar(int avatar_y, int avatar_x){
	
	init_pair(3, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(3));	
	mvaddch(avatar_y,avatar_x, 'A');
	attroff(COLOR_PAIR(3));

}
//given a list of mazenodes, draw the inner walls of the maze
void draw_inside(Maze* maze_list){
	
	int i;
	int j;
	//draw walls as green
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
				//southeast corner
				if (maze_list->maze[i][j].south_wall==1){	
					move(2*(i+1), 2*(j+1));		
					addch('*');
				}
				//northeast corner
				if (maze_list->maze[i][j].north_wall==1){		
                                        move(2*i, 2*(j+1));
                                        addch('*');
				}
			}
			//if the node has a south wall		
			if (maze_list->maze[i][j].south_wall==1){
					//make south wall   			
          				move(2*(i+1), 2*j+1);
					addch('-');
				//southwest corner
				if (maze_list->maze[i][j].west_wall==1){	
					move(2*(i+1),2*j);
					addch('*');	
	
				}
			}
			
			//if node has west wall, draw northwest if also has north wall	
			if (maze_list->maze[i][j].west_wall == 1){
				if (maze_list->maze[i][j].north_wall == 1){
					move(2*i ,2*j);
					addch('*');
				}
			}			
		}
	}
	attroff(COLOR_PAIR(2));
  if(print_fake == 1){
    draw_fakes(maze_list);
  }
}

//look through maze nodes and draw fake walls as magenta
void draw_fakes(Maze* maze_list){

        int i;
        int j;
	//initialize magenta
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
        attron(COLOR_PAIR(5));
	//iterate through all nodes, looking for fake walls marked as 2
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
	//turn off magenta
        attroff(COLOR_PAIR(5));
}
