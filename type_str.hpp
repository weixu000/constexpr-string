#include <string_view>
#include <type_traits>
#include <utility>

template <char... Chars> class type_str {
  static_assert((Chars && ...));

public:
  static constexpr char c_str[] = {Chars..., '\0'};

  constexpr operator std::string_view() const {
    return std::string_view{c_str};
  }
};

template <char... CharsX, char... CharsY>
constexpr auto operator==(type_str<CharsX...>, type_str<CharsY...>) {
  return false;
}

template <char... Chars>
constexpr auto operator==(type_str<Chars...>, type_str<Chars...>) {
  return true;
}

template <char... CharsX, char... CharsY>
constexpr auto operator!=(type_str<CharsX...> x, type_str<CharsY...> y) {
  return !(x == y);
}

template <char... CharsX, char... CharsY>
constexpr auto operator+(type_str<CharsX...>, type_str<CharsY...>) {
  return type_str<CharsX..., CharsY...>{};
}

template <auto &CStr, std::size_t... Is>
constexpr auto make_type_str_impl(std::index_sequence<Is...>) {
  return type_str<CStr[Is]...>{};
}

template <auto &CStr> constexpr auto make_type_str() {
  constexpr auto N = std::extent_v<std::remove_reference_t<decltype(CStr)>>;
  static_assert(N);
  return make_type_str_impl<CStr>(std::make_index_sequence<N - 1>{});
}

#define LITERAL(x)                                                             \
  ([]() constexpr {                                                            \
    auto lambda = []() {                                                       \
      static constexpr char arr[] = x;                                         \
      return make_type_str<arr>();                                             \
    };                                                                         \
    return decltype(lambda()){};                                               \
  }())
