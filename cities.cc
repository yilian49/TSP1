#include "cities.hh"
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>

///////////////////////////////////////////////////////////////////////////////////////
// operator >> reads 2 words each while loop and store them in the city_list
std::istream& operator>> (std::istream& is, Cities& city)
{
	int x;
	int y;
	while(is>>x)
	{
		is>>y;
		Cities::coord_t loc = {x,y};
		city.city_list_add(loc);
	}
	return is;
}

///////////////////////////////////////////////////////////////////////////////////////
// works similarly to >>				
std::ostream& operator<< (std::ostream& os, Cities& city)
{
	int x;
	int y;
	auto city_list_temp = city.get_list();
	for (auto i:city_list_temp)
	{
		x = i.first;
		y = i.second;
		os<<x << "	";
		os<<y << "\n";
	}	
	return os;
}
///////////////////////////////////////////////////////////////////////////////////////
// a free function that takes a length and generate 
// a random, non-repeating sequence of the length
// uses the std::unifor_int_distribution::operator()
// see http://www.cplusplus.com/reference/random/uniform_int_distribution/operator()/

Cities::permutation_t
random_permutation(unsigned int len){

	Cities::permutation_t random_order;
	
	// seed is generated based on the current time
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::default_random_engine generator(seed) ;
	std::uniform_int_distribution<int> distribution(0, len-1);

	while (random_order.size() < len){
		int rand_gen = distribution(generator);

		// checks if the randomly generated int is in the permutation already
		// if it is not, add it to the list
		// if it is, do nothing and repeat the loop
		// until the list is full
		if(std::find(random_order.begin(), random_order.end(), rand_gen) == random_order.end()) {
   			random_order.push_back(rand_gen);
		} 
	}

	return random_order;

}


///////////////////////////////////////////////////////////////////////////////////////
// returns city_list since it is a private member
Cities::city_list_t 
Cities::get_list() const
{
	return city_list;
}

///////////////////////////////////////////////////////////////////////////////////////
// returns the total distance
// uses the std::hypot to find out the distance between two adjacent cities 
double 
Cities::total_path_distance(const permutation_t& ordering) const
{
	double distance = 0;
	long unsigned int i = 0;
	int xi, yi, xj, yj;	// coord of two cities 
	while (i<ordering.size())
	{
		xi = city_list[(ordering[i])].first;	
		yi = city_list[(ordering[i])].second;
		xj = city_list[(ordering[i-1])].first;
		yj = city_list[(ordering[i-1])].second;	
		distance += std::hypot(xi-xj, yi-yj);	
		// increment distance by sqrt[(xi-xj)^2 - (yi-yj)^2]
		// which is the distance between two cities
		i++;
	}
	// add the distance between the last city and first city,
	// which is not included in the while loop
	distance += std::hypot(
			city_list[ordering[0]].first - city_list[ordering[ordering.size()-1]].first,
			
			city_list[ordering[0]].second - city_list[ordering[ordering.size()-1]].second);
	return distance;
}

///////////////////////////////////////////////////////////////////////////////////////
// reorders the cities object by a particular ordering and 
// returns a new cities object arranged in this ordering
Cities
Cities::reorder(const permutation_t& ordering) const
{
	// create a new cities object
	Cities cities_ordered;
	long unsigned int i = 0;

	while(i < ordering.size()){
		// push_back each item from ordering into the new city_list
		// push_back is called by city_list_add
		cities_ordered.city_list_add(city_list[ordering[i]]);
		i++;
	}	

	return cities_ordered;
}

//////////////////////////////////////////////////////////////////////////////////////
// adds one coord_t object to the private city_list
void Cities::city_list_add(coord_t coord)
{
	city_list.push_back(coord);
}

////////////////////////////////////////////////////////////////////////////////////////

int Cities::city_list_len() const
{
	return city_list.size();
}
