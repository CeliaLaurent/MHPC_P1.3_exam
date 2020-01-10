#include <iostream>
#include <memory>  //unique_ptr
#include <utility>
#include "ap_error.h"
#include "bst.hpp"

int main() {
  try {
  bst<int,std::string> b1{};
    b1.insert({5,"CHIEF"});
    b1.insert({3,"l"});
    b1.insert({10,"r"});
    b1.insert({6,"rl"});
    b1.insert({4,"lr"});
    b1.insert({1,"ll"});
    b1.insert({7,"rlr"});
    b1.insert({8,"rlrr"});
    b1.insert({9,"rlrrr"});
    b1.insert({14,"rr"});
    b1.insert({13,"rrl"});
//auto it0=b1.insert(5,"CHIEF"));
//it0=b1.insert(3,"l"));
//it0=b1.insert(10,"r"));
//it0=b1.insert(6,"rl"));
//it0=b1.insert(4,"lr"));
//it0=b1.insert(1,"ll"));
//it0=b1.insert(7,"rlr"));
//it0=b1.insert(8,"rlrr"));
//it0=b1.insert(9,"rlrrr"));
//it0=b1.insert(14,"rr"));
//it0=b1.insert(13,"rrl"));
  bst<int,std::string> b2(8,"MASTER");
  std::cout << "test ok"<< std::endl;

  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }

  return 0;
}
