/*
 * Declarations for Deme class to evolve a genetic algorithm for the
 * travelling-salesperson problem.  A deme is a population of individuals.
 */

#include "chromosome.hh"
#include "deme.hh"
//////////////////////////////////////////////////////////////////////////////
// Generate a Deme of the specified size with all-random chromosomes.
// Also receives a mutation rate in the range [0-1]. Adds new chromosome*'s to
// pop_size which is the population
Deme::Deme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
	: mut_rate_(mut_rate),
	generator_(rand())
{
	while(pop_.size() < pop_size) {
		Chromosome* chrome = new Chromosome(cities_ptr);
		pop_.push_back(chrome);
	}
}
//////////////////////////////////////////////////////////////////////////////
// Clean up as necessary
// Deletes the things in the population vector
Deme::~Deme()
{
  for (auto i : pop_) {
  	delete i;
  }
}
//////////////////////////////////////////////////////////////////////////////
// Evolve a single generation of new chromosomes, as follows:
// We select pop_size/2 pairs of chromosomes (using the select() method below).
// Each chromosome in the pair can be randomly selected for mutation, with
// probability mut_rate, in which case it calls the chromosome mutate() method.
// Then, the pair is recombined once (using the recombine() method) to generate
// a new pair of chromosomes, which are stored in the Deme.
// After we've generated pop_size new chromosomes, we delete all the old ones.
void Deme::compute_next_generation()
{
	double mut1;
	double mut2;
	std::vector<Chromosome*> new_pop; // creates a new vector of chromosome*s
	for (uint64_t i = 0; i < pop_.size() / 2; i++) {
		Chromosome* p1 = select_parent();
		Chromosome* p2 = select_parent();
		std::uniform_real_distribution<double> dist(0.0,1.0);
		srand(time(0)); //seeding the generator to get random numbers
		mut1 = dist(generator_);
		srand(time(0)); //seeding the generator to get random numbers
		mut2 = dist(generator_);
		// if the mutation rates for individual new chromosome pointers is greater than the
		// mut_rate_ then we will mutate the new individuals
		if (mut1 > mut_rate_) {
			p1->mutate();
		}
		if (mut2 > mut_rate_) {
			p2->mutate();
		}
		std::pair<Chromosome*, Chromosome*> pair = p1->recombine(p2); //calls recombine on the two pointers
		new_pop.push_back(pair.first);
		new_pop.push_back(pair.second);
	}
	for (auto i : pop_) { // deleting to avoid memory leckage
		delete i;
	}
	pop_ = new_pop; // the old population becomes the new population vector
}
//////////////////////////////////////////////////////////////////////////////
// Return a copy of the chromosome with the highest fitness.
/*
For all of the chromosomes in the population vector if one has a higher fitness than the
best fitness than it becomes the best fitness. We will return a chromosome pointer to the
chromosome in the population that has the best fitness
*/
const Chromosome* Deme::get_best() const
{
  Chromosome* chrome;
  double best = 0.0;
  for (auto i : pop_) {
  	if (i->get_fitness() > best) {
  		best = i->get_fitness();
  		chrome = i;
  	}
  }
  return chrome;
}
//////////////////////////////////////////////////////////////////////////////
// Randomly select a chromosome in the population based on fitness and
// return a pointer to that chromosome.
Chromosome* Deme::select_parent()
{
	// go through the pop vector and adds up all of the fitnesses to get a total fitness
	double total = std::accumulate(pop_.cbegin(), pop_.cend(), 0.0,
		[](double sum, Chromosome* node){return sum + node->get_fitness(); });
	// threshold becomes the total value divided by the population size
	double threshold = total / (pop_.size() * 1.0);
	// make a copy of the population vector so we can manipulate the contents
	std::vector<Chromosome*> copy = pop_;
	// shuffle the vector
	std::shuffle(copy.begin(), copy.end(), generator_);
	/*
	Within the copied vector if any element's fitness surpasses the threshold, we will use that
	pointer as a parent for the next generation
	*/
	for (auto i : copy) {
		if (i->get_fitness() > threshold) {
			return i;
		}
	}
	// if no chromosome* surpasses the threshold then we random shuffle to pick a parent 
	std::uniform_int_distribution<int> distrib(0, pop_.size() - 1);
	srand(time(0)); //seeding the generator to get random numbers
	int index = distrib(generator_);
	return pop_[index];
}
