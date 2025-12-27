#include "combination.h"

#include <deque>
#include <iostream>
#include <set>
#include <string>
#include <utility>

#include "absl/strings/str_cat.h"

class RelationshipCalculator {
 public:
  using CombinationPair = std::pair<std::string, std::string>;

  void Populate() {
    for (int length = 0; length <= kMaxLength_ - 2; length++) {
      std::string second = first_combination(length);
      do {
        Insert(absl::StrCat("Q", second, "Q"), second);
      } while (next_combination(second));
    }
  }

  const std::set<CombinationPair>& RelatedPairs() const { return related_set_; }

 private:
  // Insert pair and every possible pair derived from it up to length limit.
  void Insert(std::string first, std::string second) {
    CombinationPair pair{std::move(first), std::move(second)};
    std::set<CombinationPair>::iterator it = related_set_.lower_bound(pair);
    if (it != related_set_.end() && *it == pair) {
      return;
    }

    if (pair.first.length() + 1 > static_cast<size_t>(kMaxLength_)) {
      related_set_.insert(it, std::move(pair));
      return;
    }

    std::string new_first = absl::StrCat("V", pair.first);
    const std::string new_second = pair.second;

    related_set_.insert(it, std::move(pair));

    // V property
    Insert(new_first, std::string{new_second.rbegin(), new_second.rend()});

    if (new_second.length() + 1 <= static_cast<size_t>(kMaxLength_)) {
      // L property
      new_first[0] = 'L';
      Insert(new_first, absl::StrCat("Q", new_second));
    }

    if (2 * new_second.length() <= static_cast<size_t>(kMaxLength_)) {
      // R property
      new_first[0] = 'R';
      Insert(std::move(new_first), absl::StrCat(new_second, new_second));
    }
  }

 private:
  const int kMaxLength_ = 11;

  // Pairs of combinations that are known to be specially related.
  std::set<CombinationPair> related_set_;
};

int main() {
  RelationshipCalculator r;

  r.Populate();

  const std::set<RelationshipCalculator::CombinationPair>& related_pairs =
      r.RelatedPairs();
  for (const RelationshipCalculator::CombinationPair& pair : related_pairs) {
    if (pair.first == pair.second) {
      std::cout << pair.first << std::endl;
    }
  }

  std::cout << "total number of related pairs: " << r.RelatedPairs().size()
            << std::endl;

  return 0;
}
