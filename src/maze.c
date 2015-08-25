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
/* getRight - returns the direction "right" of the avatar" */
int getRight(int dir_facing, XYPos current_pos);  //gets the direction to the right of the avatar

/* getFront - returns the direction "front" of the avatar" */
int getFront(int dir_facing, XYPos current_pos);  //gets the direction in front of the avatar

/* getLeft - returns the direction "left" of the avatar" */
int getLeft(int dir_facing, XYPos current_pos);   //gets the direction to the left of the avatar

/* getBack - returns the direction "back" of the avatar" */
int getBack(int dir_facing, XYPos current_pos);   //gets the direction behind the avatar

/* isDeadEnd - returns the direction to move to escape the dead end or -1 (if not a dead end) */
int isDeadEnd(XYPos current_pos);                 //checks if current position is a dead end and returns the direction to escape

/*====================================================================*/

/* MazeNode** initMaze(int r, int c);
 *
 * Description: initializes a 2D MazeNode array with r rows and c columns and with enclosing walls
 * 
 * Input:
 *  - r => the desired number of rows for the maze
 *  - c => the desired number of columns for the maze
 * 
 * Output: a 2D pointer array containing the initialized MazeNodes with walls around the outside
 *
 */
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
      current_node.row = i;
      current_node.col = j;
      current_node.north_wall = (i == 0) ? 1 : -1;
      current_node.south_wall = (i == r - 1) ? 1 : -1;
      current_node.west_wall = (j == 0) ? 1 : -1;
      current_node.east_wall = (j == c - 1) ? 1 : -1;
      maze[i][j] = current_node;
    }
  }
  return maze;
}

/* int rightHandRule(Avatar avatar); 
 *
 * Description: examines the avatar and returns the direction in which it should move, following the right hand rule
 *
 * Input: the Avatar for which we would like to get a direction
 *
 * Output: the direction that the Avatar should move
 *
 */
int rightHandRule(Avatar avatar){
  int new_dir;
  new_dir = isDeadEnd(avatar.pos);
  if(new_dir != -1){
    return new_dir;
  }
  
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


/* void CleanupMaze();
 *
 * Description: frees all the memory associated with the maze
 *
 * Input: none
 *
 * Output: none
 *
 */
void CleanupMaze(){
  int i;
  for(i = 0; i < num_rows; i++){
    free(maze[i]);
  }
  free(maze);
}

/* int getRight(int dir_facing, XYPos current_pos);
 *
 * Description: checks the current position and gets the direction to the right of the avatar if there is no wall
 * 
 * Input:
 *  - dir_facing => the direction that the avatar is currently facing
 *  - current_pos => the current position of the avatar
 * 
 * Output: The direction "right" of the avatar" or -1 (if there is a wall)
 *
 */
int getRight(int dir_facing, XYPos current_pos){
  int x, y, new_dir;
  x = current_pos.x;
  y = current_pos.y;
  switch(dir_facing){
    case M_NORTH:
      new_dir = (maze[x][y].east_wall < 1) ? M_EAST : -1;
      break;
    case M_SOUTH:
      new_dir = (maze[x][y].west_wall < 1) ? M_WEST : -1;
      break;
    case M_WEST:
      new_dir = (maze[x][y].north_wall < 1) ? M_NORTH : -1;
      break;
    case M_EAST:
      new_dir = (maze[x][y].south_wall < 1) ? M_SOUTH : -1;
      break;
    default:
      new_dir = -1;
      break;
  }
  return new_dir;
}

/* int getFront(int dir_facing, XYPos current_pos);
 *
 * Description: checks the current position and gets the direction in front of the avatar if there is no wall
 * 
 * Input:
 *  - dir_facing => the direction that the avatar is currently facing
 *  - current_pos => the current position of the avatar
 * 
 * Output: The direction in front of the avatar" or -1 (if there is a wall)
 *
 */
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

/* int getLeft(int dir_facing, XYPos current_pos);
 *
 * Description: checks the current position and gets the direction to the left of the avatar if there is no wall
 * 
 * Input:
 *  - dir_facing => the direction that the avatar is currently facing
 *  - current_pos => the current position of the avatar
 * 
 * Output: The direction "left" of the avatar" or -1 (if there is a wall)
 *
 */
int getLeft(int dir_facing, XYPos current_pos){
  int x, y, new_dir;
  x = current_pos.x;
  y = current_pos.y;
  switch(dir_facing){
    case M_NORTH:
      new_dir = (maze[x][y].west_wall < 1) ? M_WEST : -1;
      break;
    case M_SOUTH:
      new_dir = (maze[x][y].east_wall < 1) ? M_EAST : -1;
      break;
    case M_WEST:
      new_dir = (maze[x][y].south_wall < 1) ? M_SOUTH : -1;
      break;
    case M_EAST:
      new_dir = (maze[x][y].north_wall < 1) ? M_NORTH : -1;
      break;
    default:
      new_dir = -1;
      break;
  }
  return new_dir;
}

/* int getBack(int dir_facing, XYPos current_pos);
 *
 * Description: checks the current position and gets the direction behind of the avatar if there is no wall
 * 
 * Input:
 *  - dir_facing => the direction that the avatar is currently facing
 *  - current_pos => the current position of the avatar
 * 
 * Output: The direction behind the avatar" or -1 (if there is a wall)
 *
 */
int getBack(int dir_facing, XYPos current_pos){
  int x, y, new_dir;
  x = current_pos.x;
  y = current_pos.y;
  switch(dir_facing){
    case M_NORTH:
      new_dir = (maze[x][y].south_wall < 1) ? M_SOUTH : -1;
      break;
    case M_SOUTH:
      new_dir = (maze[x][y].north_wall < 1) ? M_NORTH : -1;
      break;
    case M_WEST:
      new_dir = (maze[x][y].east_wall < 1) ? M_EAST : -1;
      break;
    case M_EAST:
      new_dir = (maze[x][y].west_wall < 1) ? M_WEST : -1;
      break;
    default:
      new_dir = -1;
      break;
  }
  return new_dir;
}

/* int isDeadEnd(XYPos current_pos);
 *
 * Description: checks if current position is a dead end and returns the direction to escape AND adds a "fake" wall to close off the dead end
 * 
 * Input: the position we would like to check
 * 
 * Output: The direction to move to escape the dead end.
 *          If the current position is not a dead end, returns -1
 *
 */
int isDeadEnd(XYPos current_pos){
  int new_dir;
  int wall_count;
  MazeNode current_node;
  current_node = maze[current_pos.x][current_pos.y];
  wall_count = 0;

  if (current_node.north_wall < 1) new_dir = M_NORTH;
  else wall_count++;

  if (current_node.south_wall < 1) new_dir = M_SOUTH;
  else wall_count++;

  if (current_node.west_wall < 1) new_dir = M_WEST;
  else wall_count++;

  if (current_node.east_wall < 1) new_dir = M_EAST;
  else wall_count++;

  if (wall_count == 3){
    AddWall(current_pos.x, current_pos.y, new_dir, 2);
    return new_dir;
  }
  return -1;
}

/*
 * void AddWall(int r, int c, int dir, int value);
 *
 * Description: adds a wall to the given cell and the adjacent cell
 *
 * Input:
 *  - r => the row of the MazeNode to which we are adding the wall
 *  - c => the column of the MazeNode to which we are adding the wall
 *  - dir => the direction of the wall we are adding in the MazeNode (as well as the direction of the relevant adjacent MazeNode)
 *
 * Output: none
 *
 */
void AddWall(int r, int c, int dir, int value){
  MazeNode current_node;
  MazeNode adjacent_node;
  current_node = maze[r][c];
  if (dir == M_NORTH){
    current_node.north_wall = value;
    if (r > 0){
      adjacent_node = maze[r-1][c];
      adjacent_node.south_wall = value;
    }
  }
  else if (dir == M_WEST){
    current_node.west_wall = value;
    if (c > 0){
      adjacent_node = maze[r][c-1];
      adjacent_node.east_wall = value;
    }
  }
  else if (dir == M_EAST){
    current_node.east_wall = value;
    if (c < num_col-1){
      adjacent_node = maze[r][c-1];
      adjacent_node.west_wall = value;

    }
  }
  else if (dir == M_SOUTH){
    current_node.south_wall = value;
    if (r < num_rows-1){
      adjacent_node = maze[r+1][c];
      adjacent_node.north_wall = value;
    }
  }
}
