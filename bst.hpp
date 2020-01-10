#ifndef _bst_
#define _bst_

#include <iostream>
#include <memory>  //unique_ptr
#include <iterator>
#include "ap_error.h"


template <typename K, typename V, typename C = std::less<K>>
class bst {

   /* --------- node structure ----------------------------------------- */ 
   struct node {
     //K key;  // key
     //V value;// value
     std::pair<const K, V> data;
     std::unique_ptr<node> left=nullptr;
     std::unique_ptr<node> right=nullptr;
     node* next=nullptr;
     //std::pair<K,V>{key,value}; 

     node(const K& k,const V& v) : data{std::make_pair(k,v)} {
       std::cout << "called node copy ctor for ( |"<<k<<"| ,"<<v<<")" << std::endl;
     }

     explicit node(const std::unique_ptr<node>& p) : data{p->data} {
       if (p->left)
         left = std::make_unique<node>(p->left);
       if (p->right)
         right = std::make_unique<node>(p->right);
       std::cout << "called node copy ctor using another node" << std::endl;
     }
   };

   /* --------- other private entities of bst -------------------------- */ 

   std::unique_ptr<node> root=nullptr;

   C op; // comparison operator 
  public:


   /* ---------  constructors and copy/move semantics ------------------ */ 
   bst() noexcept = default;                            // default constructor
   bst(bst&& otherbst) noexcept = default;              // default move constructor
   bst& operator=(bst&& otherbst) noexcept = default;   // default move assignement

 //bst(const K key_in, const V val_in): root{new node(key_in,val_in)} { 
   bst(const K key_in, const V val_in): root{ std::make_unique<node>(node(key_in,val_in)) } { 
	    std::cout << "called bst custom constructor creating root node with (key,val)=( |"<<key_in<<"| ,"<<val_in<<")" << std::endl; 
            }   ;   // custom constructor

//   bst(const bst& otherbst);                            // custom copy constructor
//   bst& operator=(const bst& otherbst);                 // custom copy assignement

  /* ----------- bst public iterator ----------------------------------- */ 
  //template <typename OK, typename OV>

  class __iterator;
  class __const_iterator;
  using iterator = __iterator;
  using const_iterator = __const_iterator;

  iterator begin() noexcept { return iterator{root.get()}; }
  iterator end() { return iterator{nullptr}; }

  const_iterator begin() const { return const_iterator{root.get()}; }
  const_iterator end() const { return const_iterator{nullptr}; }

  const_iterator cbegin() const { return const_iterator{root.get()}; }
  const_iterator cend() const { return const_iterator{nullptr}; }

  /* ----------- functions  ----------------------------------- */ 

  //void insert(std::pair<K, V>&& newpair);
  std::pair<__iterator,bool> insert(std::pair<K, V>&& newpair);
};
#include "bst.tpp"

#endif
