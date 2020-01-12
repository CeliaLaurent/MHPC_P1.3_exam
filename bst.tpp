#ifndef _bst_tpp_
#define _bst_tpp_

#include <iostream>
#include <memory>  //unique_ptr
#include <utility>
#include <iterator>

#include "ap_error.h"
#include "bst.hpp"
 /* -----------  bst iterator -------------------------------------- */ 

  template <typename K, typename V, typename C>
  template <typename KVpair_t> //KVpair_t will be "const pair<const K,V>" or "pair<const K,V>"
  class bst<K,V,C>::__iterator {
    using bst_node_type = typename bst<K,V,C>::node_type;
     bst_node_type* current_node;

   public:
    explicit __iterator(node_type* x)noexcept : current_node{x} {}
   
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using reference = KVpair_t&;
    using pointer = KVpair_t*;

    /* -------------iterator reference / pointer   ----------------- */
    reference operator*() const noexcept { return current_node->KVpair;  }
    pointer operator->() const noexcept { return &(*(*this)); }

    /* -------------iterator operator++ --------------------------- */
    __iterator& operator++() noexcept {  // pre increment
      if(current_node->right){// if iterated node has a right, go right once then as left as i can
         current_node=current_node->right.get();
         while(current_node->left) current_node=current_node->left.get();
         }
      else{//else go up as long as i have a parent(ie not root) and as long as upward motion is leftward
         while(current_node->parent && current_node==(current_node->parent)->right)
                current_node=current_node->parent.get();
         if(!current_node->parent) current_node=nullptr;//found root, no next node
         else current_node=current_node->parent.get();//parent is right-ward, it is next node
         }
      return *this;
    }

    /* -------------iterator operator++(int) ----------------------- */
    __iterator operator++(int) noexcept {
      __iterator tmp{current_node};
      ++(*this);
      return tmp;
    }

    /* -------------iterator operator ==     ----------------------- */
    friend bool operator==(const __iterator& a, const __iterator& b) {
      return a.current_node == b.current_node;
    }
    /* -------------iterator operator !=     ----------------------- */
    friend bool operator!=(const __iterator& a, const __iterator& b) {
      return !(a == b);
    }
  };

  /*------------- insert function ----------------------*/
  template <typename K, typename V, typename C>
  typename bst<K,V,C>::Pib_t bst<K,V,C>::insert(std::pair<const K, V>&& newpair){
    auto new_k=newpair.first;
    auto new_v=newpair.second;
    std::cout << "function (insert) received new node ( |"<<new_k<<"| ,"<<new_v<<")"  << std::endl;
    /*--- if root doesn't exist for this object, create it :--- */
    if(!root){
          root=std::make_unique<bst::node>(node(new_k,new_v) );
          std::cout << "   -> (insert) created the root node |"<<root->KVpair.first <<"|"<< std::endl;
          firstnode=root.get();
          lastnode=root.get();
          return  {root.get()->KVpair,false} ; 
      }
    else {
    /*--- else, visit the tree searching for the direct parent of the new node --- */
       auto parent_test=root.get();
       auto current_test=root.get();
       size_t left_steps{0};
       size_t right_steps{0};
       while ( current_test ) {
          parent_test=current_test;
          if(op( current_test->KVpair.first , new_k)){ /* comparison indicate go right */ 
             std::cout << "   -> (insert) going right after visiting node "<<current_test->KVpair.first << std::endl;
             current_test=current_test->right.get();
             right_steps++;
           }
          else if( op( new_k,current_test->KVpair.first )){ /* comparison indicate go left */ 
             std::cout << "   -> (insert) going left after visiting node "<<current_test->KVpair.first << std::endl;
             current_test=current_test->left.get();
             left_steps++;
           }
          else{    /*--- new_k is already present in the tree  --- */
             std::cout << "   -> (insert): inserted node has a key that already exist " << std::endl;
             return {current_test->KVpair,false}; 
          }
       }
       if(op( parent_test->KVpair.first , new_k)){
          parent_test->right = std::make_unique<bst::node>( new_k,new_v); 
          if(!left_steps) lastnode=parent_test->right.get();
          std::cout << "   -> (insert) created a new node |"<<parent_test->right->KVpair.first <<"| on the right of parent node |"<<parent_test->KVpair.first<<"|"<< std::endl;
          return {parent_test->right->KVpair,true} ; 
        }
       else if( op( new_k,parent_test->KVpair.first )){  
          parent_test->left = std::make_unique<bst::node>( new_k,new_v); 
          if(!right_steps) firstnode=parent_test->left.get();
          std::cout << "   -> (insert) created a new node |"<<parent_test->left->KVpair.first <<"| on the left of parent node |"<<parent_test->KVpair.first<<"|"<< std::endl;
          return {parent_test->left->KVpair,true}  ;
        }
    }
  };

#endif
