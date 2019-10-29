//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_CONTAINS_HPP
#define CPPML_CONTAINS_HPP
#include "../Algorithm/Any.hpp"
#include "../Functional/Identity.hpp"
#include "../Functional/Partial.hpp"
#include "../TypeTraits/IsSame.hpp"

namespace ml {
/*
 * # Contains:
 * Checks if a parameter pack contains T
 */
template <typename T, typename Pipe = ml::Identity> struct Contains {
  template <typename... Ts>
  using f = typename ml::Any<ml::PrePartial<ml::IsSame<>, T>,
                             Pipe>::template f<Ts...>;
};
} // namespace ml
#endif
