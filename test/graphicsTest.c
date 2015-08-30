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
		
        clear();
        initscr();
        raw();
        create_border(20,20);


        refresh();
        getch();
        endwin();
                
        return 0;
}















		

