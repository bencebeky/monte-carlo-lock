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
        std::string first = absl::StrCat("Q", second, "Q");
        Insert(first, second);
      } while (next_combination(second));
    }
  }

  const std::set<CombinationPair>& RelatedPairs() const { return related_set_; }

 private:
  // Insert pair and every possible pair derived from it up to length limit.
  void Insert(const std::string& first, const std::string& second) {
    CombinationPair element(first, second);

    std::set<CombinationPair>::iterator it = related_set_.lower_bound(element);
    if (it != related_set_.end() && *it == element) {
      return;
    }

    related_set_.insert(it, std::move(element));

    if (first.length() + 1 > kMaxLength_) {
      return;
    }

    // V property
    std::string second_reversed{second.rbegin(), second.rend()};
    Insert(absl::StrCat("V", first), second_reversed);

    if (second.length() + 1 <= kMaxLength_) {
      // L property
      Insert(absl::StrCat("L", first), absl::StrCat("Q", second));
    }

    if (2 * second.length() <= kMaxLength_) {
      // R property
      Insert(absl::StrCat("R", first), absl::StrCat(second, second));
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
