# LongNums
A custom made proof-of-concept class for handling numbers with large number of digits.

The numbers in this class are stored as strings of digits with a boolean associated with each object denoting whether said 
number is negative or positive.

The class first will work for only integers with primary expressions (+, -, \*, /, %), but support for floating pointer
integers will be added, followed by more scientific operators like sqrt, pow, etc.

*Algorithms used*-
For addition and subtraction, the basic digit-by-digit method is used, taking individual digits from units place and adding/subtracting them with each other, using a carry-over digit if necessary.
For multiplication, the *Long multiplication* method is used.
For division, the *Long division* algorithm is used.
