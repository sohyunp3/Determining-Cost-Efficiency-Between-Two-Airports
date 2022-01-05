#pragma once
#include "Graph.h"
#include <queue>
#include <iostream>
#include <fstream>

using std::queue;

enum VERTEX_STATE{ V_UNEXPLORED, VISITED };
enum EDGE_STATE{ E_UNEXPLORED, DISCOVERY, CROSS };

template <typename V>
void printBFS(const vector<pair<V, V>>& edgeList, const vector<EDGE_STATE>& edge_state) {
    ofstream outputfile;
    outputfile.open("BFS.txt");

    for (int i = 0; i < edgeList.size(); i++) {
        outputfile << "(" << edgeList[i].first << ", " << edgeList[i].second << "): ";
        if (edge_state[i] == EDGE_STATE::CROSS)
            outputfile << "CROSS";
        else if (edge_state[i] == EDGE_STATE::DISCOVERY)
            outputfile << "DISCOVERY";
        else
            outputfile << "UNEXPLORED";
        outputfile << std::endl;
    }
    outputfile.close();
}
template <typename V>
void BFS(Graph<V> g, V vertex, vector<VERTEX_STATE> &vertex_state, vector<EDGE_STATE> &edge_state)
{
    queue<V> queue;
    vertex_state[g.getVertexIdx(vertex)] = VISITED;
    queue.push(vertex);

    V v;
    while (!queue.empty()) 
    {
        v = queue.front();
        queue.pop();
        for (V w : g.adjacent(v)) {
            pair<V ,V> edge;
            if (v < w)
            {
                edge.first = v;
                edge.second = w;
            }
            else
            {
                edge.first = w;
                edge.second = v;
            }

            int vIdx = g.getVertexIdx(w);
            int eIdx = g.getEdgeIdx(edge);

            if (vertex_state[vIdx] == VERTEX_STATE::V_UNEXPLORED)
            {
                edge_state[eIdx] = EDGE_STATE::DISCOVERY;
                vertex_state[vIdx] = VERTEX_STATE::VISITED;
                queue.push(w);
            } 
            else if (edge_state[eIdx] == EDGE_STATE::E_UNEXPLORED)
            {
                edge_state[eIdx] = EDGE_STATE::CROSS;
            }
        }
    }
}

template <typename V>
void BFS(Graph<V> g, V start)
{
    const vector<V>& vertexList = g.getVertexList();
    const vector<pair<V, V>>& edgeList = g.getEdgeList();

    vector<VERTEX_STATE> vertex_state;
    vector<EDGE_STATE> edge_state;

    // set all the vectors and edges as unvisited
    for (int i = 0;  i < vertexList.size(); i++) 
    {
        vertex_state.push_back(VERTEX_STATE::V_UNEXPLORED);
    }

    for (int i = 0; i < edgeList.size(); i++) 
    {
        edge_state.push_back(EDGE_STATE::E_UNEXPLORED);
    }

    BFS(g, start, vertex_state, edge_state);

    for (V v : vertexList)
    {
        if (vertex_state[g.getVertexIdx(v)] == VERTEX_STATE::V_UNEXPLORED)
        {
            BFS(g, v, vertex_state, edge_state);
        }
    }
    
    printBFS(edgeList, edge_state);
}