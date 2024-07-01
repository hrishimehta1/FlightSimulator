#include <unordered_map>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <chrono>
#include <queue>

using namespace std;
using namespace std::chrono;
typedef high_resolution_clock Clock;
#define INF 0x3f3f3f3f

class Graph {
private:
	//graph class will have both adjacency list and adjacency matrix member variables, with functions unique to each container
	
	//adjacency list container
	unordered_map<string, vector<pair<string, double>>> al;

	//adjacency matrix container
	vector<vector<double>> am;

	//int representation of string vertices
	unordered_map<string, int>locationsAL;
	unordered_map<string, int> locationsAM;
public:
	Graph();

	//inserts edge from to into Adjacency List
	void insertEdgeAL(string from, string to, double weight);

	//checks to see if edge exists for adjacency list and matrix
	bool isEdge(string from, string to);
	bool isEdgeAM(string from, string to);

	//returns adjacent vertices
	vector<pair<string,double>> getAdjacent(string vertex);

	//returns number of vertices in adjacency list
	int getSize();

	//helper functions to help visualize the graph - mainly for debugging purposes
	void printGraphAL();
	void printGraphAM();

	//dijkstra algorithm for both adjacency list and matrix
	void shortestPath(string src, string dest, bool cost);
	void dijkstraAM(string src, string dest, bool cost);

	//more helper print functions to help visualize what the code is doing
	void printLocations();
	void displayOptions();

	//since you can't search by value in a map, made functions that iterate through map until a value maches the passed index - returns string key
	string findLocation(int index);
	string findLocationAM(int index);

	//read file initializes both the adjacency list and matrix with the proper values depending on if user wants to determine shortest path or least costly
	void readFile(string file, bool cost);
};

Graph::Graph() {
	//we know that there are 270 unique vertices
	vector<double> temp(270);
	for (int r = 0; r < 270; r++)
		am.push_back(temp);
}

string Graph::findLocation(int index) {
	for (auto it = locationsAL.begin(); it != locationsAL.end(); it++)
		if (it->second == index)
			return it->first;
}

string Graph::findLocationAM(int index) {
	for (auto it = locationsAM.begin(); it != locationsAM.end(); it++)
		if (it->second == index)
			return it->first;
}

void Graph::printLocations() {
	for (auto it = locationsAL.begin(); it != locationsAL.end(); it++)
		cout << it->first << " " << it->second << endl;
}

void Graph::displayOptions() {
	int count = 1;
	for (auto it = locationsAL.begin(); it != locationsAL.end(); it++) {
		if (count % 27 == 0)
			cout << endl;
		cout << it->first << " ";
	}
}

void Graph::insertEdgeAL(string from, string to, double weight) {
	//if edge already exists, no need to add it
	if (isEdge(from, to))
		return;

	pair<string, double> temp(to, weight);
	al[from].push_back(temp);

	//the "to" also becomes a vertex in the directed graph, no adjacent edges yet
	if (!isEdge(to, from))
		al[to];// .push_back(make_pair(from, weight));
}

bool Graph::isEdge(string from, string to) {
	for (int i = 0; i < al[from].size(); i++)
		if (al[from][i].first == to)
			return true;
	return false;
}

bool Graph::isEdgeAM(string from, string to) {
	int fromIndex = locationsAM[from];
	int toIndex = locationsAM[to];
	if (am[fromIndex][toIndex] == 0)
		return false;
	return true;
}

vector<pair<string, double>> Graph::getAdjacent(string vertex) {
	return al[vertex];
	/*vector<pair<string, double>> adjacent;
	for (int i = 0; i < graph[vertex].size(); i++) {
		adjacent.push_back(graph[vertex][i]);
	}
	sort(adjacent.begin(), adjacent.end());
	return adjacent;*/
}

void Graph::printGraphAL() {
	vector<pair<string,double>> adjacent;
	for (auto it = al.begin(); it != al.end(); it++) {
		adjacent = getAdjacent(it->first);
		cout << it->first;
		for (int i = 0; i < adjacent.size(); i++) {
			cout << " ";
			cout << adjacent[i].first << " : " << adjacent[i].second;
		}
		if (next(it) != al.end())
			cout << endl;
	}
}

void Graph::printGraphAM() {
	for (int r = 0; r < am.size(); r++) {
		for (int c = 0; c < am[0].size(); c++)
			cout << am[r][c] << " ";
		cout << endl;
	}

}

void Graph::shortestPath(string src, string dest, bool cost) {
	//creating priority queue, where double is weight, and int is int representation of vertex
	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

	//initializing distance and previous array of size 270, number of unique airports
	vector<double> dist(270, INF);
	vector<int> prev(270, -1);

	int srcIndex = locationsAL[src];

	//marking the src vertex as having been processed
	pq.push(make_pair(0, srcIndex));
	dist[srcIndex] = 0;

	while (!pq.empty()) {

		pair<double, int> curr = pq.top();
		pq.pop();
		int u = curr.second;
		string temp = findLocation(u);

		//iterating through the top of the priority queue's adjacent edges, reassigning shortest distance when needed
		for (auto it = al[temp].begin(); it != al[temp].end(); it++) {
			string v = it->first;
			double w = it->second;

			if (dist[locationsAL[v]] > dist[u] + w) {
				dist[locationsAL[v]] = dist[u] + w;
				pq.push(make_pair(dist[locationsAL[v]], locationsAL[v]));
				prev[locationsAL[v]] = u;
			}
		}
	}

	// algorithm to display what path the user must take to reach their destination
	vector<int> path;
	int v = locationsAL[dest];
	path.push_back(v);

	//iterates through dist and prev arrays, starting from the destination and working its way back to the source, adding vertices to the path vector as it goes
	while (v != locationsAL[src]) {
		path.insert(path.begin(), prev[v]);
		v = prev[v];
	}
	path.erase(path.begin());

	if (cost)
		cout << "\tLeast Costly Path: " << endl;
	else
		cout << "\tShortest Path: " << endl;

	int index = 0;
	for (int i = 0; i < 270; i++) {
		if (i = locationsAL[dest]) {
			index = i;
			cout << "\t" << src;
			for (int h = 0; h < path.size(); h++)
				cout << " -> " << findLocation(path[h]);
			cout << endl << endl;
			break;

		}
	}

	if (cost){
		cout << "\tTotal Cost: " << endl;
		cout << "\t$";
	}
	else {
		cout << "\tTotal Distance: " << endl;
		cout << "\t";
	}
	cout << dist[index];
}

void Graph::dijkstraAM(string src, string dest, bool cost) {
	//same logic as above
	vector<double> sol(270, INF);
	vector<bool> set(270, false);
	vector<int> prev(270, -1);
	int srcIndex = locationsAM[src];
	int destIndex = locationsAM[dest];
	sol[srcIndex] = 0;
	for (int x = 0; x < 269; x++) {
		double min = INF;
		int mindex;
		for (int y = 0; y < 270; y++) {
			if (!set[y] && sol[y] <= min) {
				min = sol[y];
				mindex = y;
			}
		}
		set[mindex] = true;
		for (int z = 0; z < 270; z++) {
			if (!set[z] && am[mindex][z] != 0 && sol[mindex] != INF && sol[mindex] + am[mindex][z] < sol[z]) {
				sol[z] = sol[mindex] + am[mindex][z];
				prev[z] = mindex;
			}

		}
	}


	vector<int> path;
	int v = locationsAM[dest];
	path.push_back(v);
	while (v != locationsAM[src]) {
		path.insert(path.begin(), prev[v]);
		v = prev[v];
	}
	path.erase(path.begin());

	if (cost)
		cout << "\tLeast Costly Path: " << endl;
	else
		cout << "\tShortest Path: " << endl;
	int index = 0;
	for (int i = 0; i < 270; i++) {
		if (i == locationsAM[dest]) {
			index = i;
			cout << "\t" << src;
			for (int h = 0; h < path.size(); h++)
				cout << " -> " << findLocationAM(path[h]);
			cout << endl << endl;
			break;

		}
	}

	if (cost) {
		cout << "\tTotal Cost: " << endl;
		cout << "\t$";
	}
	else {
		cout << "\tTotal Distance: " << endl;
		cout << "\t";
	}
		
	cout << sol[index];

}

int Graph::getSize() {
	int count = 0;
	for (auto it = al.begin(); it != al.end(); it++) {
		count++;
	}
	return count;
}

void Graph::readFile(string file, bool cost) {

	//creating stream to read file
	ifstream myFile(file);
	string line;

	//burner getline call to get rid of header information
	getline(myFile, line);
	int count = 0;

	if (myFile.is_open()) {

		//initializing variables
		string src = "";
		string dest = "";
		double weight = 0.0;

		while (getline(myFile, line)) {
			//create stream
			stringstream ss(line);

			//vector holds each column in the csv file
			vector<string> parsed;
			
			//parse data by comma using stream
			while (ss.good()) {
				string data;
				getline(ss, data, ',');
				parsed.push_back(data);
			}

			//indices: 5 = src, 7 = dest, 9 = dist, 13 = cost
			src = parsed[5];
			dest = parsed[7];

			//if bool cost == true, weight is cost, if cost == false, weight is distance
			if (cost)
				weight = stod(parsed[13]);
			else
				weight = stod(parsed[9]);

			//initializing both the adjacency matrix and adjacency list along with their respective index trackers
			if (locationsAL.find(src) == locationsAL.end()) {
				locationsAL[src] = count;
				locationsAM[src] = count;
				count++;
			}
			if (locationsAL.find(dest) == locationsAL.end()) {
				locationsAL[dest] = count;
				locationsAM[dest] = count;
				count++;
			}
			if (am[locationsAM[src]][locationsAM[dest]] == 0) {
				am[locationsAM[src]][locationsAM[dest]] = weight;
				//am[locationsAM[dest]][locationsAM[dest]] = weight;
			}

			//inserts edge into adjacency list, doesn't do anything if edge already exist
			insertEdgeAL(src, dest, weight);
		}
	}
	else
		cout << "Not Open " << endl;
}

int main() {
	Graph graphCost;
	Graph graphDist;
	string fileName = "";
	bool cost = true;

	cout << "File Name: " << endl;
	cin >> fileName;
	cout << endl << endl;

	cout << "Reading File..." << endl << endl;

	auto t4 = Clock::now();
	graphCost.readFile(fileName, cost);
	auto t5 = Clock::now();
	cout << "Adjacency List Construction: " << duration_cast<nanoseconds>(t5 - t4).count() << " nanoseconds" << endl << endl;
	graphDist.readFile(fileName, !cost);
	auto t6 = Clock::now();
	cout << "Adjacency Matrix Construction: " << duration_cast<nanoseconds>(t6 - t5).count() << " nanoseconds" << endl << endl;

	string cont;
	while (cont != "N") {
		cout << "1 - Least Costly" << endl;
		cout << "2 - Least Distance Traveled" << endl << endl;
		
		int choice = 0;
		cin >> choice;
		cout << endl << endl;

		while (choice != 1 && choice != 2) {
			cout << "Please Enter A Valid Option! " << endl;
			cin >> choice;
		}

		cout << endl;
		graphDist.displayOptions();
		cout << endl;

		string src = "";
		cout << endl <<  "Origin: " << endl;
		cin >> src;
		cout << endl << endl;

		string dest = "";
		cout << "Destination: " << endl;
		cin >> dest;
		cout << endl << endl;


		if (choice == 1) {
			cout << endl;
			cout << "Least Costly Path Using Adjacency List" << endl << endl;
			auto t1 = Clock::now();
			graphCost.shortestPath(src, dest, cost);
			auto t2 = Clock::now();
			cout << endl << endl;

			cout << "\tAdjacency List Dijkstra: " << duration_cast<nanoseconds>(t2 - t1).count() << " nanoseconds" << endl << endl;

			cout << "Least Costly Path Using Adjacency Matrix" << endl << endl;
			
			graphCost.dijkstraAM(src, dest, cost);

			auto t3 = Clock::now();
			cout << endl << endl;

			cout << "\tAdjacency Matrix Dijkstra: " << duration_cast<nanoseconds>(t3 - t2).count() << " nanoseconds" << endl << endl;

		}
		if (choice == 2) {
			cout << endl;
			cout << "Least Distance Traveled Path Using Adjacency List" << endl << endl;
			auto t1 = Clock::now();
			graphDist.shortestPath(src, dest, !cost);
			auto t2 = Clock::now();
			cout << endl << endl;

			cout << "\tAdjacency List Dijkstra: " << duration_cast<nanoseconds>(t2 - t1).count() << " nanoseconds" << endl << endl;

			cout << "Least Distance Traveled Path Using Adjacency Matrix" << endl << endl;

			graphDist.dijkstraAM(src, dest, !cost);

			auto t3 = Clock::now();
			cout << endl << endl;

			cout << "\tAdjacency Matrix Dijkstra: " << duration_cast<nanoseconds>(t3 - t2).count() << " nanoseconds" << endl << endl;

		}

		cout << "Continue: Y/N" << endl;
		cin >> cont;
		cout << endl;
	}

	
	return 0;
}
