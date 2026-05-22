#include <climits>
#include <iostream>
#include <vector>
using namespace std;

// This contains the result for bellman-ford algorithm.
struct Result {
    vector<int> distances;
    vector<int> predecessors;
    bool contains_negative_cycle;
};

Result BellmanFord(vector<vector<int>>& graph, int v, int src) {
    // INT_MAX represents infinity similar to Dijikstra's algorithm.
    vector<int> dist(v, INT_MAX);

    /* Optional: this is a list of predecessors of each vector. This
       is used when you need the exact shortest path from source to
       destination. eg. 0 -> 2 -> 4 -> 5 for this graph. */
    vector<int> predecessors(v, -1);

    dist[src] = 0;

    for(int i = 0; i < v; i++){
        for(vector<int> edge : graph) {
            int start = edge[0];
            int end = edge[1];
            int wt = edge[2];

            if(dist[start] != INT_MAX && dist[end] > dist[start] + wt) {
                // If after i == v - 1, it still requires a sweep, then the graph contains a negative weight cycle.
                if(i == v - 1) {
                    return {{},{}, true};
                }

                // Relax the end node with the new computed distance.
                dist[end] = dist[start] + wt;
                predecessors[end] = start;
            }
        }
    }

    return {dist,predecessors,false};
}

int main() {
  // The adjacency lists is in the format of {node1, node2, weight}. This format
  // makes it easier when sweeping throughout the pair of nodes with their
  // corresponding weight unlike the usual format of adj_list[0] = {{node2,
  // weight}, ...}.
  vector<vector<int>> graph = {{0, 1, 5},  {0, 2, 35},  {0, 3, 40}, {1, 3, 20},
                               {1, 4, 25}, {2, 4, -30}, {2, 5, 30}, {3, 5, 20},
                               {4, 3, 45}, {4, 5, 25}};

  int v = 6; // Number of vertices in the graph.


  Result result = BellmanFord(graph, v, 0);

  // The following snippet of codes below are only for displaying the results of
  // the algorithm and is not part of the algorithm itself.
  cout << "These are the following distances for each node" << endl;
  for (int distance : result.distances) {
    cout << distance << ' ';
  }
  cout << endl;

  int target = 5;
  int start = 0;
  cout << "The most optimal path from the target node: ";
  int node = target;
  while (node != -1) {
      if (node == start) cout << static_cast<char>('A' + node);
      else cout << static_cast<char>('A' + node) << " -> ";
      node = result.predecessors[node];
  }
  cout << endl << "With a total distance of " << result.distances[target] << endl;

  return 0;
}
