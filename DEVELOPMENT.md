# Development

### Week 1
We individually committed the contract and decided which dataset and algorithm to use. Then we outlined and submitted the proposal of the project with the leading question, data acquisition and processing, graph algorithms, and timeline included.

### Week 2
We distributed the roles and responsibilities and prioritized the work. We first created Graph.h and Graph.hpp to start writing public and private functions that are needed for implementation of graph and Breadth-First Search. This process also involved writing pseudocode for the structure of graph and BFS. We combined airports.dat and routes.dat into a single csv file to only extract data we need for the graph. We also created Makefile that could run main.cpp.

### Week 3
Implementation of the actual code for structure of graph primarily using adjacency matrix and BFS using queue was completed. We made CSVReader.hpp that read the csv file that we manually modified in the previous week. We also took time to understand the principle behind Dijkstra’s shortest path algorithm and implemented it inside the Graph.hpp file. We imported HSLAPixel and PNG class files to start visually representing the world map with Dijkstra’s algorithm applied.

### Week 4
We fixed minor errors in Makefile. We completed the text output of Dijkstra’s shortest path algorithm followed by the cost factor in every edge of the nodes and map visualization of BFS. Graph and BFS parts were modified to make code more readable and neat. We wrote test suites for testing functions in each .hpp file.
