# LongNums
A custom made proof-of-concept class for arbitrary precision arithmetic.
<br/>
Supports only integers.

---

# Table of Operations

<h3>Key for examples-</h3></br>
Capitalised variables indicate `LongNumber` objects. Lower case variables indicate `int`s or `long`s.</br>


| Operation  | Function/<br/>Operator | Example           | Notes |
|------------|------------------------|-------------------|-------|
| Input      | `>>`                   | `std::cin >> X;`  |       |
| Output     | `<<`                   | `std::cout << X;` |       |
| Assignment | `=`                    | `X = y;`<br/>`X = 123;`<br/>`X = "-112";` | Can equate with a `long`, `LongNumber` or a `std::string`. Will throw a `InvalidInputException` if it is unable to parse the string. |
| Comparison | `<`<br/>`>`<br/>`==`<br/>`!=`  | `X < Y;`<br/>`X > 1123;`<br/>`X == y;`<br/>`X != 0;` | Can compare a `LongNumber` with other `LongNumber`s, as well as `long`s and `std::string`s. Can use combined comparisons like `<=` or `>=`. |
|Addition   | `+`<br/>`+=`<br/>`++`  | `X + y;`<br/>`X + Y;`<br/>`X += Y;`<br/>`X++;`<br/>`++X;`<br/>  | Can add with `long`s as well as `LongNumber`s. Each notation has its standard meaning. |
|Subtraction |`-`<br/>`-=`<br/>`--`  | `X - y;`<br/>`X - Y;`<br/>`X -= Y;`<br/>`X--;`<br/>`--X;`<br/>  | Can subtract `long`s as well as `LongNumber`s from the `LongNumber`. Each notation has its standard meaning. |
|Multiplication |`*`<br/>`*=`<br/>  | `X * y;`<br/>`X * Y;`<br/>`X *= Y;`  | Can multiply with `long`s as well as `LongNumber`s. Each notation has its standard meaning. |
|Division |`/`<br/>`/=`<br/>  | `X / y;`<br/>`X / Y;`<br/>`X /= Y;` | Can divide with `long`s as well as `LongNumber`s. Each notation has its standard meaning. Dividing by zero will throw a `DivisionByZero` exception. |
|Modulo |`%`<br/>`%=`  | `X % y;`<br/>`X % Y;`<br/>`X %= Y;`<br/>  | Can find the modulus of `LongNumber` with `long`s as well as `LongNumber`s. Each notation has its standard meaning. Finding the modulus with 0 will throw a `DivisionByZero` exception. |
|Absolute   | `absolute()`  | `X.absolute()`  | Returns a `LongNumber`. Will not change the contents of `X`.  |
|Cast to Long   | `toLong()`  | `X.toLong()`  | Returns a `long`. Does not account for overflow.  |

---

# Exceptions

| Name | Function |
|------|----------|
| `DivideByZeroException` | Thrown when any attempt is made to divide by 0. |
| `InvalidInputException` | Thrown when the entered string does not correspond to an integer. |
