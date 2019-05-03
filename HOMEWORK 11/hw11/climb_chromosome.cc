#include "climb_chromosome.hh"

//Constructor for ClimbChromosome
ClimbChromosome::ClimbChromosome(const Cities* cities_ptr)
	:
	Chromosome(cities_ptr)
{}

//////////////////////////////////////////////////////////////////////////////
//clone function that will return a new ClimbChromosome*

ClimbChromosome* ClimbChromosome::clone() const {
	return new ClimbChromosome(cities_ptr_);
}

//////////////////////////////////////////////////////////////////////////////
/*
Overrides the mutate(), will take two new climbchromosomes and the climbchromosome
that the method was called with. It will then mutate the climbchromosomes and return
a climbchromosome* to the best fit chromosome to use in tournament_deme. order_
now is the new climbchromosome's order_. If the number the random generator generates
is 0 then we will make m (which is used for indexing) to be equal to the size of
order_ - 1. Else, m will be equal to the randomly generated number minus - 1.
*/
void ClimbChromosome::mutate() {
	//creation of two new climbchromosomes
	ClimbChromosome* c2 = clone();
	ClimbChromosome* c3 = clone();
	c2->order_ = order_;
	c3->order_ = order_;
	//creates a vector of climb_chromosome* : the original cc, new cc, and other new cc
	std::vector<ClimbChromosome*> chromes;
	chromes.push_back(this);
	chromes.push_back(c2);
	chromes.push_back(c3);
	//pick a random spot in the chromosome to mutate
	uint64_t n = order_.size();
	std::uniform_int_distribution<> dist(0, n-1);
	srand(time(0));
	int p = dist(generator_);
	int val = order_[p];
	int m;
	if (p!=0) {
		m = p-1;
	}
	else {
		m = n-1; // n == order_.size() <-I found this hard to find, figured I would help.
	}
	//changing the order_ of the chromosomes
	c2->order_[p] = c2->order_[m];
	c2->order_[m] = val;
	c3->order_[p] = c3->order_[(p+1) % n]; //mod to deal with size + 1
	c3->order_[(p+1) % n] = val; //mod to deal with size + 1
	double best = 0;
	ClimbChromosome* chrome;
	//go through the vector of climbchromosomes and pick the best fit one to keep
	for (auto i : chromes) {
		if (i->get_fitness() > best || best == 0) {
			best = i->get_fitness();
			chrome = i;
		}
	}
	//the order_ now equals the order of the new climbchromosome created
	order_ = chrome->order_;
	//delete to avoid memory leakage
	delete c2;
	delete c3;
}
