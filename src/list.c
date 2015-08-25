/*  list.c


  Project name: Maze Project
  Component name:  Linked List Component

  This file contains the functions for a linked list using the FIFO stack rules.
  
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
#include "list.h"

// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 


/*====================================================================*/

/* void AddNode(MazeNode *)
 *
 * Description: adds a node to the head of the list
 *
 * Input: a pointer to the MazeNode that we wish to add to the list
 *
 * Output: none
 *
 */
void AddNode(MazeNode * maze_node){
  if (!maze_node) return;
  ListNode * new_node;
  new_node = (ListNode *) calloc(1, sizeof(ListNode));
  new_node->node = maze_node;
  if (!stack.tail){
    new_node->next = new_node;
    new_node->previous = new_node;
    stack.head = new_node;
    stack.tail = new_node;
  }
  else{
    new_node->next = stack.head;
    stack.head->previous = new_node;
    new_node->previous = stack.tail;
    stack.tail->next = new_node;
    stack.head = new_node;
  }
}

/* MazeNode * PopNode()
 *
 * Description: pops a node from the list using the FIFO stack rules
 *
 * Input: none
 *
 * Output: a pointer to the MazeNode that was just added to the stack
 *
 */
MazeNode * PopNode(){
  if(!stack.head) return NULL;
  MazeNode * maze_node;
  ListNode * head_node;
  head_node = stack.head;
  stack.tail->next = head_node->next;
  head_node->next->previous = stack.tail;
  stack.head = head_node->next;
  maze_node = head_node->node;
  free(head_node);
  return maze_node;
}

/* void CleanupList()
 *
 * Description: frees all items in the list
 *
 * Input: none
 *
 * Output: none
 *
 */
void CleanupList(){
  while(stack.head){
    PopNode();
  }
}
