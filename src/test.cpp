#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <string>
#include <sstream>
#include <chrono>
#include <algorithm>

struct Edge {
    int to;
    int weight;
};

std::vector<std::vector<Edge>> loadGraph(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<std::vector<Edge>> graph;
    
    int n, m;
    while (std::getline(file, line)) {
        if (line[0] == 'p') {
            std::istringstream ss(line.substr(1));
            std::string tmp;
            ss >> tmp >> tmp >> n >> m;
            graph.resize(n);
        } else if (line[0] == 'a') {
            int u, v, w;
            std::istringstream ss(line.substr(1));
            ss >> u >> v >> w;
            graph[u - 1].push_back({v - 1, w});
        }
    }
    return graph;
}

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
        
        if (distance_u > distances[u]) continue;

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

void processSources(const std::vector<std::vector<Edge>>& graph, const std::string& sourcesFile, const std::string& resultFile) {
    std::ifstream srcFile(sourcesFile);
    std::ofstream resFile(resultFile);
    
    std::string line;
    auto start = std::chrono::high_resolution_clock::now();
    
    while (std::getline(srcFile, line)) {
        if (line[0] == 's') {
            int source;
            std::istringstream ss(line.substr(1));
            ss >> source;
            source--;
            std::vector<int> distances = dijkstra(graph, source);
            
            // Write result to file
            resFile << "Dijkstra for source " << source + 1 << std::endl;
            for (int i = 0; i < distances.size(); i++) {
                resFile << "To vertex " << i + 1 << ": " << distances[i] << std::endl;
            }
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    resFile << "Time to compute shortest paths: " << diff.count() << " seconds" << std::endl;
}

void processPointToPoint(const std::vector<std::vector<Edge>>& graph, const std::string& pairsFile, const std::string& resultFile) {
    std::ifstream pairFile(pairsFile);
    std::ofstream resFile(resultFile);
    
    std::string line;
    while (std::getline(pairFile, line)) {
        if (line[0] == 'q') {
            int source, target;
            std::istringstream ss(line.substr(1));
            ss >> source >> target;
            source--; target--;
            
            std::vector<int> distances = dijkstra(graph, source);
            
            // Write result to file
            resFile << "Shortest path from " << source + 1 << " to " << target + 1 << ": " << distances[target] << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cerr << "Usage: dijkstra -d <graph_file> -ss <sources_file> -oss <output_file>" << std::endl;
        return 1;
    }

    std::string graphFile;
    std::string sourcesFile;
    std::string resultFile;

    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-d") {
            graphFile = argv[++i];
        } else if (std::string(argv[i]) == "-ss") {
            sourcesFile = argv[++i];
        } else if (std::string(argv[i]) == "-oss") {
            resultFile = argv[++i];
        }
    }

    // Load graph
    std::vector<std::vector<Edge>> graph = loadGraph(graphFile);

    // Process sources (Dijkstra for all sources)
    processSources(graph, sourcesFile, resultFile);
    
    return 0;
}
