htree: htree.cc test_htree.cc
	g++ -Wall -Wextra -pedantic htree.cc test_htree.cc -Werror -std=c++17 -g -o tree

hforest: hforest.cc htree.cc test_hforest.cc 
	g++ -Wall -Wextra -pedantic hforest.cc htree.cc test_hforest.cc -Werror -std=c++17 -g -o forest
