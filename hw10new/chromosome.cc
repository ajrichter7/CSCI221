/*
 * Implementation for Chromosome class
 */

#include "chromosome.hh"

//////////////////////////////////////////////////////////////////////////////
// Generate a completely random permutation from a list of cities
Chromosome::Chromosome(const Cities* cities_ptr)
  : cities_ptr_(cities_ptr),
    order_(random_permutation(cities_ptr->size())),
    generator_(rand())
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Clean up as necessary
Chromosome::~Chromosome()
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Perform a single mutation on this chromosome
void
Chromosome::mutate()
{
  // std::cout << "we're mutating!" << std::endl;
  std::uniform_int_distribution<> dis(0, cities_ptr_->size() -1 );
  srand(time(0)); //seeding the generator to get random numbers
  int in1 = dis(generator_);
  srand(time(0)); //seeding the generator to get random numbers
  int in2 = dis(generator_);
  int val = order_[in1];
  order_[in1] = order_[in2];
  order_[in2] = val;
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Return a pair of offsprings by recombining with another chromosome
// Note: this method allocates memory for the new offsprings
std::pair<Chromosome*, Chromosome*>
Chromosome::recombine(const Chromosome* other)
{
  // make sure that each chromosome* is valid
  assert(is_valid());
  assert(other->is_valid());
  std::pair<Chromosome*, Chromosome*> pair;
  // takes half of the chromosome
  int e = cities_ptr_->size() / 2;
  // calls crossover child varying which chromosome* is the parent
  Chromosome* kid1 = create_crossover_child(this, other, 0, e);
  Chromosome* kid2 = create_crossover_child(other, this, 0, e);
  pair.first = kid1;
  pair.second = kid2;
  return pair;
}

//////////////////////////////////////////////////////////////////////////////
// For an ordered set of parents, return a child using the ordered crossover.
// The child will have the same values as p1 in the range [b,e),
// and all the other values in the same order as in p2.

// Eitan 
Chromosome*
Chromosome::create_crossover_child(const Chromosome* p1, const Chromosome* p2,
                                   unsigned b, unsigned e) const
{
  Chromosome* child = p1->clone();
  // We iterate over both parents separately, copying from parent1 if the
  // value is within [b,e) and from parent2 otherwise
  unsigned i = 0, j = 0;

  for ( ; i < p1->order_.size() && j < p2->order_.size(); ++i) {
    if (i >= b and i < e) {
      child->order_[i] = p1->order_[i];
    }
    else { // Increment j as long as its value is in the [b,e) range of p1
      while (p1->is_in_range(p2->order_[j], b, e)) {
        ++j;
      }
      assert(j < p2->order_.size());
      child->order_[i] = p2->order_[j];
      j++;
    }
  }

  assert(child->is_valid());
  return child;
}
//////////////////////////////////////////////////////////////////////////////
// Return a positive fitness value, with higher numbers representing
// fitter solutions (shorter total-city traversal path).
double
Chromosome::get_fitness() const
{
  double distance = calculate_total_distance();
  double one = 1.0;
  return (one / distance);
}
//////////////////////////////////////////////////////////////////////////////
// A chromsome is valid if it has no repeated values in its permutation,
// as well as no indices above the range (length) of the chromosome.
// We implement this check with a sort, which is a bit inefficient, but simple
bool
Chromosome::is_valid() const
{
  Cities::permutation_t copy = order_;
  std::sort(copy.begin(), copy.end());
  if (copy.size() != cities_ptr_->size()) {
    return false;
  }
  for (uint64_t i = 0; i < copy.size(); i++) {
    if (copy[i] != i) {
      return false;
    }
  }
  return true;
}
//////////////////////////////////////////////////////////////////////////////
// Find whether a certain value appears in a given range of the chromosome.
// Returns true if value is within the specified the range specified
// [begin, end) and false otherwise.
bool
Chromosome::is_in_range(unsigned value, unsigned begin, unsigned end) const
{
  for (unsigned i = begin; i < end; i++) {
    if (order_[i] == value) {
      return true;
    }
  }
  return false;
}
