#include <iostream>
#include <memory>
#include <list>
#include <algorithm>
#include <vector>
#include <string>
#include "htree.hh"

//g++ -g -Wall -Wextra -pedantic test_htree.cc -Werror -std=c++17
HTree::tree_ptr_t test_Htree(int key, uint64_t value, HTree::tree_ptr_t left = nullptr, HTree::tree_ptr_t right = nullptr){
  HTree::tree_ptr_t newtree_ptr(new HTree(key, value, left, right));
  return newtree_ptr;
}

int main(){
  HTree::tree_ptr_t test_tree9 = test_Htree(9, 9);
  HTree::tree_ptr_t test_tree6 = test_Htree(6, 6, test_tree9);
  HTree::tree_ptr_t test_tree12 = test_Htree(12, 12);
  HTree::tree_ptr_t test_tree5 = test_Htree(5, 5, test_tree12, test_tree6);
  HTree::tree_ptr_t test_tree3 = test_Htree(3, 3);
  HTree::tree_ptr_t test_tree12two = test_Htree(12, 12, test_tree3);
  HTree::tree_ptr_t test_tree126 = test_Htree(126, 126, test_tree5, test_tree12two);

  HTree tree126 = *test_tree126;

  std::cout<< tree126.get_child(HTree::Direction::LEFT)->get_key()<<"\n";
  std::cout<< tree126.get_child(HTree::Direction::RIGHT)->get_key()<<"\n";

  HTree::path_t numlst = tree126.path_to(9);

  for(HTree::Direction dir : numlst) {
    if (dir == HTree::Direction::LEFT){
      std::cout << "left" << "\n";
    }else if (dir == HTree::Direction::RIGHT){
      std::cout << "right" << "\n";
    }
  }

  return 0;
}
