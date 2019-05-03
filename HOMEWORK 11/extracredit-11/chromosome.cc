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
  srand(time(0));
  int in1 = dis(generator_);
  srand(time(0));
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
  assert(is_valid());
  assert(other->is_valid());
  std::pair<Chromosome*, Chromosome*> pair;
  Chromosome* kid1 = create_crossover_child(this, other);
  Chromosome* kid2 = create_crossover_child(other, this);
  pair.first = kid1;
  pair.second = kid2;
  return pair;
}

//////////////////////////////////////////////////////////////////////////////
// For an ordered set of parents, return a child using the ordered crossover.
// The child will have the same values as p1 in the range [b,e),
// and all the other values in the same order as in p2.
Chromosome*
Chromosome::create_crossover_child(const Chromosome* p1, const Chromosome* p2) 
{
  //this produces a random order_ for c, but we will write over it
  Chromosome* c = p1->clone();
  std::vector<int> unvisited;
  //create a vector of order_.size() that is consecutive to track cities that the child has not visited
  for (uint64_t i = 0; i < cities_ptr_->size(); i++) {
    unvisited.push_back(i);
  }
  uint64_t usize = unvisited.size();
  //pick a random city to start at, set its position in unvisited to -1 and decrement usize, 
  //which keeps track of cities added to c->order_
  std::uniform_int_distribution<> dist(0, order_.size()-1);
  srand(time(0));
  int start = dist(generator_);
  c->order_[0] = start;
  unvisited.at(start) = -1;
  usize--;

  unsigned int index1, index2, in1, in2, in3, lc;
  double dist1, dist2, best;
  std::vector<int> lost_cities;

  for (uint64_t i = 1; i < order_.size(); i++) {
    //determine the index of start in both p1 and p2's order_s
    // note that it1 and it2 are iterators
    auto it1 = std::find(p1->order_.cbegin(), p1->order_.cend(), start);
    index1 = std::distance(p1->order_.cbegin(), it1);
    auto it2 = std::find(p2->order_.cbegin(), p2->order_.cend(), start);
    index2 = std::distance(p2->order_.cbegin(), it2);
    dist1 = cities_ptr_->flight(p1->order_[index1], p1->order_[(index1 + 1) % order_.size()]);
    dist2 = cities_ptr_->flight(p2->order_[index2], p2->order_[(index2 + 1) % order_.size()]);

    //if dist2 is smaller and we have not visited the next city in its order_ then we add that city to c->order_
    //and set its position in unvisited to -1
    if (dist1 > dist2 && std::find(unvisited.cbegin(), unvisited.cend(), p2->order_[(index2 + 1)  % order_.size()]) != unvisited.cend()) {
      c->order_[i] = p2->order_[(index2 + 1)  % order_.size()];
      unvisited.at(p2->order_[(index2 + 1)  % order_.size()]) = -1;
      usize--;
    }

    //if dist1 is smaller (or equal) and we have not visited the next city in its order_, then we add that city to 
    //c->order_ and adjust unvisited
    else if (std::find(unvisited.cbegin(), unvisited.cend(), p1->order_[(index1 + 1)  % order_.size()]) != unvisited.cend()){
      c->order_[i] = p1->order_[(index1+ 1)  % order_.size()];
      unvisited.at(p1->order_[(index1 + 1) % order_.size()]) = -1;
      usize--;
    }

    //if both of the next cities in the parents' orders have been visited and there are more than 3 unvisited cities, 
    //we pick three random indices and check that they have not been visited, then pick the one with the best distance
    else if (usize > 3) {
        std::uniform_int_distribution<> distrib(0, unvisited.size()-1);
        srand(time(0));
        in1 = distrib(generator_);
        in2 = distrib(generator_);
        in3 = distrib(generator_);
        while(unvisited[in1] == -1) {
          in1 = distrib(generator_);
        }
        while(unvisited[in2] == -1) {
          in2 = distrib(generator_);
        }
        while(unvisited[in3] == -1) {
          in3 = distrib(generator_);
        }
        lost_cities.clear();
        lost_cities.push_back(in1);
        lost_cities.push_back(in2);
        lost_cities.push_back(in3);
        best = 0;
        lc = 100;
        for (uint64_t j = 0; j < lost_cities.size(); j++) {
          if (best == 0 || cities_ptr_->flight(start, lost_cities[j]) < best) {
            best = cities_ptr_->flight(start, lost_cities[j]);
            lc = lost_cities[j];
          }
        }
        c->order_[i] = lc;
        unvisited.at(lc) = -1;
        usize--;
    }

    //if there are 3 or less unvisited cities, we find the best distance among them and add that to c->order_
    else {
      best = 0;
      for (uint64_t k = 0; k < unvisited.size(); k++) {
        if (unvisited[k]!= -1 && (best == 0 || cities_ptr_->flight(start, unvisited[k]) < best)) {
            best = cities_ptr_->flight(start, unvisited[k]);
            lc = k;          
        }
      }
      c->order_[i] = unvisited[lc];
      unvisited.at(unvisited[lc]) = -1;
      usize--;
    }

  //now we start at the city just added to find the next city in c->order_
  start = c->order_[i];
  }

  if (!(c->is_valid())) {
    for (auto i : c->order_) {
      std::cout<< i << std::endl;
    }
  assert(c->is_valid());
  }
  return c;
}

// Return a positive fitness value, with higher numbers representing
// fitter solutions (shorter total-city traversal path).
double
Chromosome::get_fitness() const
{
  double distance = calculate_total_distance();
  double one = 1.0;
  return (one / (distance + 1.0));
}

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


// int main() {
//   return 0;
// }

