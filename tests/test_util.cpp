#include <cstdlib>
#include <string>
#include <iostream>
#include "./test_util.hpp"

void checkEqual(int actual, int expected, std::string file, int line) {
  if (actual != expected) {
    std::cerr << file << ":" << line << ": ";
    std::cerr << "Expected " << actual << " to equal " << expected << "." << std::endl;
    exit(1);
  }
}
