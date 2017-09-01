#ifndef LONGNUMS_H
#define LONGNUMS_H

#include <vector>
#include <cstdint>

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

  //overloading input and output operators
  friend std::ostream& operator<<(std::ostream& output, const Longnums& X);

  friend std::istream& operator>>(std::istream& input, Longnums& X);


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
  void operator=(long int);

  //converting to int
  int toInt();

  //absolute value
  Longnums absolute();

  //primary operations- adding, subtracting, multiplying and dividing
  Longnums operator+(Longnums);
  Longnums operator+(int);
  Longnums operator-(Longnums);
  Longnums operator-(int);
  Longnums operator*(Longnums);
  Longnums operator*(long int);
  Longnums operator/(Longnums);
  Longnums operator/(int);
  Longnums operator%(Longnums);
  Longnums operator%(int);
};

#endif // LONGNUMS_H
