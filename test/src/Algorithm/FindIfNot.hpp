#include "CppML/CppML.hpp"

namespace FindIfNotTest {
template <typename T> using Predicate = ml::f<ml::IsSame<>, char, T>;
template <typename T> struct R {};
void run() {
  {
    using T =
        ml::f<ml::FindIfNot<ml::F<Predicate>, ml::F<R>>, char, char, bool>;
    static_assert(std::is_same<T, R<ml::Int<2>>>::value,
                  "FindIfNot with a non-empty pack 1");
  }
  {
    using T =
        ml::f<ml::FindIfNot<ml::F<Predicate>, ml::F<R>>, char, char, char, int>;
    static_assert(std::is_same<T, R<ml::Int<3>>>::value,
                  "FindIfNot with a non-empty pack 2");
  }
  {
    using T = ml::f<ml::FindIfNot<ml::F<Predicate>, ml::F<R>>>;
    static_assert(std::is_same<T, R<ml::Int<0>>>::value,
                  "FindIfNot with empty pack");
  }
}
} // namespace FindIfNotTest
