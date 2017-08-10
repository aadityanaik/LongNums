#include <iostream>
#include "longnums.hpp"

int main()
{
  //examples for 3 numbers
  Longnums x, y;
  int z;

  //input
  /*
  x.get();
  y.get();
  */
  std::cin >> x;
  std::cin >> y;
  std::cin >> z;

  //output
  std::cout << x << std::endl;
  std::cout << y << std::endl;
  std::cout << z << std::endl;

  //addition
  std::cout << "Addition" << std::endl;
  (x+y).put();
  std::cout << std::endl;
  (x + z).put();
  std::cout << std::endl;

  //subtraction
  std::cout << "Subtraction" << std::endl;
  (x - y).put();
  std::cout << std::endl;
  (x - z).put();
  std::cout << std::endl;

  //multiplication
  std::cout << "Multiplication" << std::endl;
  (x * y).put();
  std::cout << std::endl;
  (x * z).put();
  std::cout << std::endl;

  //division
  std::cout << "Division" << std::endl;
  (x / y).put();
  std::cout << std::endl;
  (x / z).put();
  std::cout << std::endl;

  //modulus
  std::cout << "Modulus" << std::endl;
  (x % y).put();
  std::cout << std::endl;
  (x % z).put();
  std::cout << std::endl;
}
