#include "CppML/CppML.hpp"
#include <string>
#include <vector>

namespace AnyOfTest {
template <typename T> using Predicate = std::is_class<T>;
void run() {
  {
    using T = ml::f<ml::AnyOf<ml::F<Predicate>>, int, char, std::string>;
    static_assert(std::is_same<T, ml::Bool<true>>::value,
                  "AnyOf with a non-empty pack 1");
  }
  {
    using T = ml::f<ml::AnyOf<ml::F<Predicate>>, int, char>;
    static_assert(std::is_same<T, ml::Bool<false>>::value,
                  "AnyOf with a non-empty pack 2");
  }
  {
    using T = ml::f<ml::AnyOf<ml::F<Predicate>>>;
    static_assert(std::is_same<T, ml::Bool<false>>::value,
                  "AnyOf with empty pack");
  }
}
} // namespace AnyOfTest
