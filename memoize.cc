#include "combination.h"
#include "related.h"
#include "view.h"

#include <iostream>
#include <string>

bool related(View first, View second) {
  return Q_related(first, second, related) ||
         L_related(first, second, related) ||
         V_related(first, second, related) || R_related(first, second, related);
}

int main() {
  const int kMaxLength = 10;

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
