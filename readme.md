 

# P1.3_exam : Binary search tree

### Presentation of the project

The project consists of the implementation of a **template** binary search tree (BST). A BST is a hierarchical (ordered) data structure where each **node** can have at most two children, namely, **left** and **right** child. Each node stores a **pair** of a **key** and the associated **value**. The binary tree is ordered according to the keys. 
If we assume that we sort the keys in ascending order (i.e., we use the less than `<` operator), then given a node `N`, all the nodes having keys **smaller** than the key of the node `N` are on the **left**. All the nodes with a key **greater** than the key of the node `N` are on the **right**.

![](.aux/binary.png)



### Source code, compilation and running commands

The source files that were implemented are the following :

```
main.cpp
bst.hpp
bst.tpp
```

a `Makefile` is as well provided, it allows to compile the code by running the `make` command.

The compilation options include the flags `-Wall -Wextra`; no warnings appear when compiling.

The compilation options include the flags `-O3` to insure optimization for benchmarking.

Once compiled, the code can be run by command `./main.x`.

To insure that the code has no memory leaks, it was tested (successfully) with valgrind using the command : `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./main.x`



# Implementations

### bst class presentation

##### template: 

- [x] The template binary search tree `bst` class was created, it has 3 templates:
  - first the key-type
  - then the value-type associated with the key
  - finally the type of the comparison operator type (optional, by default `std::less<key_type>` )

##### node sub-class

- [x] bst contains a `node` structure 

  - node contains
    - a `key`
    - a `value`
    - a `left` pointer 
    - a `right` pointer 

  - node has its own constructors, destructors and copy/move semantics

  

##### Constructors :

The following constructors were implemented:

- [x] a custom constructor creating a `bst` object and constructing a `root` node from `(key,value)` arguments
- [ ] a custom constructor creating a `bst` object and constructing a `root` node from another node (copy only)
- [ ] custom constructors creating a `bst` object from another bst object (copy and move)



##### Iterators:

- [ ] `iterator` and `const_iterator`. Forward iterator is sufficient.



### bst public member functions:

##### Insert

```c++
std::pair<iterator, bool> insert(const pair_type& x);
std::pair<iterator, bool> insert(pair_type&& x);
```

They are used to insert a new node. The function returns a pair of an iterator (pointing to the node) and a bool. The bool is true if a new node has been allocated, false otherwise (i.e., the key was already present in the tree). `pair_type` can be for example `std::pair<const key_type, value_type>`. 

> Insert function takes 1 argument.
>
> t.insert({3,4});  // the std::pair is constructor for us using the calibraces.
>
> if the key was already present return false, 
>
> if it was successfully inserted return true
>
> I can erase a key-node

##### Emplace

```c++
template< class... Types >
std::pair<iterator,bool> emplace(Types&&... args);
```

Inserts a new element into the container constructed in-place with the given args if there is no element with the key in the container.

> t.emplace(3,4);  
>
> Emplace constructs the pair inside this function.
>
> Emplace can eventually use insert.

##### Clear

```c++
void clear();
```

Clear the content of the tree.

##### Begin

```c++
iterator begin();
const_iterator begin() const;
const_iterator cbegin() const;
```

Return an iterator to the left-most node (which, likely, is not the root node).

> In the example case begin returns key-node `1`

##### End

```c++
iterator end();
const_iterator end() const;
const_iterator cend() const;
```

Return an iterator to one-past the last element.

> In this example case, key `14`

##### Find

```c++
iterator find(const key_type& x);
const_iterator find(const key_type& x) const;
```

Find a given key. If the key is present, returns an iterator to the proper node, `end()` otherwise.

> The most efficient way is to start from the root-node, in this case, `8`
>
> Find returns an iterator.

##### Balance

```c++
void balance();
```

Balance the tree. A simple and naive implementation is fine. The aim of this exam is not producing a super-performant code, but learning c++. No extra points for complicated algorithms.

> copy ordered list of nodes in a vector.
>
> clean the list
>
> center of the vector gives the root node.
>
> center of the half-left side of the vector gives the left-node below it
>
> center of the half-right side of the vector gives the right-node below root
>
> etc ...

##### Subscripting operator

```c++
value_type& operator[](const key_type& x);
value_type& operator[](key_type&& x);
```

Returns a reference to the value that is mapped to a key equivalent to `x`, performing an insertion if such key does not already exist.

##### Put-to operator

```c++
friend
std::ostream& operator<<(std::ostream& os, const bst& x);
```

Implement the friend function **inside** the class, such that you do not have to specify the templates for `bst`.

##### Copy and move

The copy semantics perform a deep-copy. Move semantics is as usual.

##### Benchmark

Test the performance of the lookups (using the function `find`) before and after the tree is balanced. Use proper numbers (and types) of nodes and lookups. Use the proper compile flags. Does lookup behaves as `O(log N)`? How your tree compares with `std::map`? 

- write a short report with plots
- test everything

> `-O0` compile flags <u>IS NOT OK</u>  for benchmarking!!
>
> We should be able to go two times faster than std::map. If my code doesn't reach that performance, don't worry.

### 

##### Particular attentions:

- [ ] Mark `noexcept` the right functions.

# Benchmarking