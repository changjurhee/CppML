# `<CppML/Algorithm/PartitionIds.hpp>`

### `PartitionIds<Predicate, Pipe>`

`PartitionIds<Predicate, Pipe>` is a metafunction that passes to `Pipe` two [`ml::ListT`](../Vocabulary/List.md)`<ml::Int<Is>...>`, where the first list consists of `ml::Int<Is>...`, indexes of types which evaluate to [`ml::Bool`](../Vocabulary/Value.md)`<true>` under `Predicate`, and the second indexes of those `ml::Int<Is>...` that evaluate to [`ml::Bool`](../Vocabulary/Value.md)`<false>`. Formally speaking, `PartitionIds<Predicate, Pipe>` forms (indexes of ) equivalence classes of `Ts...` under `Predicate`. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: Ts... -> (ml::ListT<ml::Int<I0s>...>, ml::ListT<ml::Int<I1s>...>) >-> Pipe
```

#### Predicate

Predicate can be any metafunction returning a single type.
```
f:: T -> U
```

### Example

We partition indexes a parameter pack, to those whose alignment is greater than 4, and those whose it is not.
```c++
using T = ml::f<
              ml::PartitionIds<
                    ml::AlignOf<
                        ml::PartialR<
                            ml::Greater<>,
                            ml::Int<4>>>>,
              int, char, long, bool, double>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<
                      ml::ListT<ml::Int<2>, ml::Int<4>>,
                      ml::ListT<ml::Int<0>, ml::Int<1>, ml::Int<3>>);
```
**NOTE** that
```
ml::AlignOf<          // take aligment of the input and pipe into
      ml::PartialRR<       // a partial evaluation of the metafunction
          ml::Greater<>, // greater
          ml::Int<4>>>   // on ml::Int<4>
```
is a metafunction of the type
```
f:: T -> AlignOf(T) >-> Curry<Greater>(4)
```
and conforms to the [predicate](#predicate) constraints.
