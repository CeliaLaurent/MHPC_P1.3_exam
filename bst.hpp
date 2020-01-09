#ifndef _bst_
#define _bst_

#include <iostream>
#include <memory>  //unique_ptr

#include "ap_error.h"


template <typename K, typename V, typename C = std::less<K>>
class bst {
   struct node {
     std::unique_ptr<node> left;
     std::unique_ptr<node> right;
     K key;  // key
     V value;// value
     //std::pair<K,V>{key,value}; 

     node(const K& k,const V& v) : key{k}, value{v} {
       std::cout << "copy ctor using key,val" << std::endl;
     }

     explicit node(const std::unique_ptr<node>& p) : value{p->value} {
       if (p->left)
         right = std::make_unique<node>(p->left);
       if (p->right)
         right = std::make_unique<node>(p->right);
       std::cout << "copy ctor using another node" << std::endl;
     }
   };

   C op; // comparison operator
   std::unique_ptr<node> root;

  public:
   bst() noexcept = default;                            // default constructor
   bst(bst&& otherbst) noexcept = default;              // default move constructor
   bst& operator=(bst&& otherbst) noexcept = default;   // default move assignement

//   bst(const bst& otherbst);                            // custom copy constructor
//   bst& operator=(const bst& otherbst);                 // custom copy assignement

};
#include "bst.tpp"

#endif
