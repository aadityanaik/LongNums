#ifndef LONGNUMS_H
#define LONGNUMS_H

class Longnums {
  std::string digits;
  bool negative;

public:
  Longnums();

  //input-output functions
  int get();
  int put();

  //comparing numbers
  bool operator<(Longnums);
  /*
  bool operator<(Longnums);
  bool operator==(Longnums);

  */
};

#endif // LONGNUMS_H
