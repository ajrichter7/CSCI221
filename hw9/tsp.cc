
#include "cities.hh"

using namespace std;
/*
Implementation of random_permutation where it will not be out of scope. It takes
in a length of a vector and will create a vector of Cities::permutation_t with
the same length. Then we implemented a random device and a way to shuffle
the elements in the vector to always get a new permutation of index values within
the length of the vector of cities.
*/
Cities::permutation_t random_permutation(unsigned len) {
  Cities::permutation_t perms;
  for (uint64_t i = 0; i < len; i++) {
  	perms.push_back(i);
  }
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(perms.begin(), perms.end(), g);
  return perms;
}

int main(int argc, char** argv) {
  //Checkes to make sure that there is exactly one argument given and will produce
  //an error otherwise.
	if (argc < 2) {
		cerr << "Need exactly one argument: input filename" <<endl;
		return -1;
	}

  //Opens the input file stream and then checks to make sure that the input file
  // strean is actually open and if it is not, it will produce an error.
	ifstream inp(argv[1]);
	if (!inp.is_open()) {
		cerr<< "Can't open input file " << argv[1] << "!" << endl;
		return -2;
 	}

  // opens the output file called "shortest.tsv"
 	ofstream out;
 	out.open("shortest.tsv");

  //Declaration of various variables, reads in the input file to the empty cities
 	Cities cities;
 	inp >> cities;
 	double shortest = 0;
 	Cities::permutation_t new_perm;
 	double distance;
 	int i = 0;
 	Cities best_route;

  /*
  Loop that will do 1000000 permutations. It will produce a new permutation in
  each iteration. If the distance produced by that permutation is shorter than
  current shortest or it is the first instance of the loop (shortest == 0) then
  the best route becomes the reordering of cities according to the permutation.
  The shortest distance is then equal to the current distance. The current iteration
  number (i) and the shortest distance value is sent to the ostream.

  Will continue to increment i after each permutation and than eventually the
  best_route is printed.
  */
 	while (i < 1000000) {
 		new_perm = random_permutation(cities.get_number_of_cities());
 		distance = cities.total_path_distance(new_perm);
 		if (distance < shortest || shortest == 0) {
 			best_route = cities.reorder(new_perm);
 			shortest = distance;
 			std::cout << i << "	" << shortest <<std::endl;
 		}
 		i++;
 	}
 	out << best_route;

  // The input file stream and the output file stream are both closed. 
	inp.close();
	out.close();
 	return 0;
}
