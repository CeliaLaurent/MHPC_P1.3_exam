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
template <typename OK , typename OV>
class bst<K,V,C>::__iterator {
  using nodestruct = typename bst<K,V,C>::node;
  nodestruct* current_node;

 public:
  explicit __iterator(nodestruct* x) noexcept : current_node{x} {}

  using key_type = OK;
  using value_type = OV;
//using difference_type = std::ptrdiff_t;
//using iterator_category = std::forward_iterator_tag;
  using reference = std::pair<const key_type,const value_type> &;
  using pointer = std::pair< const key_type,const value_type>*;

  reference operator*() const noexcept {
          return std::pair<key_type,value_type>(current_node->key, current_node->value); 
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

  /*------------- functions ----------------------*/
  template <typename K, typename V, typename C>
  template <typename OK, typename OV>
  void bst<K,V,C>::insert(OK&& new_k, OV&& new_v){
    if(!root){
          root=std::make_unique<bst::node>(node(new_k,new_v) );
      }
    else {
       auto test_node=root.get();
       while ( test_node ) {
         if(op( test_node->key , new_k)){
            std::cout << "called insert op("<<test_node->key<<","<<new_k<<") returns true, go right"  << std::endl;
            test_node=test_node->right.get();
          }
         else{
         std::cout << "called insert op("<<test_node->key<<","<<new_k<<") returns false, go left"  << std::endl;
            test_node=test_node->left.get();
         }
         test_node = std::make_unique<bst::node>( new_k,new_v); 
       }
    }
  }


#endif
