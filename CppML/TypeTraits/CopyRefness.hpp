//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_COPY_REFNESS_HPP
#define CPPML_COPY_REFNESS_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/IfElse.hpp"
#include <type_traits>

namespace ml {
/*
 * CopyRefness:
 * Returns type To, with the same refness as From.
 */
template <typename Pipe = ml::Identity> struct CopyRefness {
  template <typename From, typename To>
  using f = typename Pipe::template f<
      typename IfElse<!std::is_reference<From>::value>::template f<
          std::remove_reference_t<To>,
          typename IfElse<std::is_rvalue_reference<From>::value>::template f<
              std::remove_reference_t<To> &&, To &>>>;
};
} // namespace ml
#endif