/*
This includes the header file which should also include the #includes and the
declarations for the functions and variables that are contained in the Huffman
class
*/
#include "huffman.hh"

/*
Function that returns a tree_ptr_t and takes a key and frequency. It will return
a pointer to a new HTree created using the key as the key and the freq as the
value. This will allocate space to the heap for the new HTree and return a
pointer on the stack to the HTree that was created.
*/
HTree::tree_ptr_t create_tree(int key, int freq) {
	return HTree::tree_ptr_t(new HTree(key, freq));
}

/*
Function that takes the frequency vectors and creates a new instance of HForest
forest. It will add a tree for the length of frequencies (256 ASCII
characters NOT INCLUDING EOF here in the for loop). It will add a new tree
by calling the create_tree function that returns a tree_ptr_t. The tree_ptr_t
added will point to a tree that has the key value of i and the value value of
freq[i] = 0 to start. The final tree added to the forest will have the value of
256 and the value will be equal to the freq[256] because freq[size] does not work
because of 0 indexing. (The value for the freq[256] in the initial forest will
be 1.) Then it returns the forest that is created.
*/
HForest create_forest(std::vector<int> freq) {
	HForest forest;
	for (uint64_t i = 0; i < freq.size() - 1; i++) {
		forest.add_tree(create_tree(i, freq[i]));
	}
	forest.add_tree(create_tree(256, freq[freq.size() - 1]));
	return forest;
}

/*
Takes a forest and then makes a huffman_tree from the forest. As long as there is
not only one tree in the forest, then this loop will run. t1 refers to the a
function that "returns the tree with the lowest frequency count (and removes
it from forest)". Then a new tree is created from t1 and t2 with the key value
of -2 as not to be confused with the other ASCII characters. The value of the
new tree is the sum of the values of t1 and t2. The left tree pointer points
to the t2 and the right tree pointer points to t1. Then the new tree we created
from the two trees we just removed from the forest is added back to the forest.

We return a tree pointer to the tree with the lowest frequency count. <- This is
because we changed the symbol in the compare_trees functor. Eitan wrote the code
to return the tree with the highest frequency.
*/
HTree::tree_ptr_t create_huffman_tree(HForest forest) {
	while (forest.size() > 1) {
		HTree::tree_ptr_t t1 = forest.pop_top();
		HTree::tree_ptr_t t2 = forest.pop_top();
		HTree::tree_ptr_t new_tree = HTree::tree_ptr_t(new 
			HTree(-2, t1->get_value() + t2->get_value(), t2, t1));
		forest.add_tree(new_tree);
	}
	return forest.pop_top();
}

/*
This creates a std::vector<int> frequencies_ which is defined within the
private section of Huffman. The vector is initialized to 256 zeros that will
stand for the ascii values and then at the end will be a 1 for the EOF
character's original frequency. Then it creates a forest using the frequencies.
It will then create_huffman_tree from the forest. That huffman_tree will then be
able to be called later from the variable huffman_tree_ which is a private data
member defined within Huffman class and a HTree::tree_ptr_t .
*/
void Huffman::create_initial() {
	frequencies_.assign(256, 0);
	frequencies_.push_back(1);
	HForest forest = create_forest(frequencies_);
	huffman_tree_ = create_huffman_tree(forest);
}

/*
A constructor that creates an instance of a huffman class. Then it will 
create_initial() which is a private function defined within Huffman. 
The current_node_, which is a private data member defined
within Huffman class and a HTree::tree_ptr_t, is then set to be equal to
huffman_tree_ which was defined in the function create_initial that was called
in the previous line.
*/
Huffman::Huffman() {
	create_initial();
	current_node_ = huffman_tree_;
}

/*
Will take in a symbol (int key), and then return a path of LEFT and RIGHTS which
are enumerated to get to the specific key in the tree. Path
will return a list of directions to the symbol that was passed to encode.
Then initializes a std::vector<bools> path_bools. For each direction we found in
the path check if it is == to left and if it is add a 0 to the our new vector of
bools. Else, we add a 1 to the vector of bools.

After the for loop, we increment the frequency of the symbol we found by 1. 
Initialize another HForest titled forest. Then we define the forest using 
create forest using our updated vector of frequencies. Then you create an updated 
huffman tree from the forest and return the path of booleans to the symbol's node.
*/
Huffman::bits_t Huffman::encode(int symbol) {
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
	HForest forest;
	forest = create_forest(frequencies_);
	huffman_tree_ = create_huffman_tree(forest);
	return path_bools;
}

/*
Function that takes in a bit to decode and will return an int, corresponding
to the ASCII value.

If the bool == 1, then the current_node_, which is defined in the private data
section of Huffman to of type HTree::tree_ptr_t, the current_node_ will then be
equal to the tree_ptr_t pointing to the right child. Else bool == 0, then the
current_node_will then be equal to the tree_ptr_t pointing to the right child.

If the key of the current_node_ is greater than or equal to 0, then that node is
a leaf and we found an ASCII character (or EOF). Then the integer which we 
initilaized called key will be set to key of the current_node_. The frequency of
that key will be incremented in the frequency table, and we will create a new
huffman_tree based on the new data. 
The current_node_ is then reset to huffman_tree_ which is a tree_ptr_t to the
huffman tree. Then we return the key, which is the corresponding ASCII value or
EOF.

Else, if the if no symbol can be unmabiguously decoded without additional bits 
(the current_node_ is internal), returns a negative value.
*/
int Huffman::decode(bool bit) {
	if (bit) {
		current_node_ = current_node_->get_child(HTree::Direction::RIGHT);
	}
	else {
		current_node_ = current_node_->get_child(HTree::Direction::LEFT);
	}
	if (current_node_->get_key() >= 0) {
		int key = current_node_->get_key();
		frequencies_[key]++;
		HForest forest = create_forest(frequencies_);
		huffman_tree_ = create_huffman_tree(forest);
		current_node_ = huffman_tree_;
		return key;
	}
	else {
		return -3;
	}
}
