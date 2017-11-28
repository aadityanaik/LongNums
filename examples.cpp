#include <iostream>
#include <ctime>
#include "longnums.hpp"

int main()
{

  //clock_t t;
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

  std::cout << x << std::endl << y << std::endl << std::endl;
  //std::cout << z << std::endl;

	//addition

  std::cout << "Addition" << std::endl;
  std::cout << (x + y) << std::endl;

	//subtraction
	
  std::cout << "Subtraction" << std::endl;
  std::cout << (x - y) << std::endl;

	//multiplication
	
  std::cout << "Multiplication" << std::endl;
  std::cout << (x * y) << std::endl;


	//division
	
  std::cout << "Division" << std::endl;
  std::cout << (x / y) << std::endl;


	//modulus
	
  std::cout << "Modulus" << std::endl;
  std::cout << (x % y) << std::endl;

  return 0;
}
