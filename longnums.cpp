#include <iostream>
#include <algorithm>
#include <climits>
#include <math.h>
#include <exception>

#include "longnums.hpp"

/*  The following few functions are constructors, including
 *  a default constructor and a copy constructor
 *
 *  The destructor remains empty for now
 */

//default constructor
Longnums::Longnums() {                       //By default every object will be 0
  digits.push_back(0);
  negative = false;
}

//destructor
Longnums::~Longnums() {
}

//copy constructor
Longnums::Longnums(const Longnums& X) {
  //equating the two vectors
  digits = X.digits;

  //equating the booleans
  negative = X.negative;
}

/******************************************************************************/

/*  The next two functions involve the conversions of types from Longnums to int
 *  and from int (or long int) to Longnums, as well as string to Longnums
 */

//equate Longnums object to an int
void Longnums::operator=(const long int& X) {
	//gets rid of the initial 0
  digits.erase(digits.begin(), digits.end());
  //determine if negative
  if (X < 0) {
    negative = true;
  }

  //find absolute value of X to extract digits one by one
  long int rVal = std::abs(X);

  //getting individual digits
  while (rVal > 0) {
    digits.insert(digits.begin(), rVal % 10);  //inserts individual digits at the beginning of the 'digits' vector
    rVal /= 10;
  }

  //if vector is empty by any chance
  if (digits.empty()) {                                    //in case number is 0
    digits.push_back(0);
  }
}

//converting to type int
int Longnums::toInt() {
  int sum = 0, pow = 1;

  for(std::vector<int>::iterator digit = digits.end() - 1; digit >= digits.begin(); digit--) {
    sum += ((*digit)) * pow;
    pow *= 10;
  }

  return sum;
}

void Longnums::operator=(const std::string& num) {
	digits.erase(digits.begin(), digits.end());

	if(num[0] == '-') {
		negative = true;
	} else if(num[0] == '+') {
		negative = false;
	} else if ((int)num[0] > 48 && (int)num[0] < 59) {
		negative = false;
		digits.push_back((int)num[0] - 48);
	} else {
		return;
	}

	for(int i = 1; i < num.length(); i++) {
		if((int)num[0] > 48 && (int)num[0] < 59) {
			digits.push_back((int)num[i] - 48);
		} else if(num[0] == '0') {
			if(!digits.empty()) {
				digits.push_back(0);
			}
		} else {
			negative = false;
			digits = std::vector<int>(1, 0);
			return;
		}
	}

	if(digits.size() == 0) {
		negative = false;
		digits.push_back(0);
	}
}

/******************************************************************************/

//finding the absolute value of number- just the digits without the sign
Longnums Longnums::absolute() {
  Longnums ans;

  ans.digits = digits;
  ans.negative = false;

  return ans;
}

/******************************************************************************/

/*  The next two functions overload the extraction and insertion operators (>>
 *  and <<) so that one can use std::cin and std::cout to take input and display
 *  output
 */

//overloading input extraction operator
std::istream& operator>>(std::istream& input, Longnums& X) {
  X.digits.erase(X.digits.begin(), X.digits.end());
  char c;

	//getting the first character
	do {
  	input.get(c);
  	if (c == '+') {
    	X.negative = false;
  	} else if (c == '-') {
	    X.negative = true;
	  } else if ((int) c > 48 && (int) c <= 57) {
    	X.digits.push_back((int) c - 48);
  	}
	} while(isspace(c));	//can't have first character being a space... it simply won't do

  //now for the rest of the digits
  while (true) {
    input.get(c);
    if (isspace(c)) {
			break;
    } else if ((int) c > 48 && (int) c <= 57) {
      //a digit between 1 to 9
      X.digits.push_back((int) c - 48);
    } else if(c == '0') {
			if(!X.digits.empty()) {
				X.digits.push_back(0);
			}
		} else {
      //anything else... exit
			X.negative = false;
			X.digits = std::vector<int>(1, 0);
			return input;
    }
  }

	if(X.digits.empty()) {
		X.negative = false;
		X.digits.push_back(0);
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

/******************************************************************************/

/*  The following functions in the section below simply compare two Longnum
 *  objects or a Longnum object and an int.
 *
 *  Operators were ovverloaded for this effect.
 */

//comparison functions
bool Longnums::operator<(const Longnums& X) {
  if (!negative) {
    if (X.negative) {
      return false;
    }

    else {
      if (digits.size() > X.digits.size()) {
        return false;
      } else if (digits.size() == X.digits.size()) {
        for (int i = 0; i < digits.size(); i++) {
          if (digits[i] >= X.digits[i]) {
            return false;
          } else {
            return true;
          }
        }

        return false;
      } else {
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
      } else if (digits.size() == X.digits.size()) {
        for (int i = 0; i < digits.size(); i++) {
          if (digits[i] > X.digits[i]) {
            return true;
          } else if (digits[i] < X.digits[i]) {
            return false;
          }
        }

        return false;
      } else {
        return false;
      }
    }
  }
}

bool Longnums::operator<(const int& X) {
  Longnums num2;
  num2 = X;
  return ((*this) < num2);
}

bool Longnums::operator>(const Longnums& X) {
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

bool Longnums::operator>(const int& X) {
  Longnums num2;
  num2 = X;
  return ((*this) > num2);
}

bool Longnums::operator==(const Longnums& X) {
  if (negative == X.negative) {
    if (digits == X.digits) {
      return true;
    }
  }

  return false;
}

bool Longnums::operator==(const int& X) {
  Longnums num2;
  num2 = X;
  return ((*this) == num2);
}

bool Longnums::operator>=(const Longnums& X) {
  if ((*this) > X || (*this) == X) {
    return true;
  }

  return false;
}

bool Longnums::operator>=(const int& X) {
  Longnums num2;
  num2 = X;
  return ((*this) >= num2);
}

bool Longnums::operator<=(const Longnums& X) {
  if ((*this) < X || (*this) == X) {
    return true;
  }

  return false;
}

bool Longnums::operator<=(const int& X) {
  Longnums num2;
  num2 = X;
  return ((*this) <= num2);
}

bool Longnums::operator!=(const Longnums& X) {
  if ((*this) == X) {
    return false;
  }

  return true;
}

bool Longnums::operator!=(const int& X) {
  Longnums num2;
  num2 = X;
  return ((*this) != num2);
}

/******************************************************************************/

/*  The following set of functions involve the method for the Longnums object to
 *  deal with various mathematical operations like addition, subtraction,
 *  multiplication and division
 *  These may be converted into templates, along with the other comparison
 *  functions
 */

Longnums Longnums::operator+(Longnums X) {                             //Addition
  Longnums answer;
  std::vector<int> sum;
  bool ansneg = false;
  int carryover = 0;
  //std::vector<int> big, small;
  if (this->negative == X.negative) {
    //one must add
    if (this->negative) {
      ansneg = true;
      //the ans will be negative
    }

    int temp = 0;

    for (int i = digits.size() - 1, j = X.digits.size() - 1;; i--, j--) {  //following algorithm is the traditional digit-by-digit method of addition
			temp = carryover;
			if(i >= 0 && j >= 0) {
				temp += digits[i] + X.digits[j];
			} else if(i >= 0) {
				temp += digits[i];
			} else if(j >= 0) {
				temp += X.digits[j];
			} else {
				break;
			}

			carryover = temp / 10;
			temp %= 10;

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

Longnums Longnums::operator+(int X) {                     //adding to an integer
  Longnums NUM2, Ans;
  NUM2 = X;

  Ans = (*this) + NUM2;
  return Ans;
}

Longnums Longnums::operator-(Longnums X) {
	if(negative ==  X.negative) {
		Longnums answer;
		if((*this) >= X) {
			int temp;
			bool borrow = false;
			answer.digits.erase(answer.digits.begin(), answer.digits.end());
			for(int i = digits.size()-1, j = X.digits.size() - 1;i >= 0;i--, j--) {
				temp = digits[i];
				if(borrow) {
					temp--;
				}
				if(j >= 0) {
					temp -= X.digits[j];
				}
				if(temp < 0) {
					temp += 10;
					borrow = true;
				} else {
					borrow = false;
				}
				answer.digits.insert(answer.digits.begin(), temp);
			}
			
			while((*answer.digits.begin()) == 0 && answer.digits.size() > 1) {
				answer.digits.erase(answer.digits.begin());
			}
		} else {
			answer = X - (*this);
			answer.negative=true;
		}

		return answer;
	} else {
    //add
    Longnums number, answer;
    number.digits = X.digits;
    number.negative = !X.negative;

    answer = (*this) + number;
    return answer;
  }

  /*if (negative == X.negative) {
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
  }*/
}

Longnums Longnums::operator-(int X)                //subtracting with an integer
    {
  Longnums NUM2, Ans;
  NUM2 = X;

  Ans = (*this) - NUM2;
  return Ans;
}

Longnums Longnums::operator*(Longnums X) {
	//std::cout << (*this) << " " << X << " ";
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

    //to find z2
    z2 = x1 * y1;

    //to find z0
		z0 = x2 * y2;
		
    //to find z1
    {
      Longnums sumX, sumY, prodSums;
      sumX = x1 + x2;
      sumY = y1 + y2;
      prodSums = sumX * sumY;

      z1 = prodSums - z2 - z0;
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
		
    answer = z2 + z1 + z0;
	}
	
	//std::cout  << answer << std::endl;

  return answer;
}

Longnums Longnums::operator*(long int X) {
	if(X == 0) {
		return Longnums();
	} else {
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
}

Longnums Longnums::operator/(Longnums X) {
  Longnums quotient;//, divisor, dividend;
  //dividend.digits = digits;
  //divisor.digits = X.digits;

  /*if ((*this) < X) {
    return quotient;       //quotient is initialized to 0 by default constructor
  } else if ((*this) == X) {
    quotient.digits[0] = 1;                          //the 0 gets converted to 1

    if (negative != X.negative) {
      quotient.negative = true;
    } else {
      quotient.negative = false;
    }

    return quotient;
	} else */
	if(digits.size() < X.digits.size()){
		return quotient;
	}if (X == 0) {	//check if divisor is 0, since quotient as of now is 0 as well
    throw "Cannot divide by 0";
  } else {
/*
    Longnums part_rem, temp_dividend;    //partial remainder, temporary dividend
    int q;                                             //a digit of the quotient


    temp_dividend.digits = std::vector<int>(digits.begin(), digits.begin() + X.digits.size());
    //using the constructor for vector
    quotient.digits.pop_back();

    for (auto iter = digits.begin() + X.digits.size() - 1;
        iter < digits.end(); iter++) {
      for (int i = 1; i <= 10; i++) {  //the following algorithm is the same as the long division algorithm
        if ((X * i) > temp_dividend) {
          q = i - 1;
          break;
        }
      }
			
      quotient.digits.push_back(q);
      part_rem = X * q;
      part_rem = temp_dividend - part_rem;
			

      if (part_rem == 0) {
        temp_dividend.digits.erase(temp_dividend.digits.begin(),
                                   temp_dividend.digits.end());
      }

      else {
        temp_dividend.digits = part_rem.digits;
      }

      if (iter != digits.end() - 1) {
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
	*/
	
		//algorithm using repeated subtractions
		Longnums temp_dividend = (*this), temp_divisor = X;
		Longnums q;
		q = (long int) std::pow(10, digits.size() - X.digits.size());
		temp_dividend = temp_dividend - temp_divisor * q;
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
