#include <iostream>
#include <climits>
#include <limits>
#include <cmath>
#include <algorithm>
#include <exception>
#include "longnums.hpp"

const int BASE = std::pow(10, std::to_string(std::numeric_limits<int>::max()).length() - 1);

// defining the exception class for DivideByZeroException
class DivideByZeroException : public std::exception {
	virtual const char* what() const throw() {
		return "Divided by 0";
	}
};

class InvalidInputException : public std::exception {
	virtual const char* what() const throw() {
		return "Invalid input";
	}
};

/*  The following few functions are constructors, including
*  a default constructor and a copy constructor
*
*  The destructor remains empty for now
*/

//default constructor
LongNumber::LongNumber() {                       //By default every object will be 0
	digits.push_back(0);
	negative = false;
}

//destructor
LongNumber::~LongNumber() {
}

//copy constructor
LongNumber::LongNumber(const LongNumber& X) {
	//equating the two vectors
	digits = X.digits;

	//equating the booleans
	negative = X.negative;
}

LongNumber::LongNumber(const long int& X) {
	(*this) = X;
}

/******************************************************************************/

/*  The next two functions involve the conversions of types from LongNumber to int
*  and from int (or long int) to LongNumber, as well as string to LongNumber
*/

//equate LongNumber object to an int
void LongNumber::operator=(const long int& X) {
	(*this) = std::to_string(X);
}

//converting to type long int
long int LongNumber::toLong() {
	long int sum = 0, pow = 1;

	for(std::vector<int>::iterator digit = digits.begin(); digit < digits.end(); digit++) {
		sum += ((*digit)) * pow;
		pow *= BASE;
	}

	if(negative) {
		sum *= -1;
	}

	return sum;
}

void LongNumber::operator=(const std::string& num) {
	digits.erase(digits.begin(), digits.end());
	int element = 0, i;

	for(i = num.length() - 9; i > 0; i = i - 9) {
		element = 0;
		int multiplier = 1;
		int count = 8;
		while(count >= 0) {
			if(num[i + count] >= '0' && num[i + count] <= '9') {
				element += ((int)num[i + count] - 48) * multiplier;
				multiplier *= 10;
				count--;
			} else {
				digits.erase(digits.begin(), digits.end());
				digits.push_back(0);
				return;
			}
		}
		digits.push_back(element);
	}

	i = i + 9 - 1;
	element = 0;
	int multiplier = 1;
	while(i >= 1) {
		if(num[i] >= '0' && num[i] <= '9') {
			element += ((int)num[i] - 48) * multiplier;
			multiplier *= 10;
			i--;
		} else {
			throw InvalidInputException();
		}
	}

	if(num[0] == '+') {
		negative = false;
	} else if(num[0] == '-') {
		negative = true;
	} else if (num[0] >= '0' && num[0] <= '9') {
		negative = false;
		element += ((int)num[i] - 48) * multiplier;
	} else {
			throw InvalidInputException();
	}

	if(element != 0) {
		digits.push_back(element);
	}

	while(!digits.empty() && (*(digits.end() - 1) == 0)) {
		digits.erase(digits.end() - 1);
	}

	if(digits.empty()) {
		negative = false;
		digits.push_back(0);
	}
}

/******************************************************************************/

//finding the absolute value of number- just the digits without the sign
LongNumber LongNumber::absolute() {
	LongNumber ans;

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
std::istream& operator>>(std::istream& input, LongNumber& X) {
	std::string number;
	input >> number;
	X = number;

	return input;
}

//overloading the output
std::ostream& operator<<(std::ostream& output, const LongNumber& X) {
	std::string printed;
	if (X.negative) {
		output << "-";
	}

	output << *(X.digits.end()-1);

	for(int i = X.digits.size() - 2; i >= 0; i--) {
		printed = std::to_string(X.digits[i]);
		while(printed.length() < 9) {
			printed = "0" + printed;
		}
		output << printed;
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
bool LongNumber::operator<(const LongNumber& X) {
	if (!negative) {
		if (X.negative) {
			return false;
		}

		else {
			if (digits.size() > X.digits.size()) {
				return false;
			} else if (digits.size() == X.digits.size()) {
				for (int i = digits.size() - 1; i >= 0; i--) {
					if (digits[i] < X.digits[i]) {
						return true;
					} else if(digits[i] > X.digits[i]){
						return false;
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
				for (int i = digits.size() - 1; i >= 0; i--) {
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

bool LongNumber::operator>(const LongNumber& X) {
	return !(*this <= X);
}

bool LongNumber::operator==(const LongNumber& X) {
	return (negative == X.negative && digits == X.digits);
}

bool LongNumber::operator>=(const LongNumber& X) {
	return ((*this) > X || (*this) == X);
}

bool LongNumber::operator<=(const LongNumber& X) {
	return ((*this) < X || (*this) == X);
}

bool LongNumber::operator!=(const LongNumber& X) {
	return !((*this) == X);
}

/******************************************************************************/

/*  The following set of functions involve the method for the LongNumber object to
*  deal with various mathematical operations like addition, subtraction,
*  multiplication and division
*  These may be converted into templates, along with the other comparison
*  functions
*/

LongNumber LongNumber::operator+(LongNumber X) {                             //Addition
	LongNumber answer;
	answer.digits.pop_back();
	int carryover = 0;
	//std::vector<int> big, small;
	if (this->negative == X.negative) {
		//one must add
		if (this->negative) {
			answer.negative = true;
			//the ans will be negative
		}

		long int temp = 0;

		for (int i = 0, j = 0;; i++, j++) {  //following algorithm is the traditional digit-by-digit method of addition
			temp = carryover;
			if(i < digits.size() && j < X.digits.size()) {
				temp += digits[i] + X.digits[j];
			} else if(i < digits.size()) {
				temp += digits[i];
			} else if(j < X.digits.size()) {
				temp += X.digits[j];
			} else {
				break;
			}

			carryover = temp / BASE;
			temp %= BASE;

			answer.digits.push_back(temp);
		}

		if (carryover > 0) {                                 //if the carryover is 1
			answer.digits.push_back(carryover);
		}
	}

	else {
		//one must subtract the numbers
		LongNumber temp;
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

LongNumber LongNumber::operator-(LongNumber X) {
	if(negative ==  X.negative) {
		LongNumber answer;
		if(this->absolute() >= X.absolute()) {
			int temp;
			bool borrow = false;
			answer.digits.erase(answer.digits.begin(), answer.digits.end());
			for(int i = 0, j = 0;i < digits.size();i++, j++) {
				temp = digits[i];
				if(borrow) {
					temp--;
				}
				if(j < X.digits.size()) {
					temp -= X.digits[j];
				}
				if(temp < 0) {
					temp += BASE;
					borrow = true;
				} else {
					borrow = false;
				}
				answer.digits.push_back(temp);
			}

			while(*(answer.digits.end()-1) == 0 && answer.digits.size() > 1) {
				answer.digits.erase(answer.digits.end()-1);
			}

			if(answer != 0) {
				answer.negative = negative;
			}
		} else {
			answer = X - (*this);
			if(answer != 0) {
				answer.negative=!negative;
			}
		}

		return answer;
	} else {
		//add
		LongNumber number, answer;
		number.digits = X.digits;
		number.negative = !X.negative;

		answer = (*this) + number;
		return answer;
	}
}

LongNumber LongNumber::operator*(LongNumber X) {
	LongNumber answer;

	if((*this) == 0 || X == 0) {
		return answer;
	}

	if(this->absolute() < std::numeric_limits<int>::max()){
		long int multiplier = this->absolute().toLong();
		answer = X * multiplier;
	} else if(X.absolute() < std::numeric_limits<int>::max()) {
		long int multiplier = X.absolute().toLong();
		answer = (*this) * multiplier;
	} else {
		//determine the value of the position to split the numbers
		//(*this) will be split into x1, x2 and X will be split into y1 and y2
		//z2 = x1y1, z0 = x2y2 and z1 = x1y2 + x2y1 = (x1 + x2) (y1 + y2) - z2 - z0
		//to be returned: z2 * b^2 + z1 * b + z0 where b is BASE ^ midpos

		//determining midpos
		int midpos, numZero;
		if((*this) >= X) {
			midpos = this->digits.size() / 2;
			//numZero = this->digits.size() - midpos;
			numZero = midpos;
		} else {
			midpos = X.digits.size() / 2;
			//numZero = X.digits.size() - midpos;
			numZero = midpos;
		}

		//declaring x1, x2, y1, y2 using vector constructor
		LongNumber x1, x2, y1, y2, z0, z1, z2;
		if(this->digits.size() <= numZero) {
			x1 = 0;
			x2.digits = this->digits;
		} else {
			x1.digits = std::vector<int>(this->digits.begin() + numZero, this->digits.end());
			x2.digits = std::vector<int>(this->digits.begin(), this->digits.begin() + numZero);
		}

		if(X.digits.size() <= numZero) {
			y1 = 0;
			y2.digits = X.digits;
		} else {
			y1.digits = std::vector<int>(X.digits.begin() + numZero, X.digits.end());
			y2.digits = std::vector<int>(X.digits.begin(), X.digits.begin() + numZero);
		}

		//removing trailing zeroes from x2 and y2
		while(*(x2.digits.end() - 1) == 0 && x2.digits.size() > 1) {
			x2.digits.erase(x2.digits.end() - 1);
		}

		while(*(y2.digits.end() - 1) == 0 && y2.digits.size() > 1) {
			y2.digits.erase(y2.digits.end() - 1);
		}

		//to find z2
		z2 = x1 * y1;

		//to find z0
		z0 = x2 * y2;

		//to find z1
		{
			LongNumber sumX, sumY, prodSums;
			sumX = x1 + x2;
			sumY = y1 + y2;
			prodSums = sumX * sumY;

			z1 = prodSums - z2 - z0;
		}		

		//get the answer
		//first append twice the number of zeros of numZeros to z2 and numZeros to z1
		for(int i = 1; i <= 2 * numZero; i++) {
			if(z2 != 0) {
				z2 = z2 * BASE;
			}

			if(i <= numZero && z1 != 0) {
				z1 = z1 * BASE;
			}
		}
		answer = z2 + z1 + z0;
	}

	answer.negative = negative ^ X.negative;

	return answer;
}

LongNumber LongNumber::operator*(long int X) {
	if(X == 0) {
		return LongNumber();
	} else {
	LongNumber answer;
	long int product = 0, carry = 0;
	answer.digits.erase(answer.digits.begin(), answer.digits.end());

	for(int i = 0; i < digits.size(); i++) {
		product = X * (digits)[i] + carry;
		carry = product / BASE;
		product = product % BASE;
		answer.digits.push_back(product);
	}
	while (carry > 0) {
		answer.digits.push_back(carry % BASE);
		carry /= BASE;
	}

	return answer;
	}
}

LongNumber LongNumber::operator/(LongNumber X) {
	LongNumber quotient;
	if (X == 0) {
		//check if divisor is 0
		throw DivideByZeroException();
	} else if(digits.size() < X.digits.size()){
		return quotient;
	} else {		
		//following division algorithm uses Algorithm D from the Art of Computer Programming
		if(X.digits.size() > 1) {
			LongNumber dividend;
			LongNumber divisor;
			quotient.digits.pop_back();
			//Step 1- Normalize the divisor
			int normalFactor = (BASE) / (*(X.digits.end() - 1) + 1);
			dividend = absolute() * normalFactor;
			if(dividend.digits.size() == digits.size()) {
				dividend.digits.push_back(0);
			}
			divisor = X.absolute() * normalFactor;

			int n = X.digits.size();

			//step 2 and 7- loop
			for(int iter = (digits.size() - X.digits.size()); iter >= 0; iter--) {
				//step 3- approximating quotient
				long int q = (((long int)dividend.digits[iter + n] * BASE) + dividend.digits[iter + n - 1]) / divisor.digits[n-1];
				long int r = (((long int)dividend.digits[iter + n] * BASE) + dividend.digits[iter + n - 1]) % divisor.digits[n-1];
				
				int x = 0;
				bool flag;
				do {
					flag = false;
					if(q == BASE || 
					((long int)(q * divisor.digits[n-2]) > (r * BASE) + dividend.digits[iter + n - 2])) {
						q -= 1;
						r += divisor.digits[n-1];
						flag = true;
					}

					x++;
				} while(r < BASE && flag);

				//step 4- multiply and subtract
				LongNumber part_dividend;
				part_dividend.digits = std::vector<int>(dividend.digits.begin() + iter, dividend.digits.begin() + iter + n + 1);
				part_dividend = part_dividend - (divisor * q);

				if(part_dividend.negative) {
					//step 6- add back
					part_dividend = part_dividend.absolute() + divisor;
					part_dividend.digits.pop_back(); // ignoring carry generated
				}

				for(int i = iter; i < dividend.digits.size(); i++) {
					if(i - iter >= part_dividend.digits.size()) {
						dividend.digits[i] = 0;
					} else {
						dividend.digits[i] = part_dividend.digits[i - iter];
					}
				}
				
				quotient.digits.push_back(q);
			}
		} else {
			long int r = 0;
			for(int i = digits.size() - 1; i >= 0; i--) {
				quotient.digits.push_back((long int)(r * BASE + digits[i]) / X.digits[0]);
				
				r = (long int)(r * BASE + digits[i]) % X.digits[0];
				
			}
		}

		std::reverse(quotient.digits.begin(), quotient.digits.end());

		while(*(quotient.digits.end()-1) == 0 && quotient.digits.size() > 1) {
			quotient.digits.erase(quotient.digits.end()-1);
		}

		if(quotient != 0) {
			quotient.negative = negative ^ X.negative;
		}

		return quotient;
	}
}

LongNumber LongNumber::operator%(LongNumber X) {
	LongNumber quotient;
	LongNumber remainder;

	quotient = (*this) / X;
	
	remainder = (*this) - (X * quotient);

	return remainder;
}

void LongNumber::operator+=(LongNumber X) {
	*this = (*this + X);
}

void LongNumber::operator-=(LongNumber X) {
	*this = *this - X;
}

void LongNumber::operator*=(LongNumber X) {
	*this = *this * X;
}

void LongNumber::operator/=(LongNumber X) {
	*this = *this / X;
}

void LongNumber::operator%=(LongNumber X) {
	*this = *this % X;
}

// unary operators
LongNumber LongNumber::operator++() {
	*this += 1;
	return *this;
}

LongNumber LongNumber::operator++(int) {
	LongNumber temp = *this;
	++(*this);
	return temp;
}

LongNumber LongNumber::operator--() {
	*this -= 1;
	return *this;
}

LongNumber LongNumber::operator--(int) {
	LongNumber temp = *this;
	--(*this);
	return temp;
}