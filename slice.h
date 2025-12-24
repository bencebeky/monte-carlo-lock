#include <string>

// View of a substring of an externally stored string, much like
// std::string_view, but also supports reverse substrings.
class Slice {
 public:
  enum class Direction { kForward, kReverse };

  // `data` points to the first element. If `direction` is forward, then Slice
  // points to memory range [data, data + length - 1]. If `direction` is
  // reverse, then points to memory range [data - lenght + 1, data], and
  // reverses the substring stored in that range.
  Slice(char* data, size_t length, Direction direction = Direction::kForward)
      : data_(data), length_(length), direction_(direction) {}

 private:
  char* const data_;
  const size_t length_;
  const Direction direction_;
};
