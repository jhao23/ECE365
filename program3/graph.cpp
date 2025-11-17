#include "graph.h"
#include <fstream>
#include <sstream>

Graph::Vertex* Graph::addVertex(string &name)
{
    Graph::Vertex* v = new Graph::Vertex(name);
    vertices.push_back(v);
    return v;
}

void Graph::addEdge(Vertex* v1, Vertex* v2, int cost)
{
    Graph::Edge* e = new Graph::Edge(cost, v2);
    v1->neighbors.push_back(e);
}

void Graph::input(string &inputGraph, hashTable &vertexList)
{
    ifstream inputFile;
    inputFile.open(inputGraph);

    string line;

    string word1, word2;
    int weight;

    while (getline(inputFile, line))
    {
        istringstream ss(line);
        ss >> word1 >> word2 >> weight;
        
        if (!vertexList.contains(word1))
        {
            void* vpoint = addVertex(word1);
            vertexList.insert(word1, vpoint);
        }
        if (!vertexList.contains(word2))
        {
            void* vpoint = addVertex(word2);
            vertexList.insert(word2, vpoint);
        }

        Graph::Vertex* vertex1 = static_cast<Graph::Vertex*>(vertexList.getPointer(word1));
        Graph::Vertex* vertex2 = static_cast<Graph::Vertex*>(vertexList.getPointer(word2));
        addEdge(vertex1, vertex2, weight);
    }

    inputFile.close();
}

void Graph::dijkstra(string &starting, hashTable &vertexList)
{   
    Vertex* start = static_cast<Vertex*>(vertexList.getPointer(starting));
    start->distance = 0;
    start->previous = start;

    heap remaining(vertices.size());
    for (Vertex* v : vertices)
    {
        remaining.insert(v->id, v->distance, v);
    }

    Vertex* current = nullptr;
    int currentCost;
    string vertexName; // This variable is mostly a placeholder

    while(!remaining.deleteMin(&vertexName, &currentCost, &current))
    {
        current->visited = true;
        for (Edge* e : current->neighbors)
        {
            if (!e->destination->visited && (currentCost != INT_MAX) &&(e->weight + currentCost < e->destination->distance))
            {
                e->destination->distance = e->weight + currentCost;
                remaining.setKey(e->destination->id, e->weight + currentCost);
                e->destination->previous = current;
            }
        }
    }
    return;
}

void Graph::output(string &starting, string &outputName, hashTable &vertexList)
{
    ofstream outputFile;
    outputFile.open(outputName);

    Vertex* start = static_cast<Vertex*>(vertexList.getPointer(starting));

    for (Vertex* v : vertices)
    {
        outputFile << v->id << ": ";

        if (v->previous == nullptr)
        {
            outputFile << "NO PATH\n";
        }
        else
        {
            string path = v->id;
            Vertex* currentVertex = v;

            outputFile << v->distance << " ";
            outputFile << "[";

            while (currentVertex != start)
            {
                currentVertex = currentVertex->previous;
                path = currentVertex->id + ", " + path;
            }

            outputFile << path << "]\n";
        }
    }   
    outputFile.close();

    return;
}
