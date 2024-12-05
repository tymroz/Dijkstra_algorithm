#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <fstream>
#include <chrono>

using namespace std;

void diala(const vector<list<Edge>>& graph, int source, vector<int>& distances) {
  int n = graph.size();

  distances.assign(n, numeric_limits<int>::max());
  distances[source] = 0;

  int max_cost = 0;
  for (const auto& edges : graph) {
      for (const Edge& edge : edges) {
          max_cost = max(max_cost, edge.cost);
      }
  }

  int num_buckets = max_cost + 1;
  vector<list<int>> buckets(num_buckets);

  buckets.push_back(source);

  for (int i = 0; i < num_buckets; ++i) {
      while (!buckets[i].empty()) {
          int u = buckets[i].front();
          buckets[i].pop_front();

          for (const Edge& edge : graph[u]) {
              int v = edge.to;
              int new_distance = distances[u] + edge.cost;

              if (new_distance < distances[v]) {
                  distances[v] = new_distance;
                  buckets[new_distance].push_back(v);
              }
          }
      }
  }
}