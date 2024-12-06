#include <vector>
#include <queue>
#include <limits>
#include <list>
#include <array>
#include <cassert>
#include <iostream>
#include"radixHEAP.h"

struct Edge {
    long long to;
    long long cost;
};

class Graph {
public:
    Graph(long long num_vertices);
    void add_edge(long long from, long long to, long long cost);
    std::vector<long long> dijkstra(long long source);
    std::vector<long long> dial(long long source, long long max_cost);
    std::vector<long long> radix_heap(long long source);
private:
    long long num_vertices_;
    std::vector<std::vector<Edge>> adjacency_list_; ///mozna uzyc unordered map
};

Graph::Graph(long long num_vertices) : num_vertices_(num_vertices) {
    adjacency_list_.resize(num_vertices_);
}

void Graph::add_edge(long long from, long long to, long long cost) {
    adjacency_list_[from].push_back({to, cost});
}

// Dijkstra O(n^2)
std::vector<long long> Graph::dijkstra(long long source) {
    std::vector<long long> distances(num_vertices_, std::numeric_limits<long long>::max());
    distances[source] = 0;

    std::priority_queue<std::pair<long long, long long>, std::vector<std::pair<long long, long long>>, std::greater<std::pair<long long, long long>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        long long u = pq.top().second;
        pq.pop();

        for (const Edge& edge : adjacency_list_[u]) {
            long long v = edge.to;
            long long weight = edge.cost;

            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                pq.push({distances[v], v});
            }
        }
    }
    return distances;
}

// Dial O(m + nC) -- m-number of edges, #n-number of verticles, C-max_cost
std::vector<long long> Graph::dial(long long source, long long max_cost) {
    std::vector<long long> distances(num_vertices_, std::numeric_limits<long long>::max());
    distances[source] = 0;

    std::vector<std::list<long long>> buckets(max_cost+1);
    buckets[0].push_back(source);

    for(long long i=0; i<=max_cost; i++){
        while(!buckets[i].empty()) {
            long long u = buckets[i].front();
            buckets[i].pop_front();

            for (const Edge& edge : adjacency_list_[u]) {
                long long v = edge.to;
                long long weight = edge.cost;

                if (distances[u] + weight < distances[v]) {
                    if(distances[v] < std::numeric_limits<long long>::max()){
                        buckets[distances[v] % (max_cost+1)].remove(v);
                    }
                    distances[v] = distances[u] + weight;
                    buckets[distances[v] % (max_cost+1)].push_back(v);
                }
            }
        }
    }
    return distances;
}

// RadixHeap O(m + nln(nC)) -- m-number of edges, #n-number of verticles, C-max_cost
std::vector<long long> Graph::radix_heap(long long source) {
    std::vector<long long> distances(num_vertices_, std::numeric_limits<long long>::max());
    RadixHeap heap;
    
    heap.insert(source, 0);
    distances[source] = 0;

    while (!heap.empty()) {
        long long u = heap.findMin();
        heap.deleteMin();

        for (const Edge& edge : adjacency_list_[u]) {
            long long v = edge.to;
            long long weight = edge.cost;

            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                heap.insert(v, distances[u] + weight); 
            }
        }
    }
    return distances;
}