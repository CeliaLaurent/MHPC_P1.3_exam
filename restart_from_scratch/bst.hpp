#ifndef _bst_
#define _bst_
#include <iostream>
#include <memory>  //unique_ptr
#include <iterator>
#include <utility>
#include <vector>
#include "node.hpp"
#include "iterator.hpp"
template <typename K,typename V,typename C= std::less<K>> //Key, Value and Comparison-operator
 class bst{
	 using node=Node<std::pair<const K,V>>;
	 std::unique_ptr<node> root;
         node* firstnode=nullptr;
	 C op;
         int numpair;
      public:
	 /* ------- Default Constructor ------------------ */
         bst() noexcept =default;

	 /* ------- Default Destructor  ------------------ */
         ~bst() noexcept = default;

	 /* ----- Constructor taking as argument a -------- *
	  * ------comparison-operator object -------------- */
         bst(C op_obj): op{op_obj} {}

	 /* ------- move constructor                      - */
         bst(bst && bst_src):
		 root{std::move(bst_src.root)},// class type 
		 firstnode{std::move(bst_src.firstnode)},// class type 
                 op{std::move(bst_src.op)},
                 numpair{std::exchange(bst_src.numpair,0)} //non-class type
	 {std::cout<<"move constructor of a bst object has been called "<<std::endl; } 

	 /* ------- copy constructor (performs deep copy)- */
         bst(const bst & bst_src){
	    if(bst_src.root){ 
                if(root) clear();
		node* node_src{bst_src.root.get()};
                root=std::make_unique<node>(node_src->NPair);
        	if(node_src->left or node_src->right)
        	  recursively_create_left_or_right(root.get(),node_src);
		while(node_src->left)
			 node_src=node_src->left.get();
		firstnode=node_src;
            }
            numpair=bst_src.numpair;
            op=bst_src.op; 
            std::cout<<"deep copy constructor of a bst object has been called "<<std::endl;
         };
         /* -------- recursive creation of nodes for deep copy constructor --------*/
         void recursively_create_left_or_right(node * mynode, node * node_src){
            if(node_src->left){
               mynode->left=std::make_unique<node>((node_src->left)->NPair,mynode);
               recursively_create_left_or_right(mynode->left.get(),node_src->left.get());
            }
            if(node_src->right){
               mynode->right=std::make_unique<node>((node_src->right)->NPair,mynode);
               recursively_create_left_or_right(mynode->right.get(),node_src->right.get());
            }
         } 

	 /* -------- some usefull aliases ------------------*/
         using iterator = Iterator<node, std::pair<const K,V> >;
         using const_iterator = Iterator<node,const std::pair<const K,V> >;


  /*------- BEGIN ------------------ */
  iterator begin() noexcept { return iterator(firstnode); }
  const_iterator begin() const noexcept { return const_iterator(firstnode); }
  const_iterator cbegin() const noexcept { return const_iterator(firstnode); }

  /*--------- END ------------------ */
  iterator end() noexcept { return iterator(nullptr); }
  const_iterator end() const noexcept { return const_iterator(nullptr); }

  /*--------- Find ------------------ */
  iterator find(const K & key) noexcept {
          auto tmp = begin();
          for (int n=0;n<numpair;n++) {
            if((*tmp).first==key)
		    return tmp;
            tmp ++ ;
          }
	  return tmp; 
  }
  const_iterator find(const K & key) const noexcept {
          auto tmp = cbegin();
          for (int n=0;n<numpair;n++) {
            if((*tmp).first==key)
		    return tmp;
            tmp ++ ;
          }
	  return tmp; 
  }
  /*------ Subscripting operator ---------------- */
  V & operator[](const K& key){
	  if( (*(find(key))).first==key ) return (*(find(key))).second;
	  insert({key,NULL});
          return (*(find(key))).second;
  }

  /*------ Put-to operator <<  ------------------ */
  friend std::ostream& operator<<(std::ostream & os, const bst<K,V,C> & bst_object){
      auto tmp = bst_object.begin();
      os << "[ ";
      for (int n=0;n<bst_object.numpair;n++) {
        os << "["<< (*tmp).first << " , "<< (*tmp).second << "] ; ";
        tmp ++ ;
      }
      os <<" ]";
    return os;
  };
  

  /*------ insert member function  ------------------ */
  std::pair<iterator,bool> insert(const std::pair<const K, V>& newpair)
  {
    if(!root){ /*--- if root doesn't exist for this object, create it :--- */
          root=std::make_unique<node>(node(newpair));
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
          if(op( current_test->NPair.first , newpair.first)){ /* comparison indicate go right */ 
             current_test=current_test->right.get();
             right_steps++;
             if(!current_test){
               parent_test->right = std::make_unique<node>(node(newpair,parent_test) ); 
               numpair++;
               return std::make_pair(iterator(parent_test->right.get()),true) ; 
             }
           }
          else if( op( newpair.first,current_test->NPair.first )){ /* comparison indicate go left */ 
             current_test=current_test->left.get();
             left_steps++;
             if(!current_test){
               parent_test->left = std::make_unique<node>(node(newpair,parent_test)); 
               if(!right_steps) firstnode=parent_test->left.get();
               numpair++;
               return std::make_pair(iterator(parent_test->left.get()),true)  ;
             }
           }
          else{    /*--- newpair.first is already present in the tree  --- */
             return std::make_pair(iterator(current_test),false); 
          }
       }
    }
    return std::make_pair(iterator(root.get()),false); 
  }
  
  std::pair<iterator,bool> insert(std::pair<const K, V>&& newpair)
  {
    if(!root){ /*--- if root doesn't exist for this object, create it :--- */
          root=std::make_unique<node>(newpair);
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
          if(op( current_test->NPair.first , newpair.first)){ /* comparison indicate go right */ 
             current_test=current_test->right.get();
             right_steps++;
             if(!current_test){
               parent_test->right = std::make_unique<node>(newpair,parent_test) ; 
               numpair++;
               return std::make_pair(iterator(parent_test->right.get()),true) ; 
             }
           }
          else if( op( newpair.first,current_test->NPair.first )){ /* comparison indicate go left */ 
             current_test=current_test->left.get();
             left_steps++;
             if(!current_test){
               parent_test->left =std::make_unique<node>(newpair,parent_test) ; 
               if(!right_steps) firstnode=parent_test->left.get();
               numpair++;
               return std::make_pair(iterator(parent_test->left.get()),true)  ;
             }
           }
          else{    /*--- newpair.first is already present in the tree  --- */
             return std::make_pair(iterator(current_test),false); 
          }
       }
    }
    return std::make_pair(iterator(root.get()),false); 
  }
  /*------- EMPLACE ------------------ */
//std::pair<iterator, bool> emplace(Types&&... args){ return insert({std::forward<Types>(args)...});}

  /*------- CLEAR ------------------ */
  void clear() {root.reset();}

  /*------- BALANCE ------------------ */
  void balance(){
   std::vector<bool> insertpair(numpair,true);
   std::vector<std::pair< K,V>> Vec_KVpair(numpair);
   auto tmp = begin();
      for (int n=0;n<numpair;n++) {
        Vec_KVpair[n].first= (*tmp).first;
        Vec_KVpair[n].second=(*tmp).second;
        tmp ++ ;
      }
   int numpair_tmp=numpair;
   clear();
   size_t numbranches{1};
   insert(Vec_KVpair[numpair_tmp/2]);
   int insertedpairs{0};
   numbranches=1;
   while(insertedpairs<numpair_tmp){
     for(size_t branch{0}; branch<numbranches ; branch++){
       for(int pos=int((float(branch)+0.5)*(float(numpair_tmp)/float(numbranches)));pos<numpair_tmp ;pos++){
         if(insertpair[pos]){
           insert(Vec_KVpair[pos]);
           insertpair[pos]=false;
           insertedpairs++;
           break ; 
         }
       }
    }
   numbranches*=2;
   } 
  };
};
#endif
