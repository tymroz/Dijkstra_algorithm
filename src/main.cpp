#include <iostream>
#include <vector>
#include <algorithm>
#include "dijkstra.h"

int main() {
    std::vector<std::vector<Edge>> graph = {
        {{0, 1, 4}, {0, 7, 8}},
        {{1, 0, 4}, {1, 2, 8}, {1, 7, 11}},
        {{2, 1, 8}, {2, 3, 7}, {2, 5, 4}, {2, 8, 2}},
        {{3, 2, 7}, {3, 4, 9}, {3, 5, 14}},
        {{4, 3, 9}, {4, 5, 10}},
        {{5, 2, 4}, {5, 3, 14}, {5, 4, 10}, {5, 6, 6}},
        {{6, 5, 6}, {6, 7, 1}, {6, 8, 7}},
        {{7, 0, 8}, {7, 1, 11}, {7, 6, 1}, {7, 8, 7}},
        {{8, 2, 2}, {8, 6, 7}, {8, 7, 7}}
    };
    int source = 0;
    std::vector<int> distances = dijkstra(graph, source);
    
    std::cout << "Odległości od wierzchołka " << source << ":" << std::endl;
    for (int i = 0; i < distances.size(); i++) {
        std::cout << "Do wierzchołka " << i << ": " << distances[i] << std::endl;
    }
    
    int target = 5;
    std::vector<int> path;
    int current = target;
    while (current != -1) {
        path.push_back(current);
        current = predecessors[current];
    }
    std::reverse(path.begin(), path.end());
    
    std::cout << "Najkrótsza ścieżka od " << source << " do " << target << ":" << std::endl;
    for (int v : path) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
