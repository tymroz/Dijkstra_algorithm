#include "graph.h"
#include <iostream>
#include <fstream>
#include <chrono>

int main(int argc, char* argv[]) {
    std::string filename, ss, of;
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-d" && i + 1 < argc) {
            filename = std::string(argv[i + 1]);
        } else if (std::string(argv[i]) == "-ss" && i + 1 < argc) {
            ss = std::string(argv[i + 1]);
        } else if (std::string(argv[i]) == "-oss" && i + 1 < argc) {
            of = std::string(argv[i + 1]);
        }
    }

    std::ifstream file(filename);
    std::string line;
    Graph graph(0);
    long long vert, edges, from, target, cost, max_cost=-1, min_cost=std::numeric_limits<long long>::max();
    
    while (getline(file, line)) {
        if (line[0] == 'c') {
            continue;
        }
        if (line[0] == 'p'){
            sscanf(line.c_str(), "p sp %lld %lld", &vert, &edges);
            graph = Graph(vert);
        }
        if (line[0] == 'a') {
            sscanf(line.c_str(), "a %lld %lld %lld", &from, &target, &cost);
            if(cost > max_cost){
                max_cost = cost;
            }
            if(cost < min_cost){
                min_cost = cost;
            }
            graph.add_edge(from-1, target-1, cost);
        }
    }
    file.close();

//    long long source = 1;
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

    long long sources_size = sources.size(); 

    double total_time = 0;
    for (long long source : sources) {
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<long long> distances = graph.dijkstra(source - 1);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        total_time = total_time + duration.count();
//        std::cout << "Dijkstra, zrodlo " << source << ":" << std::endl;
//        for (int i = 0; i < vert; i++) {
//            std::cout << "Odleglosc od wierzcholka " << source << " do wierzcholka " << i + 1 << ": " << distances[i] << std::endl;
//        }
//        std::cout << "Czas wykonania: " << duration.count() << " ms" << std::endl;
    }
    double avg_time = total_time/sources_size;

    std::ofstream output_file(of);
    output_file << "p aux sp ss " << sources_size << "\n";
    output_file << "f " << filename << " " << ss << "\n";
//    output_file << "c siec sklada sie z " << vert << " wierzcholkow, " << edges << " lukow,\n";
//    output_file << "c koszty naleza do przedzialu : []" << min_cost <<"," << max_cost <<"]\n";
    output_file << "g " << vert << " " << edges << " " << min_cost << " " << max_cost << "\n";
    output_file << "t " << std::fixed << avg_time << "\n";

    output_file.close();

    return 0;
}