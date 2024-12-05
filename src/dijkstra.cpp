#include "dijkstra.h"
#include <iostream>
#include <fstream>

int main() {
    std::ifstream input_file("graf_10.gr");
    int num_vertices, num_edges;
    input_file >> num_vertices >> num_edges;
    Graph graph(num_vertices);
    for (int i = 0; i < num_edges; ++i) {
        int from, to, cost;
        input_file >> from >> to >> cost;
        graph.add_edge(from - 1, to - 1, cost);
    }

    int source = 0;
    std::vector<int> distances = graph.dijkstra(source);

    for (int i = 0; i < num_vertices; ++i) {
        std::cout << "Odleglosc od wierzcholka " << source+1 << " do wierzcholka " << i + 1 << ": " << distances[i] << std::endl;
    }

    return 0;
}