#include "constexpr_str.hpp"
#include "type_str.hpp"

int main() {
  using namespace std::literals;

  static_assert(LITERAL("abc") == LITERAL("abc"));
  static_assert(LITERAL("abc") != LITERAL("def"));
  static_assert(LITERAL("Hello") + LITERAL("World!") == "HelloWorld!"sv);

  static_assert(constexpr_str{"abc"} == constexpr_str{"abc"});
  static_assert(constexpr_str{"abc"} != constexpr_str{"def"});
  static_assert(constexpr_str{"Hello"} + constexpr_str{"World!"} ==
                "HelloWorld!"sv);
}
