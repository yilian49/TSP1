#include "cities.hh"
#include <iostream>
#include <fstream>



int main(int argc, char** argv)
{
	if (argc < 1)
	{
		std::cout<<"need at least one input file";
		exit(1);
	}

	auto input_file_name = argv[1];
	// open the input file
	auto fin = std::ifstream(input_file_name);
	auto fout = std::ofstream("shortest.tsv");

	// load the input file into the currently empety cities object
	Cities cities;
	fin>>cities;

	// save the list size so that 
	// the get_list function doesnt need to be called evertime
	auto list_size = cities.get_list().size();

	// generate a permutation and save it as the new best permutation
	auto best_order = random_permutation(list_size);

	for (int i = 0; i<1000000; i++)
	{
		// generate new permutation
		auto new_order = random_permutation(list_size);

		// compare the distances between the two
		// if the new one is shorter,
		// overwrite the old permutation
		if (cities.total_path_distance(new_order)
			< cities.total_path_distance(best_order))
		{
			best_order = new_order;
			std::cout<<i<<"\t"<<cities.total_path_distance(best_order)<<"\n";
		}
	}

	// reorder the cities and store the new object in cities
	cities = cities.reorder(best_order);

	// out put cities
	fout<<cities;
	cities.~Cities();
	return 0;
}

