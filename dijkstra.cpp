#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

void printPath(vector<int>& parent, int v) {
    if (v == -1)
        return;

    printPath(parent, parent[v]);
    cout << v << " ";
}

int main() {
    int n;
    cout<<"Enter no. of vertices : "<<endl;
    cin >> n;

    vector<vector<pair<int, int>>> adj(n);
    cout<<"Input adj Matrix : "<<endl;
    // Input adjacency matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int w;
            cin >> w;

            if (w != 0) {
                adj[i].push_back({j, w});
            }
        }
    }

    int src;
    cout<<"Enter source :"<<endl;
    cin >> src;

    vector<int> dist(n, INF);
    vector<int> parent(n, -1);

    // Min heap: {distance, vertex}
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto edge : adj[u]) {
            int v = edge.first;
            int wt = edge.second;

            if (dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
                parent[v] = u;

                pq.push({dist[v], v});
            }
        }
    }

    cout << "\nShortest distances from source " << src << ":\n";

    for (int i = 0; i < n; i++) {
        cout << "To " << i << ": ";

        if (dist[i] == INF) {
            cout << "Unreachable\n";
        } 
        else {
            cout << dist[i] << "\tPath: ";
            printPath(parent, i);
            cout << "\n";
        }
    }

    return 0;
}