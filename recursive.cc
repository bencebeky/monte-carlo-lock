#include "combination.h"
#include "related.h"
#include "view.h"

#include <iostream>
#include <string>

bool related(View first, View second) {
  return related_impl(first, second, related);
}

int main() {
  constexpr int kMaxLength = 11;

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
