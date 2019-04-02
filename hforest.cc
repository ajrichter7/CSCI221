#include <iostream>
#include "htree.hh"
#include "hforest.hh"
#include <memory>
#include <list>
#include <algorithm>
#include <vector>
#include <string>

bool compare_trees(HTree::tree_ptr_t t1, HTree::tree_ptr_t t2) {
    return t1->get_value() < t2->get_value();
}
//////////////////////////////////////////////////////////////////////////////
HForest::HForest(){
  std::vector<HTree::tree_ptr_t> forest;
}
//////////////////////////////////////////////////////////////////////////////
void HForest::printAll(){
  for(unsigned int i = 0; i < fv.size(); ++i){
    std::cout<<fv.at(i)->get_key()<<"\n";
  }
}
//////////////////////////////////////////////////////////////////////////////
void HForest::testcase1(){
  std::cout<<"Size is: "<<fv.size()<<"\n";
  std::cout<<"Trees in heap: "<< "\n";
  HForest::printAll();
  HForest::pop_tree();
}
//////////////////////////////////////////////////////////////////////////////
int HForest::size() const{
  return fv.size();
}
//////////////////////////////////////////////////////////////////////////////
void HForest::add_tree(HTree::tree_ptr_t new_tree){
  fv.push_back(new_tree);
  std::make_heap(fv.begin(), fv.end(), compare_trees);
}

//////////////////////////////////////////////////////////////////////////////
HTree::tree_ptr_t HForest::pop_tree(){
  HTree::tree_ptr_t largest = fv[0];
  int temp_back = fv.size();
  std::swap(fv[0],fv[temp_back - 1]);
  fv.pop_back();
  std::make_heap(fv.begin(), fv.end(), compare_trees);
  return largest;
}
