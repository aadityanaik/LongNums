#include <iostream>
#include <climits>
#include "longnums.hpp"

int main()
{
  Longnums x, y;


  //input

  std::cin >> x;
  std::cin >> y;
  std::cout << x << "\n" << y << "\n\n";


	//addition
  std::cout << "Addition" << "\n";
  std::cout << (x + y) << "\n";

	//subtraction

  std::cout << "Subtraction" << "\n";
  std::cout << (x - y) << "\n";

	//multiplication
  std::cout << "Multiplication" << "\n";
  std::cout << (x * y) << "\n";


	//division
  std::cout << "Division" << "\n";
  std::cout << (x / y) << "\n";


	//modulus

  std::cout << "Modulus" << "\n";
  std::cout << (x % y) << "\n";

  return 0;
}
