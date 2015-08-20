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

// ---------------- Constants

// ---------------- Structures/Types
typedef struct MazeNode {
    int x;
    int y;
    int north_wall;
    int south_wall;
    int east_wall;
    int west_wall;
} WordNode;

// ---------------- Public Variables

// ---------------- Prototypes/Macros
MazeNode[][] initMaze(int r, int c);
XYPos rightHandRule(Avatar avatar);



#endif // MAZE_H
