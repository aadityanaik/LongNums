#include <iostream>

#include "longnums.hpp"

Longnums::Longnums()
{
  digits = "";
  negative = false;
}

int Longnums::get()
{
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

