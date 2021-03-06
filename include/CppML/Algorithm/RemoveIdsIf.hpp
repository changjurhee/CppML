/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_REMOVE_IDS_IF_HPP
#define CPPML_REMOVE_IDS_IF_HPP
#include "../Arithmetic/Not.hpp"
#include "../Functional/Compose.hpp"
#include "./Filter.hpp"

namespace ml {
/*
 * # RemoveIdsIf:
 * Removes elements satifying the predicate, and returns indexes of remaining
 * elements
 */
template <typename Predicate, typename Pipe = ml::ToList> struct RemoveIdsIf {
  template <typename... Ts>
  using f = ml::f<ml::DelayedEval<Implementations::Filter, sizeof...(Ts)>,
                  ml::Compose<ml::Not<>, Predicate>, Pipe, ml::Get<1>, Ts...>;
};
} // namespace ml
#endif
