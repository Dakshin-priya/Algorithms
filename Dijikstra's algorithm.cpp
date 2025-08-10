#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<pair<int, int>>> adj; // Adjacency list: {neighbor, weight}

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // Undirected graph
    }

    void dijkstra(int src) {
        vector<int> dist(V, numeric_limits<int>::max()); // Distance vector initialized to infinity
        vector<bool> visited(V, false); // Visited nodes tracker

        dist[src] = 0; // Distance to the source is 0

        for (int i = 0; i < V; i++) {
            // Find the node with the minimum distance that is not visited
            int minDist = numeric_limits<int>::max();
            int minNode = -1;

            for (int j = 0; j < V; j++) {
                if (!visited[j] && dist[j] < minDist) {
                    minDist = dist[j];
                    minNode = j;
                }
            }

            if (minNode == -1) break; // All reachable nodes are visited
            visited[minNode] = true;

            // Update distances of adjacent nodes
            for (auto &neighbor : adj[minNode]) {
                int nextNode = neighbor.first;
                int edgeWeight = neighbor.second;

                if (!visited[nextNode] && dist[minNode] + edgeWeight < dist[nextNode]) {
                    dist[nextNode] = dist[minNode] + edgeWeight;
                }
            }
        }

        // Print shortest distances
        cout << "Vertex \t Distance from Source " << src << endl;
        for (int i = 0; i < V; i++) {
            cout << i << "\t\t" << dist[i] << endl;
        }
    }
};
int main() {
    Graph g(6); // Graph with 6 vertices (0 to 5)

    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 1, 2);
    g.addEdge(2, 3, 5);
    g.addEdge(3, 4, 3);
    g.addEdge(4, 5, 2);

    cout << "Dijkstra's Shortest Path Algorithm:" << endl;
    g.dijkstra(0); // Find shortest paths from node 0

    return 0;
}
