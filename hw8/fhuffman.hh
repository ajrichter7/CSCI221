
#pragma once

#include <vector>
#include <climits>

#include "fhtree.hh"
#include "fhforest.hh"

class FHuffman {
 public:

  static const int ALPHABET_SIZE = (1 << CHAR_BIT) + 1;  // (2 ** 8) + 1
  static const int HEOF = ALPHABET_SIZE - 1;  // Special symbol to denote end of file

  using bits_t = std::vector<bool>;

  FHuffman();
  ~FHuffman() = default;
  FHuffman(const FHuffman&) = delete;
  FHuffman(FHuffman&&) = delete;
  FHuffman& operator=(const FHuffman&) = delete;
  FHuffman& operator=(FHuffman&&) = delete;

  bits_t encode(int symbol);

  int decode(bool bit);
 private:
 	std::vector<int> frequencies_;
 	FHTree::tree_ptr_t fhuffman_tree_;
  FHTree::tree_ptr_t current_node_;
};
