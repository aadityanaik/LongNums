#include <iostream>
#include <ctime>
#include "longnums.hpp"

int main()
{
  Longnums x, y;
  //input

  std::cin >> x;
  std::cin >> y;

  std::cout << x << std::endl << y << std::endl << std::endl;

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
