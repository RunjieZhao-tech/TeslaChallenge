#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <utility>
#include <cmath>
#include <list>
#include <limits.h>

class Network {
private:
	//csv filename
	std::string filename;

	//origin and destination name
	std::string origin;
	std::string dest;

	//initialize the radius, charge rate, speed
	double raidus = 6356.752;
	double rate = 800;
	double speed = 105;
	int max_distance = 320;

	//create a vector with a pair of values to be longitude and latitude
	std::vector<std::pair<double,double>> net;

	//create a connection between each place and each unique id
	std::map<std::string, int> place2id;
	std::map<int, std::string> id2place;

	//create distance 2D matrix
	std::vector<std::vector<double>> edge_matrix;

	//result from shortest path function
	std::vector<int> path_order;
public:
	Network();
	Network(std::string,std::string,std::string);
	double calc_distance(int, int);
	void calc_edge();
	void soln();
	void shortest_path();
	void refuel();
};