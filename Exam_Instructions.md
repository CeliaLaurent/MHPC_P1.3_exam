# MHPC_P1.3_exam

# Advanced Programming Exam

The exam consists of a written project followed by an oral discussion. 
The written project is due to January 10, 2020, at 11:59 PM.
You can take the oral whenever you want, but before February 21, 2020.

- [x] Use a separate git repository. 
- [x] You have to upload all and <u>only the **source files** you wrote</u>, with a **Makefile** 
- [x] Create a **readme.md** where you describe 
  - [x] how to compile, 
  - [x] how to run your code, 
  - [ ] and a short report on what you have done, understood, and benchmarked.
- [ ] Your code must have no memory leaks. 

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./main.x
```

- [ ] No warnings must appear if compiled with the flags `-Wall -Wextra`.
- [ ] Don't change the name of the functions!
- [ ] Once finished, send me either the link to the repository or a `tar.gz` with the files (`.git` folder included).

## Binary search tree

The project consists of the implementation of a **template** binary search tree (BST). A BST is a hierarchical (ordered) data structure where each **node** can have at most two children, namely, **left** and **right** child. Each node stores a **pair** of a **key** and the associated **value**. The binary tree is ordered according to the keys. 
If we assume that we sort the keys in ascending order (i.e., we use the less than `<` operator), then given a node `N`, all the nodes having keys **smaller** than the key of the node `N` are on the **left**. All the nodes with a key **greater** than the key of the node `N` are on the **right**.

![](.aux/binary.png)

Practically speaking, given the binary tree in the picture, if you need to insert a new node with `key=5`, you start from the root node `8`, you go left since `5<8`, you reach node `3`, then you go right, you land in `6`, you go left reaching node `4`. Node `4` has no right child, so the new node `5` becomes the right child of node `4`. If a key is already present in the tree, the associated value **is not** changed.

From the implementation point of view, a node has two pointers `left` and `right` pointing to the left and right child, respectively. The pointers point to `nullptr` if they have no children.

It is useful to add a pointer (head, root, whatever you like) pointing to the top node, called **root node**. 

> In this example-case, 8 is the root one, the same for every other node.

### Tree traversal

The tree must be traversed in order, i.e., if I "print" the tree in the picture, I expect to see on the screen the sequence

```
1 3 4 6 7 8 10 13 14
```

node `1` is the first node, and node `14` is the last one.

> to get the first node, i go left as much as possible, and i pick the left-er node.
>
> then, i'll always try to go as left as i can.  
>
> If i can't go left, i go right.
>
> if i can't go right, i go up.
>
> when going up,  i'll try to go right.  
>
> if i can't go right, i go up.

### Assignments

You have to solve the following tasks using modern C++14 (C++17 is welcome as well).

- Implement a **template** binary search tree class, named `bst`.

- The class has three templates:

  - the key type
  - the value type associated with the key
  - the type of the comparison operator, which is used to compare two keys. `std::less<key_type>` should be used as default choice.

  >  template < typename key-type, typename value_type, typename cmp=std::less<key_type>>
  >
  > class bst {
  >
  >  cmp op;
  >
  > };

> how to use the comparison operator : 
>
> ```
> template <typename key_type, typename value_type, typename cmp>class bst{  cmp op;  ...};
> ```
>
> I cannot use the `<`, `>`, `<=`, `>=`, `==` operators. I can only use `op(a,b)` for example :
>
> ```
> a < b  --> op(a,b)
> a > b  --> op(b,a)
> a >= b --> !op(a,b)
> a <= b --> !op(b,a)
> a == b --> !op(a,b) && !op(b,a)
> ```

- Implement proper iterators for your tree (i.e., `iterator` and `const_iterator`). Forward iterator is sufficient.
- Mark `noexcept` the right functions.
- Remember the KISS principle.  

> KISS: keep it simple

- Implement at least the following public member functions.

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

>   `-O0` compile flags <u>IS NOT OK</u>  for benchmarking!!
>
> We should be able to go two times faster than std::map. If my code doesn't reach that performance, don't worry.

### Hints

- **Big hint** use `std::pair<const key_type,value_type>`, which is defined in the header `utility`
- use recursive functions
- start coding and using the iterators ASAP.

> dereferencing an iterator a should get a reference to a pair <key, value>
>
> the purpose of iterator is to provide access to data without exposing the underline structure
>
> we can use recursive functions, it simplifies and doesn't prevent performance.
>
> start coding the iterator as soon as possible, don't leave it the last step. small number of lines of code. insert will be then based on this, and everything will be easier..
>
> 
>
> One header: to include such class in another code (in the `main.cpp`), it should need to do only:
>
>  `# include "bst.hpp"`
>
> 

##### Structure of the code-files:

> ------
>
> **First solution :**
>
> bst.hpp contains:
>
> ```c++
> #ifndef bst
> #define bst
> 
> template<   >
> class bst{
>     ...
>     iterator Find(bst k& x);
> }
> #endif
> #include "bst.tpp"
> ```
>
> bst.tpp contains:
>
> ```c++
> #ifndef bst_tpp
> #define bst_tpp
> 
> template< k, v, c   >
>  bst<k,v,c>::iterator 
>  bst<k,v,c>::Find (const k & x){
>  
>  } 
> }
> #endif_tpp
> ```
>
> ------
>
> **or alternatively:**
>
> bst.hpp contains:
>
> ```c++
> #ifndef bst
> #define bst
> #include "bits_bst.hpp"
> #include "bst.tpp"
> #endif
> ```
>
> bits_bst.hpp contains:
>
> ```c++
> #ifndef bst
> #define bst
> 
> template<   >
> class bst{
>     ...
>     iterator Find(bst k& x);
> }
> #endif
> #include "bst.tpp"
> ```
>
> bst.tpp contains:
>
> ```c++
> #ifndef bst_tpp
> #define bst_tpp
> 
> template< k, v, c   >
>  bst<k,v,c>::iterator 
>  bst<k,v,c>::Find (const k & x){
>  
>  } 
> }
> #endif_tpp
> ```
>
> ------
>
> 



# TO DO LIST:

##### re-insert `#include "ap_error.h"`AA