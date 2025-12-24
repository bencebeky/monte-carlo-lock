/*
* Property `Q`: For any combination `x`, the combination `QxQ` is specially
  related to `x`.
* Property `L`: If `x` is specially related to `y`, then `Lx` is specially
  related to `Qy`.
* Property `V` (the reversal property): If `x` is specially related to `y`, then
  `Vx` is specially related to the reverse of `y`.
* Property `R` (the repetition property): If `x` is specially related to `y`,
  then `Rx` is specially related to `yy` (the repeat of `y`).
  */

#include "view.h"

#include <iostream>

int main() {
  const int kMaxLength = 12;

  for (int length = 1; length < kMaxLength; length++) {
    std::string key(length, 'a');
    std::cout << key << std::endl;
  }

  return 0;
}
