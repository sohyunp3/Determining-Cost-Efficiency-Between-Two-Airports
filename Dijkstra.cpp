#pragma once
#include "Graph.h"
#include <iostream>
#include <vector>

long double INF = 9999999999999999999.99999999999999999;

int minIdx(vector<long double>& dist, vector<bool>& T) {
    int minIdx;
    long double minimum = INF;
    for (int i = 0; i < dist.size(); i++) {
        if (T[i] == false && minimum > dist[i]) {
            minimum = dist[i];
            minIdx = i;
        }
    }
    return minIdx;
}

template <typename V>
vector<V> getPath(Graph<V> g, vector<V> prev, V start, V dst) {
    vector<V> path;
    int idx = g.getVertexIdx(dst);
    path.push_back(dst);

    while (prev[idx] != start)
    {
        path.push_back(prev[idx]);
        idx = g.getVertexIdx(prev[idx]);
    }

    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

template <typename V>
vector<V> dijkstraSSSP(Graph<V> g, V start, V dst) {
    vector<V> vertexList = g.getVertexList();
    vector<vector<long double>> adjMatrix = g.getAdjMatrix();

    vector<long double> dist;
    vector<V> prev;
    vector<V> Q = vertexList;
    vector<bool> T;

    for (V vertex : vertexList) 
    {
        dist.push_back(INF);
        prev.push_back(V());
        T.push_back(false);
    }

    dist[g.getVertexIdx(start)] = 0.0;

    for (V vertex : vertexList)
    {
        int idx = minIdx(dist, T);
        V u = vertexList[idx];

        T[idx] = true;
        for (V v : g.adjacent(u))
        {
            if (T[v] == false)
            {
                int uidx = g.getVertexIdx(u);
                int vidx = g.getVertexIdx(v);
                if (adjMatrix[uidx][vidx] + dist[uidx] < dist[vidx])
                {
                    dist[vidx] = adjMatrix[uidx][vidx] + dist[uidx];
                    prev[vidx] = u;
                }
            }
        }
    }


    return getPath(g, prev, start, dst);
}