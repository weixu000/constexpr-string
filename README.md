# constexpr-string
Two ways to have the compile-time string in C++ 17 that can be concatenated
- `type_str` embeds characters into the type as non-type template parameters
    - Different strings have distinct types where there is `static constexpr char[]` to holds data
-  `constexpr_str` exploits the fact that `std::array` can be `constexpr` so data is embedded in it as constant expression
    - `std::string_view` can also be `constexpr` but it does not own the data