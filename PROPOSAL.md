# CS 225 Data Structures

## Final Project Proposal (jyjeong2-jdoo2-sc27-sohyunp3)

**Leading Question**: Find the minimum cost path from the given source and destination region. Using the 
destination features, we will calculate the frequency of each airport depending on how many times a 
certain airport has been used as a source or destination. The distance feature calculated from the 
longitude and latitude will be used to estimate the approximate price of a flight. After all the 
prices of the flights have been estimated, the shortest path algorithm will be used using the price 
feature as weights to find the cheapest route from a source to a destination. Graph representation 
will also be implemented using the price feature as the weight to visualize how much a certain flight 
will cost by altering the thickness of an edge depending on the cost. 

**Data Acquisition and Processing**: We are going to utilize route and airport datasets from OpenFlight. 
The OpenFlight dataset can be acquired from ​​https://openflights.org/data.html, and the datasets will 
be stored in .csv format. We will use these datasets to create a pathway graph, and since we are going 
to estimate the edge weight from route and airport dataset, two datasets need to be merged; airport 
information dataset. Only the longitude and latitude from the airport dataset will be integrated on 
route dataset, and we will remove the rest features. Also, ​​we will only utilize source airport and 
destination airport features from the route dataset. There will not be any dataset-related problems 
with the airport dataset since we will only include the features of the longitude and latitude and 
there would be no error with the locations. Since we will only consider the direct route, we will remove 
routes with one or more stops during preprocessing for simplicity. The graph will be created by for loop 
iterations on the dataset. Especially, two airports will be connected if there is a route between them, 
and also we will measure the frequency of airports based on the number of routes between two airports. 
We will calculate the distance between two airports based on the longitude and latitude and the haversine 
formula.

**Graph Algorithms**: Throughout the project, we are planning to implement BFS and Dijkstra’s shortest path 
algorithm as our graph data algorithms. BFS will be implemented recursively by taking individual subroots 
as the input. A subgraph will be created with maximum distance d from the source node as an input. BFS will 
be implemented to figure out all the possible destinations from the source input and the options will be listed 
as possible destinations. The user will choose the proper destination among the options and Dijkstra’s algorithm 
will be implemented to find the shortest path with the minimum cost. Provided that the number of nodes is n, the 
big O of BFS is O(n) since we are merely visiting all the nodes in a dataset. Dijkstra’s shortest path algorithm 
is an algorithm for finding the shortest paths between nodes in a graph, and therefore it yields a shortest path 
to the destination. It will take our graph dataset and a start node as input, and the weight of nodes will be 
computed using several factors; distance, popularity, etc... . Given that N is the number of nodes and E is the 
number of edges, the big O estimation for Dijkstra’s algorithm is O(ElogN). For the complex algorithm, we decided 
to utilize eulerian path algorithm which figure out if we can travel from source node to destination node with visiting each edge exactly once. This algorithm will allow us to find if it is possible to find flight to a certain country without taking redundant flights. For this algorithm, we only need source node, destination node, and the graph representing air routes as an input, however, it is required to implement some helper functions in order to make it easier to implement and make the code more understandable. First, we need a traversal algorithm to figure out if all the nodes are visited starting from the source node. Next, we can implement helper function that return false if any unvisited node is still remaining and if destination node is the one that is unvisited. When this helper function returns false, we can conclude that we need to take some redundant flights in order to get to certain country

**Timeline**: 
identify a list of tasks such as data acquisition, data processing, completion of each individual algorithm, production 
of final deliverables, etc…

*Week 1*
- Combine data set of airports and routes to sort data in one set
- Implement an algorithm to find the distance between airports

*Week 2*
- Using BFS, traverse through the subgraph created based on the input source node with the maximum distance d from the source node 
- List up the possible destinations with the result of BFS traversal

*Week 3*
- Implement an algorithm to calculate the approximate price of each flight utilizing the frequency and distance of airports
- Implement the shortest path algorithm to find the cheapest route from a source to a destination

*Week 4*
- Visualize derived data into a connectivity graph
