#include <iostream>
#include <ctime>
#include "longnums.hpp"

int main()
{

  clock_t t;
  //examples for 3 numbers
  Longnums x, y;

  //input
  /*
  x.get();
  y.get();
  */
  std::cin >> x;
  std::cin >> y;
  //std::cin >> z;

  std::cout << x << std::endl << y << std::endl;
  //std::cout << z << std::endl;

  //addition


  std::cout << "Addition" << std::endl;
  //(x+y).put();
  std::cout << (x + y) << std::endl;


//  (x + z).put();
  std::cout << std::endl;

  //subtraction
  std::cout << "Subtraction" << std::endl;
  std::cout << (x - y) << std::endl;
//  (x - z).put();
  //std::cout << std::endl;

  //multiplication
  std::cout << "Multiplication" << std::endl;
  //t = clock();
  //(x * y).put();
  std::cout << (x * y) << std::endl;
  //t = clock() - t;
  //double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
  //  printf("multiplication took %lf seconds to execute \n", time_taken);
  //std::cout << std::endl;


  //division
  std::cout << "Division" << std::endl;
  std::cout << (x / y) << std::endl;
//  (x / z).put();
  //std::cout << std::endl;


  //modulus
  std::cout << "Modulus" << std::endl;
  std::cout << (x % y) << std::endl;
  //(x % z).put();
  std::cout << std::endl;

  return 0;
}
