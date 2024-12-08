#include "graph.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <limits>

int main(int argc, char* argv[]) {
    std::string filename, ss, of, p2p, op2p;
    bool is_ss = false, is_p2p = false;

    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-d" && i + 1 < argc) {
            filename = std::string(argv[i + 1]);
        } else if (std::string(argv[i]) == "-ss" && i + 1 < argc) {
            ss = std::string(argv[i + 1]);
            is_ss = true;
        } else if (std::string(argv[i]) == "-oss" && i + 1 < argc) {
            of = std::string(argv[i + 1]);
        } else if (std::string(argv[i]) == "-p2p" && i + 1 < argc) {
            p2p = std::string(argv[i + 1]);
            is_p2p = true;
        } else if (std::string(argv[i]) == "-op2p" && i + 1 < argc) {
            op2p = std::string(argv[i + 1]);
        }
    }

    std::ifstream file(filename);
    std::string line;
    Graph graph(0);
    long long vert, edges, from, target, cost, max_cost = -1, min_cost = std::numeric_limits<long long>::max();

    while (getline(file, line)) {
        if (line[0] == 'c') {
            continue;
        }
        if (line[0] == 'p') {
            sscanf(line.c_str(), "p sp %lld %lld", &vert, &edges);
            graph = Graph(vert);
        }
        if (line[0] == 'a') {
            sscanf(line.c_str(), "a %lld %lld %lld", &from, &target, &cost);
            if (cost > max_cost) {
                max_cost = cost;
            }
            if (cost < min_cost) {
                min_cost = cost;
            }
            graph.add_edge(from - 1, target - 1, cost);
        }
    }
    file.close();

    if (is_ss) {
        std::ifstream sources_file(ss);
        std::vector<long long> sources;
        while (getline(sources_file, line)) {
            if (line[0] == 'c' || line[0] == 'p') {
                continue;
            }
            if (line[0] == 's') {
                long long source;
                sscanf(line.c_str(), "s %lld", &source);
                sources.push_back(source);
            }
        }
        sources_file.close();

        double total_time = 0;
        for (long long source : sources) {
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<long long> distances = graph.radix_heap(source - 1);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            total_time += duration.count();
        }
        double avg_time = total_time / sources.size();

        std::ofstream output_file(of);
        output_file << "p aux sp ss " << sources.size() << "\n";
        output_file << "f " << filename << " " << ss << "\n";
        output_file << "g " << vert << " " << edges << " " << min_cost << " " << max_cost << "\n";
        output_file << "t " << std::fixed << avg_time << "\n";
        output_file.close();
    }

    if (is_p2p) {
        std::ifstream pairs_file(p2p);
        std::vector<std::pair<long long, long long>> pairs;
        while (getline(pairs_file, line)) {
            if (line[0] == 'c' || line[0] == 'p') {
                continue;
            }
            if (line[0] == 'q') {
                long long source, target;
                sscanf(line.c_str(), "q %lld %lld", &source, &target);
                pairs.emplace_back(source - 1, target - 1);
            }
        }
        pairs_file.close();

        std::ofstream output_file(op2p);
        output_file << "f " << filename << " " << p2p << "\n";
        output_file << "g " << vert << " " << edges << " " << min_cost << " " << max_cost << "\n";

        for (const auto& pair : pairs) {
            //auto start = std::chrono::high_resolution_clock::now();
            std::vector<long long> distances = graph.radix_heap(pair.first);
            //auto stop = std::chrono::high_resolution_clock::now();
            if (distances[pair.second] == std::numeric_limits<long long>::max()) {
                output_file << "d " << pair.first + 1 << " " << pair.second + 1 << " INF\n";
            } else {
                output_file << "d " << pair.first + 1 << " " << pair.second + 1 << " " << distances[pair.second] << "\n";
            }
        }
        output_file.close();
    }

    return 0;
}
