#include <iostream>
#include "../src/longnums.hpp"
#include "./test_util.hpp"

void testAbsoluteValue() {
  LongNumber x, y, r;
  x = "1", r = x.absolute();
  CHECK_EQUAL(r.toLong(), 1);
  x = "-1", r = x.absolute();
  CHECK_EQUAL(r.toLong(), 1);
  x = "5", r = x.absolute();
  CHECK_EQUAL(r.toLong(), 5);
  x = "-5", r = x.absolute();
  CHECK_EQUAL(r.toLong(), 5);
  x = "100", r = x.absolute();
  CHECK_EQUAL(r.toLong(), 100);
  x = "-100", r = x.absolute();
  CHECK_EQUAL(r.toLong(), 100);
  x = "9223372036854775807", r = x.absolute();
  CHECK_EQUAL(r.toLong(), 9223372036854775807);
  x = "-9223372036854775807", r = x.absolute();
  CHECK_EQUAL(r.toLong(), 9223372036854775807);
  std::cout << "Absolute value tests completed successfully." << std::endl;
}

void testAddition() {
  LongNumber x, y, r;
  x = "1", y = "1", r = x + y;
  CHECK_EQUAL(r.toLong(), 2);
  x = "1", y = "-1", r = x + y;
  CHECK_EQUAL(r.toLong(), 0);
  x = "4", y = "7", r = x + y;
  CHECK_EQUAL(r.toLong(), 11);
  x = "7", y = "4", r = x + y;
  CHECK_EQUAL(r.toLong(), 11);
  x = "9", y = "10", r = x + y;
  CHECK_EQUAL(r.toLong(), 19);
  x = "10", y = "-5", r = x + y;
  CHECK_EQUAL(r.toLong(), 5);
  x = "1234", y = "1234", r = x + y;
  CHECK_EQUAL(r.toLong(), 2468);
  x = "2147483646", y = "1", r = x + y;
  CHECK_EQUAL(r.toLong(), 2147483647);
  x = "9223372036854775807", y = "0", r = x + y;
  CHECK_EQUAL(r.toLong(), 9223372036854775807);
  x = "2147483648", y = "-1", r = x + y;
  CHECK_EQUAL(r.toLong(), 2147483647);
  std::cout << "Addition tests completed successfully." << std::endl;
}

void testSubstraction() {
  LongNumber x, y, r;
  x = "1", y = "1", r = x - y;
  CHECK_EQUAL(r.toLong(), 0);
  x = "4", y = "7", r = x - y;
  CHECK_EQUAL(r.toLong(), -3);
  x = "7", y = "4", r = x - y;
  CHECK_EQUAL(r.toLong(), 3);
  x = "9", y = "10", r = x - y;
  CHECK_EQUAL(r.toLong(), -1);
  x = "1234", y = "1234", r = x - y;
  CHECK_EQUAL(r.toLong(), 0);
  x = "9223372036854775807", y = "1", r = x - y;
  CHECK_EQUAL(r.toLong(), 9223372036854775806);
  x = "9223372036854775808", y = "1", r = x - y;
  CHECK_EQUAL(r.toLong(), 9223372036854775807);
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
