#include <iostream>
#include <memory>  // For unique_ptr
#include <utility>
#include <vector>
#include <map>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include "bst.hpp"

int main() {
  /********** Construction of a bst object of type <int,int> **************************/
  bst<int,int> bst_ii; 
  //bst<int,int,std::greater<int>> bst_ii{as_function_ptr<std::greater<int>()}; 

  /********** Testing the insert member function **************************************/
  srand(time(0));  // Initialize random number generator
  auto key{rand()%30};	  
  auto pair_r{bst_ii.insert({key,0})};    // insert the root pair of key, value=0
  std::cout<<key<<" inserted as root"<<std::endl;
  for(size_t value{1};value<50;value++){  // Try to insert up to 50 more pairs of key, value
     key=rand()%30;	  
     pair_r=bst_ii.insert({key,value});
     if(pair_r.second)std::cout<<key<<" inserted successfully"<<std::endl;
     else std::cout<<key<<" already exists in bst"<<std::endl;
  }

  /********* Testing the operator <<,          ****************************************
   ********* the balance member function       ****************************************
   ********* and doing so, as well operator ++ *****************************************/
  std::cout<<bst_ii<<std::endl;
  bst_ii.balance();
  std::cout<<bst_ii<<std::endl;



  std::cout << "MAIN ENDED NORMALLY"<< std::endl;
  return 0;
}
