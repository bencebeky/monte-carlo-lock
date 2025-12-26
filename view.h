#pragma once

#include <string>
#include <string_view>

// View of a substring of an externally stored string, much like
// std::string_view, but also supports reverse substrings.
class View {
 public:
  // A signed size_type allows for seemless signed arithmetics.
  using size_type = int;
  using value_type = char;

  enum class Direction { kForward = 1, kReverse = -1 };

  View() : data_(nullptr), length_(0), direction_(Direction::kForward) {}

  // `data` points to the first element. If `direction` is forward, then View
  // points to memory range [data, data + length - 1]. If `direction` is
  // reverse, then points to memory range [data - lenght + 1, data], and
  // reverses the substring stored in that range.
  View(const value_type* data, size_type length,
       Direction direction = Direction::kForward)
      : data_(data), length_(length), direction_(direction) {}

  // This allows conversion from std::string and C-style string (including
  // string literals) as well, courtesy of std::string_view's implicit
  // constructors.
  View(std::string_view s)
      : data_(s.data()), length_(s.length()), direction_(Direction::kForward) {}

  class iterator {
   public:
    iterator(const View& view, size_type index) : view_(view), index_(index) {}

    // ++it
    iterator& operator++() {
      index_++;
      return *this;
    }
    // it++
    iterator operator++(int) {
      iterator temp = *this;
      index_++;
      return temp;
    }

    value_type operator*() const { return view_[index_]; }
    bool operator==(const iterator& other) const {
      return &view_ == &other.view_ && index_ == other.index_;
    }
    bool operator!=(const iterator& other) const { return !operator==(other); }

   private:
    const View& view_;
    size_type index_;
  };

  bool empty() const { return length_ == 0; }

  size_type length() const { return length_; }

  value_type operator[](size_type index) const {
    return *(data_ + static_cast<int>(direction_) * index);
  }

  iterator begin() const { return iterator(*this, 0); }
  iterator end() const { return iterator(*this, length_); }

  View reverse() const {
    if (empty()) {
      return View();
    }

    return View(data_ + static_cast<int>(direction_) * (length_ - 1), length_,
                static_cast<Direction>((-1) * static_cast<int>(direction_)));
  }

  bool operator==(const View& other) const {
    return length_ == other.length_ &&
           std::equal(begin(), end(), other.begin(),
                      [](value_type a, value_type b) { return a == b; });
  }

  bool operator==(std::string_view other) const { return *this == View(other); }

  View substr(size_type start, size_type length) {
    return View(data_ + static_cast<int>(direction_) * start, length,
                direction_);
  }

  std::string ToString() const {
    std::string result;
    result.reserve(length_);
    for (char c : *this) {
      result.push_back(c);
    }
    return result;
  }

 private:
  const value_type* const data_;
  const size_type length_;
  const Direction direction_;
};

bool operator==(std::string_view first, View second) { return second == first; }

namespace std {
template <> struct iterator_traits<View::iterator> {
  using iterator_category = std::forward_iterator_tag;
  using value_type = char;
  using difference_type = std::ptrdiff_t;
};
} // namespace std
