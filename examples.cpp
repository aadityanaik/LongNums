#include <iostream>
#include "longnums.hpp"

int main()
{
  //examples for 3 numbers
  Longnums x, y;

  do{
    //input
    x.get();
    y.get();

    //output
    x.put();
    std::cout << std::endl;
    y.put();
    std::cout << std::endl;
    std::cout << std::endl;

    //addition
    std::cout << "Addition" << std::endl;
    (x+y).put();
    std::cout << std::endl;
    std::cout << std::endl;

    //subtraction
    std::cout << "Subtraction" << std::endl;
    (x-y).put();
    std::cout << std::endl;
    std::cout << std::endl;

    //multiplication
    std::cout << "Multiplication" << std::endl;
    (x * y).put();
    std::cout << std::endl;
    std::cout << std::endl;
  }while(1);
}
