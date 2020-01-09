#ifndef _bst_
#define _bst_

#include <iostream>
#include <memory>  //unique_ptr

#include "ap_error.h"


template <typename K, typename V, typename C = std::less<K>>
class bst {
   struct node {
     std::unique_ptr<node> left=nullptr;
     std::unique_ptr<node> right=nullptr;
     K key;  // key
     V value;// value
     //std::pair<K,V>{key,value}; 

     node(const K& k,const V& v) : key{k}, value{v} {
       std::cout << "called node copy ctor (key,val)" << std::endl;
     }

     explicit node(const std::unique_ptr<node>& p) : key{p->key}, value{p->value} {
       if (p->left)
         right = std::make_unique<node>(p->left);
       if (p->right)
         right = std::make_unique<node>(p->right);
       std::cout << "called node copy ctor using another node" << std::endl;
     }
   };

   C op; // comparison operator 
   std::unique_ptr<node> root=nullptr;

  public:
   bst() noexcept = default;                            // default constructor
   bst(bst&& otherbst) noexcept = default;              // default move constructor
   bst& operator=(bst&& otherbst) noexcept = default;   // default move assignement

 //bst(const K key_in, const V val_in): root{new node(key_in,val_in)} { 
   bst(const K key_in, const V val_in): root{ std::make_unique<node>( node(key_in,val_in)) } { 
	    std::cout << "called bst custom constructor creating root node" << std::endl; 
            }   ;   // custom constructor

//   bst(const bst& otherbst);                            // custom copy constructor
//   bst& operator=(const bst& otherbst);                 // custom copy assignement

};
#include "bst.tpp"

#endif
