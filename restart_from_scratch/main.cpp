#include <iostream>
#include <memory>  // For unique_ptr
#include <utility>
#include <vector>
#include <map>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include "bst.hpp"
bst<int,int> exam_tree()
{
    bst<int,int> bst_obj;
    bst_obj.insert({8,0});
    bst_obj.insert({3,1});
    bst_obj.insert({10,2});
    bst_obj.insert({1,3});
    bst_obj.insert({6,4});
    bst_obj.insert({14,5});
    bst_obj.insert({4,6});
    bst_obj.insert({7,7});
    bst_obj.insert({13,8});
    return bst_obj;
}
 
int main() {
  /********** Construction of a bst object of type <int,int> **************************/
  std::cout<<std::endl<<" Testing Constructor "<<std::endl;
  bst<int,int> bst_ii; 
  //bst<int,int,std::greater<int>> bst_ii{as_function_ptr<std::greater<int>()}; 

  /********** Testing the insert member function **************************************/
  std::cout<<std::endl<<" Testing insert member function "<<std::endl;
  srand(time(0));  // Initialize random number generator
  auto key{rand()%30};	  
  auto pair_r{bst_ii.insert({key,0})};    // insert the root pair of key, value=0
  std::cout<<key<<" inserted as root"<<std::endl;
  for(size_t value{1};value<15;value++){  // Try to insert up to 50 more pairs of key, value
     key=rand()%10;	  
     pair_r=bst_ii.insert({key,value});
     if(pair_r.second)std::cout<<key<<" inserted successfully"<<std::endl;
     else std::cout<<key<<" already exists in bst"<<std::endl;
  }

  /********* Testing the operator <<,          ****************************************
   ********* the balance member function       ****************************************
   ********* and doing so, as well operator ++ *****************************************/
  std::cout<<std::endl<<" Testing << operator "<<std::endl;
  std::cout<<bst_ii<<std::endl;
  std::cout<<std::endl<<" Testing balance member function "<<std::endl;
  bst_ii.balance();
  std::cout<<bst_ii<<std::endl;


  /********* Testing the move constructor ****************************************/
  std::cout<<std::endl<<" Testing move constructor "<<std::endl;
  auto bst_moved{std::move(exam_tree())};
  std::cout<<bst_moved<<std::endl;

  /********* Testing the copy constructor ****************************************/
  std::cout<<std::endl<<" Testing deep copy "<<std::endl;
  bst<int,int> bst_copied{bst_moved};
  std::cout<<bst_copied<<std::endl;

  /********* Testing the Find member function ****************************************/
  std::cout<<std::endl<<" Testing find member function "<<std::endl;
  for(key=0;key<15;key++){
      if((*(bst_copied.find(key))).first==key)
	       std::cout<<key<<" is in bst_copied"<<std::endl;
      else
	      std::cout<<key<<" is NOT in bst_copied"<<std::endl;
  } 

  /********* Testing []operator *******************************************************/
  std::cout<<std::endl<<" Testing [] operator "<<std::endl;
  for(size_t test{1};test<8;test++){  // Try to insert up to 50 more pairs of key, value
     key=rand()%10;     
     std::cout<<"bst_ii["<<key<<"] returns value : "<<bst_ii[key]<<std::endl;
  }
  std::cout<<bst_ii<<std::endl;

  std::cout << "MAIN ENDED NORMALLY"<< std::endl;
  return 0;
}
