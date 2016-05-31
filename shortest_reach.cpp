#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <climits>
#include <queue>
#include <map>
using namespace std;

// Simple Djiskra's algorithm with constant edge weights = 6 and without finding paths
int main()
{
    int T;
    vector<set<int>> adjacency;
    vector<int> distance;
    set<pair<int,int>, less<pair<int,int>>> vertices;
    set<int> blue;

    cin >> T;
    for (int t = 0; t < T; t++) {
        int N, M;
        int S;

        cin >> N >> M;
        adjacency.resize(N);
        distance.resize(N, INT_MAX);

        for (int m = 0; m < M; m++) {
            int n0, n1;
            cin >> n0 >> n1;
            --n0, --n1; // all numbers from cin are 1 based indices
            adjacency[n0].insert(n1);
            adjacency[n1].insert(n0);
        }
        
        cin >> S;
        --S;
        
        // at the begining distance of starting node S is equal 0, ceterae equal infinity
        distance[S] = 0;
        for (int i = 0; i < N; i++) {
            vertices.insert(make_pair(distance[i], i));
        }
        
        while (!vertices.empty()) {
            int u = vertices.begin()->second;
            // it means that rest is disconnected from S
            if (vertices.begin()->first == INT_MAX) {
                vertices.clear();
                break;
            }
            vertices.erase(vertices.begin());
            // update all adjacent neighbours
            // note that second set of 'done' vertices is unnecessery because they will never
            // fulfill relaxation condition as they already have proper distance value
            for (set<int>::iterator iv = adjacency[u].begin(); iv != adjacency[u].end(); ++iv) {
                int v = *iv;
                int dist_update = distance[u] + 6; // 6 is the weight of each edge
                if (distance[v] > dist_update) {
                    set<pair<int,int>>::iterator ig = vertices.find(make_pair(distance[v], v));
                    // update distance and the set with updated distance value
                    distance[v] = dist_update;
                    vertices.erase(ig);
                    vertices.insert(make_pair(dist_update, v));
                }
            }
        }
        
        for (int i = 0; i < N; i++) {
            if (i != S) {
                cout << (distance[i] != INT_MAX ? distance[i] : -1) << " "; 
            }
        }
        cout << "\n";
        
        adjacency.clear();
        distance.clear();
    }
    return 0;
}
