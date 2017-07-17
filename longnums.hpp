#ifndef LONGNUMS_H
#define LONGNUMS_H

#include <vector>

class Longnums {
  std::vector<int> digits;
  bool negative;

public:
  //constructor
  Longnums();

  //destructor
  ~Longnums();

  //input-output functions
  int get();
  int put();

  //comparing numbers
  bool operator<(Longnums);
  bool operator<(int);
  bool operator>(Longnums);
  bool operator>(int);
  bool operator==(Longnums);
  bool operator==(int);
  bool operator<=(Longnums);
  bool operator<=(int);
  bool operator>=(Longnums);
  bool operator>=(int);
  bool operator!=(Longnums);
  bool operator!=(int);

  //Equality functions
  Longnums(Longnums&);
  void operator=(int);

  //absolute value
  Longnums absolute();

  //primary operations- adding, subtracting, multiplying and dividing
  Longnums operator+(Longnums);
  Longnums operator+(int);
  Longnums operator-(Longnums);
  Longnums operator-(int);
  Longnums operator*(Longnums);
  Longnums operator*(int);
  Longnums operator/(Longnums);
  Longnums operator/(int);
  Longnums operator%(Longnums);
  Longnums operator%(int);
};

#endif // LONGNUMS_H
