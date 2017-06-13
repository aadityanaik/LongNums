#include <iostream>
#include <algorithm>

#include "longnums.hpp"

//default constructor
Longnums::Longnums()
{
  digits = "0";
  negative = false;
}

//to equate two Longnums
Longnums::Longnums(Longnums &X)
{
  digits = X.digits;
  negative = X.negative;
}

//constructor for equating number to string
Longnums::Longnums(std::string &X)
{
  if(X[0] == '-'){
    negative = true;
    digits = X.substr(1);
  }

  else if(X[0] == '+'){
    negative = false;
    digits = X.substr(1);
  }

  else{
      negative = false;
    digits = X;
  }
}

//finding the modulus of number
Longnums Longnums::mod()
{
  Longnums ans;
  ans = digits;
  ans.negative = false;
  return ans;
}

//input method
int Longnums::get()
{
  digits = "";
  char c;
  //denotes each individual digit or the sign

  std::cin.get(c);

  if(c == '+'){
    negative = false;
  }

  else if(c == '-'){
    negative = true;
  }

  else if(int(c) >= 49 && int(c) <= 57){
    //only numbers can be digits
    negative = false;
    digits.push_back(c);
  }

  else if(c == '0'){
    //no leading zeros
    negative = false;
  }

  else{
    std::cerr << std::endl << "No such sign" << std::endl;
    return 1;
    //error
  }

  while(true){
    std::cin.get(c);
    if(c >= 49 && c <= 57){
      digits.push_back(c);
    }

    else if(c == '0'){
      if(digits != ""){
        digits.push_back(c);
      }
    }

    else if(c == '\n' || c == '\t' || c == ' '){
      break;
      //return, tab or space terminates the input
    }

    else{
      //error
      std::cerr << std::endl << "Not a valid integer" << std::endl;
      digits = "0";
      return 1;
    }
  }

  if(digits == ""){
    digits = "0";
  }

  return 0;
}

//output function
int Longnums::put()
{
  if(negative){
    std::cout << "-";
  }

  std::cout << digits;
  return 0;
}

//comparison functions
bool Longnums::operator<(Longnums X)
{
  if(!negative){
    if(X.negative){
      return false;
    }

    else{
      if(digits.length() > X.digits.length()){
        return false;
      }

      else if(digits.length() == X.digits.length()){
        for(int i = 0; i < digits.length(); i++){
          if(digits[i] > X.digits[i]){
            return false;
          }

          else if(digits[i] < X.digits[i]){
            return true;
          }
        }

        return false;
      }

      else{
        return true;
      }
    }
  }

  else{
    if(!X.negative){
      return true;
    }

    else{
      if(digits.length() > X.digits.length()){
        return true;
      }

      else if(digits.length() == X.digits.length()){
        for(int i = 0; i < digits.length(); i++){
          if(digits[i] > X.digits[i]){
            return true;
          }

          else if(digits[i] < X.digits[i]){
            return false;
          }
        }

        return false;
      }

      else{
        return false;
      }
    }
  }
}

bool Longnums::operator>(Longnums X)
{
  if(!negative){
    if(X.negative){
      return true;
    }

    else{
      if(digits.length() > X.digits.length()){
        return true;
      }

      else if(digits.length() == X.digits.length()){
        for(int i = 0; i < digits.length(); i++){
          if(digits[i] > X.digits[i]){
            return true;
          }

          else if(digits[i] < X.digits[i]){
            return false;
          }
        }

        return false;
      }

      else{
        return false;
      }
    }
  }

  else{
    if(!X.negative){
      return false;
    }

    else{
      if(digits.length() > X.digits.length()){
        return false;
      }

      else if(digits.length() == X.digits.length()){
        for(int i = 0; i < digits.length(); i++){
          if(digits[i] > X.digits[i]){
            return false;
          }

          else if(digits[i] < X.digits[i]){
            return true;
          }
        }

        return false;
      }

      else{
        return true;
      }
    }
  }
}

bool Longnums::operator==(Longnums X)
{
  if(negative == X.negative){
    if(digits == X.digits){
      return true;
    }
  }

  return false;
}

Longnums Longnums::operator+(Longnums X)
{
  int maxlength = std::max(digits.length(), X.digits.length());
  std::string ans(maxlength, '0');
  int num1, num2;
  bool ansneg = false;
  int carryover = 0;
  if(this->negative == X.negative){
    //one must add
    if(this->negative){
      ansneg = true;
      //the ans will be negative
    }

    if(digits.length() != X.digits.length()){
      std::string res = "", add = "0";
      for(int i = 1; i <= (maxlength - digits.length()); i++){
        res += add;
      }

      digits = res + digits;

      res = "";
      for(int i = 1; i <= (maxlength - X.digits.length()); i++){
        res += add;
      }

      X.digits = res + X.digits;
    }

    for(int i = digits.length() - 1; i >= 0; i--){
      num1 = int(digits[i]) - 48;
      num2 = int(X.digits[i]) - 48;

      ans[i] = char(((num1 + num2 + carryover) % 10) + 48);

      carryover = (num1 + num2 + carryover) / 10;
    }

    if(carryover > 0){
      ans = std::to_string(carryover) + ans;
    }
    Longnums answer;
    answer = ans;
    answer.negative = ansneg;
    return answer;
  }

  else{
    //one must subtract the numbers
    Longnums answer, temp;
    if(negative){
      temp = this->mod();
      answer = (X - temp);
      return answer;
    }

    else if(X.negative){
      temp = X.mod();
      answer = ((*this) - temp);
      return answer;
    }
  }
}

Longnums Longnums::operator-(Longnums X)
{
  if(negative == X.negative){
    //subtract
    Longnums result;
    int maxlength = std::max(digits.length(), X.digits.length());
    std::string big, small;

    if(X == (*this)){
      result.digits = "0";
      result.negative = false;
      return result;
    }

    else if(X > (*this)){
      result.negative = true;
      if(negative){
        big = this->digits;
        small = X.digits;
      }
      else{
        big = X.digits;
        small = this->digits;
      }
    }

    else{
      result.negative = false;
      if(!negative){
        big = this->digits;
        small = X.digits;
      }
      else{
        big = X.digits;
        small = this->digits;
      }
    }

    std::string res = "", add = "0";

    for(int i = 1; i <= (maxlength - small.length()); i++){
      res += add;
    }

    small = res + small;

    //big - small
    std::string answer = "";
    int num1, num2, ans;
    for(int i = maxlength - 1; i >= 0; i--){
      num1 = int(big[i]) - 48;
      num2 = int(small[i]) - 48;
      ans = num1 - num2;
      if(ans < 0){
        ans += 10;
        big[i - 1] = char(int(big[i - 1]) - 1);
      }

      answer.insert(0, std::to_string(ans));
    }

    result.digits = answer;
    //this has trailing zeros which must be removed
    int pos;
    for(int i = 0; i < result.digits.length(); i++){
      if(result.digits[i] != '0'){
        pos = i;
        break;
      }
    }

    result.digits.erase(0, pos);
    return result;
  }

  else{
    //add
    Longnums number, answer;
    number.digits = X.digits;
    number.negative = !X.negative;

    answer = (*this) + number;
    return answer;
  }
}
