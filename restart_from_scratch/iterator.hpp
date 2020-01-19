#ifndef _iterator_
#define _iterator_
  template <typename N_t, typename OP_t> //a node-type and a pair-type
  class Iterator {
     N_t* current_node;

   public:
   
    using value_type = OP_t;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using reference = value_type&;
    using pointer = value_type*;

    /* -------------iterator reference / pointer   ----------------- */
    reference operator*() const noexcept { return current_node->NPair;  }
    pointer operator->() const noexcept { return &(*(*this)); }

    Iterator () noexcept = default;
    explicit Iterator(N_t* x)noexcept : current_node{x} {}


    /* -------------iterator operator++ --------------------------- */
    Iterator& operator++() noexcept {  // pre increment
      //std::cout<<"Operator ++ on node of key "<<current_node->NPair.first << std::endl;
      if(current_node->right){// if iterated node has a right, go right once then as left as i can
         //std::cout<<"Found a right child " << std::endl;
         current_node=current_node->right.get();
         //std::cout<<"Operator ++ go right on node of key "<<current_node->NPair.first << std::endl;
         while(current_node->left) {
                //std::cout<<"Found a left child "<< std::endl;
		current_node=current_node->left.get();
                //std::cout<<"Operator ++ go left on node of key "<<current_node->NPair.first << std::endl;
	 }
         //std::cout<<"we found the next node it has a key "<<current_node->NPair.first  << std::endl;
      }
      else{//else go up as long as i have a parent(ie not root) and as long as upward motion is leftward
         //std::cout<<"node of key "<<current_node->NPair.first <<" Doesnt have children " << std::endl;
         while(current_node->parent){
         //std::cout<<"node of key "<<current_node->NPair.first <<" has a parent of key " <<(current_node->parent)->NPair.first<< std::endl;
         if( (current_node->parent)->left ) {
           if(current_node->NPair.first==((current_node->parent)->left)->NPair.first) {
                  current_node=current_node->parent;
                  //std::cout<<"upward is right-ward, we found the next node is has a key " << current_node->NPair.first << std::endl;
		  break;} 
	 }
            current_node=current_node->parent;
            //std::cout<<" going up-left-ward we became the parent of key "<<current_node->NPair.first << std::endl;
	 }
         //if(!current_node->parent) current_node=nullptr;//found root, no next node
         //else current_node=current_node->parent;//parent is right-ward, it is next node
         //std::cout<<"Operator ++ go up2 to node of key "<<current_node->NPair.first << std::endl;
         }
      return *this;
    }

    /* -------------iterator operator++(int) ------------------- */
    Iterator operator++(int) noexcept {
      Iterator tmp{current_node};
      ++(*this);
      return tmp;
    }

    /* -------------iterator operator ==     ----------------------- */
    friend bool operator==(const Iterator& a, const Iterator& b) {
      return a.current_node == b.current_node;
    }
    /* -------------iterator operator !=     ----------------------- */
    friend bool operator!=(const Iterator& a, const Iterator& b) {
      return !(a == b);
    }



};
#endif
