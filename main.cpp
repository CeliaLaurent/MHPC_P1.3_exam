#include <iostream>
#include <memory>  //unique_ptr
#include <utility>
#include "ap_error.h"
#include "bst.hpp"

int main() {
  try {

  bst<int,std::string> b1{};
  b1.insert(5,static_cast<std::string>("CHIEF"));
  b1.insert(3,static_cast<std::string>("l"));
  b1.insert(10,static_cast<std::string>("r"));
  b1.insert(6,static_cast<std::string>("rl"));
  b1.insert(4,static_cast<std::string>("lr"));
  b1.insert(1,static_cast<std::string>("ll"));
  b1.insert(7,static_cast<std::string>("rlr"));
  b1.insert(8,static_cast<std::string>("rlrr"));
  b1.insert(9,static_cast<std::string>("rlrrr"));
  b1.insert(14,static_cast<std::string>("rr"));
  b1.insert(13,static_cast<std::string>("rrl"));
  bst<int,std::string> b2(8,"MASTER");
  std::cout << "test ok"<< std::endl;

  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }

  return 0;
}
