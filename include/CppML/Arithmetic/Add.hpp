/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_ADD_HPP
#define CPPML_ADD_HPP
#include "../Functional/Identity.hpp"
#include "../Vocabulary/Value.hpp"
namespace ml {
/*
 * Add:
 * Adds the underlying values
 */
template <typename Pipe = Identity> struct Add {
  template <typename T1, typename T2>
  using f = typename Pipe::template f<ml::Int<(T1::value + T2::value)>>;
};

} // namespace ml
#endif
