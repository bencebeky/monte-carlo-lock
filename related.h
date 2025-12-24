#include <functional>

#include "view.h"

using related_type = std::function<bool(View, View)>;

bool Q_related(View first, View second, related_type unused) {
  return first.length() == second.length() + 2 && first[0] == 'Q' &&
         first[first.length() - 1] == 'Q' &&
         first.substr(1, first.length() - 2) == second;
}

bool L_related(View first, View second, related_type related) {
  return !first.empty() && first[0] == 'L' && !second.empty() &&
         second[0] == 'Q' &&
         related(first.substr(1, first.length() - 1),
                 second.substr(1, second.length() - 1));
}

bool V_related(View first, View second, related_type related) {
  return !first.empty() && first[0] == 'V' &&
         related(first.substr(1, first.length() - 1), second.reverse());
}

bool R_related(View first, View second, related_type related) {
  const int half_length = second.length() / 2;

  return !first.empty() && first[0] == 'R' && second.length() % 2 == 0 &&
         second.substr(0, half_length) ==
             second.substr(half_length, half_length) &&
         related(first.substr(1, first.length() - 1),
                 second.substr(0, half_length));
}
