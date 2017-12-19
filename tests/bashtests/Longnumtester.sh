#!/bin/bash

# This is a testing script for LongNums class
# This compares the value of each output to the output gained with bash calculator(bc)

# This script will run for 100 test cases each time

function calc {                                                                 #The above function makes sure that the output from bc does not contain the '\ ' string as it does when the value of BC_LINE_LENGTH is on the default
  BC_LINE_LENGTH=0 bc
}

while                                                                           
  NUM1=$(echo "$((RANDOM - 16383))" ^ "$((RANDOM % 1000))" | calc)                            #refers to x in examples.cpp

  NUM2=$(echo "$((RANDOM - 16383))" ^ "$((RANDOM % 1000))" | calc)                            #refers to y in examples.cpp

  # to generate input file
  echo $NUM1 > input                                                            #x

  echo $NUM2 >> input                                                           #y

  # to generate a control file
  echo $NUM1 > control
  echo -e "$NUM2\n" >> control
  echo Addition >> control
  echo $(echo $NUM1 + $NUM2 | calc) >> control
  echo Subtraction >> control
  echo $(echo $NUM1 - $NUM2 | calc) >> control
  echo Multiplication >> control 
  echo $(echo $NUM1 '*' $NUM2 | calc) >> control  
  echo Division >> control 
  echo $(echo $NUM1 / $NUM2 | calc) >> control  
  echo Modulus >> control  
  echo $(echo $NUM1 % $NUM2 | calc) >> control

  # to generate output
  ./bin/examples < input > output

do
  (( index++ ))
  if [ "$index" -gt 100 ]                                                       #Number of test cases run must be <= 100
  then
    break
  fi

  ( diff output control && echo "Test $index successful" ) || exit 1               #tells when both files (output and test) are different which indicates a bug in Longnums.cpp

done

if [ $? -eq 0 ]                                                                 #if everything's hunky-dory
then
  echo "All tests successful" && rm input output control
fi
