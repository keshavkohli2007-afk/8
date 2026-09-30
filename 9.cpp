#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
//keshav kohli
//25/da/035
using namespace std;

struct Edge {
    int u, v, w;
};

bool compare(Edge a, Edge b) {
    return a.w < b.w;
}

int findParent(int node, vector<int>& parent) {
    if (parent[node] == node)
        return node;
    return parent[node] = findParent(parent[node], parent);
}

void unionSet(int u, int v, vector<int>& parent, vector<int>& rank) {
    u = findParent(u, parent);
    v = findParent(v, parent);

    if (u == v)
        return;

    if (rank[u] < rank[v])
        parent[u] = v;
    else if (rank[u] > rank[v])
        parent[v] = u;
    else {
        parent[v] = u;
        rank[u]++;
    }
}

void prim(vector<vector<int>>& graph, int V) {
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> mst(V, false);

    key[0] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = -1;

        for (int i = 0; i < V; i++) {
            if (!mst[i] && (u == -1 || key[i] < key[u]))
                u = i;
        }

        mst[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mst[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    int total = 0;

    cout << "Prim's MST:\n";

    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << " : " << graph[i][parent[i]] << endl;
        total += graph[i][parent[i]];
    }

    cout << "Minimum Cost: " << total << endl;
}

void kruskal(vector<Edge>& edges, int V) {
    sort(edges.begin(), edges.end(), compare);

    vector<int> parent(V);
    vector<int> rank(V, 0);

    for (int i = 0; i < V; i++)
        parent[i] = i;

    int total = 0;
    int count = 0;

    cout << "\nKruskal's MST:\n";

    for (Edge edge : edges) {
        int u = findParent(edge.u, parent);
        int v = findParent(edge.v, parent);

        if (u != v) {
            cout << edge.u << " - " << edge.v << " : " << edge.w << endl;
            total += edge.w;
            unionSet(u, v, parent, rank);
            count++;

            if (count == V - 1)
                break;
        }
    }

    cout << "Minimum Cost: " << total << endl;
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<int>> graph(V, vector<int>(V, 0));
    vector<Edge> edges;

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        graph[u][v] = w;
        graph[v][u] = w;

        edges.push_back({u, v, w});
    }

    prim(graph, V);
    kruskal(edges, V);

    return 0;
}