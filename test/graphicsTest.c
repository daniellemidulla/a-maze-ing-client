/* graphicsTest.c
 *
 * project name: Amazing Project
 *      Component name:  graphics
 *       *
 *        *        Unit testing for graphics
 *         *
 *          *          Primary Author: James Jia
 *           *            Date Created: Aug 2015
 *            *
 *             *              Special considerations:
 *              *                  (e.g., special compilation options, platform limitations, etc.)
 *               *
 *                *                  ======================================================================*/

// // ---------------- Open Issues
// //
// // // ---------------- System includes e.g., <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

// ---------------- Local includes  e.g., "file.h"
#include "../src/amazing.h"
#include "../src/maze.c"
#include "../src/graphics.c"

Avatar* init_random_av();

int main (int argc, char *argv[]){

        int h=20;
        int w=20;
	int max=4;
	int count;

	Avatar **avatar_list = (Avatar **) calloc(1, sizeof(Avatar));
	Maze *maze = initMaze(h, w);
	for (count=0; count<max; count++){
		Avatar *avatar = init_random_av();
		avatar_list[count] = avatar;
		/*
		printf("avatar x: %d\n", avatar->pos.x);
		printf("avatar y: %d\n", avatar->pos.x);
		printf("avatar_list[0] x:%d y:%d",avatar_list[0]->pos.x, avatar_list[0]->pos.y);
		*/

	}
	
        clear();
        initscr();
        raw();
        create_border(w,h);
	draw_avatars(avatar_list, max);
	draw_inside(maze);
        refresh();
        getch();
        endwin();
                
        return 0;
}

Avatar* init_random_av(){

	int rand_x = (rand() % 20)*2;
	int rand_y = (rand() % 20)*2;
	Avatar *cur_avatar = (Avatar*)malloc(sizeof(Avatar));
        cur_avatar->fd=1;
        cur_avatar->pos.x = rand_x;
        cur_avatar->pos.y = rand_y;
	return cur_avatar;
}




		

