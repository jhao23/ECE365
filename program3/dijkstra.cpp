#include "graph.h"
#include "hash.h"

#include <iostream>
#include <chrono>

using namespace std;

int main()
{
    string inputGraph, startingVertex, outputName;
    Graph dGraph;

    cout << "Graph File Name: ";
    cin >> inputGraph;

    hashTable vertexList;

    dGraph.input(inputGraph, vertexList); 
    
    cout << "Starting Vertex Name: ";
    cin >> startingVertex;
    while (!vertexList.contains(startingVertex))
    {
        cout << "Invalid vertex, re-enter another vertex: ";
        cin >> startingVertex;
    }

    const auto start{chrono::steady_clock::now()};
    dGraph.dijkstra(startingVertex, vertexList);
    const auto finish{chrono::steady_clock::now()};

    const chrono::duration<double> elapsed_seconds{finish - start};
    cout << "Time to run Dijkstra's algorithm (in seconds): " << elapsed_seconds.count() << "\n";

    cout << "Output File Name: ";
    cin >> outputName;

    dGraph.output(startingVertex, outputName, vertexList);

    return 0;
}
