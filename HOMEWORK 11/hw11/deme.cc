/*
 * Declarations for Deme class to evolve a genetic algorithm for the
 * travelling-salesperson problem.  A deme is a population of individuals.
 */

//Changed this to be using climbchromosomes instead of chromosomes
#include "climb_chromosome.hh"
#include "deme.hh"

// Generate a Deme of the specified size with all-random chromosomes.
// Also receives a mutation rate in the range [0-1].
Deme::Deme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
	: mut_rate_(mut_rate),
	generator_(rand())
{
	while(pop_.size() < pop_size) {
		ClimbChromosome* chrome = new ClimbChromosome(cities_ptr);
		pop_.push_back(chrome);
	}
}

//////////////////////////////////////////////////////////////////////////////
// Clean up as necessary
Deme::~Deme()
{
  for (auto i : pop_) {
  	delete i;
  }
}

//////////////////////////////////////////////////////////////////////////////
// Evolve a single generation of new climbchromosomes, as follows:
// We select pop_size/2 pairs of climbchromosomes (using the select() method below).
// Each climbchromosome in the pair can be randomly selected for mutation, with
// probability mut_rate, in which case it calls the climbchromosome mutate() method.
// Then, the pair is recombined once (using the recombine() method) to generate
// a new pair of climbchromosomes, which are stored in the Deme.
// After we've generated pop_size new climbchromosomes, we delete all the old ones.
void Deme::compute_next_generation()
{
	double mut1;
	double mut2;
	std::vector<ClimbChromosome*> new_pop;  // creates a new vector of climbchromosome*s
	for (uint64_t i = 0; i < pop_.size() / 2; i++) {
		ClimbChromosome* p1 = select_parent();
		ClimbChromosome* p2 = select_parent();
		std::uniform_real_distribution<double> dist(0.0,1.0);
		srand(time(0)); //seeding the generator to get random numbers
		mut1 = dist(generator_);
		srand(time(0)); //seeding the generator to get random numbers
		mut2 = dist(generator_);
		// if the mutation rates for individual new climbchromosome pointers is greater than the
		// mut_rate_ then we will mutate the new individuals
		if (mut1 > mut_rate_) {
			p1->mutate();
		}
		if (mut2 > mut_rate_) {
			p2->mutate();
		}
		//creates a new pair of climbchromosome ptrs that will be recombined
		std::pair<Chromosome*, Chromosome*> pair = p1->recombine(p2);
		//have to dynamically cast the new climbchromosomes to climbchromosomes
		auto first = dynamic_cast<ClimbChromosome*>(pair.first);
		auto second = dynamic_cast<ClimbChromosome*>(pair.second);
		new_pop.push_back(first);
		new_pop.push_back(second);
	}
	for (auto i : pop_) {
		delete i;
	}
	pop_ = new_pop;
}

//////////////////////////////////////////////////////////////////////////////
// Return a copy of the chromosome with the highest fitness.
/*
For all of the climbchromosomes in the population vector if one has a higher fitness than the
best fitness than it becomes the best fitness. We will return a climbchromosome pointer to the
climbchromosome in the population that has the best fitness
*/
const ClimbChromosome* Deme::get_best() const
{
  ClimbChromosome* chrome;
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
// Randomly select a climbchromosome in the population based on fitness and
// return a pointer to that climbchromosome.
ClimbChromosome* Deme::select_parent()
{
	// go through the pop vector and adds up all of the fitnesses to get a total fitness
	double total = std::accumulate(pop_.cbegin(), pop_.cend(), 0.0,
		[](double sum, ClimbChromosome* node){return sum + node->get_fitness(); });
	// threshold becomes the total value divided by the population size
	double threshold = total / (pop_.size() * 1.0);
	// make a copy of the population vector so we can manipulate the contents
	std::vector<ClimbChromosome*> copy = pop_;
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
	// if no climbchromosome* surpasses the threshold then we random shuffle to pick a parent
	std::uniform_int_distribution<int> distrib(0, pop_.size() - 1);
	srand(time(0)); //seeding the generator to get random numbers
	int index = distrib(generator_);
	return pop_[index];
}
