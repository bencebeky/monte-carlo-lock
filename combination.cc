#include "combination.h"

#include <algorithm>
#include <array>
#include <string>

using alphabet_type = std::array<char, 4>;

std::string first_combination(int length) {
  return std::string(length, kAlphabet[0]);
}

bool next_combination(std::string& combination) {
  std::string::reverse_iterator it = combination.rbegin();

  while (true) {
    if (it == combination.rend()) {
      return false;
    }

    alphabet_type::const_iterator letter =
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
