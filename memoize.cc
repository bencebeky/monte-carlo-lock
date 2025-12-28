#include "combination.h"
#include "related.h"
#include "view.h"

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <utility>

class RelationshipCache {
 public:
  using CombinationPair = std::pair<std::string, std::string>;
  using Cache = std::map<CombinationPair, bool>;

  RelationshipCache()
      : related_entry_count_(0), related_query_count_(0),
        related_cache_hit_count_(0), not_related_entry_count_(0),
        not_related_query_count_(0), not_related_cache_hit_count_(0),
        bound_related_(std::bind(&RelationshipCache::related, this,
                                 std::placeholders::_1,
                                 std::placeholders::_2)) {}

  bool related(View first, View second) {
    CombinationPair pair(first.ToString(), second.ToString());

    Cache::iterator related_it = related_cache_.lower_bound(pair);
    if (related_it != related_cache_.end() && related_it->first == pair) {
      const bool is_related = related_it->second;

      if (is_related) {
        related_query_count_++;
        related_cache_hit_count_++;
      } else {
        not_related_query_count_++;
        not_related_cache_hit_count_++;
      }

      return is_related;
    }

    const bool is_related = related_impl(first, second, bound_related_);

    if (is_related) {
      related_query_count_++;
      related_entry_count_++;
    } else {
      not_related_query_count_++;
      not_related_entry_count_++;
    }

    related_cache_.insert(related_it, {std::move(pair), is_related});

    return is_related;
  }

  int related_entry_count() const { return related_entry_count_; }
  int related_query_count() const { return related_query_count_; }
  int related_cache_hit_count() const { return related_cache_hit_count_; }
  int not_related_entry_count() const { return not_related_entry_count_; }
  int not_related_query_count() const { return not_related_query_count_; }
  int not_related_cache_hit_count() const {
    return not_related_cache_hit_count_;
  }

 private:
  Cache related_cache_;

  int related_entry_count_;
  int related_query_count_;
  int related_cache_hit_count_;
  int not_related_entry_count_;
  int not_related_query_count_;
  int not_related_cache_hit_count_;

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

  std::cout << "related_entry_count: " << r.related_entry_count() << std::endl;
  std::cout << "related_query_count: " << r.related_query_count() << std::endl;
  std::cout << "related_cache_hit_count: " << r.related_cache_hit_count()
            << std::endl;
  std::cout << "related hit rate: "
            << static_cast<float>(r.related_cache_hit_count()) /
                   r.related_query_count()
            << std::endl;
  std::cout << "not_related_entry_count: " << r.not_related_entry_count()
            << std::endl;
  std::cout << "not_related_query_count: " << r.not_related_query_count()
            << std::endl;
  std::cout << "not_related_cache_hit_count: "
            << r.not_related_cache_hit_count() << std::endl;
  std::cout << "not_related hit rate: "
            << static_cast<float>(r.not_related_cache_hit_count()) /
                   r.not_related_query_count()
            << std::endl;

  return 0;
}
