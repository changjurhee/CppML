/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_PARTIAL_HPP
#define CPPML_PARTIAL_HPP
#include "./DelayedEval.hpp"
namespace ml {
/*
 * Partial:
 * Partial evaluation of a metafunction
 */
template <typename F, typename... Ts> struct Partial {
  template <typename... Us>
  using f =
      ml::f<DelayedEval<F, (sizeof...(Us) + sizeof...(Ts))>, Ts..., Us...>;
};
} // namespace ml
#endif
