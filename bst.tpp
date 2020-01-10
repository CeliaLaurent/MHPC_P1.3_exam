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
//template <typename OK , typename OV>
class bst<K,V,C>::__iterator {
  using node_type = typename bst<K,V,C>::node;
  node_type* current_node;

 public:
  explicit __iterator(node_type* x)noexcept : current_node{x} {}

 
  using value_type = std::pair<const K,V>;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;
  using reference = value_type&;
  using pointer = value_type*;

  reference operator*() const noexcept {
          return current_node->data; 
          }
  pointer operator->() const noexcept { return &(*(*this)); }

  __iterator& operator++() noexcept {  // pre increment
    current_node = current_node->next.get();
    return *this;
  }

  __iterator operator++(int) noexcept {
    __iterator tmp{current_node};
    ++(*this);
    return tmp;
  }

  friend bool operator==(const __iterator& a, const __iterator& b) {
    return a.current_node == b.current_node;
  }
  friend bool operator!=(const __iterator& a, const __iterator& b) {
    return !(a == b);
  }
};

template <typename K, typename V, typename C>
class bst<K,V,C>::__const_iterator {
  using node_type = typename bst<K,V,C>::node;
  //using paircustomtype=std::pair<node_type,bool>;//customized pair type taking a node-struct type and a bool
  node_type* current_node;

 public:
  explicit __const_iterator(node_type* x)noexcept : current_node{x} {}

 
  using value_type = const std::pair<const K,V>;
  using difference_type = std::ptrdiff_t;
 using iterator_category = std::forward_iterator_tag;
  using reference = value_type&;
  using pointer = value_type*;

  reference operator*() const noexcept {
          return current_node->data; 
          }
  pointer operator->() const noexcept { return &(*(*this)); }

  __iterator& operator++() noexcept {  // pre increment
    current_node = current_node->next.get();
    return *this;
  }

  __iterator operator++(int) noexcept {
    __iterator tmp{current_node};
    ++(*this);
    return tmp;
  }

  friend bool operator==(const __iterator& a, const __iterator& b) {
    return a.current_node == b.current_node;
  }
  friend bool operator!=(const __iterator& a, const __iterator& b) {
    return !(a == b);
  }
};

  /*------------- insert function ----------------------*/
  template <typename K, typename V, typename C>
  //void bst<K,V,C>::insert(std::pair<K,V>&& newpair){
  std::pair<typename bst<K,V,C>::__iterator,bool> bst<K,V,C>::insert(std::pair<K,V>&& newpair){
    auto new_k=newpair.first;
    auto new_v=newpair.second;
    using iterator =typename bst<K,V,C>::__iterator;
    std::cout << "function (insert) received new node ( |"<<new_k<<"| ,"<<new_v<<")"  << std::endl;
    /*--- if root doesn't exist for this object, create it :--- */
    if(!root){
          root=std::make_unique<bst::node>(node(new_k,new_v) );
          std::cout << "   -> (insert) created the root node |"<<root->data.first <<"|"<< std::endl;
          return std::pair<iterator, bool>(root.get(),false); 
      }
    else {
    /*--- else, visit the tree searching for a node to which--- *
     *--- the new node could be attached                    --- */
       auto parent_node=root.get();
       auto test_node=root.get();
       while ( test_node ) {
         parent_node=test_node;
         if(op( test_node->data.first , new_k)){
            std::cout << "   -> (insert) going right after visiting node "<<test_node->data.first << std::endl;
            test_node=test_node->right.get();
          }
         else if( op( new_k,test_node->data.first )){  
            std::cout << "   -> (insert) going left after visiting node "<<test_node->data.first << std::endl;
            test_node=test_node->left.get();
          }
         else{
            /*--- if the comparison opertor doesn't give    --- *
             *--- true to both opposite, means equal data.firsts   --- */
            //nodeiscreated=false;
            std::cout << "   -> (insert): seems like this key already exist " << std::endl;
            break;
            return std::pair<iterator, bool>(test_node,false); 
         }
       }
       if(op( parent_node->data.first , new_k)){
         parent_node->right = std::make_unique<bst::node>( new_k,new_v); 
         std::cout << "   -> (insert) created a new node |"<<parent_node->right->data.first <<"| on the right of parent node |"<<parent_node->data.first<<"|"<< std::endl;
         return std::pair<iterator, bool>(parent_node->right.get(),false) ; 
        }
       else if( op( new_k,parent_node->data.first )){  
         parent_node->left = std::make_unique<bst::node>( new_k,new_v); 
         std::cout << "   -> (insert) created a new node |"<<parent_node->left->data.first <<"| on the left of parent node |"<<parent_node->data.first<<"|"<< std::endl;
         return std::pair<iterator , bool>(parent_node->left.get(),false) ; 
        }
    }
    std::cout << "------------------------------------" << std::endl;
  }


#endif
