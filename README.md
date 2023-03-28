# Autopilot Simulation Challenge

Your objective is to construct a search algorithm to find the minimum time path through a hypothetical
network of Tesla supercharging stations. Your final route does not have to fully charge at every visited charger,
so long as it never runs out of charge between two chargers. You should expect to need no more 
than 4-6 hours to solve this problem. We suggest implementing a quick brute force method before
attempting to find an optimal algorithm.

You may compare your solutions against our reference implementation using the provided
"checker" programs in either OSX (checker_osx), Windows Subsystem for Linux (checker_linux_64), or Linux (checker_linux_64). Make sure to use it to check your submission output
against several different start and end chargers.

---

You will be provided with a csv which includes the charger network data
in the format below with newlines separating each charger:

	name, latitude in degrees, longitude in degrees

Your program should take as input three strings: 
		
		./your_solution [path to list of chargers csv] [start charger name] [end charger name]

Your program’s only output should be a print to standard out in the format:

		initial charger name, first charger name, charge time in hrs, second charger name, charge time in hrs, …, …, goal charger name

This is the format required by the checker program as well, for example the command:

		./your_solution network.csv Council_Bluffs_IA Cadillac_MI 

might return:

		Council_Bluffs_IA, Worthington_MN, 0.17, Albert_Lea_MN, 0.33, Mauston_WI, 0.23, Sheboygan_WI, 0.24, Cadillac_MI
	
You can check the solution by providing your output to the included checker, for example:
		
		./checker_osx network.csv "Council_Bluffs_IA, Worthington_MN, 0.17, Albert_Lea_MN, 0.33, Mauston_WI, 0.23, Sheboygan_WI, 0.24, Cadillac_MI"

will return:
		
		Finding Path Between Council_Bluffs_IA and Cadillac_MI
		Reference result: Success, cost was 17.2531
		Candidate result: Success, cost was 17.2548


You should make the following assumptions:

- The car begins at the start charger with a full charge of 320km
- The superchargers have a charge rate of 800km/hr
- The car travels at a constant speed of 105km/hr along great circle routes between chargers
- The Earth is a sphere of radius 6356.752km


Your submission will be run against several start and end chargers and evaluated in terms of the 
following metrics:

- Path satisfiability (car remains above 0km of range throughout entire trip)
- Path optimality (total time driving + charging)
- Coding structure
- Code clarity
- Computational cost


You should ensure that your submission compiles under gcc with optimization level 1, for example:

	g++ -std=c++17 -O1 main.cpp network.cpp -o candidate_solution

Do not use libraries outside of the C++ Standard Library.

Feel free to add a README explaining your solution. If your solution includes additional cpp files include the appropriate compiler string in your README as well.

Runjie Zhao's Solution: In this problem, we first need to access csv file and retrieve the data from it. Then, we use the latitude/longitude distance formula to calculate the distance between two points. Then, we consider each place as a vertex and there is an edge between two vertices if and only if the distance between those two edges is less than 320. In that case, we can consider the distance between two vertices as the weights. Then, we can use Dijkstra's algorithm to calculate the shortest path from the source node to our destination node. Since the weight of each edge is not an integer, we are unable to use Dial's algorithm which is more efficient.
