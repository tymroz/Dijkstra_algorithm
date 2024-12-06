#include <vector>
#include <queue>
#include <limits>
#include <list>
#include <array>
#include <cassert>

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
    ///mozna uzyc unordered map
};

Graph::Graph(long long num_vertices) : num_vertices_(num_vertices) {
    adjacency_list_.resize(num_vertices_);
}

void Graph::add_edge(long long from, long long to, long long cost) {
    adjacency_list_[from].push_back({to, cost});
}

class RadixHeap {
public:
    RadixHeap() : size_(0), last_(0), buckets_(num_buckets), buckets_min_(num_buckets, std::numeric_limits<long long>::max()) {}

    void insert(long long node, long long distance) {
        if (last_ <= distance) {
            size_++;
            long long bucket_index = find_bucket(distance, last_);
            buckets_[bucket_index].emplace_back(distance, node);
            buckets_min_[bucket_index] = std::min(buckets_min_[bucket_index], distance);
        }
    }

    long long findMin() {
        pull();
        return buckets_[0].back().second;
    }

    void deleteMin() {
        pull();
        buckets_[0].pop_back();
        size_--;
    }

    bool empty() const {
        return size_ == 0;
    }

private:
    long long size_;
    long long last_;
    long long num_buckets = std::numeric_limits<long long>::digits + 1;
    std::vector<std::vector<std::pair<long long, long long>>> buckets_;
    std::vector<long long> buckets_min_;

    long long find_bucket(long long x, long long last) const {
        if (x == last) {
            return 0;
        } else {
            return 64 - __builtin_clzll(x ^ last);
        }
    }

    void pull() {
        if (size_ > 0) {
            if (!buckets_[0].empty()) {
                return;
            } else {
                long long i;
                for (i = 1; buckets_[i].empty(); ++i);

                last_ = buckets_min_[i];

                for (const auto& [distance, node] : buckets_[i]) {
                    long long new_bucket_index = find_bucket(distance, last_);
                    buckets_[new_bucket_index].emplace_back(distance, node);
                    buckets_min_[new_bucket_index] = std::min(buckets_min_[new_bucket_index], distance);
                }
                buckets_[i].clear();
                buckets_min_[i] = std::numeric_limits<long long>::max();
            }
        }
    }
};


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
                    distances[v] = distances[u] + weight;
                    buckets[std::min(max_cost, distances[v])].push_back(v);
                }
            }
        }
    }
    return distances;
}

// RadixHeap O(m + ln(nC)) -- m-number of edges, #n-number of verticles, C-max_cost
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