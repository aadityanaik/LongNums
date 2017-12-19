#ifndef TESTS_UTIL_H
#define TESTS_UTIL_H

#include <string>

#define CHECK_EQUAL(actual, expected) checkEqual((actual), (expected),  __FILE__, __LINE__);

void checkEqual(long int actual, long int expected, std::string file, int line);

#endif // TESTS_UTIL_H
