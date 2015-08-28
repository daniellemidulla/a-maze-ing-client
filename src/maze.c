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
#include <stdio.h>          //printf

// ---------------- Local includes  e.g., "file.h"
#include "amazing.h"        //Avatar
#include "maze.h"

// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 
Maze full_maze;

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
Maze* initMaze(int r, int c){
  if (r == 0) return NULL;
  if(c == 0) return NULL;
  if((full_maze.maze != NULL) && (full_maze.maze[0] != NULL)) return &full_maze;
  full_maze.num_row = r;
  full_maze.num_col = c;
  full_maze.maze = calloc(full_maze.num_row, sizeof(MazeNode *)); //(MazeNode **) 
  int i;
  int j;
  for(i= 0; i < full_maze.num_row ; i++){
    full_maze.maze[i] = (MazeNode *)calloc(full_maze.num_col, sizeof(MazeNode));
    for(j=0; j < full_maze.num_col; j++){
      MazeNode current_node;
      current_node.row = i;
      current_node.col = j;
      current_node.north_wall = (i == 0) ? 1 : -1;
      current_node.south_wall = (i == r - 1) ? 1 : -1;
      current_node.west_wall = (j == 0) ? 1 : -1;
      current_node.east_wall = (j == c - 1) ? 1 : -1;
      full_maze.maze[i][j] = current_node;
    }
  }
  return &full_maze;
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
  //MazeNode * current_node = &full_maze.maze[avatar.pos.y][avatar.pos.x];
  //printf("\nin rightHandRule: avatar %d: pos: x: %d, y: %d, direction: %d\n\tmaze: north_wall: %d, south_wall: %d, west_wall: %d, east_wall: %d\n", avatar.id, avatar.pos.x, avatar.pos.y, avatar.direction, current_node->north_wall, current_node->south_wall, current_node->west_wall, current_node->east_wall);
  if((avatar.pos.x >= full_maze.num_col) || (avatar.pos.y >= full_maze.num_row) || (avatar.direction < 0)){
    return -1;
  }

  int new_dir;
  new_dir = isDeadEnd(avatar.pos);
  if(new_dir == -1){
    //printf("not a dead end!");
    new_dir = getRight(avatar.direction, avatar.pos);
    if (new_dir == -1) {
      //printf("cannot go right");
      new_dir = getFront(avatar.direction, avatar.pos);
      if (new_dir == -1) {
        //printf("cannot go forward!");
        new_dir = getLeft(avatar.direction, avatar.pos);
        if (new_dir == -1) {
          //printf("cannot go left!");
          new_dir = getBack(avatar.direction, avatar.pos);
          if(new_dir != -1){
            AddWall(avatar.pos.y, avatar.pos.x, new_dir, 2);
          }
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
  if(!full_maze.maze) return;
  int i;
  for(i = 0; i < full_maze.num_row; i++){
    free(full_maze.maze[i]);
  }
  free(full_maze.maze);
  full_maze.maze = NULL;
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
  int new_dir;
  MazeNode current_node;
  current_node = full_maze.maze[current_pos.y][current_pos.x]; //get the node at row y, column x
  switch(dir_facing){
    case M_NORTH:
      new_dir = (current_node.east_wall < 1) ? M_EAST : -1;
      break;
    case M_SOUTH:
      new_dir = (current_node.west_wall < 1) ? M_WEST : -1;
      break;
    case M_WEST:
      new_dir = (current_node.north_wall < 1) ? M_NORTH : -1;
      break;
    case M_EAST:
      new_dir = (current_node.south_wall < 1) ? M_SOUTH : -1;
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
  int new_dir;
  MazeNode current_node;
  current_node = full_maze.maze[current_pos.y][current_pos.x]; //get the node at row y, column x
  switch(dir_facing){
    case M_NORTH:
      new_dir = (current_node.north_wall < 1) ? M_NORTH : -1;
      break;
    case M_SOUTH:
      new_dir = (current_node.south_wall < 1) ? M_SOUTH : -1;
      break;
    case M_WEST:
      new_dir = (current_node.west_wall < 1) ? M_WEST : -1;
      break;
    case M_EAST:
      new_dir = (current_node.east_wall < 1) ? M_EAST : -1;
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
  int new_dir;
  MazeNode current_node;
  current_node = full_maze.maze[current_pos.y][current_pos.x]; //get the node at row y, column x

  switch(dir_facing){
    case M_NORTH:
      new_dir = (current_node.west_wall < 1) ? M_WEST : -1;
      break;
    case M_SOUTH:
      new_dir = (current_node.east_wall < 1) ? M_EAST : -1;
      break;
    case M_WEST:
      new_dir = (current_node.south_wall < 1) ? M_SOUTH : -1;
      break;
    case M_EAST:
      new_dir = (current_node.north_wall < 1) ? M_NORTH : -1;
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
  int new_dir;
  MazeNode current_node;
  current_node = full_maze.maze[current_pos.y][current_pos.x]; //get the node at row y, column x

  switch(dir_facing){
    case M_NORTH:
      new_dir = (current_node.south_wall < 1) ? M_SOUTH : -1;
      break;
    case M_SOUTH:
      new_dir = (current_node.north_wall < 1) ? M_NORTH : -1;
      break;
    case M_WEST:
      new_dir = (current_node.east_wall < 1) ? M_EAST : -1;
      break;
    case M_EAST:
      new_dir = (current_node.west_wall < 1) ? M_WEST : -1;
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
  current_node = full_maze.maze[current_pos.y][current_pos.x]; //get maze node at row y, column x
  wall_count = 0;

  if (current_node.north_wall < 1) new_dir = M_NORTH;
  else wall_count++;

  if (current_node.south_wall < 1) new_dir = M_SOUTH;
  else wall_count++;

  if (current_node.west_wall < 1) new_dir = M_WEST;
  else wall_count++;

  if (current_node.east_wall < 1) new_dir = M_EAST;
  else wall_count++;

  if (wall_count == 3){ //if there are 3 walls
    AddWall(current_pos.y, current_pos.x, new_dir, 2); //add a fake wall at row y, column x
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
  if((r < 0) || (c < 0) || (r >= full_maze.num_row) || (c >= full_maze.num_col)) return;
  MazeNode *current_node;
  MazeNode *adjacent_node;
  current_node = &full_maze.maze[r][c];
  if (dir == M_NORTH){
    if (r > 0){ //if we aren't in the top row, update the north wall and the adjacent south wall
      current_node->north_wall = value;
      adjacent_node = &full_maze.maze[r-1][c];
      adjacent_node->south_wall = value;
    }
  }
  else if (dir == M_WEST){
    if (c > 0){ //if we aren't in the 0th column, update the west wall and the adjacent east wall
      current_node->west_wall = value;
      adjacent_node = &full_maze.maze[r][c-1];
      adjacent_node->east_wall = value;
    }
  }
  else if (dir == M_EAST){
    if (c < full_maze.num_col-1){ //if we aren't in the last column, update the east wall and the adjacent west wall
      current_node->east_wall = value;
      adjacent_node = &full_maze.maze[r][c+1];
      adjacent_node->west_wall = value;

    }
  }
  else if (dir == M_SOUTH){
    if (r < full_maze.num_row-1){ //if we aren't in the bottom row, update the south wall and the adjacent north wall
      current_node->south_wall = value;
      adjacent_node = &full_maze.maze[r+1][c];
      adjacent_node->north_wall = value;
    }
  }
}
