#ifndef _bst_
#define _bst_

#include <iostream>
#include <memory>  //unique_ptr
#include <iterator>
#include <utility>
#include <vector>
#include "ap_error.h"


template <typename K, typename V, typename C = std::less<K>>
class bst {

   /* --------- node structure ----------------------------------------- */ 
   struct node {
     std::pair<const K, V> KVpair;
     std::unique_ptr<node> left=nullptr;
     std::unique_ptr<node> right=nullptr;
     node* parent=nullptr;

     node(const K& key, V& val) : KVpair{std::make_pair(key,val)} {};
     node(std::pair<const K,V>& pair) : KVpair{std::make_pair(pair.first,pair.second)} {};

   };

   node* firstnode=nullptr;
   /* --------- other private entities of bst -------------------------- */ 

   std::unique_ptr<node> root=nullptr;

   C op; // comparison operator 
   int numpair{0};

 public:

   /* ---------  constructors and copy/move semantics ------------------ */ 
   bst() noexcept = default;                            // default constructor
   bst(bst&& otherbst) noexcept = default;              // default move constructor
   bst& operator=(bst&& otherbst) noexcept = default;   // default move assignement
   

   /* ----------- bst public iterator ----------------------------------- */ 
  template <typename KVpair_t> //KVpair_t will be "const pair<const K,V>" or "pair<const K,V>"
  class __iterator {
    using bst_node_type = typename bst<K,V,C>::node;
     bst_node_type* current_node;

   public:
    explicit __iterator(bst_node_type* x)noexcept : current_node{x} {}
   
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
  /* ------------------- some usefull aliases of types ------------------ */  
  using iterator = __iterator<std::pair<const K,V>>;
  using const_iterator = __iterator<const std::pair<const K,V>>;
  using Pib_t =std::pair<iterator, bool> ;

  /* --------------------  bst member functions  ------------------------ */ 


  /*------- BEGIN ------------------ */
  iterator begin() noexcept { return iterator(firstnode); }
  const_iterator begin() const noexcept { return const_iterator(firstnode); }
  const_iterator cbegin() const noexcept { return const_iterator(firstnode); }

  /*--------- END ------------------ */
  iterator end() noexcept { return iterator(nullptr); }
  const_iterator end() const noexcept { return const_iterator(nullptr); }
  const_iterator cend() const noexcept { return const_iterator(nullptr); }

  /* ---------- find --------------------------------*/
  iterator find(const K& x ){
       auto current_test=root.get();
       while ( current_test ) {
          if(op( current_test->KVpair.first , x )){ /* comparison indicate go right */ 
             current_test=current_test->right.get();
             if(!current_test) return iterator(nullptr); 
             }
          else if( op( x ,current_test->KVpair.first )){ /* comparison indicate go left */ 
             current_test=current_test->left.get();
             if(!current_test) return iterator(nullptr); 
           }
          else{    /*--- key x  present in the tree  --- */
             return iterator(current_test); 
          }
       }
      
       return iterator(current_test); 
  }

  const_iterator find(const K& x) const{
       auto current_test=root.get();
       while ( current_test ) {
          if(op( current_test->KVpair.first , x )){ /* comparison indicate go right */ 
             current_test=current_test->right.get();
             if(!current_test) return iterator(nullptr); 
             }
          else if( op( x ,current_test->KVpair.first )){ /* comparison indicate go left */ 
             current_test=current_test->left.get();
             if(!current_test) return iterator(nullptr); 
           }
          else{    /*--- key x  present in the tree  --- */
             return iterator(current_test); 
          }
       }
       return end;
  }
  
  /*------- INSERT ------------------ */
  std::pair<iterator,bool> insert(const std::pair<const K, V>& newpair)
  {
    auto new_k=newpair.first;
    auto new_v=newpair.second;
    if(!root){ /*--- if root doesn't exist for this object, create it :--- */
          root=std::make_unique<bst::node>(node(new_k,new_v) );
          firstnode=root.get();
          numpair=1;
          return  std::make_pair(iterator(root.get()),false) ; 
      }
    else {    /*--- else, visit the tree searching for the direct parent of the new node --- */
       auto parent_test=root.get();
       auto current_test=root.get();
       size_t left_steps{0};
       size_t right_steps{0};
       while ( current_test ) {
          parent_test=current_test;
          if(op( current_test->KVpair.first , new_k)){ /* comparison indicate go right */ 
             current_test=current_test->right.get();
             right_steps++;
             if(!current_test){
               parent_test->right = std::make_unique<bst::node>( new_k,new_v); 
               numpair++;
               return std::make_pair(iterator(parent_test->right.get()),true) ; 
             }
           }
          else if( op( new_k,current_test->KVpair.first )){ /* comparison indicate go left */ 
             current_test=current_test->left.get();
             left_steps++;
             if(!current_test){
               parent_test->left = std::make_unique<bst::node>( new_k,new_v); 
               if(!right_steps) firstnode=parent_test->left.get();
               numpair++;
               return std::make_pair(iterator(parent_test->left.get()),true)  ;
             }
           }
          else{    /*--- new_k is already present in the tree  --- */
             return std::make_pair(iterator(current_test),false); 
          }
       }
    }
  };
  
  std::pair<iterator,bool> insert(std::pair<const K, V>&& newpair)
  {
    auto new_k=newpair.first;
    auto new_v=newpair.second;
    if(!root){ /*--- if root doesn't exist for this object, create it :--- */
          root=std::make_unique<bst::node>(node(new_k,new_v) );
          firstnode=root.get();
          numpair=1;
          return  std::make_pair(iterator(root.get()),false) ; 
      }
    else {    /*--- else, visit the tree searching for the direct parent of the new node --- */
       auto parent_test=root.get();
       auto current_test=root.get();
       size_t left_steps{0};
       size_t right_steps{0};
       while ( current_test ) {
          parent_test=current_test;
          if(op( current_test->KVpair.first , new_k)){ /* comparison indicate go right */ 
             current_test=current_test->right.get();
             right_steps++;
             if(!current_test){
               parent_test->right = std::make_unique<bst::node>( new_k,new_v); 
               numpair++;
               return std::make_pair(iterator(parent_test->right.get()),true) ; 
             }
           }
          else if( op( new_k,current_test->KVpair.first )){ /* comparison indicate go left */ 
             current_test=current_test->left.get();
             left_steps++;
             if(!current_test){
               parent_test->left = std::make_unique<bst::node>( new_k,new_v); 
               if(!right_steps) firstnode=parent_test->left.get();
               numpair++;
               return std::make_pair(iterator(parent_test->left.get()),true)  ;
             }
           }
          else{    /*--- new_k is already present in the tree  --- */
             return std::make_pair(iterator(current_test),false); 
          }
       }
    }
  };
  
  /*------- EMPLACE ------------------ */
  template <typename... Types>
  std::pair<iterator, bool> emplace(Types&&... args){ return insert({std::forward<Types>(args)...});}
  
  /*------- CLEAR ------------------ */
  void clear() {root.reset();}

  /*------- BALANCE ------------------ */
  void balance(){
   std::vector<bool> insertpair(numpair,true);
   //std::vector<iterator> Vec_KVpair;
   //for(auto x: (*this)) Vec_KVpair.push_back(x);
   std::vector<std::pair<const K,V>> Vec_KVpair(numpair);
   std::copy( begin(), end(), Vec_KVpair.begin() );
   clear();
   std::cout<<"re-balancing the tree-----------------------"<<std::endl;
   size_t numbranches{1};
   insert(Vec_KVpair[numpair/2]);
   int insertedpairs{0};
   numbranches=1;
   while(insertedpairs<numpair){
     for(size_t branch{0}; branch<numbranches ; branch++){
       for(size_t pos=int((float(branch)+0.5)*(numpair/numbranches));pos<numpair ;pos++){
         if(insertpair[pos]){
           insert(Vec_KVpair[pos]);
           insertpair[pos]=false;
           insertedpairs++;
           break ; 
         }
       }
     numbranches*=2;
    } 
   } 
  };

  /*------- subscripting operator ------------------ */
  V& operator[](K&& key){
        iterator find_out{find(key)};
        if(find_out==end())
	   find_out = (emplace(std::forward<K>(key),V{})).first;
	return (*find_out).second;
}
  /*------- put to operator ------------------ */
  friend std::ostream& operator<<(std::ostream& os,const bst& bstobject){
    for(const auto pair : bstobject) os << pair.first <<"("<<pair.second<<"), ";
    os << std::endl;
    return os;
  }
};

#endif
