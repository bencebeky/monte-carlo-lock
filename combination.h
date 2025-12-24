#pragma once

#include <array>
#include <string>

using alphabet_type = std::array<char, 5>;
static constexpr alphabet_type kAlphabet{'Q', 'L', 'V', 'R', 'X'};

std::string first_combination(int length);
bool next_combination(std::string& combination);
