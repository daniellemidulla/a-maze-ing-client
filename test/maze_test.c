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
// The following test cases are for function:
// 
// MazeNode** initMaze(int r, int c);
// 
// Test case: initMaze: 1
// This test case calls initMaze() for the condition where r is 0
// Result is for returned MazeNode** to be NULL (and an error to be thrown?).
// 
// Test case: initMaze: 2
// This test case calls initMaze() for the condition where c is 0
// Result is for returned MazeNode** to be NULL (and an error to be thrown?).
// 
// Test case: initMaze: 3
// This test case calls initMaze() for the condition where r= 1 and c = 1 
// Result is for returned MazeNode** to have 1 node with 4 walls
// 
// Test case: initMaze: 4
// This test case calls initMaze() for the condition where r > 1 and c > 1 
// Result is for returned MazeNode** to have r*c nodes and walls along the outside(rows 0 & r-1 & columns 0 & c-1)
// 
// 
// The following test cases are for function:
// 
// int rightHandRule(Avatar avatar);
// 
// Test case: rightHandRule: 1
// This test case calls rightHandRule() for the condition where Avatar avatar is empty
// Result is for the returned direction to be empty (and an error to be thrown?).
// 
// Test case: rightHandRule: 2
// This test case calls DisplayResults() for the condition where Avatar avatar is in a node without walls
// Result is for the returned direction to be "right" of the position avatar is facing
// 
// Test case: rightHandRule: 3
// This test case calls DisplayResults() for the condition where Avatar avatar is in a node with a wall to the Avatar's right
// Result is for the returned direction to be in the direction that avatar is facing
//
// Test case: rightHandRule: 4
// This test case calls DisplayResults() for the condition where Avatar avatar is in a node with 2 walls - right & front
// Result is for the returned direction to be "left" of the position avatar is facing
//
// Test case: rightHandRule: 5
// This test case calls DisplayResults() for the condition where Avatar avatar is in a node with 3 walls - right, front, & left
// Result is for the returned direction to be "backwards" from the position avatar is facing
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


// Test case: initMaze: 1
// This test case calls initMaze() for the condition where r is 0
// Result is for returned MazeNode** to be NULL (and an error to be thrown?).
int TestInitMaze1(){
  START_TEST_CASE;
  MazeNode ** maze;
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
  MazeNode ** maze;
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
  MazeNode ** maze;
  maze = initMaze(1, 1);
  SHOULD_BE(maze != NULL);
  SHOULD_BE(maze[0][0].north_wall == 1);
  SHOULD_BE(maze[0][0].south_wall == 1);
  SHOULD_BE(maze[0][0].west_wall == 1);
  SHOULD_BE(maze[0][0].east_wall == 1);
  CleanupMaze();
  END_TEST_CASE;
}

// Test case: initMaze: 4
// This test case calls initMaze() for the condition where r > 1 and c > 1 
// Result is for returned MazeNode** to have r*c nodes and walls along the outside(rows 0 & r-1 & columns 0 & c-1)
int TestInitMaze4(){
  START_TEST_CASE;
  MazeNode ** maze;
  maze = initMaze(3, 3);
  SHOULD_BE(maze != NULL);
  //top left corner
  SHOULD_BE(maze[0][0].north_wall == 1);
  SHOULD_BE(maze[0][0].west_wall == 1);
  SHOULD_BE(maze[0][0].south_wall == 0);
  SHOULD_BE(maze[0][0].east_wall == 0);
  //top middle node
  SHOULD_BE(maze[0][1].north_wall == 1);
  SHOULD_BE(maze[0][1].west_wall == 0);
  SHOULD_BE(maze[0][1].south_wall == 0);
  SHOULD_BE(maze[0][1].east_wall == 0);
  //top right corner
  SHOULD_BE(maze[0][2].north_wall == 1);
  SHOULD_BE(maze[0][2].west_wall == 0);
  SHOULD_BE(maze[0][2].south_wall == 0);
  SHOULD_BE(maze[0][2].east_wall == 1);
  //center left node
  SHOULD_BE(maze[1][0].north_wall == 0);
  SHOULD_BE(maze[1][0].west_wall == 1);
  SHOULD_BE(maze[1][0].south_wall == 0);
  SHOULD_BE(maze[1][0].east_wall == 0);
  //center middle node
  SHOULD_BE(maze[1][1].north_wall == 0);
  SHOULD_BE(maze[1][1].west_wall == 0);
  SHOULD_BE(maze[1][1].south_wall == 0);
  SHOULD_BE(maze[1][1].east_wall == 0);
  //center right node
  SHOULD_BE(maze[1][2].north_wall == 0);
  SHOULD_BE(maze[1][2].west_wall == 0);
  SHOULD_BE(maze[1][2].south_wall == 0);
  SHOULD_BE(maze[1][2].east_wall == 1);
  //bottom left corner
  SHOULD_BE(maze[2][0].north_wall == 0);
  SHOULD_BE(maze[2][0].west_wall == 1);
  SHOULD_BE(maze[2][0].south_wall == 1);
  SHOULD_BE(maze[2][0].east_wall == 0);
  //bottom middle node
  SHOULD_BE(maze[2][1].north_wall == 0);
  SHOULD_BE(maze[2][1].west_wall == 0);
  SHOULD_BE(maze[2][1].south_wall == 1);
  SHOULD_BE(maze[2][1].east_wall == 0);
  //bottom right corner
  SHOULD_BE(maze[2][2].north_wall == 0);
  SHOULD_BE(maze[2][2].west_wall == 0);
  SHOULD_BE(maze[2][2].south_wall == 1);
  SHOULD_BE(maze[2][2].east_wall == 1);
  CleanupMaze();
  END_TEST_CASE;
}

// Test case: rightHandRule: 1
// This test case calls rightHandRule() for the condition where Avatar avatar is empty
// Result is for the returned direction to be empty (and an error to be thrown?).
int TestRHR1(){
  START_TEST_CASE;

  END_TEST_CASE;
}

// Test case: rightHandRule: 2
// This test case calls DisplayResults() for the condition where Avatar avatar is in a node without walls
// Result is for the returned direction to be "right" of the position avatar is facing
int TestRHR2(){
  START_TEST_CASE;

  END_TEST_CASE;
}

// Test case: rightHandRule: 3
// This test case calls DisplayResults() for the condition where Avatar avatar is in a node with a wall to the Avatar's right
// Result is for the returned direction to be in the direction that avatar is facing
int TestRHR3(){
  START_TEST_CASE;

  END_TEST_CASE;
}

// Test case: rightHandRule: 4
// This test case calls DisplayResults() for the condition where Avatar avatar is in a node with 2 walls - right & front
// Result is for the returned direction to be "left" of the position avatar is facing
int TestRHR4(){
  START_TEST_CASE;

  END_TEST_CASE;
}

// Test case: rightHandRule: 5
// This test case calls DisplayResults() for the condition where Avatar avatar is in a node with 3 walls - right, front, & left
// Result is for the returned direction to be "backwards" from the position avatar is facing
int TestRHR5(){
  START_TEST_CASE;

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
  // RUN_TEST(TestRHR1, "rightHandRule() Test case 1");
  // RUN_TEST(TestRHR2, "rightHandRule() Test case 2");
  // RUN_TEST(TestRHR3, "rightHandRule() Test case 3");
  // RUN_TEST(TestRHR4, "rightHandRule() Test case 4");
  // RUN_TEST(TestRHR5, "rightHandRule() Test case 5");
  
  if (!cnt) {
    printf("All passed!\n"); return 0;
  } else {
    printf("Some fails!\n"); return 1;
  }
}

