#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>




int main (int argc, char *argv[]){
		
	int h=20;
	int w=20;
	int i;
	int avatar_x = 1;
	int avatar_y = 10;

	while(avatar_x<2*w+1){

		clear();	
		initscr();
		raw();
	
		//top
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

		move(avatar_y, avatar_x);
		addch('*');
		avatar_x = avatar_x +1;

		refresh();	
		getch();
		endwin();
		}
	
	return 0;
}

