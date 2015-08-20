/*	maze.c


	Project name: Maze Project
	Component name:  Maze Component

	This file contains client side startup to communiate with server
	
	Primary Author:	Danielle Midulla
	Date Created:	Aug 2015

	Special considerations:  
		(e.g., special compilation options, platform limitations, etc.) 
	
======================================================================*/

// do not remove any of these sections, even if they are empty
//
// ---------------- Open Issues 

// ---------------- System includes e.g., <stdio.h>
#include <stdlib.h>		//calloc

// ---------------- Local includes  e.g., "file.h"

#include "amazing.h"
#include "maze.h"

// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 
MazeNode ** maze;

// ---------------- Private prototypes 


/*====================================================================*/
MazeNode** initMaze(int r, int c){
	maze = calloc(r, sizeof(MazeNode *)); //(MazeNode **) 
	int x;
	int y;
	for(x= 0; x < r ; x++){
		maze[x] = (MazeNode *)calloc(c, sizeof(MazeNode));
		for(y=0; y < c; y++){
			//set the north and south walls based on x
			if (x == 0){
				maze[x][y].north_wall = 1;
				maze[x][y].south_wall = 0;
			}
			else if(x == r-1){
				maze[x][y].north_wall = 0;
				maze[x][y].south_wall = 1;
			}
			else{
				maze[x][y].north_wall = 0;
				maze[x][y].south_wall = 0;
			}
			//set the east and west walls based on y
			if(y == 0){
				maze[x][y].east_wall = 0;
				maze[x][y].west_wall = 1;
			}
			else if(y == c - 1){
				maze[x][y].east_wall = 1;
				maze[x][y].west_wall = 0;
			}
			else{
				maze[x][y].east_wall = 0;
				maze[x][y].west_wall = 0;
			}
		}
	}
	return maze;
}

// XYPos rightHandRule(Avatar avatar){

	
// }
