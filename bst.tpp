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
  template <typename KVpair> //KVpair will be "const pair<const K,V>" or "pair<const K,V>"
  class bst<K,V,C>::__iterator {
    //using node_type = typename bst<K,V,C>::node;
     bst<K,V,C>::node_type* current_node;

   public:
    explicit __iterator(node_type* x)noexcept : current_node{x} {}
   
  //  using KVpair_type = O; //std::pair<const K,V>;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using reference = KVpair&;
    using pointer = KVpair*;

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
  typename bst<K,V,C>::Pib_t bst<K,V,C>::insert(std::pair<const K, V>&& newpair){
    auto new_k=newpair.first;
    auto new_v=newpair.second;
    std::cout << "function (insert) received new node ( |"<<new_k<<"| ,"<<new_v<<")"  << std::endl;
    /*--- if root doesn't exist for this object, create it :--- */
    if(!root){
          root=std::make_unique<bst::node>(node(new_k,new_v) );
          std::cout << "   -> (insert) created the root node |"<<root->data.first <<"|"<< std::endl;
          lastinserted=root.get();
          return  {root.get()->data,false} ; 
      }
    else {
    /*--- else, visit the tree searching for a node to which--- *
     *--- the new node could be attached                    --- */
       auto parent_node=root.get();
       auto test_node=root.get();
       while ( test_node ) {
         parent_node=test_node;
         if(op( test_node->data.first , new_k)){
            test_node=test_node->right.get();
            std::cout << "   -> (insert) going right after visiting node "<<test_node->data.first << std::endl;
          }
         else if( op( new_k,test_node->data.first )){   test_node=test_node->left.get();
            std::cout << "   -> (insert) going left after visiting node "<<test_node->data.first << std::endl;
          }
         else{
            /*--- mew_k is already present in the tree  --- */
            std::cout << "   -> (insert): seems like this key already exist " << std::endl;
            return {test_node->data,false}; 
         }
        }
       if(op( parent_node->data.first , new_k)){
         parent_node->right = std::make_unique<bst::node>( new_k,new_v); 
         std::cout << "   -> (insert) created a new node |"<<parent_node->right->data.first <<"| on the right of parent node |"<<parent_node->data.first<<"|"<< std::endl;
          lastinserted->next=parent_node->right.get();//each node has next pointing to the node inserted after him (after in time)
          lastinserted=parent_node->right.get();      // the node we inserted will be known by the next node that will be inserted (in future)
         return {parent_node->right->data,true} ; 
        }
       else if( op( new_k,parent_node->data.first )){  
         parent_node->left = std::make_unique<bst::node>( new_k,new_v); 
         std::cout << "   -> (insert) created a new node |"<<parent_node->left->data.first <<"| on the left of parent node |"<<parent_node->data.first<<"|"<< std::endl;
          lastinserted->next=parent_node->left.get();//each node has next pointing to the node inserted after him (after in time)
          lastinserted=parent_node->left.get();      // the node we inserted will be known by the next node that will be inserted (in future)
         return {parent_node->left->data,true}  ;
        }
    }
  }

#endif
