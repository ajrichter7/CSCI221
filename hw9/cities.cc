/*
* Implementation file for Travelling-Salesperson Cities class and utilities
*/

#include "cities.hh"

/*
Given two coordinate pairs this will apply an implementation of the
distance formula which we wrote where (c1x, c2y) == (x,y) for the first pair and
(cx2, cy2) == (x,y) for the second pair. Will return the value calculated
for the distance.
*/
double distance(Cities::coord_t c1, Cities::coord_t c2) {
  int c1x = c1.first;
  int c1y = c1.second;
  int c2x = c2.first;
  int c2y = c2.second;
  return std::sqrt(std::pow(c2x - c1x, 2) + std::pow(c2y - c1y, 2));
}

/*
Given a permutation, return a new Cities object where the order of the cities
reflects the original order of this class after reordering with the given
ordering. So for example, the ordering { 1, 0 } simply swaps the first two
elements (coordinates) in the new Cities object.
*/
Cities Cities::reorder(const permutation_t& ordering) const {
  Cities new_cities;
  for (auto i : ordering) {
    new_cities.v_cities_.push_back(v_cities_[i]);
  }
  return new_cities;
}

//Returns the length of the vecotr which is also the number of cities.
int Cities::get_number_of_cities() const {
  return v_cities_.size();
}

/*
For a given permutation of the cities in this object, compute how long (distance)
it would take to traverse all the cities in the order of the permutation, and
then returning to the first city. The distance between any two cities is
computed as the Euclidean distance on a plane between their coordinates.
*/
double Cities::total_path_distance(const permutation_t& ordering) const {
  double total_distance = 0;
  Cities new_cities = this->reorder(ordering);
  for (uint64_t i = 0; i < ordering.size() - 1; i++) {
    total_distance += distance(new_cities.v_cities_[i], new_cities.v_cities_[i+1]);
  }
  total_distance += distance(new_cities.v_cities_[0], new_cities.v_cities_[new_cities.v_cities_.size() - 1]);
  return total_distance;
}

/*
Overriding the operator>> takes in a reference to the istream and a reference
to a cities object. While there is a first value in a pair then it will read in
the first value and then read in the second value. The vector of cities will then
be pushed back for that pair. A reference to the istream is returned.
*/
std::istream& operator>>(std::istream& is, Cities& cities) {
  Cities::coord_t loc;
  while (is >> loc.first) {
    is >> loc.second;
    cities.v_cities_.push_back(loc);
  }
  return is;
}

/*
Overriding the operator<< takes in a reference to the ostream and a reference
to a cities object. For each item in the vector of cities, sends the first element
in the pair to the ostream, a space, and then the second element in the pair
to the ostream. It will return a reference to the ostream.
*/
std::ostream& operator<<(std::ostream& os, Cities& cities) {
  for (auto i : cities.v_cities_) {
    os << i.first << " " << i.second << std::endl;
  }
  return os;
}
