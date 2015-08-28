#!/bin/bash
# 
# Description: this is a build and automated test system to test the query engine


make clean > /dev/null

#Create a logfile
logfile="../test/mazeClientTestLog.$(date '+%a_%b_%d_%T_%Y')"
touch $logfile

#Write date and time stamp of the beginning of the build to the log file
echo "Test Start: $(date '+%c')" > $logfile

#Write the hostname and Operating System where the build was run to the log file
echo "hostname: $(uname -n)" >> $logfile
echo "operating system: $(uname -o)" >> $logfile
echo >> $logfile
echo "--------------------------------------------------------------" >> $logfile
echo >> $logfile

#Write the results of each step of the build to the log file
cd ../src; make maze >> $logfile 2>&1
echo >> $logfile
echo "--------------------------------------------------------------" >> $logfile
echo >> $logfile

#Write the results of running all the tests(name or purpose of the test, success/fail, etc...) to the log file
fail_exit_code=1
pass_exit_code=0
passes=0
fails=0

#TODO: insert the tests for the avatars and the startup client HERE!!!!!

#Write the results of each step of the test build to the log file
make clean > /dev/null
cd ../test/
make maze_test >> $logfile 2>&1
echo >> $logfile
echo "--------------------------------------------------------------" >> $logfile
echo >> $logfile

#Test valid arguments => Run the unit tests for the maze
expected_exit_code=$pass_exit_code
expected_output="Test initMaze() Test case 1 passed\n\
Test initMaze() Test case 2 passed\n\
Test initMaze() Test case 3 passed\n\
Test initMaze() Test case 4 passed\n\
Test rightHandRule() Test case 1 passed\n\
Test rightHandRule() Test case 2 passed\n\
Test rightHandRule() Test case 3 passed\n\
Test rightHandRule() Test case 4 passed\n\
Test rightHandRule() Test case 5 passed\n\
Test rightHandRule() Test case 6 passed\n\
Test rightHandRule() Test case 7 passed\n\
Test AddWall() Test case 1 passed\n\
Test AddWall() Test case 2 passed\n\
Test AddWall() Test case 3 passed\n\
Test AddWall() Test case 4 passed\n\
Test AddWall() Test case 5 passed\n\
Test AddWall() Test case 6 passed\n\
Test AddWall() Test case 7 passed\n\
Test AddWall() Test case 8 passed\n\
Test AddWall() Test case 9 passed\n\
All passed!"
echo "Testing valid arguments - running the unit tests for the maze." >> $logfile
echo "Command: ./maze_test" >> $logfile
echo "Exit code should be: $expected_exit_code" >> $logfile
echo -e "Output should be:\n$expected_output" >> $logfile
output=$(./maze_test 2>&1)
echo -e "Output was:\n$output" >> $logfile
exit_code=$?
echo "Exit code was: $exit_code" >> $logfile
if [ $exit_code -ne $expected_exit_code ]
then
  echo "Incorrect exit code!" >> $logfile
  echo "Test failed!" >> $logfile
  fails=$(( fails+1 ))
else
  echo "Exit code is correct!" >> $logfile
  output=$(echo -n "$output" | sed 's/\n/ /g')
  expected_output=$(echo -en "$expected_output" | sed 's/\n/ /g')
  if [ "$output" == "$expected_output" ]
    then
    echo "Output matches!" >> $logfile
    echo "Test passed!" >> $logfile
    passes=$(( passes+1 ))
  else
    echo "Incorrect output!" >> $logfile
    echo "Test failed!" >> $logfile
    fails=$(( fails+1 ))
  fi
fi
echo >> $logfile
echo "--------------------------------------------------------------" >> $logfile
echo >> $logfile

#Write the results of each step of the test build to the log file
make clean > /dev/null
make list_test >> $logfile 2>&1
echo >> $logfile
echo "--------------------------------------------------------------" >> $logfile
echo >> $logfile

#Test valid arguments => Run the unit tests for the maze
expected_exit_code=$pass_exit_code
expected_output="Test AddNode() Test case 1 passed\n\
Test PopNode() Test case 1 passed\n\
All passed!"
echo "Testing valid arguments - running the unit tests for the maze." >> $logfile
echo "Command: ./list_test" >> $logfile
echo "Exit code should be: $expected_exit_code" >> $logfile
echo -e "Output should be:\n$expected_output" >> $logfile
output=$(./list_test 2>&1)
echo -e "Output was:\n$output" >> $logfile
exit_code=$?
echo "Exit code was: $exit_code" >> $logfile
if [ $exit_code -ne $expected_exit_code ]
then
  echo "Incorrect exit code!" >> $logfile
  echo "Test failed!" >> $logfile
  fails=$(( fails+1 ))
else
  echo "Exit code is correct!" >> $logfile
  output=$(echo -n "$output" | sed 's/\n/ /g')
  expected_output=$(echo -en "$expected_output" | sed 's/\n/ /g')
  if [ "$output" == "$expected_output" ]
    then
    echo "Output matches!" >> $logfile
    echo "Test passed!" >> $logfile
    passes=$(( passes+1 ))
  else
    echo "Incorrect output!" >> $logfile
    echo "Test failed!" >> $logfile
    fails=$(( fails+1 ))
  fi
fi
echo >> $logfile

#Write date and time stamp of the end of the build to the log file
echo "--------------------------------------------------------------" >> $logfile
echo "Test Summary:" >> $logfile
echo "Passes: $passes" >> $logfile
echo "Fails: $fails" >> $logfile
echo >> $logfile
echo "Test End: $(date '+%c')" >> $logfile
cd ../; make clean > /dev/null
