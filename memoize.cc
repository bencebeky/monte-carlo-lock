#include "combination.h"
#include "related.h"
#include "view.h"

#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <utility>

class RelationshipCache {
 public:
  using CombinationPair = std::pair<std::string, std::string>;
  using SetOfPairs = std::set<CombinationPair>;

  RelationshipCache()
      : bound_related_(std::bind(&RelationshipCache::related, this,
                                 std::placeholders::_1,
                                 std::placeholders::_2)) {}

  bool related(View first, View second) {
    CombinationPair pair(first.ToString(), second.ToString());

    SetOfPairs::iterator related_it = related_cache_.lower_bound(pair);
    if (related_it != related_cache_.end() && *related_it == pair) {
      return true;
    }

    SetOfPairs::iterator not_related_it = not_related_cache_.lower_bound(pair);
    if (not_related_it != not_related_cache_.end() && *not_related_it == pair) {
      return false;
    }

    const bool is_related = Q_related(first, second, bound_related_) ||
                            L_related(first, second, bound_related_) ||
                            V_related(first, second, bound_related_) ||
                            R_related(first, second, bound_related_);

    if (is_related) {
      related_cache_.insert(related_it, std::move(pair));
    } else {
      not_related_cache_.insert(not_related_it, std::move(pair));
    }

    return is_related;
  }

  size_t related_cache_size() const { return related_cache_.size(); }
  size_t not_related_cache_size() const { return not_related_cache_.size(); }

 private:
  SetOfPairs related_cache_;
  SetOfPairs not_related_cache_;

  const related_type bound_related_;
};

int main() {
  constexpr int kMaxLength = 11;
  RelationshipCache r;

  for (int length = 1; length <= kMaxLength; length++) {
    std::string combination = first_combination(length);
    do {
      if (r.related(View(combination), View(combination))) {
        std::cout << combination << std::endl;
      }
    } while (next_combination(combination));
  }

  std::cout << "related_cache_size: " << r.related_cache_size() << std::endl;
  std::cout << "not_related_cache_size: " << r.not_related_cache_size()
            << std::endl;

  return 0;
}
