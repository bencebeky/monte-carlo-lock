#pragma once

#include <array>
#include <string>

using alphabet_type = std::array<char, 4>;
static constexpr alphabet_type kAlphabet{'Q', 'L', 'V', 'R'};

std::string first_combination(int length);
bool next_combination(std::string& combination);
