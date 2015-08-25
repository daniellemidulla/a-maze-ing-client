// Filename: Test cases for maze.h/.c
// Description: A unit test for maze
// 

//
// Test Harness Spec:
// ------------------
//
// It uses these files but they are not unit tested in this test harness:
//
// void CleanupList();
// 
// It tests the following functions:
// 
// void AddNode(MazeNode *);
// MazeNode * PopNode();
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
#include "../src/list.h"
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
// void AddNode(MazeNode *);
// 
// Test case: AddNode: 1
// This test case calls AddNode() for the condition where given MazeNode * is NULL
// Result is for no node to be added to the stack
int TestAddNode1(){
  START_TEST_CASE;
  AddNode(NULL);
  SHOULD_BE(stack.head == NULL);
  SHOULD_BE(stack.tail == NULL);
  CleanupList();
  END_TEST_CASE;
}

// The following test cases are for function:
// 
// MazeNode * PopNode();
// 
// Test case: PopNode: 1
// This test case calls PopNode() for the condition where the stack is empty
// Result is for returned value to be NULL.
int TestPopNode1(){
  START_TEST_CASE;
  SHOULD_BE(PopNode() == NULL);
  CleanupList();
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

  RUN_TEST(TestAddNode1, "AddNode() Test case 1");
  RUN_TEST(TestPopNode1, "PopNode() Test case 1");

  
  if (!cnt) {
    printf("All passed!\n"); return 0;
  } else {
    printf("Some fails!\n"); return 1;
  }
}

