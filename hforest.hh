#include "htree.hh"
#include <memory>
#include <list>
#include <algorithm>
#include <vector>
#include <string>
/*
 * HForest: a class to represent a forest
 */

#pragma once

class HForest {
  private:
    std::vector<HTree::tree_ptr_t> fv;

  public:
    using tree_ptr_t = std::shared_ptr<const HTree>;
    enum class Direction { LEFT, RIGHT };
    using path_t = std::list<Direction>;

    HForest();

    ~HForest() = default;

    int size() const;

    void printAll();

    void testcase1();

    void add_tree(tree_ptr_t newtree);

    tree_ptr_t pop_tree();

};
