#ifndef LONGNUMS_H
#define LONGNUMS_H

#include <vector>

class LongNumber {
	std::vector<int> digits;
	bool negative;

public:
	//constructor
	LongNumber();
	LongNumber(const LongNumber&);
	LongNumber(const long int&);

	//destructor
	~LongNumber();

	//overloading input and output operators
	friend std::ostream& operator<<(std::ostream& output, const LongNumber& X);

	friend std::istream& operator>>(std::istream& input, LongNumber& X);


	//comparing numbers
	bool operator<(const LongNumber&);
	bool operator>(const LongNumber&);
	bool operator==(const LongNumber&);
	bool operator<=(const LongNumber&);
	bool operator>=(const LongNumber&);
	bool operator!=(const LongNumber&);

	//Equality functions
	void operator=(const long int&);
	void operator=(const std::string&);

	//converting to int
	long int toLong();

	//absolute value
	LongNumber absolute();

	//primary operations(binary) - adding, subtracting, multiplying and dividing
	LongNumber operator+(LongNumber);
	LongNumber operator-(LongNumber);
	LongNumber operator*(LongNumber);
	LongNumber operator*(long int);
	LongNumber operator/(LongNumber);
	LongNumber operator%(LongNumber);

	void operator+=(LongNumber);
	void operator-=(LongNumber);
	void operator*=(LongNumber);
	void operator/=(LongNumber);
	void operator%=(LongNumber);

	//operations (unary)
	LongNumber operator++();
	LongNumber operator++(int);
	LongNumber operator--();
	LongNumber operator--(int);
};

#endif // LONGNUMS_H
