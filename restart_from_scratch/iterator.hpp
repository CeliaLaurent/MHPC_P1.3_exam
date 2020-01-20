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
      if(current_node->right){// if iterated node has a right, go right once then as left as i can
         current_node=current_node->right.get();
         while(current_node->left) {
		current_node=current_node->left.get();
	 }
      }
      else{//else go up as long as i have a parent(ie not root) and as long as upward motion is leftward
         while(current_node->parent){
         if( (current_node->parent)->left ) {
           if(current_node->NPair.first==((current_node->parent)->left)->NPair.first) {
                  current_node=current_node->parent;
		  break;} 
	 }
            current_node=current_node->parent;
	 }
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
