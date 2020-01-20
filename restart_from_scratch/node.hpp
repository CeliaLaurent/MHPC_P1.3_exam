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
   Node *parent;

   //If my constructor takes more than 1 argument, do not put explicit
   explicit Node(const value_type& x) : NPair{x}, parent{nullptr} {}
   Node(value_type& x, Node* y):NPair{x},parent{y}{}
   Node(const value_type& x, Node* y):NPair{x},parent{y}{}
   Node(const Node<value_type> & p): NPair{p.NPair}, parent{p.parent} {}
   Node(value_type&& x, Node* y) : NPair{std::move(x)},parent{y} {}
 //explicit Node(const std::unique_ptr<node>& p) : NPair{p->Npair},parent{p->parent} {
 //   if (p->left)
 //     next = std::make_unique<node>(p->left);
 // }
   
  Node() = default;
  ~Node() = default;
};
#endif
