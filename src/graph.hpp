#include <vector>
#include <queue>
#include <limits>
#include <list>
#include <array>
#include <cassert>
#include <iostream>
#include "radixHEAP.hpp"

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
    std::vector<std::vector<Edge>> adjacency_list_;
};

Graph::Graph(long long num_vertices) : num_vertices_(num_vertices) {
    adjacency_list_.resize(num_vertices_);
}

void Graph::add_edge(long long from, long long to, long long cost) {
    adjacency_list_[from].push_back({to, cost});
}

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

std::vector<long long> Graph::dial(long long source, long long max_cost) {
    std::vector<long long> distances(num_vertices_, std::numeric_limits<long long>::max());
    distances[source] = 0;

    std::vector<std::list<long long>> buckets(max_cost+1);
    buckets[0].push_back(source);
    long long currentBucket = 0;

    std::vector<bool> visited(num_vertices_, false);
    while (1) {
        while (buckets[currentBucket].empty()){
            currentBucket = (currentBucket+1) % (max_cost+1);
        }

        for (long long u: buckets[currentBucket]){
            visited[u]=true;
            
            for (const Edge& edge : adjacency_list_[u]) {
                long long v = edge.to;
                long long weight = edge.cost;

                if (distances[u] + weight < distances[v]) {
                    buckets[distances[v] % (max_cost+1)].remove(v);
                    distances[v] = distances[u] + weight;
                    buckets[distances[v] % (max_cost+1)].push_back(v);
                }
            }
        }
        buckets[currentBucket].clear();
        currentBucket = (currentBucket+1) % (max_cost+1);
        
        bool allVisited=true;
        for (long long i=0; i < num_vertices_; i++){
            if(!visited[i]){
                allVisited=false;
                break;
            }
        }

        if(allVisited){
            break;
        }
    }
    return distances;
}

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