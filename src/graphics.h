
/* File: graphics.h
 *  *
 *   * Project name: A maze Project
 *    * Component name: Maze Component
 *     *
 *      * Description:
 *       *
 *
 * 
 */
#ifndef GRAPHICS_H
#define GRAPHICS_H
// ---------------- Prerequisites e.g., Requires "math.h"
#include "amazing.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "maze.h"

// ---------------- Constants
//
// ---------------- Structures/Types
//
// ---------------- Prototypes/Macros
void create_border(int w, int h);

void draw_avatar(int x, int y);

void draw_inside(Maze* maze_list);

void draw_fakes(Maze* maze_list);

#endif //GRAPHICS_H
