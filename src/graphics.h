
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
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "amazing.h"
#include "maze.h"

// ---------------- Constants

// ---------------- Structures/Types

// ---------------- Public variables
int print_fake;

// ---------------- Prototypes/Macros
// draws maze border
void create_border(int w, int h);
// draws avatar
void draw_avatar(int x, int y);
// draws maze inner walls
void draw_inside(Maze* maze_list);
// draws maze fake walls
void draw_fakes(Maze* maze_list);



#endif //GRAPHICS_H
