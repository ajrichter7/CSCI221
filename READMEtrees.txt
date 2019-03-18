//////////////////////////////////////////////////////////////////////////////
create_tree:
Created a tree using the struct defined in the header file.
Implementing the tree struct in the test_tree.cc file was difficult,
I ended up just implementing a lot of small trees.

//////////////////////////////////////////////////////////////////////////////
destroy_tree:
Used references to destroy the tree both the right and left side of the trees
and then destroy the tree_ptr_t itself. Recursive function.

//////////////////////////////////////////////////////////////////////////////
has_num: (helper function to path_to)
Returned a boolean value to make sure that the key was in the tree, checked
the left side first because the tree was supposed to return the left most
occurrence of the key. I had difficulty in trying to implement this originally
as I was using boolean logic. However, that was unsuccessful because it was
giving me a segmentation error in my program so I ended up switching it to
two if statements the left one prior to the right one. Recursive function. 

path_to:
Through using pointers returned the an empty string if the key was the place
being pointed to. Recursive function that would call the left subtree prior to
the right subtree and correctly add the "L" or "R". I returned a string at
the very end to avoid the error of invalid characters being called.

//////////////////////////////////////////////////////////////////////////////
node_at:
Recursive function that will return the tree (or current place in the tree) if
the string is empty. The else statement will take the first index in the string
and then it will check and see if it is an "L" or "R" and then continue down the
correct subtree and remove the character at the first index. If the string is
given an invalid character, it will return assert(false) and abort.
