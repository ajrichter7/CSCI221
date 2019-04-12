
#include "fhuffman.hh"

HTree::tree_ptr_t create_tree(int key, int freq) {
	return HTree::tree_ptr_t(new HTree(key, freq));
}

HForest create_forest(std::vector<int> freq) {
	HForest forest;
	for (uint64_t i = 0; i < freq.size() - 1; i++) {
		forest.add_tree(create_tree(i, freq[i]));
	}
	forest.add_tree(create_tree(256, freq[freq.size() - 1]));
	return forest;
}

HTree::tree_ptr_t create_huffman_tree(HForest forest) {
	while (forest.size() > 1) {
		HTree::tree_ptr_t t1 = forest.pop_top();
		HTree::tree_ptr_t t2 = forest.pop_top();
		HTree::tree_ptr_t new_tree = HTree::tree_ptr_t(new
			HTree(-2, t1->get_value() + t2->get_value(), t2, t1));
		t2->set_parent(new_tree);
		t1->set_parent(new_tree);
		forest.add_tree(new_tree);
	}
	return forest.pop_top();
}


void FHuffman::create_initial() {
	frequencies_.assign(256, 0);
	frequencies_.push_back(1);
	HForest forest = create_forest(frequencies_);
	huffman_tree_ = create_huffman_tree(forest);
}

FHuffman::FHuffman() {
	create_initial();
	current_node_ = fhuffman_tree_;
}

bits_t FHuffman::encode(int symbol) {
	HTree::path_t path = huffman_tree_->path_to(symbol);
	bits_t path_bools;
	for (HTree::Direction dir: path) {
		if (dir == HTree::Direction::LEFT) {
			path_bools.push_back(0);
		}
		else {
			path_bools.push_back(1);
		}
	}
	frequencies_[symbol]++;
	//we don't know how to implement see fhuffman readme and pdf attached


}

int FHuffman::decode(bool bit) {
//we have begun to understand what we need to do but implementation, has proved
//more difficult than originially anticipated 
}
