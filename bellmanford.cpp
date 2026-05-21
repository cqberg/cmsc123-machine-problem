#include <iostream>
#include <vector>
using namespace std;

vector<int> BellmanFord(vector<vector<int>>& graph, int v, int src) {
    
    vector<int> dist(v, 1e8);
    dist[src] = 0;
    
    for(int i = 0; i < v; i++){
        for(vector<int> edge : graph) {
            int start = edge[0];
            int end = edge[1];
            int wt = edge[2];
            
            if(dist[start] != 1e8 && dist[end] > dist[start] + wt) {
                if(i == v - 1) {
                    return {-1};
                }
                
                dist[end] = dist[start] + wt;
            }
        }
    }
    
    return dist;
}

int main() {

    vector<vector<int>> graph = {
        {0, 1, 5}, 
        {0, 2, 35},
        {0, 3, 40}, 
        {1, 3, 20},
        {1, 4, 25},
        {2, 4, -30},
        {2, 5, 30},
        {3, 5, 20},
        {4, 3, 45},
        {4, 5, 25}
    };
    
    int v = 6;

    vector<int> distances = BellmanFord(graph, v, 0);
    
    for(int distance : distances) {
        cout << distance << ' ';
    }

    return 0;
}