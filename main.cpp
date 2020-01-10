#include <iostream>
#include <memory>  //unique_ptr
#include <utility>
#include "ap_error.h"
#include "bst.hpp"

int main() {
  try {

  bst<int,std::string> b1{};
  b1.insert(12,static_cast<std::string>("CHIEF"));
  b1.insert(3,static_cast<std::string>("little"));
  b1.insert(13,static_cast<std::string>("big"));
  bst<int,std::string> b2(8,"MASTER");
  std::cout << "test ok"<< std::endl;

  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }

  return 0;
}
