#include "graph.h"
#include <iostream>
#include <fstream>
#include <chrono>

int main() {
    std::ifstream input_file("graf_10.gr");
    long long num_vertices, num_edges;
    input_file >> num_vertices >> num_edges;
    Graph graph(num_vertices);
    long long max_cost = 0;
    for (int i = 0; i < num_edges; i++) {
        long long from, to, cost;
        input_file >> from >> to >> cost;
        if(cost > max_cost) {
            max_cost = cost;
        }
        graph.add_edge(from - 1, to - 1, cost);
    }

    long long source = 1;


    auto start = std::chrono::high_resolution_clock::now();
    std::vector<long long> distances = graph.dijkstra(source - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Dijkstra - podstawowy:" << std::endl;
    for (int i = 0; i < num_vertices; i++) {
        std::cout << "Odleglosc od wierzcholka " << source << " do wierzcholka " << i + 1 << ": " << distances[i] << std::endl;
    }
    std::cout << "Czas wykonania: " << duration.count() << " mikrosekund" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::vector<long long> distances2 = graph.dial(source - 1, max_cost);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "\nDial:" << std::endl;
    for (int i = 0; i < num_vertices; i++) {
        std::cout << "Odleglosc od wierzcholka " << source << " do wierzcholka " << i + 1 << ": " << distances2[i] << std::endl;
    }
    std::cout << "Czas wykonania: " << duration.count() << " mikrosekund" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::vector<long long> distances3 = graph.radix_heap(source - 1);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "\nRadixHeap:" << std::endl;
    for (int i = 0; i < num_vertices; i++) {
        std::cout << "Odleglosc od wierzcholka " << source << " do wierzcholka " << i + 1 << ": " << distances3[i] << std::endl;
    }
    std::cout << "Czas wykonania: " << duration.count() << " mikrosekund" << std::endl;

    return 0;
}