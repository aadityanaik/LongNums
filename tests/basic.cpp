#include <iostream>
#include "../src/longnums.hpp"
#include "./test_util.hpp"

void testAbsoluteValue() {
  longnums::Longnums x, y, r;
  x = "1", r = x.absolute();
  CHECK_EQUAL(r.toInt(), 1);
  x = "-1", r = x.absolute();
  CHECK_EQUAL(r.toInt(), 1);
  x = "5", r = x.absolute();
  CHECK_EQUAL(r.toInt(), 5);
  x = "-5", r = x.absolute();
  CHECK_EQUAL(r.toInt(), 5);
  x = "100", r = x.absolute();
  CHECK_EQUAL(r.toInt(), 100);
  x = "-100", r = x.absolute();
  CHECK_EQUAL(r.toInt(), 100);
  x = "2147483647", r = x.absolute();
  CHECK_EQUAL(r.toInt(), 2147483647);
  x = "-2147483647", r = x.absolute();
  CHECK_EQUAL(r.toInt(), 2147483647);
  std::cout << "Absolute value tests completed successfully." << std::endl;
}

void testAddition() {
  longnums::Longnums x, y, r;
  x = "1", y = "1", r = x + y;
  CHECK_EQUAL(r.toInt(), 2);
  x = "1", y = "-1", r = x + y;
  CHECK_EQUAL(r.toInt(), 0);
  x = "4", y = "7", r = x + y;
  CHECK_EQUAL(r.toInt(), 11);
  x = "7", y = "4", r = x + y;
  CHECK_EQUAL(r.toInt(), 11);
  x = "9", y = "10", r = x + y;
  CHECK_EQUAL(r.toInt(), 19);
  x = "10", y = "-5", r = x + y;
  CHECK_EQUAL(r.toInt(), 5);
  x = "1234", y = "1234", r = x + y;
  CHECK_EQUAL(r.toInt(), 2468);
  x = "2147483646", y = "1", r = x + y;
  CHECK_EQUAL(r.toInt(), 2147483647);
  x = "2147483647", y = "1", r = x + y;
  CHECK_EQUAL(r.toInt(), -2147483648);
  x = "2147483648", y = "-1", r = x + y;
  CHECK_EQUAL(r.toInt(), 2147483647);
  std::cout << "Addition tests completed successfully." << std::endl;
}

void testSubstraction() {
  longnums::Longnums x, y, r;
  x = "1", y = "1", r = x - y;
  CHECK_EQUAL(r.toInt(), 0);
  x = "4", y = "7", r = x - y;
  CHECK_EQUAL(r.toInt(), -3);
  x = "7", y = "4", r = x - y;
  CHECK_EQUAL(r.toInt(), 3);
  x = "9", y = "10", r = x - y;
  CHECK_EQUAL(r.toInt(), -1);
  x = "1234", y = "1234", r = x - y;
  CHECK_EQUAL(r.toInt(), 0);
  x = "2147483646", y = "1", r = x - y;
  CHECK_EQUAL(r.toInt(), 2147483645);
  x = "2147483648", y = "1", r = x - y;
  CHECK_EQUAL(r.toInt(), 2147483647);
  std::cout << "Substraction tests completed successfully." << std::endl;
}

int main() {
  std::cout << "Running basic tests." << std::endl;
  testAbsoluteValue();
  testAddition();
  testSubstraction();
  std::cout << "Basic tests completed successfully." << std::endl;
  return 0;
}
