#include "cities.hh"
#include <cmath>

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
	
double 
Cities::total_path_distance(const permutation_t& ordering) const
{
	double distance = 0;
	int i = 1;
	int xi, yi, xj, yj;	// cood of two cities
	while (i<ordering.size())
	{
		xi = city_list[(ordering[i])].first;	//doesn't work!!!!
		yi = city_list[(ordering[i])].second;
		xj = city_list[(ordering[i-1])].first;
		yj = city_list[(ordering[i-1])].second;	
		distance += std::hypot(xi-xj, yi-yj);
		i++;
	}
	distance += std::hypot(
			city_list[(ordering.begin())].first - city_list[(ordering.end())].first,
			
			city_list[(ordering.begin())].second - city_list[(ordering.end())].second);
	return distance;
}

Cities
Cities::reorder(const permutation_t& ordering) const
{
	
