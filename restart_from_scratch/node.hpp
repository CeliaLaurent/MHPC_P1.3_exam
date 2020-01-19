#ifndef _node_
#define _node_

#include <iostream>
#include <memory>  //unique_ptr
#include <utility>
#include <vector>
//
template <typename P_t>
struct Node{
   P_t NPair;
   using value_type=P_t;  // out of the class this can be called through " typename Node::value_type"
   std::unique_ptr<Node> left,right;
   Node * next,*parent;

   //If my constructor takes more than 1 argument, do not put explicit
   Node(const value_type& x, Node* y):NPair{x},parent{y}{};
   explicit Node(const value_type& x) : NPair{x} {};
   
  Node() = default;
  ~Node() = default;
};
#endif
