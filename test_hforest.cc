#include <iostream>
#include "htree.hh"
#include "hforest.hh"
#include <memory>
#include <list>
#include <algorithm>
#include <vector>
#include <string>

HTree::tree_ptr_t test_Htree(int key, uint64_t value, HTree::tree_ptr_t left = nullptr, HTree::tree_ptr_t right = nullptr){
  HTree::tree_ptr_t newtree_ptr(new HTree(key, value, left, right));
  return newtree_ptr;
}

int main(){
  HForest forestpark = *(new HForest());

  HTree::tree_ptr_t test_tree9 = test_Htree(9, 9);
  HTree::tree_ptr_t test_tree6 = test_Htree(6, 6, test_tree9);
  HTree::tree_ptr_t test_tree12 = test_Htree(12, 12);
  HTree::tree_ptr_t test_tree5 = test_Htree(5, 5, test_tree12, test_tree6);
  HTree::tree_ptr_t test_tree3 = test_Htree(3, 3);
  HTree::tree_ptr_t test_tree12two = test_Htree(12, 12, test_tree3);
  HTree::tree_ptr_t test_tree126 = test_Htree(126, 126, test_tree5, test_tree12two);

  forestpark.add_tree(test_tree9);
  forestpark.add_tree(test_tree6);
  forestpark.add_tree(test_tree12);
  forestpark.add_tree(test_tree3);
  forestpark.add_tree(test_tree5);
  forestpark.add_tree(test_tree12two);
  forestpark.add_tree(test_tree126);

  forestpark.testcase1();
  forestpark.testcase1();
  forestpark.testcase1();
  forestpark.testcase1();
  forestpark.testcase1();
  forestpark.testcase1();
  forestpark.testcase1();

}
