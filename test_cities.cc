#include "cities.hh"
#include <iostream>

int main()
{
	auto fin = std::ifstream("five.tsv");
	Cities cities;
	fin>>cities;
	for (Cities::coord_t c:cities.city_list)
	{
		std::cout<<c.first<<"\t"<<c.second<<"\n";
		
	}

	Cities::permutation_t ordering = {1,4,0,2,3};	

	std::cout<<cities.total_path_distance(ordering);

	auto fout = std::ofstream("out");
	fout<<cities;

	return 0;
}
