/* ========================================================================== */
/* File: list.h
 *
 * Project name: Maze Project
 * Component name: Linked List Component
 *
 * Description: This file contains the functions for a linked list using the FIFO stack rules.
 *
 */
/* ========================================================================== */
#ifndef LIST_H
#define LIST_H

// ---------------- Prerequisites e.g., Requires "math.h"
#include "amazing.h"
#include "maze.h"

// ---------------- Constants

// ---------------- Structures/Types
typedef struct ListNode {
  MazeNode * node;
  struct ListNode * next;
  struct ListNode * previous;
} ListNode;

typedef struct List {
  ListNode * head;
  ListNode * tail;
} List;

// ---------------- Public Variables
List stack;

// ---------------- Prototypes/Macros
/* AddNode */
void AddNode(MazeNode *);//adds a node to the head of the list

/* PopNode - returns a pointer to the MazeNode that was just added to the stack */
MazeNode * PopNode();//pops a node from the list using the FIFO stack rules

/* CleanupList */
void CleanupList(); //frees all items in the list

#endif // LIST_H
