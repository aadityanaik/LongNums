#ifndef LONGNUMS_H
#define LONGNUMS_H

#include <vector>

class Longnums {
  std::vector<int> digits;
  bool negative;


	void operator=(std::vector<int>&);

public:
  //constructor
  Longnums();

  //destructor
  ~Longnums();

  //overloading input and output operators
  friend std::ostream& operator<<(std::ostream& output, const Longnums& X);

  friend std::istream& operator>>(std::istream& input, Longnums& X);


  //comparing numbers
  bool operator<(const Longnums&);
  bool operator<(const int&);
  bool operator>(const Longnums&);
  bool operator>(const int&);
  bool operator==(const Longnums&);
  bool operator==(const int&);
  bool operator<=(const Longnums&);
  bool operator<=(const int&);
  bool operator>=(const Longnums&);
  bool operator>=(const int&);
  bool operator!=(const Longnums&);
  bool operator!=(const int&);

  //Equality functions
  Longnums(const Longnums&);
  void operator=(const long int&);
	void operator=(const std::string&);
	void operator=(const std::vector<int>&);

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
