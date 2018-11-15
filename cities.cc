#include "cities.hh"

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
				

