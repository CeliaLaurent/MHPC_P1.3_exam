 

# P1.3_exam : Binary search tree

### Presentation of the project

The project consists of the implementation of a **template** binary search tree (BST). A BST is a hierarchical (ordered) data structure where each **node** can have at most two children, namely, **left** and **right** child. Each node stores a **pair** of a **key** and the associated **value**. The binary tree is ordered according to the keys. 
If we assume that we sort the keys in ascending order (i.e., we use the less than `<` operator), then given a node `N`, all the nodes having keys **smaller** than the key of the node `N` are on the **left**. All the nodes with a key **greater** than the key of the node `N` are on the **right**.

![](.aux/binary.png)



### Source code, compilation and running commands

- The source files that were implemented are the following :

```
main.cpp
bst.hpp
bst.tpp
```

- A `Makefile` is as well provided, it allows to compile the code by running the command:

```
make
```

The compilation options include the flags `-Wall -Wextra`; no warnings appear when compiling.

The compilation options include the flags `-O3` to insure optimization for benchmarking.

- Running and testing

Once compiled, the code can be run by command `./main.x`.

To compile and run the program in one single command, use:

```
make run
```

To insure that the code has no memory leaks, it was tested (successfully) with valgrind using the command : 

```
make valgrind
```

which corresponds to the command `make` followed by  `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./main.x`, or 



# Implementations

### bst class presentation

##### template: 

The template binary search tree `bst` class was created, it has 3 templates:
- first the key-type
- then the value-type associated with the key
- finally the type of the comparison operator type (optional, by default `std::less<key_type>` )

##### node sub-class

bst contains a `node` structure 

- node contains
  - a `key`
  - a `value`
  - a `left` pointer 
  - a `right` pointer 

- node has its own constructors, destructors and copy/move semantics



##### Iterators:

`iterator` and `const_iterator`. Forward iterator is sufficient.



### bst public member functions:

##### construction of a bst object

in the main, to declare an object:

```c++
bst<int,std::string> bstobject{};
```

or

```c++
bst<int,std::string> bstobject(8,'topnode');
```

##### Insert

The insert function takes as input any pair that can be casted in a pair of 2 arguments having the same types as those given in the construction of the bst object. Per example:

```c++
auto out=bstobject.insert({3,"lower node"});
```

The function returns a pair of an iterator (pointing to the node) and a bool. The bool is true if a new node has been allocated, false otherwise (i.e., the key was already present in the tree). 

The other functions were implemented but suffer from some coding errors that prevented me to test them or run the benchmarks.

One of the main difficulties that i encountered  is linked to the way of handling the return types and templates of the functions. The first version of my code used 2 separated for the bst class, the .hpp handling the declaration and short definitions and the .tpp containing the more complex definitions. But this way of doing created to many conflicts and error messages involving types too long to understand the origin of the errors. For this reason, to simplify the situation I implemented all the definitions inside the class declaration section, even if i know that it is not a good practice.

I tried to keep the code as simple as possible, but I see that it is not simple enough to make me understand where my compilation errors are coming from.

I chosed to focus on the debugging of the code searching to understand the origin of the compilation errors, given that balance was non functional i didn't complete the benchmarks.