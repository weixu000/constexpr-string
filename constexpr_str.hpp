#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <string_view>

template <std::size_t N> class constexpr_str {
public:
  constexpr constexpr_str() = default;

  explicit constexpr constexpr_str(const char (&c_str)[N + 1]) {
    for (size_t i = 0; i < N + 1; ++i) {
      data_[i] = c_str[i];
    }
  }

  constexpr char operator[](std::size_t i) const { return data_[i]; }
  constexpr char &operator[](std::size_t i) { return data_[i]; }

  constexpr operator std::string_view() const {
    return std::string_view(data_.data());
  }

private:
  std::array<char, N + 1> data_{};
};

template <std::size_t N>
constexpr_str(const char (&c_str)[N]) -> constexpr_str<N - 1>;

template <std::size_t N, std::size_t M>
constexpr auto operator==(const constexpr_str<N> &x,
                          const constexpr_str<M> &y) {
  return std::string_view(x) == std::string_view(y);
}

template <std::size_t N, std::size_t M>
constexpr auto operator!=(const constexpr_str<N> &x,
                          const constexpr_str<M> &y) {
  return !(x == y);
}

template <std::size_t N, std::size_t M>
constexpr auto operator+(const constexpr_str<N> &x, const constexpr_str<M> &y) {
  constexpr_str<N + M> ret;
  for (std::size_t i = 0; i < N; ++i)
    ret[i] = x[i];
  for (std::size_t i = 0; i < M; ++i)
    ret[i + N] = y[i];
  ret[N + M] = '\0';
  return ret;
}