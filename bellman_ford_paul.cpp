#include <climits>
#include <iostream>
#include <vector>
using namespace std;

using vertex = pair<int,int>;
using adj_list = vector<vector<vertex>>;

void bellman_ford(adj_list& adjList, int start, int target) {
    int V = adjList.size();

    vector<int> dist(V, INT_MAX);
    vector<int> predecessors(V, -1);

    dist[start] = 0;
    for (int i = 0; i < V; i++) {
        bool has_relaxed = false;
        for (int j = 0; j < V; j++) {
            vector<vertex> vertices = adjList[j];
            for (vertex v: vertices) {
                if (dist[j] == INT_MAX && dist[v.first] == INT_MAX) continue;
                int current_dist = dist[j] + v.second;
                if (current_dist < dist[v.first]) {
                    cout << "Sweep " << i + 1 << ": Node " << static_cast<char>('A' + v.first) << " has been relaxed with " << current_dist << endl;
                    has_relaxed = true;
                    dist[v.first] = current_dist;
                    predecessors[v.first] = j;
                }
            }
        }
        if (!has_relaxed) break;
    }

    for (int i = 0; i < V; i++) {
        cout << static_cast<char>('A' + predecessors[i]) << " -> " << static_cast<char>('A' + i) << endl;
    }

    cout << "The most optimal path is: ";
    int node = target;
    while (node != -1) {
        if (node == start) cout << static_cast<char>('A' + node);
        else cout << static_cast<char>('A' + node) << " -> ";
        node = predecessors[node];
    }
    cout << endl << "With a total dist of " << dist[target] << endl;
}

int main() {
  adj_list adjList = {
      {{1, 5}, {2, 35}, {3, 40}},
      {{3, 20}, {4, 25}},
      {{4, -30}, {5, 30}},
      {{5, 20}},
      {{3, 45}, {5, 25}},
      {}
  };

  bellman_ford(adjList, 0, 5);

  return 0;
}
