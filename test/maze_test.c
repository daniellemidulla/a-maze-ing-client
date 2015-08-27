// Filename: Test cases for maze.h/.c
// Description: A unit test for maze
// 

//
// Test Harness Spec:
// ------------------
//
// It uses these files but they are not unit tested in this test harness:
//
// void CleanupMaze();
// 
// It tests the following functions:
// 
// MazeNode** initMaze(int r, int c);
// int rightHandRule(Avatar avatar);
// void AddWall(int r, int c, int dir, int value);
// 
// If any of the tests fail it prints status.
// If all tests pass it prints status.
// 
// Test Cases:
// -----------
// 
// The test harness runs a number of test cases to test the code.
// The approach is to first set up the environment for the test,
// invoke the function to be tested,
// then validate the state of the data structures using the SHOULD_BE macro.
// This is repeated for each test case.
// 
// The test harness isolates the functions under test and settin up the environment the code expects when integrated in the real system.
// 
// The test harness dummies out the real hash function and through the use of a valiable called index manipulates
// where WordNodes are inserted into the HashTable.
// 
// 
// 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/amazing.h"
#include "../src/maze.h"

// Useful MACROS for controlling the unit tests.

// each test should start by setting the result count to zero

#define START_TEST_CASE  int rs=0

// check a condition and if false print the test condition failed
// e.g., SHOULD_BE(dict->start == NULL)
// note: the construct "#x" below is the sstringification preprocessor operator that
//       converts the argument x into a character string constant

#define SHOULD_BE(x) if (!(x))  {rs=rs+1; \
    printf("Line %d test [%s] Failed\n", __LINE__,#x); \
  }


// return the result count at the end of a test

#define END_TEST_CASE return rs

//
// general macro for running a best
// e.g., RUN_TEST(TestDAdd1, "DAdd Test case 1");
// translates to:
// if (!TestDAdd1()) {
//     printf("Test %s passed\n","DAdd Test case 1");
// } else { 
//     printf("Test %s failed\n", "DAdd Test case 1");
//     cnt = cnt +1;
// }
//

#define RUN_TEST(x, y) if (!x()) {              \
    printf("Test %s passed\n", y);              \
} else {                                        \
    printf("Test %s failed\n", y);              \
    cnt = cnt + 1;                              \
}


// The following test cases are for function:
// 
// MazeNode** initMaze(int r, int c);
// 
// Test case: initMaze: 1
// This test case calls initMaze() for the condition where r is 0
// Result is for returned MazeNode** to be NULL (and an error to be thrown?).
int TestInitMaze1(){
  START_TEST_CASE;
  Maze * maze;
  maze = initMaze(0, 5);
  SHOULD_BE(maze == NULL);
  CleanupMaze();
  END_TEST_CASE;
}

// Test case: initMaze: 2
// This test case calls initMaze() for the condition where c is 0
// Result is for returned MazeNode** to be NULL (and an error to be thrown?).
int TestInitMaze2(){
  START_TEST_CASE;
  Maze * maze;
  maze = initMaze(5, 0);
  SHOULD_BE(maze == NULL);
  CleanupMaze();
  END_TEST_CASE;
}

// Test case: initMaze: 3
// This test case calls initMaze() for the condition where r= 1 and c = 1 
// Result is for returned MazeNode** to have 1 node with 4 walls
int TestInitMaze3(){
  START_TEST_CASE;
  Maze* maze;
  maze = initMaze(1, 1);
  SHOULD_BE(maze != NULL);
  SHOULD_BE(maze->maze[0][0].north_wall == 1);
  SHOULD_BE(maze->maze[0][0].south_wall == 1);
  SHOULD_BE(maze->maze[0][0].west_wall == 1);
  SHOULD_BE(maze->maze[0][0].east_wall == 1);
  CleanupMaze();
  END_TEST_CASE;
}

// Test case: initMaze: 4
// This test case calls initMaze() for the condition where r > 1 and c > 1 
// Result is for returned MazeNode** to have r*c nodes and walls along the outside(rows 0 & r-1 & columns 0 & c-1)
int TestInitMaze4(){
  START_TEST_CASE;
  MazeNode ** maze;
  maze = initMaze(3, 3)->maze;
  SHOULD_BE(maze != NULL);
  //top left corner
  SHOULD_BE(maze[0][0].north_wall == 1);
  SHOULD_BE(maze[0][0].west_wall == 1);
  SHOULD_BE(maze[0][0].south_wall == -1);
  SHOULD_BE(maze[0][0].east_wall == -1);
  //top middle node
  SHOULD_BE(maze[0][1].north_wall == 1);
  SHOULD_BE(maze[0][1].west_wall == -1);
  SHOULD_BE(maze[0][1].south_wall == -1);
  SHOULD_BE(maze[0][1].east_wall == -1);
  //top right corner
  SHOULD_BE(maze[0][2].north_wall == 1);
  SHOULD_BE(maze[0][2].west_wall == -1);
  SHOULD_BE(maze[0][2].south_wall == -1);
  SHOULD_BE(maze[0][2].east_wall == 1);
  //center left node
  SHOULD_BE(maze[1][0].north_wall == -1);
  SHOULD_BE(maze[1][0].west_wall == 1);
  SHOULD_BE(maze[1][0].south_wall == -1);
  SHOULD_BE(maze[1][0].east_wall == -1);
  //center middle node
  SHOULD_BE(maze[1][1].north_wall == -1);
  SHOULD_BE(maze[1][1].west_wall == -1);
  SHOULD_BE(maze[1][1].south_wall == -1);
  SHOULD_BE(maze[1][1].east_wall == -1);
  //center right node
  SHOULD_BE(maze[1][2].north_wall == -1);
  SHOULD_BE(maze[1][2].west_wall == -1);
  SHOULD_BE(maze[1][2].south_wall == -1);
  SHOULD_BE(maze[1][2].east_wall == 1);
  //bottom left corner
  SHOULD_BE(maze[2][0].north_wall == -1);
  SHOULD_BE(maze[2][0].west_wall == 1);
  SHOULD_BE(maze[2][0].south_wall == 1);
  SHOULD_BE(maze[2][0].east_wall == -1);
  //bottom middle node
  SHOULD_BE(maze[2][1].north_wall == -1);
  SHOULD_BE(maze[2][1].west_wall == -1);
  SHOULD_BE(maze[2][1].south_wall == 1);
  SHOULD_BE(maze[2][1].east_wall == -1);
  //bottom right corner
  SHOULD_BE(maze[2][2].north_wall == -1);
  SHOULD_BE(maze[2][2].west_wall == -1);
  SHOULD_BE(maze[2][2].south_wall == 1);
  SHOULD_BE(maze[2][2].east_wall == 1);
  CleanupMaze();
  END_TEST_CASE;
}

// Test case: initMaze: 5
// This test case calls initMaze() for the condition where the maze has already been initialized 
// Result is for returned Maze* to be a pointer to the address of the existing Maze
int TestInitMaze5(){
  START_TEST_CASE;
  Maze* maze, *new_maze;
  maze = initMaze(3, 3);
  SHOULD_BE(maze != NULL);
  new_maze = initMaze(3, 3);
  SHOULD_BE(new_maze != NULL);
  SHOULD_BE(maze == new_maze);
  CleanupMaze();
  END_TEST_CASE;
}

// The following test cases are for function:
// 
// int rightHandRule(Avatar avatar);
// 
// Test case: rightHandRule: 1
// This test case calls rightHandRule() for the condition where Avatar avatar direction is invalid (-1)
// Result is for the returned value to be -1.
int TestRHR1(){
  START_TEST_CASE;
  Avatar avatar;
  avatar.direction = -1;
  initMaze(3, 3);
  SHOULD_BE(rightHandRule(avatar) == -1);
  CleanupMaze();
  END_TEST_CASE;
}

// The following test cases are for function:
// 
// int rightHandRule(Avatar avatar);
// 
// Test case: rightHandRule: 2
// This test case calls rightHandRule() for the condition where Avatar avatar position is invalid (-1)
// Result is for the returned value to be -1.
int TestRHR2(){
  START_TEST_CASE;
  Avatar avatar;
  avatar.pos.x = -1;
  initMaze(3, 3);
  SHOULD_BE(rightHandRule(avatar) == -1);
  CleanupMaze();
  END_TEST_CASE;
}

// The following test cases are for function:
// 
// int rightHandRule(Avatar avatar);
// 
// Test case: rightHandRule: 3
// This test case calls rightHandRule() for the condition where Avatar avatar position is invalid (>num_row)
// Result is for the returned value to be -1.
int TestRHR3(){
  START_TEST_CASE;
  Avatar avatar;
  avatar.pos.x = 3;
  initMaze(3, 3);
  SHOULD_BE(rightHandRule(avatar) == -1);
  CleanupMaze();
  END_TEST_CASE;
}

// Test case: rightHandRule: 4
// This test case calls DisplayResults() for the condition where Avatar avatar is in a node without walls
// Result is for the returned direction to be "right" of the position avatar is facing
int TestRHR4(){
  START_TEST_CASE;
  MazeNode ** maze;
  Avatar avatar;
  maze = initMaze(3, 3)->maze;
  avatar.pos.x = 1;
  avatar.pos.y = 1;
  SHOULD_BE(maze[1][1].north_wall == -1);
  SHOULD_BE(maze[1][1].west_wall == -1);
  SHOULD_BE(maze[1][1].east_wall == -1);
  SHOULD_BE(maze[1][1].south_wall == -1);
  avatar.direction = M_NORTH;
  SHOULD_BE(rightHandRule(avatar) == M_EAST);
  avatar.direction = M_EAST;
  SHOULD_BE(rightHandRule(avatar) == M_SOUTH);
  avatar.direction = M_SOUTH;
  SHOULD_BE(rightHandRule(avatar) == M_WEST);
  avatar.direction = M_WEST;
  SHOULD_BE(rightHandRule(avatar) == M_NORTH);
  CleanupMaze();
  END_TEST_CASE;
}

// Test case: rightHandRule: 5
// This test case calls DisplayResults() for the condition where Avatar avatar is in a node with a wall to the Avatar's right
// Result is for the returned direction to be in the direction that avatar is facing
int TestRHR5(){
  START_TEST_CASE;
  MazeNode ** maze;
  Avatar avatar;
  maze = initMaze(3, 3)->maze;
  avatar.pos.x = 1; //avatar is in column 1
  avatar.pos.y = 0; //avatar is in row 0
  avatar.direction = M_WEST;
  SHOULD_BE(maze[0][1].north_wall == 1); //there should be a wall north of the avatar
  SHOULD_BE(rightHandRule(avatar) == M_WEST);
  avatar.pos.x = 0; //avatar is in column 0
  avatar.pos.y = 1; //avatar is in row 1
  avatar.direction = M_SOUTH;
  SHOULD_BE(maze[1][0].west_wall == 1); //there should be a wall west of the avatar
  SHOULD_BE(rightHandRule(avatar) == M_SOUTH);
  avatar.pos.x = 1; //avatar is in column 1
  avatar.pos.y = 2; //avatar is in row 2
  avatar.direction = M_EAST;
  SHOULD_BE(maze[2][1].south_wall == 1); //there should be a wall south of the avatar
  SHOULD_BE(rightHandRule(avatar) == M_EAST);
  avatar.pos.x = 2; //avatar is in column 2
  avatar.pos.y = 1; //avatar is in row 1
  avatar.direction = M_NORTH;
  SHOULD_BE(maze[1][2].east_wall == 1); //there should be a wall east of the avatar
  SHOULD_BE(rightHandRule(avatar) == M_NORTH);

  CleanupMaze();
  END_TEST_CASE;
}

// Test case: rightHandRule: 6
// This test case calls DisplayResults() for the condition where Avatar avatar is in a node with 2 walls - right & front
// Result is for the returned direction to be "left" of the position avatar is facing
int TestRHR6(){
  START_TEST_CASE;
  MazeNode ** maze;
  Avatar avatar;
  maze = initMaze(3, 3)->maze;
  //avatar in the top left corner facing west, should go south
  avatar.pos.x = 0;
  avatar.pos.y = 0;
  avatar.direction = M_WEST;
  SHOULD_BE(maze[0][0].north_wall == 1);
  SHOULD_BE(maze[0][0].west_wall == 1);
  SHOULD_BE(rightHandRule(avatar) == M_SOUTH);
  //avatar in the bottom left corner facing south, should go east
  avatar.pos.x = 0;
  avatar.pos.y = 2;
  avatar.direction = M_SOUTH;
  SHOULD_BE(maze[2][0].west_wall == 1);
  SHOULD_BE(maze[2][0].south_wall == 1);
  SHOULD_BE(rightHandRule(avatar) == M_EAST);
  //avatar in the bottom right corner facing east, should go north
  avatar.pos.x = 2;
  avatar.pos.y = 2;
  avatar.direction = M_EAST;
  SHOULD_BE(maze[2][2].east_wall == 1);
  SHOULD_BE(maze[2][2].south_wall == 1);
  SHOULD_BE(rightHandRule(avatar) == M_NORTH);
  //avatar in the top right corner facing north, should go west
  avatar.pos.x = 2;
  avatar.pos.y = 0;
  avatar.direction = M_NORTH;
  SHOULD_BE(maze[0][2].east_wall == 1);
  SHOULD_BE(maze[0][2].north_wall == 1);
  SHOULD_BE(rightHandRule(avatar) == M_WEST);
  CleanupMaze();
  END_TEST_CASE;
}

// Test case: rightHandRule: 7
// This test case calls DisplayResults() for the condition where Avatar avatar is in a node with 3 walls - right, front, & left
// Result is for the returned direction to be "backwards" from the position avatar is facing and for the maze to have a new wall
int TestRHR7(){
  START_TEST_CASE;
  MazeNode ** maze;
  Avatar avatar;
  maze = initMaze(3, 3)->maze;
  //avatar is in the middle of the maze
  avatar.pos.x = 1;
  avatar.pos.y = 1;
  //avatar facing north in a maze node with north, east, and west walls
  avatar.direction = M_NORTH;
  AddWall(1, 1, M_NORTH, 1);
  AddWall(1, 1, M_EAST, 1);
  AddWall(1, 1, M_WEST, 1);
  SHOULD_BE(rightHandRule(avatar) == M_SOUTH); //avatar will go south
  SHOULD_BE(maze[1][1].south_wall == 2); //maze node where the avatar was now has a 4th wall
  SHOULD_BE(maze[2][1].north_wall == 2); //maze node the avatar will move to has a "fake" north wall
  //avatar facing west in a maze node with north, south, and west walls
  avatar.direction = M_WEST;
  AddWall(1, 1, M_NORTH, 1);
  AddWall(1, 1, M_EAST, 0); //reset value of east wall to 0
  AddWall(1, 1, M_WEST, 1);
  AddWall(1, 1, M_SOUTH, 1);
  SHOULD_BE(rightHandRule(avatar) == M_EAST); //avatar will go east
  SHOULD_BE(maze[1][1].east_wall == 2); //maze node where the avatar was now has a 4th wall
  SHOULD_BE(maze[1][2].west_wall == 2); //maze node the avatar will move to has a "fake" west wall
  //avatar facing south in a maze node with east, south, and west walls
  avatar.direction = M_SOUTH;
  AddWall(1, 1, M_NORTH, 0); //reset value of north wall to 0
  AddWall(1, 1, M_EAST, 1);
  AddWall(1, 1, M_WEST, 1);
  AddWall(1, 1, M_SOUTH, 1);
  SHOULD_BE(rightHandRule(avatar) == M_NORTH); //avatar will go north
  SHOULD_BE(maze[1][1].north_wall == 2); //maze node where the avatar was now has a 4th wall
  SHOULD_BE(maze[0][1].south_wall == 2); //maze node the avatar will move to has a "fake" south wall
  //avatar facing east in a maze node with north, south, and west walls
  avatar.direction = M_EAST;
  AddWall(1, 1, M_NORTH, 1);
  AddWall(1, 1, M_EAST, 1);
  AddWall(1, 1, M_WEST, 0); //reset value of north wall to 0
  AddWall(1, 1, M_SOUTH, 1);
  SHOULD_BE(rightHandRule(avatar) == M_WEST); //avatar will go east
  SHOULD_BE(maze[1][1].west_wall == 2); //maze node where the avatar was now has a 4th wall
  SHOULD_BE(maze[1][0].east_wall == 2); //maze node the avatar will move to has a "fake" east wall
  CleanupMaze();
  END_TEST_CASE;
}
// The following test cases are for function:
// 
// void AddWall(int r, int c, int dir, int value);
// 
// Test case: AddWall: 1
// This test case calls AddWall() for the condition where dir is not M_NORTH, M_SOUTH, M_EAST, or M_WEST
// Result is for nothing to happen to the maze.
int TestAddWall1(){
  START_TEST_CASE;
  int north, south, east, west;
  MazeNode ** maze;
  maze = initMaze(3, 3)->maze;
  north = maze[1][1].north_wall;
  south = maze[1][1].south_wall;
  east = maze[1][1].east_wall;
  west = maze[1][1].west_wall;
  AddWall(1, 1, -1, 2);
  SHOULD_BE(maze[1][1].north_wall == north);
  SHOULD_BE(maze[1][1].south_wall == south);
  SHOULD_BE(maze[1][1].east_wall == east);
  SHOULD_BE(maze[1][1].west_wall == west);
  CleanupMaze();
  END_TEST_CASE;
}

// Test case: AddWall: 2
// This test case calls AddWall() for the condition where r is 0 and we are changing the value of a north wall
// Result is for nothing to happen to the maze.
int TestAddWall2(){
  START_TEST_CASE;
  int north, south, east, west;
  MazeNode ** maze;
  maze = initMaze(3, 3)->maze;
  north = maze[0][1].north_wall;
  south = maze[0][1].south_wall;
  east = maze[0][1].east_wall;
  west = maze[0][1].west_wall;
  AddWall(0, 1, M_NORTH, 2);
  SHOULD_BE(maze[0][1].north_wall == north);
  SHOULD_BE(maze[0][1].south_wall == south);
  SHOULD_BE(maze[0][1].east_wall == east);
  SHOULD_BE(maze[0][1].west_wall == west);
  CleanupMaze();
  END_TEST_CASE;
}

// Test case: AddWall: 3
// This test case calls AddWall() for the condition where r is the last row and we are changing the value of a south wall
// Result is for nothing to happen to the maze.
int TestAddWall3(){
  START_TEST_CASE;
  int north, south, east, west;
  MazeNode ** maze;
  maze = initMaze(3, 3)->maze;
  north = maze[2][1].north_wall;
  south = maze[2][1].south_wall;
  east = maze[2][1].east_wall;
  west = maze[2][1].west_wall;
  AddWall(2, 1, M_SOUTH, 2);
  SHOULD_BE(maze[2][1].north_wall == north);
  SHOULD_BE(maze[2][1].south_wall == south);
  SHOULD_BE(maze[2][1].east_wall == east);
  SHOULD_BE(maze[2][1].west_wall == west);
  CleanupMaze();
  END_TEST_CASE;
}

// Test case: AddWall: 4
// This test case calls AddWall() for the condition where c = 0 and we are changing the value of a west wall
// Result is for nothing to happen to the maze.
int TestAddWall4(){
  START_TEST_CASE;
  int north, south, east, west;
  MazeNode ** maze;
  maze = initMaze(3, 3)->maze;
  north = maze[1][0].north_wall;
  south = maze[1][0].south_wall;
  east = maze[1][0].east_wall;
  west = maze[1][0].west_wall;
  AddWall(1, 0, M_WEST, 2);
  SHOULD_BE(maze[1][0].north_wall == north);
  SHOULD_BE(maze[1][0].south_wall == south);
  SHOULD_BE(maze[1][0].east_wall == east);
  SHOULD_BE(maze[1][0].west_wall == west);
  CleanupMaze();
  END_TEST_CASE;
}

// Test case: AddWall: 5
// This test case calls AddWall() for the condition where c is the last column and we are changing the value of an east wall
// Result is for nothing to happen to the maze.
int TestAddWall5(){
  START_TEST_CASE;
  int north, south, east, west;
  MazeNode ** maze;
  maze = initMaze(3, 3)->maze;
  north = maze[1][2].north_wall;
  south = maze[1][2].south_wall;
  east = maze[1][2].east_wall;
  west = maze[1][2].west_wall;
  AddWall(1, 2, M_EAST, 2);
  SHOULD_BE(maze[1][2].north_wall == north);
  SHOULD_BE(maze[1][2].south_wall == south);
  SHOULD_BE(maze[1][2].east_wall == east);
  SHOULD_BE(maze[1][2].west_wall == west);
  CleanupMaze();
  END_TEST_CASE;
}

// Test case: AddWall: 6
// This test case calls AddWall() for the condition where r is not the first nor the last row and we add a north wall
// Result is for a north wall to be added to maze[r][c] and a south wall of the same value to be added to maze[r-1][c]
int TestAddWall6(){
  START_TEST_CASE;
  int r, c;
  MazeNode ** maze;
  maze = initMaze(3, 3)->maze;
  r = 1;
  c = 1;
  AddWall(r, c, M_NORTH, 2);
  SHOULD_BE(maze[r][c].north_wall == 2);
  SHOULD_BE(maze[r-1][c].south_wall == 2);
  CleanupMaze();
  END_TEST_CASE;
}

// Test case: AddWall: 7
// This test case calls AddWall() for the condition where r is not the first nor the last row and we add a south wall
// Result is for a south wall to be added to maze[r][c] and a north wall of the same value to be added to maze[r+1][c]
int TestAddWall7(){
  START_TEST_CASE;
  int r, c;
  MazeNode ** maze;
  maze = initMaze(3, 3)->maze;
  r = 1;
  c = 1;
  AddWall(r, c, M_SOUTH, 2);
  SHOULD_BE(maze[r][c].south_wall == 2);
  SHOULD_BE(maze[r+1][c].north_wall == 2);
  CleanupMaze();
  END_TEST_CASE;
}

// Test case: AddWall: 8
// This test case calls AddWall() for the condition where c is not the first nor the last column and we add a west wall
// Result is for a west wall to be added to maze[r][c] and an east wall of the same value to be added to maze[r][c-1]
int TestAddWall8(){
  START_TEST_CASE;
  int r, c;
  MazeNode ** maze;
  maze = initMaze(3, 3)->maze;
  r = 1;
  c = 1;
  AddWall(r, c, M_WEST, 2);
  SHOULD_BE(maze[r][c].west_wall == 2);
  SHOULD_BE(maze[r][c-1].east_wall == 2);
  CleanupMaze();
  END_TEST_CASE;
}
// Test case: AddWall: 9
// This test case calls AddWall() for the condition where c is not the first nor the last column and we add an east wall
// Result is for an east wall to be added to maze[r][c] and a west wall of the same value to be added to maze[r][c+1]
int TestAddWall9(){
  START_TEST_CASE;
  int r, c;
  MazeNode ** maze;
  maze = initMaze(3, 3)->maze;
  r = 1;
  c = 1;
  AddWall(r, c, M_EAST, 2);
  SHOULD_BE(maze[r][c].east_wall == 2);
  SHOULD_BE(maze[r][c+1].west_wall == 2);
  CleanupMaze();
  END_TEST_CASE;
}

// This is the main test harness for the set of maze functions. It tests all the code
// in maze.c:
//
// It uses these files but they are not unit tested in this test harness:
//
// 
// It tests the following functions:
// 
// MazeNode** initMaze(int r, int c);
// int rightHandRule(Avatar avatar);
// 
// If any of the tests fail it prints status.
// If all tests pass it prints status.

int main(int argc, char** argv) {
  int cnt = 0;

  RUN_TEST(TestInitMaze1, "initMaze() Test case 1");
  RUN_TEST(TestInitMaze2, "initMaze() Test case 2");
  RUN_TEST(TestInitMaze3, "initMaze() Test case 3");
  RUN_TEST(TestInitMaze4, "initMaze() Test case 4");
  RUN_TEST(TestInitMaze5, "initMaze() Test case 5");
  RUN_TEST(TestRHR1, "rightHandRule() Test case 1");
  RUN_TEST(TestRHR2, "rightHandRule() Test case 2");
  RUN_TEST(TestRHR3, "rightHandRule() Test case 3");
  RUN_TEST(TestRHR4, "rightHandRule() Test case 4");
  RUN_TEST(TestRHR5, "rightHandRule() Test case 5");
  RUN_TEST(TestRHR6, "rightHandRule() Test case 6");
  RUN_TEST(TestRHR7, "rightHandRule() Test case 7");
  RUN_TEST(TestAddWall1, "AddWall() Test case 1");
  RUN_TEST(TestAddWall2, "AddWall() Test case 2");
  RUN_TEST(TestAddWall3, "AddWall() Test case 3");
  RUN_TEST(TestAddWall4, "AddWall() Test case 4");
  RUN_TEST(TestAddWall5, "AddWall() Test case 5");
  RUN_TEST(TestAddWall6, "AddWall() Test case 6");
  RUN_TEST(TestAddWall7, "AddWall() Test case 7");
  RUN_TEST(TestAddWall8, "AddWall() Test case 8");
  RUN_TEST(TestAddWall9, "AddWall() Test case 9");
  
  if (!cnt) {
    printf("All passed!\n"); return 0;
  } else {
    printf("Some fails!\n"); return 1;
  }
}

