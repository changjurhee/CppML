//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_MAX_ELEMENT_HPP
#define CPPML_MAX_ELEMENT_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/IfElse.hpp"

namespace ml {
namespace Implementations {
template <bool Done> struct MaxEement {
  template <typename Compare, typename T0, typename T1, typename... Ts>
  using f = typename IfElse<(sizeof...(Ts) < 10000)>::
      template f<MaxEement<static_cast<bool>(sizeof...(Ts))>, void>::template f<
          Compare,
          typename IfElse<Compare::template f<T0, T1>::value>::template f<T0,
                                                                          T1>,
          Ts...>;
};
template <> struct MaxEement<false> { template <typename T> using f = T; };
}; // namespace Implementations

/*
 * MaxEement:
 * Max element in a pack, given a comparison operator
 */
template <typename Compare, typename Pipe = ml::Identity> struct MaxEement {
  template <typename... Ts>
  using f = typename Pipe::template f<typename Implementations::MaxEement<(
      sizeof...(Ts) > 1)>::template f<Compare, Ts...>>;
};
} // namespace ml
#endif
