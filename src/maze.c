/*  maze.c


  Project name: Maze Project
  Component name:  Maze Component

  This file contains client side startup to communiate with server
  
  Primary Author: Danielle Midulla
  Date Created: Aug 2015

  Special considerations:  
    (e.g., special compilation options, platform limitations, etc.) 
  
======================================================================*/

// do not remove any of these sections, even if they are empty
//
// ---------------- Open Issues 

// ---------------- System includes e.g., <stdio.h>
#include <stdlib.h>         //calloc

// ---------------- Local includes  e.g., "file.h"
#include "amazing.h"        //Avatar
#include "maze.h"

// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 
MazeNode ** maze;
int num_rows;
int num_col;

// ---------------- Private prototypes 


/*====================================================================*/
MazeNode** initMaze(int r, int c){
  if (r == 0) return NULL;
  if(c == 0) return NULL;
  num_rows = r;
  num_col = c;
  maze = calloc(num_rows, sizeof(MazeNode *)); //(MazeNode **) 
  int i;
  int j;
  for(i= 0; i < num_rows ; i++){
    maze[i] = (MazeNode *)calloc(num_col, sizeof(MazeNode));
    for(j=0; j < num_col; j++){
      MazeNode current_node;
      current_node.x = i;
      current_node.y = j;
      current_node.north_wall = (i == 0) ? 1 : 0;
      current_node.south_wall = (i == r - 1) ? 1 : 0;
      current_node.west_wall = (j == 0) ? 1 : 0;
      current_node.east_wall = (j == c - 1) ? 1 : 0;
      
      // //set the east and west walls based on j
      // if(j == 0){
      //   current_node.west_wall = 1;
      // }
      // if(j == c - 1){
      //   current_node.east_wall = 1;
      // }
      maze[i][j] = current_node;
    }
  }
  return maze;
}

// XYPos rightHandRule(Avatar avatar){


// }

void CleanupMaze(){
  int i;
  for(i = 0; i < num_rows; i++){
    free(maze[i]);
  }
  free(maze);
}

