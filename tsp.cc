#include "cities.hh"
#include <iostream>
#include <fstream>



int main(int argc, char** argv)
{
	if (argc < 1)
	{
		std::cout<<"need at least one input file";
	}

	auto input_file_name = argv[1];
//	std::ifstream input_file(input_file_name, std::ios::in);
	auto fin = std::ifstream(input_file_name);
	
	auto fout = std::ofstream("shortest.tsv");

	Cities cities;
	fin>>cities;

	auto list_size = cities.get_list().size();

	auto best_order = random_permutation(list_size);
	auto new_order = random_permutation(list_size);

	for (int i = 0; i<1000000; i++)
	{

		new_order = random_permutation(list_size);
		if (cities.total_path_distance(new_order)
			< cities.total_path_distance(best_order))
		{
			best_order = new_order;
			std::cout<<i<<"\t"<<cities.total_path_distance(best_order)<<"\n";
		}
	}

	cities = cities.reorder(best_order);
	fout<<cities;
	return 0;
}

