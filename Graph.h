#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <limits.h>
#include <fstream>

using std::string;
using std::vector;
using std::pair;
using std::find;

template <class V>
class Graph {
    public:
        Graph(vector<vector<string>>& data);
        void addVertex(V v);
        void addEdge(V v1, V v2);
        //void BFS(V start);
        vector<V> adjacent(V v);
        //longitude, latitude of the vertices
        vector<pair<long double, long double>> vertexLoc;


        vector<pair<long double, long double>> getVertexLoc() { return vertexLoc; }
        int getVertexIdx(V v) const;
        int getEdgeIdx(pair<V, V> e) const;
        const vector<V>& getVertexList() { return vertexList; }
        const vector<pair<V, V>>& getEdgeList() { return edgeList;}
        const vector<vector<long double>> getAdjMatrix() { return adjMatrix; }        

    private:

        //private helper function
        void dataProcessing(vector<vector<string>>& data, vector<int>& vectorList, vector<pair<int,int>>& edgeList, vector<pair<long double, long double>>& vertexLoc);

        long double computeDistance(long double start_long, long double start_lat, long double dest_long, long double dest_lat);
        long double convertRadian(long double d);
        long double costFunction(long double lat1, long double long1, long double lat2, long double long2, int freq, int totalFreq);

        //assign the frequency value to each node
        void getFreq(vector<vector<string>>& data);
        int getTotalFreq();

        //list of vertices
        vector<V> vertexList;
        //list of edges
        vector<pair<V, V>> edgeList;
        //matrix that represents the adjacencies of vertices
        vector<vector<long double>> adjMatrix;
        //map which stores frequencies of each route
        std::map<pair<V, V>, int> freq;
};

#include "Graph.cpp"