#include "dijkstras.h"

struct Node {
    int vertex;
    int dist;
    Node(int v, int d) : vertex(v), dist(d) {}
};

struct CompareDist {
    bool operator()(const Node& a, const Node& b) {
        return a.dist > b.dist;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distances(n, INF);
    vector<bool> visited(n, false);
    distances[source] = 0;
    previous.assign(n, -1);

    priority_queue<Node, vector<Node>, CompareDist> pq;
    pq.push(Node(source, 0));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;
        if (visited[u]) continue;
        visited[u] = true;

        for (auto &edge : G[u]) {
            int v = edge.dst;
            int w = edge.weight;
            if (!visited[v] && distances[u] != INF &&
                distances[u] + w < distances[v]) {
                distances[v] = distances[u] + w;
                previous[v]  = u;
                pq.push(Node(v, distances[v]));
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances,
                                  const vector<int>& previous,
                                  int destination) {
    vector<int> path;
    if (destination < 0 || destination >= (int)distances.size() || distances[destination] == INF) {
        return path;
    }
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    if (v.empty()) {
        cout << endl;
        cout << "Total cost is " << total << endl;
        return;
    }
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}
