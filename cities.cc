#include "cities.hh"
#include <algorithm>
#include <cmath>
#include <random>

///////////////////////////////////////////////////////////////////////////////////////

std::istream& operator>> (std::istream& is, Cities& city)
{
	int x;
	int y;
	while(is>>x)
	{
		is>>y;
		Cities::coord_t loc = {x,y};
		city.city_list.push_back(loc);
	}
	return is;
}

///////////////////////////////////////////////////////////////////////////////////////
				
std::ostream& operator<< (std::ostream& os, Cities& city)
{
	int x;
	int y;
	for (auto i:city.city_list)
	{
		x = i.first;
		y = i.second;
		os<<x << "	";
		os<<y << "\n";
	}	
	return os;
}
	
///////////////////////////////////////////////////////////////////////////////////////

double 
Cities::total_path_distance(const permutation_t& ordering) const
{
	double distance = 0;
	long unsigned int i = 0;
	int xi, yi, xj, yj;	// cood of two cities
	while (i<ordering.size())
	{
		xi = city_list[(ordering[i])].first;	
		yi = city_list[(ordering[i])].second;
		xj = city_list[(ordering[i-1])].first;
		yj = city_list[(ordering[i-1])].second;	
		distance += std::hypot(xi-xj, yi-yj);
		i++;
	}
	distance += std::hypot(
			city_list[ordering[0]].first - city_list[ordering[ordering.size()-1]].first,
			
			city_list[ordering[0]].second - city_list[ordering[ordering.size()-1]].second);
	return distance;
}

///////////////////////////////////////////////////////////////////////////////////////

Cities
Cities::reorder(const permutation_t& ordering) const
{
	Cities cities_ordered;
	long unsigned int i = 0;

	while(i < ordering.size()){
		cities_ordered.city_list.push_back(city_list[ordering[i]]);
	}	

	return cities_ordered;
}

///////////////////////////////////////////////////////////////////////////////////////

Cities::permutation_t
random_permutation(unsigned int len){

	Cities::permutation_t random_order;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, len-1);

	while (random_order.size() < len){
		int rand_gen = distribution(generator);

		if(std::find(random_order.begin(), random_order.end(), rand_gen) == random_order.end()) {
   			random_order.push_back(rand_gen);
		} 
	}

	return random_order;
}
