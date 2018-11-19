# TSP1
Traveling salesperson problem part 1
by Yilian Liu Q75098
and Vinay Gopalan

cities.hh
	the header file, it declares class Cities 
	as well as 3 free functions:
		operator >>, which reads from a file and stores into a cities object
		operator <<, which stores data from a cities object into a file
		random_permutation, which returns a vector of randomized non-repeating int
	-city_list is a private member, so city_list_add and get_list are added
	to read from and write into city_list
	-reorder returns a new cities object in the new ordering
	
cities.cc
	specifies the methods declared in the header file
		
tsp.cc
	uses the random_permutation funtion to find the shortest solution in 1,000,000
	permutations
	it then returns the new cities arranged in the order that gives the 
	shortest distance	
