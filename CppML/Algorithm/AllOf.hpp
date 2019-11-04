//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_ALL_OF_HPP
#define CPPML_ALL_OF_HPP
#include "../Algorithm/FindIfNot.hpp"
#include "../Functional/Identity.hpp"
#include "../Functional/Invoke.hpp"
#include "../Vocabulary/Const.hpp"
namespace ml {
/*
 * AllOf:
 * Checks if all values satisfy the predicate
 */
#ifdef __cpp_fold_expressions
template <typename Predicate, typename Pipe = Identity> struct AllOf {
  template <typename... Ts>
  using f = typename Pipe::template f<
      Bool<(Predicate::template f<Ts>::value && ...)>>;
};
#else
template <typename Predicate, typename Pipe = ml::Identity> struct AllOf {
  template <typename... Ts>
  using f =
      ml::Invoke<Pipe, ml::Bool<(ml::Invoke<ml::FindIfNot<Predicate>,
                                            Ts...>::value == sizeof...(Ts))>>;
};
#endif
} // namespace ml
#endif