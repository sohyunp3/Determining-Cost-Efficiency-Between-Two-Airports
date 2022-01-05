#include "Graph.h"
#include "CSVReader.hpp"
#include "algorithm"
#include "cctype"
#include <iostream>
#include "Image.h"
#include "BFS.cpp"
#include "Dijkstra.cpp"

string getAirportName(int IATA, vector<vector<string>> IATAList);

int main() {
	std::cout << "Loading the dataset ...";
    vector<vector<string>> data = readCSV("dataset.csv");
	std::cout << " done\n";
	std::cout << "Loading the IATA list ...";
	vector<vector<string>> IATAList = readCSV("airports.csv");
	std::cout << " done\n";
    Graph<int> g(data);

	string src;
	string dst;
	std::cout << "Please choose the IATA code of the source Airport: ";
	std::cin >> src;
	std::cout << "Please choose the IATA code of the destination Airport: ";
	std::cin >> dst;

	std::cout << "Writing the BFS on the source airport ... ";
	BFS(g, stoi(src));

	std::cout << "BFS done\n" << "The cheapest flight from the " << getAirportName(stoi(src), IATAList) << " to " << getAirportName(stoi(dst), IATAList) << " is: ";
	vector<int> path = dijkstraSSSP(g, stoi(src), stoi(dst));
	
	for (int i = 0; i < path.size(); i++) {
		if (i == path.size() - 1)
			std::cout << getAirportName(path[i], IATAList) << std::endl;
		else
			std::cout << getAirportName(path[i], IATAList) << " -> ";
	}
    return 0;
}

string getAirportName(int IATA, vector<vector<string>> IATAList) {
	for (int i = 1; i < IATAList.size(); i++) {
		if (stoi(IATAList[i][1]) == IATA) {
			return IATAList[i][2];
		}
	}
	return "none";
}