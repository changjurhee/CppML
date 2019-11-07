# `<CppML/Functional/ProductMap.hpp>`

## `ProductMap`

```c++
template <typename ...Fs, typename Pipe>
struct ProductMap {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `ProductMap<Fs..., Pipe>`

`ProductMap<Fs..., Pipe>` is a metafunction that passes to `Pipe` the parameter pack `Us...`, which is generated by invoking each `F` in the parameter pack `Fs...` on the corresponding element of the parameter pack `Ts...`.

```c++
f:: Ts... -> Fs(Ts).. -> ResultOf(Pipe)
```

#### `Args...`

The parameter pack of the `ProductMap<Args...>` will be treated as `Pipe`, and must always be provided (there is no default).

### Example

We will write the [`ml::CountIf`](../Algorithm/CountIf.md)[`<ml::IsClass<>`](../TypeTraits/IsClass.md) using [`ml::Reduce`](../Algorithm/Reduce.md). For that, we need the accumulator function
```
f:: Init, T -> Init, IsClass(T) -> U
```
which we will make using [`ml::ProductMap`](../Algorithm/ProductMap.md). Note that the above is equivalent to
```
f:: Init, T -> Identity(Init), IsClass(T) -> U
```
Thus,
```c++
template <typename Predicate>
using MakeCounter = ml::ProductMap<ml::Identity<>, Predicate, ml::Add<>>;

using T = ml::Invoke<
    ml::Reduce<
               MakeCounter<ml::CountIf<>>>,
    ml::Int<0>,                           // Init
    int, std::string, bool, std::string>; // Ts...

static_assert(
              std::is_same_v<
                  T,
                  ml::Int<2>>);

```