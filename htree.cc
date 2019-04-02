#include <iostream>
#include <memory>
#include <list>
#include <algorithm>
#include <vector>
#include <string>
#include "htree.hh"

using namespace std;

HTree::HTree(int key,
      uint64_t value,
      tree_ptr_t left,
      tree_ptr_t right):
      k(key), v(value), l(left), r(right) {}
//////////////////////////////////////////////////////////////////////////////
int HTree::get_key() const{
  return k;
}
//////////////////////////////////////////////////////////////////////////////
uint64_t HTree::get_value() const{
  return v;
}
//////////////////////////////////////////////////////////////////////////////
HTree::tree_ptr_t HTree::get_left() const{
  return l;
}
//////////////////////////////////////////////////////////////////////////////
HTree::tree_ptr_t HTree::get_right() const{
  return r;
}
//////////////////////////////////////////////////////////////////////////////
  HTree::tree_ptr_t HTree::get_child(HTree::Direction dir) const{
    if (dir == HTree::Direction::LEFT){
      return this->get_left();
    }if (dir == HTree::Direction::RIGHT){
      return this->get_right();
    }else{
      return nullptr;
    }
  }
//////////////////////////////////////////////////////////////////////////////
  bool has_num(HTree::tree_ptr_t tree, int key){
    bool oak_right;
    bool oak_left;
    if (key == tree->get_key()){
      return true;
    }else{
      if(tree->get_left() && has_num(tree->get_child(HTree::Direction::LEFT), key)){
        oak_left = has_num(tree->get_child(HTree::Direction::LEFT), key);
        return oak_left;
      }if(tree->get_right() && has_num(tree->get_child(HTree::Direction::RIGHT), key)){
        oak_right = has_num(tree->get_child(HTree::Direction::RIGHT), key);
        return oak_right;
      }
    }
  return false;
  }

  HTree::path_t lst;
  HTree::path_t HTree::path_to(int key) const{
    if(key == k){
        return lst;
    }else{
      if (get_left() && has_num(HTree::get_child(HTree::Direction::LEFT), key))
      {
        lst.push_back(HTree::Direction::LEFT);
        return HTree::get_left()->path_to(key);
      }
      else if (get_right() && has_num(HTree::get_child(HTree::Direction::RIGHT), key))
      {
        lst.push_back(HTree::Direction::RIGHT);
        return HTree::get_right()->path_to(key);
      }
    }
    HTree::path_t newlst;
    return newlst;
  }

//////////////////////////////////////////////////////////////////////////////
