#pragma once

#include <functional>

#include "view.h"

using related_type = std::function<bool(View, View)>;

bool related_impl(View first, View second, related_type related) {
  if (first.empty()) {
    return false;
  }

  if (first[0] == 'Q') {
    // Q property
    return first[first.length() - 1] == 'Q' &&
           first.substr(1, first.length() - 2) == second;
  } else if (first[0] == 'L') {
    // L property
    return !second.empty() && second[0] == 'Q' &&
           related(first.substr(1, first.length() - 1),
                   second.substr(1, second.length() - 1));
  } else if (first[0] == 'V') {
    // V property
    return related(first.substr(1, first.length() - 1), second.reverse());
  } else {
    // R property
    if (second.length() % 2 != 0) {
      return false;
    }

    const int half_length = second.length() / 2;
    const View first_half_of_second = second.substr(0, half_length);
    const View second_half_of_second = second.substr(half_length, half_length);

    return first_half_of_second == second_half_of_second &&
           related(first.substr(1, first.length() - 1), first_half_of_second);
  }
}
