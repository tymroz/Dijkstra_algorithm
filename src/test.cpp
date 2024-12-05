#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

struct Edge {
  int to;
  int weight;
};

struct NodeComparator {
  bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
    return a.second > b.second;
  }
};

vector<int> dijkstra(const vector<vector<Edge>> &graph, int source) {
  int numNodes = graph.size();

  vector<int> distances(numNodes, numeric_limits<int>::max());
  distances[source] = 0;

  priority_queue<pair<int, int>, vector<pair<int, int>>, NodeComparator> heap;
  heap.push(make_pair(source, 0));

  while (!heap.empty()) {
    int u = heap.top().first;
    heap.pop();

    for (const Edge &edge : graph[u]) {
      int v = edge.to;
      int newDistance = distances[u] + edge.weight;

      if (newDistance < distances[v]) {
        distances[v] = newDistance;
        heap.push(make_pair(v, newDistance));
      }
    }
  }

  return distances;
}

vector<vector<Edge>> readGraph(const string &filename) {
  vector<vector<Edge>> graph;
  ifstream file(filename);

  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      if (line == 'c') {
        continue;
      }

      if (line == 'p') {
        istringstream iss(line);
        string dummy;
        int numNodes, numEdges;
        iss >> dummy >> dummy >> numNodes >> numEdges;
        graph.resize(numNodes);
      }

      if (line == 'a') {
        istringstream iss(line);
        char dummy;
        int from, to, weight;
        iss >> dummy >> from >> to >> weight;
        graph[from - 1].push_back({to - 1, weight});
      }
    }
    file.close();
  } else {
    cerr << "Nie można otworzyć pliku: " << filename << endl;
  }

  return graph;
}

vector<int> readSources(const string &filename) {
  vector<int> sources;
  ifstream file(filename);

  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      if (line == 's') {
        istringstream iss(line);
        char dummy;
        int source;
        iss >> dummy >> source;
        sources.push_back(source - 1); 
      }
    }
    file.close();
  } else {
    cerr << "Nie można otworzyć pliku: " << filename << endl;
  }

  return sources;
}

void writeResults(const string &filename, const vector<vector<Edge>> &graph, const vector<int> &sources, const vector<vector<int>> &distances) {
  ofstream file(filename);

  if (file.is_open()) {
    file << "c Wyniki testu dla grafu: " << endl;
    file << "c " << endl;

    file << "c Graf składa się z " << graph.size() << " węzłów i " << endl;
    int numEdges = 0;
    for (const auto &edges : graph) {
      numEdges += edges.size();
    }
    file << "c " << numEdges << " krawędzi." << endl;
    file << "c " << endl;

    for (int i = 0; i < sources.size(); ++i) {
      file << "c Średni czas dla źródła " << sources[i] + 1 << ": "
           << chrono::duration<double, milli>(distances[i]).count() << " ms" << endl;
    }
    file << "c" << endl;

    for (int i = 0; i < sources.size(); ++i) {
      file << "c Wyniki dla źródła " << sources[i] + 1 << ":" << endl;
      for (int j = 1; j < distances[i].size(); ++j) {
        file << "d " << sources[i] + 1 << " " << j << " " << distances[i][j] << endl;
      }
      file << "c" << endl;
    }

    file.close();
  } else {
    cerr << "Nie można otworzyć pliku: " << filename << endl;
  }
}

int main(int argc, char *argv[]) {
  string graphFilename;
  string sourcesFilename;
  string resultsFilename;

  for (int i = 1; i < argc; ++i) {
    if (string(argv[i]) == "-d") {
      graphFilename = argv[++i];
    } else if (string(argv[i]) == "-ss") {
      sourcesFilename = argv[++i];
    } else if (string(argv[i]) == "-oss") {
      resultsFilename = argv[++i];
    }
  }

  vector<vector<Edge>> graph = readGraph(graphFilename);
  vector<int> sources = readSources(sourcesFilename);

  vector<vector<int>> distances;
  for (int source : sources) {
    auto start = chrono::high_resolution_clock::now();
    vector<int> dist = dijkstra(graph, source);
    auto end = chrono::high_resolution_clock::now();
    dist.insert(dist.begin(), chrono::duration_cast<chrono::microseconds>(end - start).count());
    distances.push_back(dist);
  }

  writeResults(resultsFilename, graph, sources, distances);

  return 0;
}