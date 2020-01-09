#include <iostream>
#include <memory>  //unique_ptr

#include "ap_error.h"
#include "bst.hpp"

int main() {
  try {

  bst<int,int,int> b1{};
  std::cout << "test ok"<< std::endl;

  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }

  return 0;
}
