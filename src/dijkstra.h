#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>

struct Edge {
    int from;
    int to;
    int weight;
};

std::vector<int> dijkstra(const std::vector<std::vector<Edge>>& graph, int source);

#endif
