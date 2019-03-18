#include <string>
#include <iostream>
#include "tree.hh"

using key_t = int;
using value_t = uint64_t;
using namespace std;

//////////////////////////////////////////////////////////////////////////////
tree_ptr_t create_tree(const key_t& key,
                       const value_t& value,
                       tree_ptr_t left,
                       tree_ptr_t right){
      tree_ptr_t hefty_oak = new Tree;
      hefty_oak -> key_ = key;
      hefty_oak -> value_ = value;
      hefty_oak -> left_ = left;
      hefty_oak -> right_ = right;
      return hefty_oak;
                       }

//////////////////////////////////////////////////////////////////////////////
void destroy_tree(tree_ptr_t tree){
  if(tree->left_ != NULL){
    destroy_tree(tree->left_);
  }
  if(tree->right_ != NULL){
    destroy_tree(tree->right_);
  }
  delete tree;
}
//////////////////////////////////////////////////////////////////////////////
bool has_num(tree_ptr_t tree, key_t key){
  bool oak_right;
  bool oak_left;
  if (tree->key_ == key){
    return true;
  }else{
    if(has_num(tree->left_, key)){
      oak_left = has_num(tree->left_, key);
      return oak_left;
    }
    if(has_num(tree->right_, key)){
      oak_right = has_num(tree->right_, key);
      return oak_right;
    }
  }
  assert(false);
}
string path_to(tree_ptr_t tree, key_t key){
  if (tree->key_ == key){
    return "";
  }else{
    if (has_num(tree->left_, key)){
      return "L" + path_to(tree->left_, key);
    }
    else if (has_num(tree->right_, key)){
      return "R" + path_to(tree->right_, key);
    }
  }
  return "Get away from you me";
}
//////////////////////////////////////////////////////////////////////////////
tree_ptr_t node_at(tree_ptr_t tree, string path){
  if (path.empty()){
    return tree;
  }else{
    char firstletter_ = path.at(0);
    if (firstletter_ == 'L' || firstletter_ == 'l'){
      path.erase(0,1);
      return node_at(tree->left_, path);
    }
    if (firstletter_ == 'R' || firstletter_ == 'r' ){
      path.erase(0,1);
      return node_at(tree->right_, path);
    }
  }
  assert(false);
}
