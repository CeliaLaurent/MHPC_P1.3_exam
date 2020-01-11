#include <iostream>
#include <memory>  //unique_ptr
#include <utility>
#include "ap_error.h"
#include "bst.hpp"
#include <vector>

int main() {
  try {
  bst<int,std::string> b0{};
  auto it0=b0.insert({8,"ENDIAN"});
//auto it = it0.first;
  //*it.second = "ciao";
//std::cout << "oleeeeeeeee " << it0.first->first << " " << it0.first->second << std::endl;
//std::vector<typename bst<int,std::string>::nodetype> v(11);
  
  //std::vector<std::decay(decltype(*(it0.first)))> v(13);
//bst<int,std::string> b1{};
//auto ita{b1.insert({5,"CHIEF"})};
//auto itb=b1.insert({3,"l"});
//itb=b1.insert({10,"r"});
//itb=b1.insert({6,"rl"});
//itb=b1.insert({4,"lr"});
//itb=b1.insert({1,"ll"});
//itb=b1.insert({7,"rlr"});
//itb=b1.insert({8,"rlrr"});
//itb=b1.insert({9,"rlrrr"});
//itb=b1.insert({14,"rr"});
//itb=b1.insert({13,"rrl"});

//std::vector<std::pair<const int, std::string>> v(12);
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
