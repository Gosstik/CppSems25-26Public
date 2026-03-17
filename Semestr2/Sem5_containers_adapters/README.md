# Class 5. Containers and container adaptors

To iterate over list, map and unordered_map we have to use iterators. Therefore we studied them before studying those containers.

## List

Supported operations:

- insert(iter, elem)
- erase(iter), erase(start, finish)
- push_back/pop_back
- push_front/pop_front
- size()

Bidirectional iterator.

Cyclic structure with fake node in implementation. We can't store T to support types without default ctor. If we store T* that we need x2 allocations. Therefore we have two types: BaseNode (2 pointers) and Node (BaseNode + T).

Fields: BaseNode and size.

After swap inly iterator to end() is invalidated.

Additional operations:

- sort
- merge
- splice(it, from, to) (O(to-from) if other list, O(1) if same list)

## Forward List

- No push_back/pop_back
- No size()
- Forward Iterator
- No insert, but has insert_after

## Tasks on list

- Is list cyclically looped
- Copy fancy list (create n fake nodes)
- LRU cache

## Map

Operations:

- pair<iterator,bool> insert(const pair<Key,Value>&)
- size_t erase(Key)
- iterator erase(iterator)
- Value& at(Key)
- Value& operator[](Key) --- cannot be called on constant map !!!
- iterator find(Key)
- size_t count(Key)
- contains

Ineffective way (use find instead):

```c++
if (m.count(1)) {
  m[1] = 2;
}

if (auto it = m.find(1); it != end()) {
  it->second = 2;
}
```

Internal structure (fields and fields of Node).

bool store in one of pointer bits (e.g. parent).

Time for iterator increment.

Mistake in type in range based for:

```c++
for (const pair<int, std::string>& p: m) { // will make copy
  // ...
}

for (const auto& p: m) { // no copy

}
```

For the same reason modification operations (next_permutation, reverse) from `<algorithm>` also do not work.

Additional operations:

- lower_bound
- upper_bound

Exception safety. Compare can throw exceptions.

## Unordered Map

- Store array for HashTable and ForwardList for iterators. In implementation we need access to private fields of ForwardList.
- In array we store pointer to the last element of previous bucket. First bucket stores pointer to FakeNode
- Store hash in Node to be able to do Find
- Insert new bucket
- Erase bucket with only one element
- Erase by iterator
- Rehash: erase + insert. References and pointers must remain valid in umap and uset (after insert). Iterators may remain invalid (after insert that caused rehash)
- swap does not invalidate iterators but it invalidate iterator to end()
- Exception safety: Hash and Equal can throw. During rehash we have to precompute hashes and check equality for values with the same hash.

