/* ========================================================================== */
/* File: maze.h
 *
 * Project name: Maze Project
 * Component name: Maze Component
 *
 * Description:
 *
 */
/* ========================================================================== */
#ifndef MAZE_H
#define MAZE_H

// ---------------- Prerequisites e.g., Requires "math.h"
#include "amazing.h"

// ---------------- Constants

// ---------------- Structures/Types
typedef struct MazeNode {
    int row;  //the row of the MazeNode
    int col;  //the column of the MazeNode
    //walls have the following values: -1 for unknown, 0 for no wall, 1 for a real wall, 2 for an assumed wall(a dead end)
    int north_wall;
    int south_wall;
    int east_wall;
    int west_wall;
} MazeNode;

typedef struct Maze{
  MazeNode** maze;
  int num_row;
  int num_col;
} Maze;

// ---------------- Public Variables

// ---------------- Prototypes/Macros
/* initMaze - returns a 2D pointer array containing the initialized MazeNodes with walls around the outside */
Maze* initMaze(int r, int c); //initializes a 2D MazeNode array with r rows and c columns and with enclosing walls

/* rightHandRule - returns the direction that the Avatar should move */
int rightHandRule(Avatar avatar); //examines the avatar and returns the direction in which it should move, following the right hand rule

/* CleanupMaze */
void CleanupMaze();//frees all the memory associated with the maze

/* AddWall */
void AddWall(int r, int c, int dir, int value); //adds a wall to the given cell and the adjacent cell

#endif // MAZE_H
