/*
* Property `Q`: For any combination `x`, the combination `QxQ` is specially
  related to `x`.
* Property `L`: If `x` is specially related to `y`, then `Lx` is specially
  related to `Qy`.
* Property `V` (the reversal property): If `x` is specially related to `y`, then
  `Vx` is specially related to the reverse of `y`.
* Property `R` (the repetition property): If `x` is specially related to `y`,
  then `Rx` is specially related to `yy` (the repeat of `y`).
  */

#include "view.h"

#include <algorithm>
#include <array>
#include <iostream>

using alphabet_type = std::array<char, 5>;
alphabet_type kAlphabet{'Q', 'L', 'V', 'R', 'X'};

std::string first_combination(int length) {
  return std::string(length, kAlphabet[0]);
}

bool next_combination(std::string& combination) {
  std::string::reverse_iterator it = combination.rbegin();

  while (true) {
    if (it == combination.rend()) {
      return false;
    }

    alphabet_type::iterator letter =
        std::find(kAlphabet.begin(), kAlphabet.end(), *it);
    letter++;

    if (letter != kAlphabet.end()) {
      *it = *letter;
      return true;
    }

    *it = *kAlphabet.begin();
    it++;
  }
}

int main() {
  const int kMaxLength = 2;

  for (int length = 1; length <= kMaxLength; length++) {
    std::string combination = first_combination(length);
    do {
      std::cout << combination << std::endl;
    } while (next_combination(combination));
  }

  return 0;
}
