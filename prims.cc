#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>


// You should NOT assume that edge costs are positive, nor should you assume 
//   that they are distinct.

// Your task is to run Prim's minimum spanning tree algorithm on this graph.
//   You should report the overall cost of a minimum spanning tree --- an 
//   integer, which may or may not be negative --- in the box below. 

// IMPLEMENTATION NOTES: This graph is small enough that the straightforward 
//   O(mn) time implementation of Prim's algorithm should work fine. OPTIONAL: 
//   For those of you seeking an additional challenge, try implementing a 
//   heap-based version. The simpler approach, which should already give you a 
//   healthy speed-up, is to maintain relevant edges in a heap (with keys = edge
//   costs). The superior approach stores the unprocessed vertices in the heap,
//   as described in lecture. 
// Note this requires a heap that supports deletions, and you'll probably need 
//   to maintain some kind of mapping between vertices and their positions in 
//   the heap.
int prims_MST(std::unordered_map<size_t, std::vector<Edge>>& G);


// Represents an edge of the graph.
struct Edge {
    size_t u;
    size_t v;
    int weight;

    // Constructor.
    Edge(size_t v_1, size_t v_2, int cost) : u(v_1), v(v_2), weight(cost) {}

    // Comparison operator for the priority queue.
    bool operator<(const struct Edge& other) const {
        return weight > other.weight;
    }
};


int main() {
    std::cout << "Starting Prims's MST algorithm..." << std::endl;

    // Open input file.
    std::ifstream input_file("./input/edges.txt");
    if (!input_file.is_open()) {
        std::cout << "ERROR: error reading input file." << std::endl;
        return EXIT_FAILURE;
    }

    // Number of nodes, V and edges, E.
    size_t V, E;
    input_file >> V >> E;

    // Represent graph by an adjacency-list, G.
    std::unordered_map<size_t, std::vector<Edge>> G;

    // Read from input file, line by line.
    size_t v_1, v_2;
    int cost;
    while (input_file >> v_1 >> v_2 >> cost) {
        // Undirected graph.
        Edge edge_1 = Edge(v_1, v_2, cost);
        Edge edge_2 = Edge(v_2, v_1, cost);

        // Insert into adjacency list.
        G[v_1].push_back(edge_1);
        G[v_2].push_back(edge_2);
    }

    // Sanity check - total items read.
    size_t size = 0;
    for (auto it = G.begin(); it != G.end(); ++it) {
        size += it->second.size();
    }
    std::cout << "Read " << size / 2 << " lines in total." << std::endl;

    // Run algorithm.
    std::cout << "Weighted sum: " << prims_MST(G) << std::endl;

    // Finish and tidy up.
    input_file.close();
    std::cout << "Algorithm terminated successfully." << std::endl;
    return EXIT_SUCCESS;
}


int prims_MST(std::unordered_map<size_t, std::vector<Edge>>& G) {
    std::priority_queue<Edge> pq;    

    return 0;
}
