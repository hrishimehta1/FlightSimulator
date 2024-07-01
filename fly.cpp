#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

void writeFile() {
	string fileName = "flights.csv";
	string line;
	
	ifstream file(fileName);
	vector<string> info;
	set<pair<pair<string, string>, pair<double, double>>> locations;
	set<pair<double, double>> distWeight;
	int count = 0;
	if (file.is_open()) {
		getline(file, line);
		info.push_back(line);
		while (getline(file, line)) {
			if(count%10 == 0)
				info.push_back(line);
			count++;
		}
	}
	else
		cout << "Not Open " << endl;

	ofstream myFile;
	myFile.open("flightsv4.csv");
	if (myFile.is_open())
		cout << "Open";
	for (int i = 0; i < info.size(); i++)
		myFile << info[i] << endl;
}

int main() {
	writeFile();
	return 0;
}
