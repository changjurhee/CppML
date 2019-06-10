//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_FUNCTIONAL_HPP
#define CPPML_FUNCTIONAL_HPP
#include "Const.hpp"
#include "ControlFlow.hpp"
#include "Identity.hpp"
#include "List.hpp"
#include <type_traits>
namespace ml {
namespace UnListDetail {
template <typename...> struct UnListImpl;
template <typename Pipe, template <class...> class List, typename... Es>
struct UnListImpl<Pipe, List<Es...>> {
  using type = typename Pipe::template f<Es...>;
};
}; // namespace UnListDetail
/*
 * UnList:
 * Pipes the un-wrapped elements of a list like type
 */
template <typename Pipe> struct UnList {
  template <typename... Ls>
  using f = typename UnListDetail::UnListImpl<Pipe, Ls...>::type;
};
/*
 * Invoke:
 * Invokes a meta function
 */
template <typename Pipe, typename... Ts>
using Invoke = typename Pipe::template f<Ts...>;
/*
 * InvokeA:
 * Invokes a meta function
 */
template <typename Pipe, auto... Ts>
using InvokeA = typename Pipe::template f<Ts...>;
/*
 * WrapIn:
 * Wraps a type in a wrapper
 */
template <template <class...> class Wrapper> struct WrapIn {
  template <typename... Ts> using f = Wrapper<Ts...>;
};
/*
 * WrapInSingle:
 * Wraps a type in a wrapper. We need it because WrapIn (above) only
 * works for parameter pack aliases.
 */
template <template <class...> class Wrapper> struct WrapInSingle {
  template <typename T> using f = Wrapper<T>;
};
/*
 * ToList:
 * Wraps the pack in a list
 */
using ToList = WrapIn<ListT>;
/*
 * MakeMetaFunction:
 * Creates a MetaFunction from a template
 */
template <template <class...> class Template> struct MakeMetaFunction {
  template <typename... Args> using f = Template<Args...>;
};
/*
 * ToValue:
 * Returns an auto list of underlying values
 */
struct ToValue {
  template <typename... Ts> using f = ListA<Ts::value...>;
};
/*
 * All:
 * Checks if all values satisfy the predicate
 */
template <typename Predicate, typename Pipe = Identity> struct All {
  template <typename... Ts>
  using f = typename Pipe::template f<
      Bool<(Predicate::template f<Ts>::value && ...)>>;
};

/*
 * Any:
 * Checks if any value satisfies the predicate
 */
template <typename Predicate, typename Pipe = Identity> struct Any {
  template <typename... Ts>
  using f = typename Pipe::template f<
      Bool<(Predicate::template f<Ts>::value || ...)>>;
};

/*
 * Apply:
 * Applies the function to all types
 */
template <typename F, typename Pipe = ToList> struct Apply {
  template <typename... Ts>
  using f = typename IfElse<(sizeof...(Ts) < 10000)>::template f<
      Pipe, void>::template f<typename F::template f<Ts>...>;
};

/*
 * Partial:
 * Partial evaluation of a metafunction
 */
template <typename Pipe, typename... Ts> struct Partial {
  template <typename... Us> using f = typename Pipe::template f<Us..., Ts...>;
};

/*
 * lPartial:
 * Partial evaluation of a metaList like
 */
template <template <class...> class Pipe, typename... Ts> struct lPartial {
  template <typename... Us> using f = Pipe<Us..., Ts...>;
};

/*
 * PrePartial:
 * Partial evaluation of a metafunction
 */
template <typename Pipe, typename... Ts> struct PrePartial {
  template <typename... Us> using f = typename Pipe::template f<Ts..., Us...>;
};

/*
 * PartialA:
 * Partial evaluation of a metafunction
 */
template <typename Pipe, auto... Ts> struct PartialA {
  template <typename... Us> using f = typename Pipe::template f<Us..., Ts...>;
};

namespace ReplaceDetail {
template <typename T, typename U, typename Pipe = Identity>
struct ReplaceSingleImpl {
  template <typename Z>
  using f = typename Pipe::template f<
      typename IfElse<std::is_same<T, Z>::value>::template f<U, Z>>;
};
}; // namespace ReplaceDetail

/*
 * Replace:
 * Replaces all ocurences of T, with U
 */
template <typename T, typename U, typename Pipe = ToList> struct Replace {
  template <typename... Ts>
  using f = typename Apply<ReplaceDetail::ReplaceSingleImpl<T, U>,
                           Pipe>::template f<Ts...>;
};

/*
 * PipeN:
 * Applies Pipe to Result N times.
 */
template <int N> struct PipeN {
  template <typename Result, typename Pipe>
  using f = typename PipeN<N - 1>::template f<typename Pipe::template f<Result>,
                                              Pipe>;
};
template <> struct PipeN<0> {
  template <typename Result, typename Pipe> using f = Result;
};

/*
 * Greater:
 * Greater than meta function
 */
template <typename Pipe = Identity> struct Greater {
  template <typename T1, typename T2>
  using f = typename Pipe::template f<Bool<(T1::value > T2::value)>>;
};

/*
 * Less:
 * Less than meta function
 */
template <typename Pipe = Identity> struct Less {
  template <typename T1, typename T2>
  using f = typename Pipe::template f<Bool<(T1::value < T2::value)>>;
};
}; // namespace ml
#endif