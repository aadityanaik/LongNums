#!/bin/bash

# This is a testing script for LongNums class
# This compares the value of each output to the output gained with bash calculator(bc)

# This script will run for 100 test cases each time

function calc {                                                                 #The above function makes sure that the output from bc does not contain the '\ ' string as it does when the value of BC_LINE_LENGTH is on the default
  BC_LINE_LENGTH=0 bc
}

while                                                                           #diff -q output test
  NUM1=$(echo "$((RANDOM - 16383))" ^ "$((RANDOM % 1000))" | calc)                            #refers to x in examples.cpp

  NUM2=$(echo "$((RANDOM - 16383))" ^ "$((RANDOM % 1000))" | calc)                            #refers to y in examples.cpp

  # to generate input file
  echo $NUM1 > input                                                            #x

  echo $NUM2 >> input                                                           #y

  # to generate a test file
  echo $NUM1 > test
  echo -e "$NUM2\n" >> test
  echo Addition >> test
  echo $(echo $NUM1 + $NUM2 | calc) >> test
  echo Subtraction >> test
  echo $(echo $NUM1 - $NUM2 | calc) >> test
  echo Multiplication >> test 
  echo $(echo $NUM1 '*' $NUM2 | calc) >> test  
  echo Division >> test 
  echo $(echo $NUM1 / $NUM2 | calc) >> test  
  echo Modulus >> test  
  echo $(echo $NUM1 % $NUM2 | calc) >> test

  # to generate output
  ./bin/examples < input > output

do
  (( index++ ))
  if [ "$index" -gt 100 ]                                                       #Number of test cases run must be <= 100
  then
    break
  fi

  ( diff output test && echo "Test $index successful" ) || exit 1               #tells when both files (output and test) are different which indicates a bug in Longnums.cpp

done

if [ $? -eq 0 ]                                                                 #if everything's hunky-dory
then
  echo "All tests successful" && rm input output test
fi
