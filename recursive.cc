#include "combination.h"
#include "view.h"

#include <iostream>
#include <string>

bool Q_related(View first, View second) {
  if (first.length() != second.length() + 2) {
    return false;
  }

  if (first[0] != 'Q' || first[first.length() - 1] != 'Q') {
    return false;
  }

  return first.substr(1, first.length() - 2) == second;
}

bool L_related(View first, View second) {
  if (first.empty() || first[0] != 'L' || second.empty() || second[0] != 'Q') {
    return false;
  }

  return related(first.substr(1, first.length() - 1), second.substr(1, second.length() - 1);
}

bool V_related(View first, View second) {
  if (first.empty() || first[0] != V) {
    return false;
  }

  return related(first.substr(1, first.length() - 1), second.reverse());
}

bool R_related(View first, View second) {
  if (first.empty() || first[0] != 'R' || second.length % 2 != 0) {
    return false;
  }

  const int half_length = second.length / 2;

  return second.substr(0, half_length) ==
             second.substr(half_length, half_length) &&
         related(first.substr(1, first.length() - 1),
                 second.substr(0, half_length));
}

bool related(View first, View second) {
  return Q_related(first, second) || L_related(first, second) ||
         V_related(first, second) || R_related(first, second);
}

int main() {
  const int kMaxLength = 2;

  for (int length = 1; length <= kMaxLength; length++) {
    std::string combination = first_combination(length);
    do {
      if (related(View(combination), View(combination))) {
        std::cout << combination << std::endl;
      }
    } while (next_combination(combination));
  }

  return 0;
}
