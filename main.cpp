#include <iostream>
#include "network.h"

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cout << "Error: requires csv path, initial supercharger names, and final supercharger names" << std::endl;        
        return -1;
    }
    
    std::string charger_csv_path = argv[1];
    std::string initial_charger_name = argv[2];
    std::string goal_charger_name = argv[3];

    //create a new network class
    Network* network = new Network(charger_csv_path, initial_charger_name, goal_charger_name);
    network->soln();

    return 0;
}