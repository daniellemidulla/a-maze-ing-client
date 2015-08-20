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
  int x;
  int y;
  for(x= 0; x < num_rows ; x++){
    maze[x] = (MazeNode *)calloc(num_col, sizeof(MazeNode));
    for(y=0; y < num_col; y++){
      MazeNode current_node;
      //set the north and south walls based on x
      if (x == 0){
        current_node.north_wall = 1;
        current_node.south_wall = 0;
      }
      else if(x == r-1){
        current_node.north_wall = 0;
        current_node.south_wall = 1;
      }
      else{
        current_node.north_wall = 0;
        current_node.south_wall = 0;
      }
      //set the east and west walls based on y
      if(y == 0){
        current_node.east_wall = 0;
        current_node.west_wall = 1;
      }
      else if(y == c - 1){
        current_node.east_wall = 1;
        current_node.west_wall = 0;
      }
      else{
        current_node.east_wall = 0;
        current_node.west_wall = 0;
      }
      maze[x][y] = current_node;
    }
  }
  return maze;
}

// XYPos rightHandRule(Avatar avatar){


// }

void CleanupMaze(){
  int x;
  for(x = 0; x < num_rows; x++){
    free(maze[x]);
  }
  free(maze);
}

