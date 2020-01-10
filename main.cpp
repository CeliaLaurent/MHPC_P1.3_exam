#include <iostream>
#include <memory>  //unique_ptr
#include <utility>
#include "ap_error.h"
#include "bst.hpp"
#include <vector>

int main() {
  try {
  bst<int,std::string> b0{};
  auto it0=b0.insert({5,"CHIEF"});
  auto it = it0.first;
  *it.second = "ciao";
  std::cout << "oleeeeeeeee " << it0.first->first << " " << it0.first->second << std::endl;
//std::vector<typename bst<int,std::string>::nodetype> v(11);
  
  //std::vector<std::pair<const int, std::string>> v(12);
  //std::vector<std::decay(decltype(*(it0.first)))> v(13);
//bst<int,std::string> b1{};
//it0=b1.insert({5,"CHIEF"});
//it0=b1.insert({3,"l"});
//it0=b1.insert({10,"r"});
//it0=b1.insert({6,"rl"});
//it0=b1.insert({4,"lr"});
//it0=b1.insert({1,"ll"});
//it0=b1.insert({7,"rlr"});
//it0=b1.insert({8,"rlrr"});
//it0=b1.insert({9,"rlrrr"});
//it0=b1.insert({14,"rr"});
//it0=b1.insert({13,"rrl"});

//std::copy(b1.cbegin(), b1.cend(), v.begin());
//for (auto x : v)
//    std::cout << 1 << std::endl;
  std::cout << "MAIN ENDED NORMALLY"<< std::endl;

  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }

  return 0;
}
