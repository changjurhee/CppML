# `<CppML/Algorithm/Contains.hpp>`

## `Contains`

```c++
template <typename T, typename Pipe = ml::Identity>
struct Contains {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Contains<T, Pipe>`

`Contains<T, Pipe>` is a metafunction that passes to `Pipe` an [`ml::Bool`](../Vocabulary/Value.md)`<truth_value>`, where truth_value marks whether the parameter pack `Ts` contains `T`. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f:: Ts... -> ml::Bool<truth_value> >-> Pipe
```

### Example

```c++
using T0 = ml::f<
                 ml::Contains<int>,
                 int, char, std::string>;
static_assert(
              std::is_same_v<T, ml::Bool<true>);

using T1 = ml::f<
                 ml::Contains<
                           int,
                           ml::Not<>>,
                 int, char, std::string>;
static_assert(
              std::is_same_v<T, ml::Bool<false>);
```
