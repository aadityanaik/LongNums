#include <iostream>
#include <algorithm>

#include "longnums.hpp"

Longnums::Longnums()
{
  digits = "0";
  negative = false;
}

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
    negative = false;
    digits.push_back(c);
  }

  else if(c == '0'){
    negative = false;
  }

  else{
    std::cerr << std::endl << "No such sign" << std::endl;
    return 1;
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

    else if(c == '\n'){
      break;
    }

    else{
      std::cerr << std::endl << "Not a valid integer" << std::endl;
      digits = "";
      return 1;
    }
  }

  if(digits == ""){
    digits = "0";
  }

  return 0;
}

int Longnums::put()
{
  if(negative){
    std::cout << "-";
  }

  std::cout << digits;
  return 0;
}

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

Longnums::Longnums(Longnums &X)
{
  digits = X.digits;
  negative = X.negative;
}

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

Longnums Longnums::mod()
{
  Longnums ans;
  ans = digits;
  ans.negative = false;
  return ans;
}


Longnums Longnums::operator+(Longnums X)
{
  int maxlength = std::max(digits.length(), X.digits.length());
  std::string ans(maxlength, '0');
  int num1, num2;
  int carryover = 0;
  if(this->negative == X.negative){
    //one must add
    if(digits.length() == X.digits.length()){
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
      return answer;
    }


  }

  else{
    //one must subtract the numbers

  }
}
