#include "combination.h"
#include "related.h"
#include "view.h"

#include <iostream>
#include <set>
#include <string>

// TODO Look up how to partially bind class instance to method and package
// these in a class.
std::set<std::pair<std::string, std::string>> related_cache;
std::set<std::pair<std::string, std::string>> not_related_cache;

bool related(View first, View second) {
  std::pair<std::string, std::string> pair(first.ToString(), second.ToString());

  if (related_cache.find(pair) != related_cache.end()) {
    return true;
  }

  if (not_related_cache.find(pair) != not_related_cache.end()) {
    return false;
  }

  const bool is_related =
      Q_related(first, second, related) || L_related(first, second, related) ||
      V_related(first, second, related) || R_related(first, second, related);

  if (is_related) {
    related_cache.insert(pair);
  } else {
    not_related_cache.insert(pair);
  }

  return is_related;
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
