#include <vector>
#include <queue>
#include <limits>

struct Edge {
    int to;
    int cost;
};

class Graph {
public:
    Graph(int num_vertices);
    void add_edge(int from, int to, int cost);
    std::vector<int> dijkstra(int source);
private:
    int num_vertices_;
    std::vector<std::vector<Edge>> adjacency_list_;
    ///mozna uzyc unordered map
};

Graph::Graph(int num_vertices) : num_vertices_(num_vertices) {
    adjacency_list_.resize(num_vertices_);
}

void Graph::add_edge(int from, int to, int cost) {
    adjacency_list_[from].push_back({to, cost});
}

std::vector<int> Graph::dijkstra(int source) {
    std::vector<int> distances(num_vertices_, std::numeric_limits<int>::max());
    distances[source] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const Edge& edge : adjacency_list_[u]) {
            int v = edge.to;
            int weight = edge.cost;

            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                pq.push({distances[v], v});
            }
        }
    }
    return distances;
}