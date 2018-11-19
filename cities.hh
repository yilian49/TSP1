/*
 * API file for Travelling-Salesperson Cities class and utilities
 */

#pragma once

#include <vector>
#include <fstream>

// Representation of an ordering of cities
class Cities {
 public:
  // A pair of integral coordinates for each city
  using coord_t = std::pair<int, int>;
  
  using city_list_t = std::vector<coord_t>;

  // An ordering of the cities in cities_t. Each value represents a unique index
  // into the current city ordering.
  using permutation_t = std::vector<unsigned int>;

  ~Cities() = default;

  // Given a permutation, return a new Cities object where the order of the
  // cities reflects the original order of this class after reordering with
  // the given ordering. So for example, the ordering { 1, 0 } simply swaps
  // the first two elements (coordinates) in the new Cities object.
  Cities reorder(const permutation_t& ordering) const;

  // For a given permutation of the cities in this object,
  // compute how long (distance) it would take to traverse all the cities in the
  // order of the permutation, and then returning to the first city.
  // The distance between any two cities is computed as the Euclidean 
  // distance on a plane between their coordinates.
  double total_path_distance(const permutation_t& ordering) const;
 
  // used to add one item to the city list, which is a private member 
  void city_list_add(coord_t coord);
  
  // returns the length of city list, a private member.
  // this is a constant function
  int city_list_len() const;

  // returns a copy of city_list
  // also constant function
  city_list_t get_list() const;  

 private:
  city_list_t city_list;
};


std::istream& operator>> (std::istream& is, Cities& city); 
std::ostream& operator<< (std::ostream& is, Cities& city);

// generates a random permutation by a given length
Cities::permutation_t random_permutation(unsigned int len);
