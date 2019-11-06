# `<CppML/Algorithm/CountIf.hpp>`

## `CountIf`

```c++
template <typename Predicate, typename Pipe = ml::Identity>
struct CountIf {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `CountIf<Predicate, Pipe>`

`CountIf<Predicate, Pipe>` is a metafunction that returns [`ml::Int`](../Vocabulary/Const.md)`<count>`,  where count is the number of elements of the parameter pack `Ts`, for which the Predicate holds.  The result is passed to `Pipe`, which defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f:: Ts... -> ml::Int<count> -> ResultOf(Pipe)
```

#### Predicate

Predicate must be a metafunction returning [`ml::Bool<truth_value>`](../Vocabulary/Const.md).
```
f:: T -> ml::Bool<truth_value>
```

### Example

```c++
using T0 = ml::Invoke<
                     ml::CountIf<ml::IsClass<>>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<T, ml::Int<1>);

using T1 = ml::Invoke<
                     ml::CountIf<
                               ml::IsClass<>,
                               ml::Increment<>>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<T, ml::Int<2>);
```