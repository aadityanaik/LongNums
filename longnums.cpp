#include <iostream>
#include <algorithm>

#include "longnums.hpp"

//default constructor
Longnums::Longnums()
{
  digits.push_back(0);
  negative = false;
}

//to equate two Longnums
Longnums::Longnums(Longnums &X)
{
  digits = X.digits;
  negative = X.negative;
}

//finding the modulus of number
Longnums Longnums::mod()
{
  Longnums ans;
  ans.digits = digits;
  ans.negative = false;
  return ans;
}

//input method
int Longnums::get()
{
  digits.erase(digits.begin(), digits.end());
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
    digits.push_back(int(c) - 48);
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
    if(int(c) >= 49 && int(c) <= 57){
      digits.push_back(int(c) - 48);
    }

    else if(c == '0'){
      if(!digits.empty()){
        digits.push_back(int(c) - 48);
      }
    }

    else if(c == '\n' || c == '\t' || c == ' '){
      break;
      //return, tab or space terminates the input
    }

    else{
      //error
      std::cerr << std::endl << "Not a valid integer" << std::endl;
      digits.clear();
      digits.push_back(0);
      return 1;
    }
  }

  if(digits.empty()){
    digits.push_back(0);
  }

  return 0;
}

//output function
int Longnums::put()
{
  if(negative){
    std::cout << "-";
  }

  for(auto iter = digits.begin(); iter < digits.end(); iter++){
    std::cout << *iter;
  }

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
      if(digits.size() > X.digits.size()){
        return false;
      }

      else if(digits.size() == X.digits.size()){
        for(int i = 0; i < digits.size(); i++){
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
      if(digits.size() > X.digits.size()){
        return true;
      }

      else if(digits.size() == X.digits.size()){
        for(int i = 0; i < digits.size(); i++){
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
      if(digits.size() > X.digits.size()){
        return true;
      }

      else if(digits.size() == X.digits.size()){
        for(int i = 0; i < digits.size(); i++){
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
      if(digits.size() > X.digits.size()){
        return false;
      }

      else if(digits.size() == X.digits.size()){
        for(int i = 0; i < digits.size(); i++){
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
  Longnums answer;
  std::vector<int> sum;
  bool ansneg = false;
  int carryover = 0;
  std::vector<int> big, small;
  if(this->negative == X.negative){
    //one must add
    if(this->negative){
      ansneg = true;
      //the ans will be negative
    }

    if(X > (*this)){
      if(negative){
        big = digits;
        small = X.digits;
      }
      else{
        big = X.digits;
        small = digits;
      }
    }
    else{
      if(!negative){
        big = digits;
        small = X.digits;
      }
      else{
        big = X.digits;
        small = digits;
      }
    }

    while(big.size() != small.size()){
      small.insert(small.begin(), 0);
    }

    int temp = 0;

    for(int i = big.size() - 1; i >= 0; i--){
      temp = ((big[i] + small[i] + carryover) % 10);

      carryover = (big[i] + small[i] + carryover) / 10;

      sum.insert(sum.begin(), temp);
    }

    if(carryover > 0){
      sum.insert(sum.begin(), carryover);
    }
    answer.digits = sum;
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
    int maxlength = std::max(digits.size(), X.digits.size());
    std::vector<int> big, small;

    if(X == (*this)){
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

    std::vector<int> res;

    while(big.size() != small.size()){
      small.insert(small.begin(), 0);
    }

    //big - small
    result.digits.pop_back();
    int ans;
    for(int i = maxlength - 1; i >= 0; i--){
      ans = big[i] - small[i];
      if(ans < 0){
        ans += 10;
        big[i - 1] = big[i - 1] - 1;
      }

      result.digits.insert(result.digits.begin(), ans);
    }

    //this has trailing zeros which must be removed
    std::vector<int>::iterator pos;
    for(auto i = result.digits.begin(); i < result.digits.end(); i++){
      if(*i != 0){
        pos = i;
        break;
      }
    }

    result.digits.erase(result.digits.begin(), pos);
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

Longnums Longnums::operator*(Longnums X)
{
  Longnums answer;
  std::vector<Longnums> product(X.digits.size());
  int carryover = 0;
  int prod_temp = 0, count = 0;

  for(auto multiplier = X.digits.end() - 1; multiplier >= X.digits.begin(); multiplier--){
    product[count].digits.pop_back();
    for(int i = 0; i < count; i++){
      product[count].digits.push_back(0);
    }

    for(auto multiplicand = digits.end() - 1; multiplicand >= digits.begin(); multiplicand--){
      prod_temp = ((*multiplicand) * (*multiplier)) + carryover;
      carryover = prod_temp / 10;
      prod_temp %= 10;
      product[count].digits.insert(product[count].digits.begin(), prod_temp);
    }
    count++;
  }

  for(auto iter = product.begin(); iter < product.end(); iter++){
    answer = answer + (*iter);
  }

  if(negative == X.negative){
    answer.negative = false;
  }
  else{
    answer.negative = true;
  }

  return answer;
}
