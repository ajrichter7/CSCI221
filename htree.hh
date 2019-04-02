/*
 * HTree: a class to represent a tree node with two values: a key
 * and a value.
 */

#pragma once

#include <memory>
#include <list>

class HTree {

  private:
    int k;
    uint64_t v;
    std::shared_ptr<const HTree> l, r;

  public:
    using tree_ptr_t = std::shared_ptr<const HTree>;
    enum class Direction { LEFT, RIGHT };
    using path_t = std::list<Direction>;

    // Initialize with a key and a value:
    HTree(int key,
          uint64_t value,
          tree_ptr_t left = nullptr,
          tree_ptr_t right = nullptr);

    ~HTree() = default;

    int get_key() const;

    uint64_t get_value() const;

    tree_ptr_t get_left() const;

    tree_ptr_t get_right() const;

    tree_ptr_t get_child(Direction dir) const;

    path_t path_to(int key) const;

};
