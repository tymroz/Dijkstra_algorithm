#include "dijkstra.h"
#include <queue>
#include <limits>
#include <algorithm>

std::vector<int> dijkstra(const std::vector<std::vector<Edge>>& graph, int source) {
    int n = graph.size();
    std::vector<int> distances(n, INT_MAX);
    distances[source] = 0;
    std::vector<int> predecessors(n, -1);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, source));
    while (!pq.empty()) {
        int u = pq.top().second;
        int distance_u = pq.top().first;
        pq.pop();
        if (distance_u > distances[u]) {
            continue;
        }
        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int distance_v = distance_u + edge.weight;
            if (distance_v < distances[v]) {
                distances[v] = distance_v;
                predecessors[v] = u;
                pq.push(std::make_pair(distance_v, v));
            }
        }
    }
    return distances;
}
