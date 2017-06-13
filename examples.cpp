#include <iostream>
#include "longnums.hpp"

int main()
{
  //examples for 3 numbers
  Longnums x, y, z;

  //input
  x.get();
  y.get();
  z.get();

  //output
  x.put();
  std::cout << std::endl;
  y.put();
  std::cout << std::endl;
  z.put();
  std::cout << std::endl;
  std::cout << std::endl;

  //addition
  (x+y+z).put();
  std::cout << std::endl;
  std::cout << std::endl;

  //subtraction
  (x-y).put();
  std::cout << std::endl;
}
