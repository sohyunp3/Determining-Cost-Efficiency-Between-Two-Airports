CS 225 Final Project: OpenFlights: Determining Cost Efficiency

Team Members: jyjeong2-jdoo2-sc27-sohyunp3

Introduction:
    Our final project uses the OpenFlights database containing airports and routes where airports were used as the vertex and flights were used as the edges. We constructed a weighted graph using the apporximated cost of the flight. BFS was used to find the path with the least layovers, and Dijkstra's algorithm was used to find the flight with the cheapest cost. 

File Description
    - Graph: contains the code to construct a weighted graph using the airports as the vertexes. There are functions to process the data, create vertexes and edges. We implemented a function to calculate the frequency of each flight and a function to calculate the approximated cost based on the distance and frequency of the flight. 
    - BFS: Using the graph created, implements the BFS traversal based on the algorithm given in lecture
    - Dijkstra: Using the weighted graph, calculates the route with the lowest cost from a source airport to the destination airport. 
    - Visualization: Code to take the edges and draw them out on a PNG world map (failed to implement completely).
    - main: File that runs all the necessary tests and algorithms


How to run the Program
    - The program can be run by using the following commands

        make
        ./main

    - There are more instructions about the functions implemented in the presentation video

Presentation Video 
    - 

Signatures: 
    - Jae Yoon Jeong, Seonggeun Cho, Sohyun Park, Jae Doo