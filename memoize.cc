#include "combination.h"
#include "related.h"
#include "view.h"

#include <functional>
#include <iostream>
#include <set>
#include <string>

class RelationshipCache {
 public:
  using CombinationPair = std::pair<std::string, std::string>;
  using SetOfPairs = std::set<CombinationPair>;

  bool related(View first, View second) {
    const related_type bound_related =
        std::bind(&RelationshipCache::related, this, std::placeholders::_1,
                  std::placeholders::_2);

    CombinationPair pair(first.ToString(), second.ToString());

    SetOfPairs::iterator related_it = related_cache_.lower_bound(pair);
    if (related_it != related_cache_.end() && *related_it == pair) {
      return true;
    }

    SetOfPairs::iterator not_related_it = not_related_cache_.lower_bound(pair);
    if (not_related_it != not_related_cache_.end() && *not_related_it == pair) {
      return false;
    }

    const bool is_related = Q_related(first, second, bound_related) ||
                            L_related(first, second, bound_related) ||
                            V_related(first, second, bound_related) ||
                            R_related(first, second, bound_related);

    if (is_related) {
      related_cache_.insert(related_it, pair);
    } else {
      not_related_cache_.insert(not_related_it, pair);
    }

    return is_related;
  }

 private:
  SetOfPairs related_cache_;
  SetOfPairs not_related_cache_;
};

int main() {
  const int kMaxLength = 10;
  RelationshipCache r;

  for (int length = 1; length <= kMaxLength; length++) {
    std::string combination = first_combination(length);
    do {
      if (r.related(View(combination), View(combination))) {
        std::cout << combination << std::endl;
      }
    } while (next_combination(combination));
  }

  return 0;
}
