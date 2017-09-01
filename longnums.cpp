#include <iostream>
#include <algorithm>
#include <climits>
#include <math.h>

#include "longnums.hpp"

//default constructor
Longnums::Longnums() {                       //By default every object will be 0
  digits.push_back(0);
  negative = false;
}

//destructor
Longnums::~Longnums() {
}

//copy constructor
Longnums::Longnums(Longnums &X) {
  digits = X.digits;
  while((*digits.begin()) == 0 && digits.size() > 1) {
    digits.erase(digits.begin());
  }
  negative = X.negative;
}

//equate Longnums object to an int
void Longnums::operator=(long int X) {
  digits.erase(digits.begin(), digits.end());                                 //gets rid of the initial 0

  if (X < 0) {
    negative = true;
  }
  X = abs(X);
  while (X > 0) {
    digits.insert(digits.begin(), X % 10);  //inserts individual digits at the beginning of the 'digits' vector
    X /= 10;
  }

  if (digits.empty()) {                                    //in case number is 0
    digits.push_back(0);
  }
}

//converting to type int
int Longnums::toInt() {
  int sum = 0, pow = 1;

  for(auto digit = digits.end() - 1; digit >= digits.begin(); digit--) {
    sum += ((*digit)) * pow;
    pow *= 10;
  }

  return sum;
}

//finding the absolute value of number
Longnums Longnums::absolute() {
  Longnums ans;

  ans.digits = digits;
  ans.negative = false;

  return ans;
}

//overloading input extraction operator
std::istream& operator>>(std::istream& input, Longnums& X) {
  X.digits.erase(X.digits.begin(), X.digits.end());
  char c;

  input.get(c);
  //first character distinguishing
  if (c == '+') {
    X.negative = false;
  } else if (c == '-') {
    X.negative = true;
  } else if ((int) c > 48 && (int) c <= 57) {
    X.digits.push_back((int) c - 48);
  }

  //now to the rest of the digits
  while (true) {
    input.get(c);
    if (isspace(c)) {
      //a space after the first input
      if (!X.digits.empty()) {
        break;
      }
    } else if (c == '0') {
      //there shouldn't be trailing zeroes
      if (!X.digits.empty()) {
        X.digits.push_back((int) c - 48);
      }
    } else if ((int) c > 48 && (int) c <= 57) {
      //a digit between 1 to 9
      X.digits.push_back((int) c - 48);
    } else {
      //anything else... exit
      exit(1);
    }
  }

  return input;
}

//overloading the output
std::ostream& operator<<(std::ostream& output, const Longnums& X) {
  if (X.negative) {
    output << "-";
  }

  for (int digit : X.digits) {
    output << digit;
  }

  return output;
}

//input method
int Longnums::get() {
  digits.erase(digits.begin(), digits.end());  //remove any initial value in 'digits'
  char c;
  //denotes each individual digit or the sign
  START:

  std::cin.get(c);

  if (c == '+') {
    negative = false;
  }

  else if (c == '-') {
    negative = true;
  }

  else if (int(c) >= 49 && int(c) <= 57) {  //if c is not a number aka can't be a digit
  //only numbers can be digits
    negative = false;
    digits.push_back(int(c) - 48);
  }

  else if (c == '0') {
    //no leading zeros
    negative = false;
  }

  else if (!isspace(c)) {                    //if c is anything but a whitespace
    std::cerr << std::endl << "No such sign" << std::endl;
    return 1;
    //error
  }

  else {
    goto START;
  }

  while (true) {
    std::cin.get(c);
    if (int(c) >= 49 && int(c) <= 57) {
      digits.push_back(int(c) - 48);
    }

    else if (c == '0') {
      if (!digits.empty()) {
        digits.push_back(int(c) - 48);
      }
    }

    else if (isspace(c)) {
      break;                         //return, tab or space terminates the input
    }

    else {
      //error
      std::cerr << std::endl << "Not a valid integer" << std::endl;
      digits.clear();
      digits.push_back(0);
      return 1;
    }
  }

  if (digits.empty()) {
    digits.push_back(0);
  }

  return 0;
}

//output function
int Longnums::put() {
  if (negative) {
    std::cout << "-";
  }

  for (auto digit : digits) {
    std::cout << (int)digit;
  }

  return 0;
}

//comparison functions
bool Longnums::operator<(Longnums X) {
  if (!negative) {
    if (X.negative) {
      return false;
    }

    else {
      if (digits.size() > X.digits.size()) {
        return false;
      }

      else if (digits.size() == X.digits.size()) {
        for (int i = 0; i < digits.size(); i++) {
          if (digits[i] > X.digits[i]) {
            return false;
          }

          else if (digits[i] < X.digits[i]) {
            return true;
          }
        }

        return false;
      }

      else {
        return true;
      }
    }
  }

  else {
    if (!X.negative) {
      return true;
    }

    else {
      if (digits.size() > X.digits.size()) {
        return true;
      }

      else if (digits.size() == X.digits.size()) {
        for (int i = 0; i < digits.size(); i++) {
          if (digits[i] > X.digits[i]) {
            return true;
          }

          else if (digits[i] < X.digits[i]) {
            return false;
          }
        }

        return false;
      }

      else {
        return false;
      }
    }
  }
}

bool Longnums::operator<(int X) {
  Longnums num2;
  num2 = X;
  return ((*this) < num2);
}

bool Longnums::operator>(Longnums X) {
  if (!negative) {
    if (X.negative) {
      return true;
    }

    else {
      if (digits.size() > X.digits.size()) {
        return true;
      }

      else if (digits.size() == X.digits.size()) {
        for (int i = 0; i < digits.size(); i++) {
          if (digits[i] > X.digits[i]) {
            return true;
          }

          else if (digits[i] < X.digits[i]) {
            return false;
          }
        }

        return false;
      }

      else {
        return false;
      }
    }
  }

  else {
    if (!X.negative) {
      return false;
    }

    else {
      if (digits.size() > X.digits.size()) {
        return false;
      }

      else if (digits.size() == X.digits.size()) {
        for (int i = 0; i < digits.size(); i++) {
          if (digits[i] > X.digits[i]) {
            return false;
          }

          else if (digits[i] < X.digits[i]) {
            return true;
          }
        }

        return false;
      }

      else {
        return true;
      }
    }
  }
}

bool Longnums::operator>(int X) {
  Longnums num2;
  num2 = X;
  return ((*this) > num2);
}

bool Longnums::operator==(Longnums X) {
  if (negative == X.negative) {
    if (digits == X.digits) {
      return true;
    }
  }

  return false;
}

bool Longnums::operator==(int X) {
  Longnums num2;
  num2 = X;
  return ((*this) == num2);
}

bool Longnums::operator>=(Longnums X) {
  if ((*this) > X || (*this) == X) {
    return true;
  }

  return false;
}

bool Longnums::operator>=(int X) {
  Longnums num2;
  num2 = X;
  return ((*this) >= num2);
}

bool Longnums::operator<=(Longnums X) {
  if ((*this) < X || (*this) == X) {
    return true;
  }

  return false;
}

bool Longnums::operator<=(int X) {
  Longnums num2;
  num2 = X;
  return ((*this) <= num2);
}

bool Longnums::operator!=(Longnums X) {
  if ((*this) == X) {
    return false;
  }

  return true;
}

bool Longnums::operator!=(int X) {
  Longnums num2;
  num2 = X;
  return ((*this) != num2);
}

Longnums Longnums::operator+(Longnums X)                              //Addition
    {
  Longnums answer;
  std::vector<int> sum;
  bool ansneg = false;
  int carryover = 0;
  std::vector<int> big, small;
  if (this->negative == X.negative) {
    //one must add
    if (this->negative) {
      ansneg = true;
      //the ans will be negative
    }

    //determining which number is big or small (only considering the length of digits)
    if (X > (*this)) {
      if (negative) {
        big = digits;
        small = X.digits;
      } else {
        big = X.digits;
        small = digits;
      }
    } else {
      if (!negative) {
        big = digits;
        small = X.digits;
      } else {
        big = X.digits;
        small = digits;
      }
    }

    while (big.size() != small.size()) {
      small.insert(small.begin(), 0);  //adds 0s to the start of 'small' so that length of digits is same
    }

    int temp = 0;

    for (int i = big.size() - 1; i >= 0; i--) {  //following algorithm is the traditional digit-by-digit method of addition
      temp = ((big[i] + small[i] + carryover) % 10);

      carryover = (big[i] + small[i] + carryover) / 10;

      sum.insert(sum.begin(), temp);
    }

    if (carryover > 0) {                                 //if the carryover is 1
      sum.insert(sum.begin(), carryover);
    }
    answer.digits = sum;
    answer.negative = ansneg;
  }

  else {
    //one must subtract the numbers
    Longnums temp;
    if (negative) {                 //for cases like -1 + 2 == 2 + (-1) == 2 - 1
      temp = this->absolute();
      answer = (X - temp);
    }

    else if (X.negative) {                    //for cases like 1 + (-2) == 1 - 2
      temp = X.absolute();
      answer = ((*this) - temp);
    }
  }

  return answer;
}

Longnums Longnums::operator+(int X)                       //adding to an integer
    {
  Longnums NUM2, Ans;
  NUM2 = X;

  Ans = (*this) + NUM2;
  return Ans;
}

Longnums Longnums::operator-(Longnums X) {
  if (negative == X.negative) {
    //subtract
    Longnums result;
    int maxlength = std::max(digits.size(), X.digits.size());
    std::vector<int> big, small;

    if (X == (*this)) {                                            //answer is 0
      return result;
    }

    else if (X > (*this)) {
      result.negative = true;
      if (negative) {  //big or small numbers by considering the length of digits
        big = this->digits;
        small = X.digits;
      } else {
        big = X.digits;
        small = this->digits;
      }
    }

    else {
      result.negative = false;
      if (!negative) {
        big = this->digits;
        small = X.digits;
      } else {
        big = X.digits;
        small = this->digits;
      }
    }

    std::vector<int> res;                           //resultant vector of digits

    while (big.size() != small.size()) {  //equate length of digits by adding 0s to the start of smaller size number
      small.insert(small.begin(), 0);
    }

    //big - small
    result.digits.pop_back();
    int ans;
    for (int i = maxlength - 1; i >= 0; i--) {  //traditional method of subtraction digit by digit from units place
      ans = big[i] - small[i];
      if (ans < 0) {
        ans += 10;
        big[i - 1] = big[i - 1] - 1;
      }

      result.digits.insert(result.digits.begin(), ans);
    }

    //this has trailing zeros which must be removed
    std::vector<int>::iterator pos;
    for (auto i = result.digits.begin(); i < result.digits.end(); i++) {
      if (*i != 0) {
        pos = i;
        break;
      }
    }

    result.digits.erase(result.digits.begin(), pos);
    return result;
  }

  else {
    //add
    Longnums number, answer;
    number.digits = X.digits;
    number.negative = !X.negative;

    answer = (*this) + number;
    return answer;
  }
}

Longnums Longnums::operator-(int X)                //subtracting with an integer
    {
  Longnums NUM2, Ans;
  NUM2 = X;

  Ans = (*this) - NUM2;
  return Ans;
}

Longnums Longnums::operator*(Longnums X) {
  Longnums answer;

  if((*this) == 0 || X == 0) {
    return answer;
  }

  //for negative numbers
  answer.negative = negative ^ X.negative;

  if((*this) < INT_MAX && X < INT_MAX) {
    long int product;
    long int _this = toInt();
    long int _x = X.toInt();
    product = _this * _x;
    //std::cout << _this << " times " << _x << " gives product " << product << std::endl;

    answer = product;
    //std::cout << "with answer as " << answer << std::endl;
  } else if((*this) < INT_MAX){
    long int multiplier = this->toInt();
    answer = X * multiplier;
  } else if(X < INT_MAX) {
    long int multiplier = X.toInt();
    answer = (*this) * multiplier;
  } else {
    //determine the value of the position to split the numbers
    //(*this) will be split into x1, x2 and X will be split into y1 and y2
    //z2 = x1y1, z0 = x2y2 and z1 = x1y2 + x2y1 = (x1 + x2) (y1 + y2) - z2 - z0
    //to be returned: z2 * b^2 + z1 * b + z0 where b is 10 ^ midpos

    //determining midpos
    int midpos, numZero;
    if((*this) >= X) {
      midpos = this->digits.size() / 2;
      numZero = this->digits.size() - midpos;
    } else {
      midpos = X.digits.size() / 2;
      numZero = X.digits.size() - midpos;
    }

    //std::cout << midpos << " " << numZero << std::endl;

    //declaring x1, x2, y1, y2 using vector constructor
    Longnums x1, x2, y1, y2, z0, z1, z2;
    if(this->digits.size() <= numZero) {
      x1 = 0;
      x2.digits = this->digits;
    } else {
      x1.digits = std::vector<int>(this->digits.begin(), this->digits.end() - numZero);
      x2.digits = std::vector<int>(this->digits.end() - numZero, this->digits.end());
    }

    if(X.digits.size() <= numZero) {
      y1 = 0;
      y2.digits = X.digits;
    } else {
      y1.digits = std::vector<int>(X.digits.begin(), X.digits.end() - numZero);
      y2.digits = std::vector<int>(X.digits.end() - numZero, X.digits.end());
    }

    //removing trailing zeroes from x2 and y2
    while((*x2.digits.begin()) == 0 && x2.digits.size() > 1) {
      x2.digits.erase(x2.digits.begin());
    }

    while((*y2.digits.begin()) == 0 && y2.digits.size() > 1) {
      y2.digits.erase(y2.digits.begin());
    }


    //std::cout << *this << " as X splits into " << x1 << " and " << x2 << std::endl;
    //std::cout << X << " as Y splits into " << y1 << " and " << y2 << std::endl;


    //to find z2
    z2 = x1 * y1;
    //std::cout << "z2 for " << x1 << " and " << y1 << " calculated" << std::endl;

    //to find z0
    //std::cout << "z1 is " << x2 << " times " << y2 << std::endl;
    z0 = x2 * y2;
    //std::cout << "z0 for " << x2 << " and " << y2 << " calculated" << std::endl;
    //to find z1
    {
      Longnums sumX, sumY, prodSums;
      sumX = x1 + x2;
      sumY = y1 + y2;
      prodSums = sumX * sumY;

      z1 = prodSums - z2 - z0;
      //std::cout << "product of sums is " << prodSums << std::endl;
      //std::cout << "No issues for z1" << std::endl;
    }

    //get the answer
    //first append twice the number of zeros of numZeros to z2 and numZeros to z1
    for(int i = 1; i <= 2 * numZero; i++) {
      if(z2 != 0) {
        z2.digits.push_back(0);
      }

      if(i <= numZero && z1 != 0) {
        z1.digits.push_back(0);
      }
    }

    //std::cout << (*this) << " times " << X << std::endl;

    //std::cout << "Zeroes appended" << std::endl;
    //std::cout << "answer will be " << z2 << " + " << z1 << " + " << z0 << std::endl;

    //answer  = z2 + z11 + z0
    answer = z2 + z1 + z0;

    //std::cout << "x1 is " << x1 << " and x2 is " << x2 << std::endl
    //          << "y1 is " << y1 << " and y2 is " << y2 << std::endl
    //          << "z1 is " << z1 << "\nz2 is " << z2 << "\nz0 is " << z0 << std::endl;
  }



  /*
  Longnums product;
  int carryover, count = 0, prod_temp;
  for (auto multiplier = X.digits.end() - 1; multiplier >= X.digits.begin();
      multiplier--) {
    product.digits.erase(product.digits.begin(), product.digits.end());  //algorithm is traditional long multiplication algorithm
    carryover = 0;
    for (int i = 0; i < count; i++) {
      product.digits.push_back(0);  //number of zeros the temporaryproduct should have at the end
    }

    for (auto multiplicand = digits.end() - 1; multiplicand >= digits.begin();
        multiplicand--) {
      prod_temp = ((*multiplicand) * (*multiplier)) + carryover;
      carryover = prod_temp / 10;
      prod_temp %= 10;
      product.digits.insert(product.digits.begin(), prod_temp);
    }
    if (carryover > 0) {
      product.digits.insert(product.digits.begin(), carryover);
    }

    answer = answer + product;

    count++;
  }
  */

  return answer;
}

Longnums Longnums::operator*(long int X) {
  Longnums answer;
  long int product = 0, carry = 0;
  answer.digits.erase(answer.digits.begin(), answer.digits.end());

  for(int i = (this->digits).size() - 1; i >= 0; i--) {
    product = X * (this->digits)[i] + carry;
    carry = product / 10;
    product = product % 10;
    answer.digits.insert(answer.digits.begin(), product);
  }
  while (carry > 0) {
    answer.digits.insert(answer.digits.begin(), carry % 10);
    carry /= 10;
  }

  return answer;
}

Longnums Longnums::operator/(Longnums X) {
  Longnums quotient, divisor, dividend;
  dividend.digits = digits;
  divisor.digits = X.digits;

  if (dividend < divisor) {
    return quotient;       //quotient is initialized to 0 by default constructor
  }

  else if (dividend == divisor) {
    quotient.digits[0] = 1;                          //the 0 gets converted to 1

    if (negative != X.negative) {
      quotient.negative = true;
    } else {
      quotient.negative = false;
    }

    return quotient;
  }

  else if (divisor == 0) {	//check iif divisor is 0, since quotient as of now is 0 as well
    std::cerr << "Cannot divide by 0" << std::endl;
    return quotient;
  }

  else {
    Longnums part_rem, temp_dividend;    //partial remainder, temporary dividend
    int q;                                             //a digit of the quotient

    temp_dividend.digits = std::vector<int>(dividend.digits.begin(), dividend.digits.begin() + divisor.digits.size());
    //using the constructor for vector
    quotient.digits.pop_back();

    for (auto iter = dividend.digits.begin() + divisor.digits.size() - 1;
        iter < dividend.digits.end(); iter++) {
      for (int i = 1; i <= 10; i++) {  //the following algorithm is the same as the long division algorithm
        if ((divisor * i) > temp_dividend) {
          q = i - 1;
          break;
        }
      }

      quotient.digits.push_back(q);
      part_rem = divisor * q;
      part_rem = temp_dividend - part_rem;

      if (part_rem.digits[0] == 0) {
        temp_dividend.digits.erase(temp_dividend.digits.begin(),
                                   temp_dividend.digits.end());
      }

      else {
        temp_dividend.digits = part_rem.digits;
      }

      if (iter != dividend.digits.end() - 1) {
        temp_dividend.digits.push_back(*(iter + 1));
      }

    }

    //remove the trailing zero if any
    if (quotient.digits[0] == 0) {
      quotient.digits.erase(quotient.digits.begin());
    }

    if (negative != X.negative) {
      quotient.negative = true;
    } else {
      quotient.negative = false;
    }

    return quotient;
  }
}

Longnums Longnums::operator/(int X) {
  Longnums NUM2, Ans;
  NUM2 = X;
  Ans = (*this) / NUM2;
  return Ans;
}

Longnums Longnums::operator%(Longnums X) {
  Longnums quotient;
  Longnums remainder;

  quotient = (*this) / X;

  remainder = (X * quotient);

  remainder = (*this) - remainder;

  return remainder;
}

Longnums Longnums::operator%(int X) {
  Longnums NUM2, Ans;
  NUM2 = X;
  Ans = (*this) % NUM2;
  return Ans;
}
