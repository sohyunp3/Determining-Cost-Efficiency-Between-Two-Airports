using namespace std;

template <typename V>
Graph<V>::Graph(vector<vector<string>>& data) {

    dataProcessing(data, vertexList, edgeList, vertexLoc);

    //adjacency matrix initialization
    for (int i = 0; i < vertexList.size() ; i++) {
        adjMatrix.push_back(vector<long double>());
        for (int j = 0; j < vertexList.size(); j++) {
            adjMatrix[i].push_back(0.0);
        }
    }

    for (pair<V, V> edge : edgeList) {
        freq.insert(pair<pair<V, V>, int>(edge, 0));
    }

    getFreq(data);
    int totalFreq = getTotalFreq();

    int srcIdx, dstIdx;
    long double cost;
    for (pair<V, V> edge : edgeList) {
        srcIdx = getVertexIdx(edge.first);
        dstIdx = getVertexIdx(edge.second);
        cost = costFunction(vertexLoc[srcIdx].first, vertexLoc[srcIdx].second, vertexLoc[dstIdx].first, vertexLoc[dstIdx].second, freq[edge], totalFreq);
        adjMatrix[srcIdx][dstIdx] = cost;
        adjMatrix[dstIdx][srcIdx] = cost;
    }
}

template <typename V>
void Graph<V>::dataProcessing(vector<vector<string>>& data, vector<int>& vertexList, vector<pair<int,int>>& edgeList, vector<pair<long double, long double>>& vertexLoc) {

    //data processing
    for (int i = 1; i < data.size(); i++)
    {
        int src = std::stoi(data[i][1]);
        int dst = std::stoi(data[i][4]);
        if (find(vertexList.begin(), vertexList.end(), src) == vertexList.end())
        {
            vertexList.push_back(src);
            vertexLoc.push_back(pair<double, double>(std::stold(data[i][2]), std::stold(data[i][3])));
        }

        if (find(vertexList.begin(), vertexList.end(), dst) == vertexList.end())
        {
            vertexList.push_back(dst);
            vertexLoc.push_back(pair<double, double>(std::stold(data[i][5]), std::stold(data[i][6])));
        }
        
        pair<V, V> edge;
        if (src < dst)
        {
            edge.first = src;
            edge.second = dst;
        }
        else
        {
            edge.first = dst;
            edge.second = src;
        }

        if (find(edgeList.begin(), edgeList.end(), edge) == edgeList.end())
        {
            edgeList.push_back(edge);
        }
    }
}

template <typename V>
void Graph<V>::addVertex(V v) {
    vertexList.push_back(v);
}

template <typename V>
void Graph<V>::addEdge(V v1, V v2) {
    //set the adjacency of vertex1 and vertex2 true
    adjMatrix[getVertexIdx(v1)][getVertexIdx(v2)] = 1.0;
    adjMatrix[getVertexIdx(v2)][getVertexIdx(v1)] = 1.0;
}

template <typename V>
int Graph<V>::getVertexIdx(V v) const {
    auto iter = find(vertexList.begin(), vertexList.end(), v);
    if (iter == vertexList.end())
    {
        //if the element is not in the list
        return -1;
    } else 
    {
        //find the corresponding index of the given vertex
        int idx = iter - vertexList.begin();
        return idx;
    }
}

template <typename V>
int Graph<V>::getEdgeIdx(pair<V, V> e) const {
    pair<V, V> edge;
    if (e.first < e.second)
    {
        edge.first = e.first;
        edge.second = e.second;
    }
    else
    {
        edge.second = e.first;
        edge.first = e.second;
    }
    auto iter = find(edgeList.begin(), edgeList.end(), edge);
    if (iter == edgeList.end())
    {
        //if the element is not in the list
        return -1;
    } else 
    {
        //find the corresponding index of the given edge
        int idx = iter - edgeList.begin();
        return idx;
    }
}

template <typename V>
long double Graph<V>::computeDistance(long double lat1, long double long1, long double lat2, long double long2)
{
    long double dx = convertRadian(lat2 - lat1);
    long double dy = convertRadian(long2 - long1);

    long double x1 = convertRadian(lat1);
    long double x2 = convertRadian(lat2);

    long double a = pow(sin(dx / 2), 2) + pow(sin(dy / 2), 2) * cos(x1) * cos(x2);
    
    long double rad = 6371.0;
    long double c = 2 * asin(sqrt(a)); 
    return rad * c;
}

template <typename V>
long double Graph<V>::convertRadian(long double d){
    return d * M_PI / 180.0;
}

template <typename V>
void Graph<V>::getFreq(vector<vector<string>>& data) {

    V first;
    V second;
    pair<V, V> edge;
    for (int i = 0; i < data.size(); i++) {
        if (first < second) 
        {
            edge.first = first;
            edge.second = second;
        } 
        else
        {
            edge.first = second;
            edge.second = first;
        }

        freq[edge] += 1;
    }
}

template <typename V>
int Graph<V>::getTotalFreq() {
    int totalFreq = 0;

    for (auto iter = freq.begin(); iter != freq.end(); iter++) {
        totalFreq += iter->second;
    }

    return totalFreq;
}

template <typename V>
long double Graph<V>::costFunction(long double lat1, long double long1, long double lat2, long double long2, int freq, int totalFreq){
    long double f = (long double)freq;
    long double d = computeDistance(long1, lat1, long2, lat2);

    //total frequecy to divide individual frequency of the path;
    //may need to adjust factor depending on size
    long double kkanbu_fac = 1 + (f / totalFreq);
    long double cost = d / kkanbu_fac;
    return cost;
}

template <typename V>
vector<V> Graph<V>::adjacent(V v) {
    vector<V> adjVertexList;

    int idx = getVertexIdx(v);
    for (int i = 0; i < vertexList.size(); i++) {
        if (bool(adjMatrix[idx][i]))
        {
            adjVertexList.push_back(vertexList[i]);
        }
    }

    return adjVertexList;
}
/*
template <typename V>
long double Graph<V>::minDistance(long double dist[], bool sptSet[])
{

	// Initialize min value
	long double min = INF, min_index;

	for (int v = 0; v < V_num; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

template <typename V>
long double Graph<V>::dijkstra(vector<vector<long double>> graph, int src, int dst)
{
	bool sptSet[V_num]; // sptSet[i] will be true if vertex i is included in shortest
	// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	for (long double i = 0; i < V_num; i++)
		dist[i] = INF, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (long double count = 0; count < V_num - 1; count++) {
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in the first iteration.
		long double u = minDistance(dist, sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (long double v = 0; v < V_num; v++)

			// Update dist[v] only if is not in sptSet, there is an edge from
			// u to v, and total weight of path from src to v through u is
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INF
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

    return dist[dst];
}

template <typename V>
void Graph<V>::getDijkstra() {
    int srcIdx, dstIdx;
    long double dijkstra_val;
    for (pair<V, V> edge : edgeList) {
        srcIdx = getVertexIdx(edge.first);
        dstIdx = getVertexIdx(edge.second);
        dijkstra_val = dikstra(adjMatrix, srcIdx, dstIdx);
        dijMatrix[srcIdx][dstIdx] = dijkstra_val;
        dijMatrix[dstIdx][srcIdx] = dijkstra_val;
    }
}

template <typename V>
void Graph<V>::printDijkstra() {
    ofstream outputfile;
    for (long double i = 0; i < V_num; i++) {
        for (long double j = 0; j < V_num; j++) {
            if (adjMatrix[i][j] != 0) {
                if (adjMatrix[i][j] > dijMatrix[i][j]) {
                    outputfile.open("cheaperflights.txt");
                    outputfile << "From Aiport ID: " << i << " to Airport ID: " << j << ", flights by layover is cheaper by " << adjMatrix[i][j] - dijMatrix[i][j] << endl;
                }
            }
        }
    }
    outputfile.close();
}*/