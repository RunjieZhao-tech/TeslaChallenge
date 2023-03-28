#include "network.h"
using namespace std;
# define INF 0x3f3f3f3f

//helper function degree to radian
double d2rad(double degree) {
	return degree / 180.0 * M_PI;
}

Network::Network():filename() {}

Network::Network(std::string filename,string origin, string dest):filename(filename),origin(origin),dest(dest) {}

//calculate the distance between place 1 and place 2
double Network::calc_distance(int source1, int source2) {
	double lat1 = d2rad(net[source1].first);
	double lon1 = d2rad(net[source1].second);
	double lat2 = d2rad(net[source2].first);
	double lon2 = d2rad(net[source2].second);
	float distance = acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon2 - lon1)) * raidus;
	return distance;
}

//calculate the edge matrix
void Network::calc_edge() {
	for (int i = 0; i < net.size(); i++) {
		vector<double> temp;
		edge_matrix.push_back(temp);
		for (int j = 0; j < net.size(); j++) {
			if (i == j) {
				edge_matrix.at(i).push_back(-1);
				continue;
			}
			double dist = calc_distance(i,j);
			if (dist > 320) { 
				edge_matrix.at(i).push_back(-1); 
				continue;
			}
			edge_matrix.at(i).push_back(dist);	
		}
	}
}

//find shortest path in this weighted graph
void Network::shortest_path() {
	//initialize the origin and destination
	int origin_id = place2id[origin];
	int dest_id = place2id[dest];
	vector<pair<int, vector<int>>> dist(net.size());

	bool sptSet[net.size()];
	for (int i = 0; i < net.size(); i++)
		dist[i].first = INT_MAX, sptSet[i] = false;
	
	//initialize the source node
	dist[origin_id].first = 0;
	vector<int> order;
	order.push_back(origin_id);
	dist[origin_id].second = order;
	sptSet[origin_id] = true;

	//Separate Set initialization
	vector<int> sep_set;
	sep_set.push_back(origin_id);
	
	//According to Dijkstra's algorithm, it will iterate at most net.size() times.
	for (int i = 0; i < net.size(); i++) {
		double minimum_distance = 2 * M_PI * 6356;
		int current_dest = -1;
		int current_origin = -1;
		for (int j = 0; j < sep_set.size(); j++) {
			for (int k = 0; k < net.size(); k++) {
				//check if the destination is in the same set, if origin is same as destination and if edge matrix value is smaller than 0
				if (sptSet[k] || j == k || edge_matrix[sep_set[j]][k] < 0)continue;

				//if current distance is smaller than minimum distance, then we assign the value.
				if (dist[sep_set[j]].first + edge_matrix[sep_set[j]][k] < minimum_distance) {
					minimum_distance = dist[sep_set[j]].first + edge_matrix[sep_set[j]][k];
					current_dest = k;
					current_origin = sep_set[j];
				}
			}
		}
		//std::cout << current_dest << std::endl;
		sptSet[current_dest] = true;
		sep_set.push_back(current_dest);


		//check if the graph is not connected
		if (current_dest == -1) {
			cout << "cannot reach destination from our origin" << endl;
			return;
		}

		//path distance from source node to current node
		dist[current_dest].first = minimum_distance;
		vector<int> current_order(dist[current_origin].second);
		current_order.push_back(current_dest);
		dist[current_dest].second = current_order;
		if (dest_id == current_dest) {
			path_order = dist[dest_id].second;
			return;
		}
	}
}

//calculate refuel time
void Network::refuel() {
	//initialize the origin and destination
	int previous_id = place2id[origin];
	int dest_id = place2id[dest];
	double current_fuel = 320;
	cout << origin << ", ";
	for (int i = 1; i < path_order.size(); i++) {
		int current_id = path_order[i];
		double distance = edge_matrix[previous_id][current_id];
		if (current_fuel - distance > 0) {
			current_fuel -= distance;

		}else{
			double time = (distance - current_fuel) / rate;
			cout << id2place[previous_id] << ", " << time << ", ";
			current_fuel = 0;
		}
		previous_id = current_id;
	}
	cout << dest << endl;
}

//solution to this problem
void Network::soln() {
	//intialize file pinter
	fstream fin;

	//open an existing file
	fin.open(filename, ios::in);

	//initialize line to be read into and the name of the place we will read
	string line, place_name;

	int id = 0;
	while (fin >> place_name) {
		getline(fin, line);
		place_name += line;

		// used for breaking words
		stringstream s(place_name);

		vector<std::string> row;
		
		//content
		string content;
		
		while (getline(s, content, ',')) {
			// add all the column data of a row to a vector
			row.push_back(content);
		}
		//set the precision
		cout.precision(10);

		//assign the latitude degree value and longitude degree value
		double latitude = stod(row.at(1));
		double longitude = stod(row.at(2));

		place2id[row.at(0)] = id;
		id2place[id] = row.at(0);
		net.push_back(make_pair(latitude,longitude));
		id++;
	}

	//check if the input origin and destination place exist
	if (place2id.find(origin) == place2id.end() || place2id.find(dest) == place2id.end()) {
		std::cout << "origin or destination name is not valid" << std::endl;
		return;
	}

	//calculate distance
	double distance = calc_distance(place2id[origin],place2id[dest]);

	//calculate edge_matrix
	calc_edge();

	//use Dijkstra's algorithm
	int origin_id = place2id[origin];
	int dest_id = place2id[dest];

	//find shortest path
	shortest_path();

	//calculate refuel time
	refuel();

	//close the file
	fin.close();
}