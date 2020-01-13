#ifndef _bst_tpp_
#define _bst_tpp_

#include <iostream>
#include <memory>  //unique_ptr
#include <utility>
#include <iterator>
#include <vector>

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
   
    using value_type = KVpair_t;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using reference = value_type&;
    using pointer = value_type*;

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
                current_node=current_node->parent;
         if(!current_node->parent) current_node=nullptr;//found root, no next node
         else current_node=current_node->parent;//parent is right-ward, it is next node
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

///*------- BALANCE ------------------ */
//template <typename K, typename V, typename C>
//void bst<K,V,C>::balance(){
// std::vector<typename bst<K,V,C>::iterator_t> Vec_KVpair(numpair);
// std::vector<bool> insertpair(numpair,true);
// 
// //for(auto x: (*this)) Vec_KVpair.push_back(x);
// //std::copy( bst<K,V,C>::begin(), bst<K,V,C>::end(), Vec_KVpair.begin() );
// clear();
// std::cout<<"re-balancing the tree-----------------------"<<std::endl;
// size_t numbranches{1};
// auto Pib_out{insert(std::pair<const K,V>(Vec_KVpair[numpair/2]))};
// int insertedpairs{0};
// numbranches=1;
// while(insertedpairs<numpair){
//   for(size_t branch{0}; branch<numbranches ; branch++){
//     for(size_t pos=int((float(branch)+0.5)*(numpair/numbranches));pos<(branch+1)*numpair/numbranches ;pos++){
//       if(insertpair[pos]){
//         auto Pib_out2=insert(std::pair<const K,V>(Vec_KVpair[pos]));
//         if(Pib_out.second){ // if insertion went all right
//             insertpair[pos]=false;
//             insertedpairs++;
//         }
//         break ; 
//       }
//     }
//   numbranches*=2;
//  } 
// } 
//};
//

  /*------------- INSERT ----------------------*/
//template <typename K, typename V, typename C>
//template <typename KVpair_t>
//typename bst<K,V,C>::Pib_t bst<K,V,C>::insert(std::pair<const K, V>&& newpair){
// using iterator = typename bst<K,V,C>::__iterator<KVpair_t>;
//  auto new_k=newpair.first;
//  auto new_v=newpair.second;
//  std::cout << "function (insert) received new node ( |"<<new_k<<"| ,"<<new_v<<")"  << std::endl;
//  /*--- if root doesn't exist for this object, create it :--- */
//  if(!root){
//        root=std::make_unique<bst::node>(node(new_k,new_v) );
//        std::cout << "   -> (insert) created the root node |"<<root->KVpair.first <<"|"<< std::endl;
//        firstnode=root.get();
//        lastnode=root.get();
//        numpair=1;
//        return  {iterator(root.get()),false} ; 
//    }
//  else {
//  /*--- else, visit the tree searching for the direct parent of the new node --- */
//     auto parent_test=root.get();
//     auto current_test=root.get();
//     size_t left_steps{0};
//     size_t right_steps{0};
//     while ( current_test ) {
//        parent_test=current_test;
//        if(op( current_test->KVpair.first , new_k)){ /* comparison indicate go right */ 
//           std::cout << "   -> (insert) going right after visiting node "<<current_test->KVpair.first << std::endl;
//           current_test=current_test->right.get();
//           right_steps++;
//           if(!current_test){
//             parent_test->right = std::make_unique<bst::node>( new_k,new_v); 
//             if(!left_steps) lastnode=parent_test->right.get();
//             std::cout << "   -> (insert) created a new node |"<<parent_test->right->KVpair.first <<"| on the right of parent node |"<<parent_test->KVpair.first<<"|"<< std::endl;
//             numpair++;
//             return {iterator(parent_test->right),true} ; 
//           }
//         }
//        else if( op( new_k,current_test->KVpair.first )){ /* comparison indicate go left */ 
//           std::cout << "   -> (insert) going left after visiting node "<<current_test->KVpair.first << std::endl;
//           current_test=current_test->left.get();
//           left_steps++;
//           if(!current_test){
//             parent_test->left = std::make_unique<bst::node>( new_k,new_v); 
//             if(!right_steps) firstnode=parent_test->left.get();
//             std::cout << "   -> (insert) created a new node |"<<parent_test->left->KVpair.first <<"| on the left of parent node |"<<parent_test->KVpair.first<<"|"<< std::endl;
//             numpair++;
//             return {iterator(parent_test)->left,true}  ;
//           }
//         }
//        else{    /*--- new_k is already present in the tree  --- */
//           std::cout << "   -> (insert): inserted node has a key that already exist " << std::endl;
//           return {iterator(current_test),false}; 
//        }
//     }
//  }
//};


#endif
