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
  //std::pair<typename bst<K,V,C>::typename __iterator<KO,VO>,bool> bst<K,V,C>::insert(OK&& new_k, OV&& new_v){
  //using iterator =typename bst<K,V,C>::__iterator<KO,VO>
    std::cout << "function (insert) received new node ( |"<<new_k<<"| ,"<<new_v<<")"  << std::endl;
    /*--- if root doesn't exist for this object, create it :--- */
    if(!root){
          root=std::make_unique<bst::node>(node(new_k,new_v) );
          std::cout << "   -> (insert) created the root node |"<<root->key <<"|"<< std::endl;
      }
    else {
    /*--- else, visit the tree searching for a node to which--- *
     *--- the new node could be attached                    --- */
       auto parent_node=root.get();
       auto test_node=root.get();
       while ( test_node ) {
         parent_node=test_node;
         if(op( test_node->key , new_k)){
            std::cout << "   -> (insert) going right after visiting node "<<test_node->key << std::endl;
            test_node=test_node->right.get();
          }
         else if( op( new_k,test_node->key )){  
            std::cout << "   -> (insert) going left after visiting node "<<test_node->key << std::endl;
            test_node=test_node->left.get();
          }
         else{
            /*--- if the comparison opertor doesn't give    --- *
             *--- true to both opposite, means equal keys   --- */
            //nodeiscreated=false;
            std::cout << "   -> (insert): seems like this key already exist " << std::endl;
            break;
            //return std::pair<iterator, bool>(test_node,false); 
         }
       }
       if(op( parent_node->key , new_k)){
         parent_node->right = std::make_unique<bst::node>( new_k,new_v); 
         std::cout << "   -> (insert) created a new node |"<<parent_node->right->key <<"| on the right of parent node |"<<parent_node->key<<"|"<< std::endl;
         //return std::pair<iterator, bool>(iterator(parent_node->right),false) ; 
        }
       else if( op( new_k,parent_node->key )){  
         parent_node->left = std::make_unique<bst::node>( new_k,new_v); 
         std::cout << "   -> (insert) created a new node |"<<parent_node->left->key <<"| on the left of parent node |"<<parent_node->key<<"|"<< std::endl;
         //return std::pair<iterator , bool>(iterator(parent_node->left),false) ; 
        }
    }
    std::cout << "------------------------------------" << std::endl;
  }


#endif
