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
int getRight(int dir_facing, XYPos current_pos);
int getFront(int dir_facing, XYPos current_pos);
int getLeft(int dir_facing, XYPos current_pos);
int getBack(int dir_facing, XYPos current_pos);

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
      current_node.north_wall = (i == 0) ? 1 : -1;
      current_node.south_wall = (i == r - 1) ? 1 : -1;
      current_node.west_wall = (j == 0) ? 1 : -1;
      current_node.east_wall = (j == c - 1) ? 1 : -1;
      maze[i][j] = current_node;
    }
  }
  return maze;
}

int rightHandRule(Avatar avatar){
  int new_dir;
  new_dir = getRight(avatar.fd, avatar.pos);
  if (new_dir == -1) {
    new_dir = getFront(avatar.fd, avatar.pos);
    if (new_dir == -1) {
      new_dir = getLeft(avatar.fd, avatar.pos);
      if (new_dir == -1) {
        new_dir = getBack(avatar.fd, avatar.pos);
        switch(new_dir){
          case M_NORTH:
            maze[avatar.pos.x][avatar.pos.y].north_wall = 2;
          case M_SOUTH:
            maze[avatar.pos.x][avatar.pos.y].south_wall = 2;
          case M_WEST:
            maze[avatar.pos.x][avatar.pos.y].west_wall = 2;
          case M_EAST:
            maze[avatar.pos.x][avatar.pos.y].east_wall = 2;
          default:
            break;
        }
      }
    }
  }
  return new_dir;
}

void CleanupMaze(){
  int i;
  for(i = 0; i < num_rows; i++){
    free(maze[i]);
  }
  free(maze);
}

int getRight(int dir_facing, XYPos current_pos){
  int x, y, new_dir;
  x = current_pos.x;
  y = current_pos.y;
  switch(dir_facing){
    case M_NORTH:
      new_dir = (maze[x][y].north_wall < 1) ? M_EAST : -1;
      break;
    case M_SOUTH:
      new_dir = (maze[x][y].south_wall < 1) ? M_WEST : -1;
      break;
    case M_WEST:
      new_dir = (maze[x][y].west_wall < 1) ? M_NORTH : -1;
      break;
    case M_EAST:
      new_dir = (maze[x][y].east_wall < 1) ? M_SOUTH : -1;
      break;
    default:
      new_dir = -1;
      break;
  }
  return new_dir;
}

int getFront(int dir_facing, XYPos current_pos){
  int x, y, new_dir;
  x = current_pos.x;
  y = current_pos.y;
  switch(dir_facing){
    case M_NORTH:
      new_dir = (maze[x][y].north_wall < 1) ? M_NORTH : -1;
      break;
    case M_SOUTH:
      new_dir = (maze[x][y].south_wall < 1) ? M_SOUTH : -1;
      break;
    case M_WEST:
      new_dir = (maze[x][y].west_wall < 1) ? M_WEST : -1;
      break;
    case M_EAST:
      new_dir = (maze[x][y].east_wall < 1) ? M_EAST : -1;
      break;
    default:
      new_dir = -1;
      break;
  }
  return new_dir;
}


int getLeft(int dir_facing, XYPos current_pos){
  int x, y, new_dir;
  x = current_pos.x;
  y = current_pos.y;
  switch(dir_facing){
    case M_NORTH:
      new_dir = (maze[x][y].north_wall < 1) ? M_WEST : -1;
      break;
    case M_SOUTH:
      new_dir = (maze[x][y].south_wall < 1) ? M_EAST : -1;
      break;
    case M_WEST:
      new_dir = (maze[x][y].west_wall < 1) ? M_SOUTH : -1;
      break;
    case M_EAST:
      new_dir = (maze[x][y].east_wall < 1) ? M_NORTH : -1;
      break;
    default:
      new_dir = -1;
      break;
  }
  return new_dir;
}

int getBack(int dir_facing, XYPos current_pos){
  int x, y, new_dir;
  x = current_pos.x;
  y = current_pos.y;
  switch(dir_facing){
    case M_NORTH:
      new_dir = (maze[x][y].north_wall < 1) ? M_SOUTH : -1;
      break;
    case M_SOUTH:
      new_dir = (maze[x][y].south_wall < 1) ? M_NORTH : -1;
      break;
    case M_WEST:
      new_dir = (maze[x][y].west_wall < 1) ? M_EAST : -1;
      break;
    case M_EAST:
      new_dir = (maze[x][y].east_wall < 1) ? M_WEST : -1;
      break;
    default:
      new_dir = -1;
      break;
  }
  return new_dir;
}
