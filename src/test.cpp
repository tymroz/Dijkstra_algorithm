#include "dijkstra.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <limits>

using namespace std;

// Funkcja wczytująca graf z pliku zgodnie z formatem aod_lab3
Graph load_graph(const string& filename) {
    ifstream file(filename);
    string line;
    int num_vertices, num_edges;

    // Pomijanie komentarzy i wczytywanie liczby wierzchołków i krawędzi
    while (getline(file, line)) {
        if (line == 'c') { 
            continue;
        } else if (line == 'p') { 
            stringstream ss(line);
            string p, sp, type;
            ss >> p >> sp >> type >> num_vertices >> num_edges;
            break;
        }
    }

    Graph graph(num_vertices);

    // Wczytywanie krawędzi
    while (getline(file, line)) {
        if (line == 'a') { 
            stringstream ss(line);
            string a, sp;
            int from, to, cost;
            ss >> a >> sp >> from >> to >> cost;
            graph.add_edge(from - 1, to - 1, cost); 
        }
    }

    return graph;
}

// Funkcja wczytująca listę źródeł z pliku zgodnie z formatem aod_lab3
vector<int> load_sources(const string& filename) {
    ifstream file(filename);
    string line;
    vector<int> sources;

    while (getline(file, line)) {
        if (line == 's') {
            stringstream ss(line);
            string s;
            int source;
            ss >> s >> source;
            sources.push_back(source - 1); 
        }
    }

    return sources;
}

// Funkcja zapisująca wyniki do pliku zgodnie z formatem aod_lab3
void save_results(const string& data_filename, const string& sources_filename,
                  const vector<int>& distances, int source, 
                  double elapsed_seconds, const string& output_filename) {

    ofstream file(output_filename, ios_base::app);

    file << "c Wyniki dla zródła: " << source + 1 << endl; 
    file << "f " << data_filename << " " << sources_filename << endl;

    // Informacje o grafie
    file << "g " << distances.size() << " " << " " /* liczba krawędzi - brak w oryginalnym kodzie */
         << " " << " " /* min cost - brak w oryginalnym kodzie */
         << " " << " " /* max cost - brak w oryginalnym kodzie */ << endl;

    // Średni czas 
    file << "t " << elapsed_seconds * 1000 << endl; 

    // Odległości
    for (int i = 0; i < distances.size(); ++i) {
        if (distances[i] == numeric_limits<int>::max()) {
            file << "c Wierzchołek " << i + 1 << " jest nieosiągalny ze źródła " << source + 1 << endl;
        } else {
            file << "d " << source + 1 << " " << i + 1 << " " << distances[i] << endl; 
        }
    }
    file << "-------------------------------------------------------------" << endl;
}

int main(int argc, char* argv[]) {
    string graph_filename, sources_filename, output_filename;

    // Parsowanie argumentów wiersza poleceń
    for (int i = 1; i < argc; ++i) {
        string arg(argv[i]);
        if (arg == "-d") {
            graph_filename = argv[++i];
        } else if (arg == "-ss") {
            sources_filename = argv[++i];
        } else if (arg == "-oss") {
            output_filename = argv[++i];
        }
    }

    // Wczytanie grafu
    Graph graph = load_graph(graph_filename);

    // Wczytanie listy źródeł
    vector<int> sources = load_sources(sources_filename);

    // Uruchomienie algorytmu Dijkstry dla każdego źródła
    for (int source : sources) {
        auto start_time = chrono::high_resolution_clock::now();
        vector<int> distances = graph.dijkstra(source);
        auto end_time = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed_seconds = end_time - start_time;

        // Zapis wyników
        save_results(graph_filename, sources_filename, distances, source, 
                    elapsed_seconds.count(), output_filename);

        // Wyświetlenie czasu wykonania - opcjonalnie
        cout << "Czas wykonania dla źródła " << source + 1 << ": " 
             << elapsed_seconds.count() << " s" << endl;
    }

    return 0;
}