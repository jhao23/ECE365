#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "hash.h"
#include "heap.h"

#include <vector>
#include <string>
#include <climits>

using namespace std;

class Graph
{
    private:
        class Edge;

        class Vertex
        {
            public:
                string id;
                vector<Graph::Edge*> neighbors;

                bool visited;
                int distance;
                Vertex* previous;

                Vertex(string &name)
                {
                    id = name;
                    visited = false;
                    distance = INT_MAX;
                    previous = nullptr;
                }
        };

        class Edge
        {
            public:
                int weight;
                Vertex *destination;

                Edge(int cost, Vertex* dest)
                {
                    weight = cost;
                    destination = dest;
                }
        };

    public:
        vector<Vertex*> vertices;
        Vertex* addVertex(string &name);
        void addEdge(Vertex* v1, Vertex* v2, int cost);
        void input(string &inputGraph, hashTable &vertexList);
        void dijkstra(string &starting, hashTable &vertexList);
        void output(string &starting, string &outputName, hashTable &vertexList);
};

#endif
