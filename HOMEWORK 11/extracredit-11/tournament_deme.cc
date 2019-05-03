
#include "tournament_deme.hh"

//constructor that will call Deme
TournamentDeme::TournamentDeme(const Cities* cities_ptr,
								unsigned pop_size, double mut_rate)
	:
	Deme(cities_ptr, pop_size, mut_rate)
	{}

//////////////////////////////////////////////////////////////////////////////
//doing nothing special in the destructor to account for, no memory leakage
TournamentDeme::~TournamentDeme() = default;

//////////////////////////////////////////////////////////////////////////////
/*
Overrides deme's select_parent method. Chose a power of 2 to run the for loop on
to generate a random selection of parent climbchromosomes. Will there are potential
parent climbchromosomes in the vector then we will pop two from the vector, and
keep the one with better fitness. Does that until there is only one more parent
in the vector.
*/
ClimbChromosome* TournamentDeme::select_parent() {
	int p = 32;
	std::vector<ClimbChromosome*> parents;
	//randomly add climbchromosomes from the population vector
	for (int i=0; i < p; i++) {
		std::uniform_int_distribution<int> distrib(0, pop_.size() - 1);
		srand(time(0));
		int index = distrib(generator_);
		parents.push_back(pop_[index]);
	}
	ClimbChromosome* p1;
	ClimbChromosome* p2;
	//tournament selection to pick the parent
	while (parents.size() > 1) {
		p1 = parents.back();
		parents.pop_back();
		p2 = parents.back();
		parents.pop_back();
		if (p1->get_fitness() > p2->get_fitness()) {
		parents.insert(parents.begin(), p1);
		}
		else {
		parents.insert(parents.begin(), p2);
		}
	}
	return parents.back();
}
