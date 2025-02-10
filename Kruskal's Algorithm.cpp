#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int V, E;
    vector<Edge> edges;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent, rank;
};

// Find function for union-find (path compression)
int find(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent); // Path compression
    return subsets[i].parent;
}

// Union function for union-find (union by rank)
void Union(vector<Subset>& subsets, int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Kruskal's Algorithm
void kruskalMST(Graph& graph) {
    vector<Edge> result; // Stores the final MST
    int V = graph.V;
    vector<Subset> subsets(V);

    // Step 1: Sort edges in ascending order of weight
    sort(graph.edges.begin(), graph.edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    // Step 2: Initialize subsets for union-find
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int e = 0, i = 0; // e: Count of edges in MST, i: Index in sorted edges
    while (e < V - 1 && i < graph.E) {
        Edge nextEdge = graph.edges[i++];
        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y) { // If adding this edge doesn’t form a cycle
            result.push_back(nextEdge);
            Union(subsets, x, y);
            e++;
        }
    }

    // Print the MST
    cout << "Edge \tWeight\n";
    for (auto edge : result)
        cout << edge.src << " - " << edge.dest << "\t" << edge.weight << "\n";
}

// Driver code
int main() {
    Graph graph;
    graph.V = 4;
    graph.E = 5;
    
    // Add edges (src, dest, weight)
    graph.edges.push_back({0, 1, 10});
    graph.edges.push_back({0, 2, 6});
    graph.edges.push_back({0, 3, 5});
    graph.edges.push_back({1, 3, 15});
    graph.edges.push_back({2, 3, 4});

    kruskalMST(graph);

    return 0;
}
