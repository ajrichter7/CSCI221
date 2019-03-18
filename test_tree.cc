#include <iostream>
#include "tree.hh"

//g++ -g -Wall -Wextra -pedantic test_tree.cc tree.cc -Werror -std=c++17

using key_t = int;
using value_t = uint64_t;
using namespace std;

int main(){
  key_t key9 = 9;
  value_t value9 = 9;
  tree_ptr_t tree9 = create_tree(key9, value9);

  key_t key6 = 6;
  value_t value6 = 6;
  tree_ptr_t tree6 = create_tree(key6, value6, tree9);

  key_t key12 = 12;
  value_t value12 = 12;
  tree_ptr_t tree12;
  tree12 = create_tree(key12, value12);

  key_t key5 = 5;
  value_t value5 = 5;
  tree_ptr_t tree5;
  tree5 = create_tree(key5, value5, tree12, tree6);

  key_t key3 = 3;
  value_t value3 = 3;
  tree_ptr_t tree3;
  tree3 = create_tree(key3, value3);

  key_t key12two = 12;
  value_t value12two = 12;
  tree_ptr_t tree12two;
  tree12two = create_tree(key12two, value12two, tree3);

  key_t key126 = 126;
  value_t value126 = 126;
  tree_ptr_t tree126;
  tree126= create_tree(key126, value126, tree5, tree12two);

  cout<< path_to(tree126, 5)<< "\n";
  cout<< path_to(tree126, 12)<< "\n";
  cout<< node_at(tree126, "LR")->key_<<"\n";
  cout<< node_at(tree126, "")->key_<<"\n";
  cout<< node_at(tree126, "PIE")->key_<<"\n";

  destroy_tree(tree126);
}
