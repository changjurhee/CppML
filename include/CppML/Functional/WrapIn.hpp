/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_WRAP_IN_HPP
#define CPPML_WRAP_IN_HPP

namespace ml {
/*
 * WrapIn:
 * Wraps a type in a wrapper
 */
template <template <class...> class Wrapper> struct WrapIn {
  template <typename... Ts> using f = Wrapper<Ts...>;
};
/*
 * WrapIn1:
 * Wraps a type in a wrapper. We need it because WrapIn (above) only
 * works for parameter pack aliases.
 */
template <template <class> class Wrapper> struct WrapIn1 {
  template <typename T> using f = Wrapper<T>;
};
} // namespace ml
#endif
