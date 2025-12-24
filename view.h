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
  View(value_type* data, size_type length,
       Direction direction = Direction::kForward)
      : data_(data), length_(length), direction_(direction) {}

  // This allows conversion from std::string and C-style string (including
  // string literals) as well, courtesy of std::string_view's implicit
  // constructors.
  View(std::string_view s)
      : data_(s.data()), length_(s.length()), direction_(Direction::kForward) {}

  bool empty() const { return length_ == 0; }

  size_type length() const { return length_; }

 private:
  const value_type* const data_;
  const size_type length_;
  const Direction direction_;
};
