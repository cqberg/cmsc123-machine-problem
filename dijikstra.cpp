#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

using vertex = pair<int,int>;
using adj_list = vector<vector<vertex>>;

void dijikstra(adj_list& adjList, int start, int target) {
    int V = adjList.size();

    priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
    vector<int> dist(V, INT_MAX);
    vector<int> predecessors(V, -1);

    dist[start] = 0;
    pq.push({0,0});
    while (!pq.empty()) {
        vertex start_vert = pq.top();
        pq.pop();
        for (vertex v: adjList[start_vert.first]) {
            int current_dist = start_vert.second + v.second;
            if (current_dist < dist[v.first]) {
                dist[v.first] = current_dist;
                pq.push({v.first, current_dist});
                predecessors[v.first] = start_vert.first;
            }
        }
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
      {{4, 30}, {5, 30}},
      {{5, 20}},
      {{3, 45}, {5, 25}},
      {}
  };

  dijikstra(adjList, 0, 5);

  return 0;
}
