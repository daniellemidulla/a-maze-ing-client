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
    int x;
    int y;
    int north_wall;
    int south_wall;
    int east_wall;
    int west_wall;
} MazeNode;

// ---------------- Public Variables

// ---------------- Prototypes/Macros
/* initMaze - returns a 2D pointer array containing the initialized MazeNodes with walls around the outside */
MazeNode** initMaze(int r, int c); //initializes a 2D MazeNode array with r rows and c columns and with enclosing walls

/* rightHandRule - returns the direction that the Avatar should move */
int rightHandRule(Avatar avatar); //examines the avatar and returns the direction in which it should move, following the right hand rule



#endif // MAZE_H