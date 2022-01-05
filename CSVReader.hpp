#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<vector<string>> readCSV(string file_name) {
    ifstream fin(file_name);
    
    string line;
    vector<vector<string>> data;
    int count = 0;
    
    while (getline(fin, line)) {
        stringstream ss(line);
        string temp;
        data.push_back(vector<string>());

        while (getline(ss, temp, ',')) {
            data[count].push_back(temp);
        }
        count++;
    }

    return data;
}