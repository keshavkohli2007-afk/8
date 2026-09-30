#include <iostream>
#include <vector>
#include <algorithm>
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

int main() {
    int V, E;
    cin >> V >> E;

    vector<Edge> edges(E);

    for (int i = 0; i < E; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    sort(edges.begin(), edges.end(), compare);

    vector<int> parent(V);
    vector<int> rank(V, 0);

    for (int i = 0; i < V; i++)
        parent[i] = i;

    int mstWeight = 0;

    cout << "Edges in Minimum Spanning Tree:\n";

    for (Edge edge : edges) {
        int u = findParent(edge.u, parent);
        int v = findParent(edge.v, parent);

        if (u != v) {
            cout << edge.u << " - " << edge.v << " : " << edge.w << endl;
            mstWeight += edge.w;
            unionSet(u, v, parent, rank);
        }
    }

    cout << "Minimum Cost: " << mstWeight << endl;

    return 0;
}