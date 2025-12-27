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
      CombinationPair pair{std::string(), first_combination(length)};
      do {
        pair.first = absl::StrCat("Q", pair.second, "Q");
        Insert(pair);
      } while (next_combination(pair.second));
    }
  }

  const std::set<CombinationPair>& RelatedPairs() const { return related_set_; }

 private:
  // Insert pair and every possible pair derived from it up to length limit.
  void Insert(CombinationPair pair) {
    std::set<CombinationPair>::iterator it = related_set_.lower_bound(pair);
    if (it != related_set_.end() && *it == pair) {
      return;
    }

    if (pair.first.length() + 1 > static_cast<size_t>(kMaxLength_)) {
      related_set_.insert(it, std::move(pair));
      return;
    }

    const std::string second = pair.second;
    std::string second_reversed{second.rbegin(), second.rend()};
    CombinationPair new_pair{absl::StrCat("V", pair.first),
                             std::move(second_reversed)};

    related_set_.insert(it, std::move(pair));

    // V property
    Insert(new_pair);

    if (second.length() + 1 <= static_cast<size_t>(kMaxLength_)) {
      // L property
      new_pair.first[0] = 'L';
      new_pair.second = absl::StrCat("Q", second);
      Insert(new_pair);
    }

    if (2 * second.length() <= static_cast<size_t>(kMaxLength_)) {
      // R property
      new_pair.first[0] = 'R';
      new_pair.second = absl::StrCat(second, second);
      Insert(std::move(new_pair));
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
