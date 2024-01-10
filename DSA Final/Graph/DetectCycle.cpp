#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

// Define the Edge type as a pair of int (weight, destination)
typedef pair<int, int> Edge;
void addEdge(vector<vector<Edge>>& graph, int u, int v, int weight) {
    graph[u].emplace_back(weight, v);
    graph[v].emplace_back(weight, u); // for undirected graph
}
// Function to find the shortest path using BFS
void bfsShortestPath(const vector<vector<Edge>>& graph, int start, int end, vector<int>& distance, vector<int>& parent) {
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;

    distance.assign(n, -1);
    parent.assign(n, -1);

    distance[start] = 0;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const Edge& edge : graph[u]) {
            int v = edge.second;
            int weight_uv = edge.first;

            if (!visited[v]) {
                visited[v] = true;
                distance[v] = distance[u] + weight_uv;
                parent[v] = u;
                q.push(v);
            }
        }
    }
}

// Function to print the shortest path from start to end
void printShortestPath(const vector<int>& parent, int end) {
    if (parent[end] == -1) {
        cout << "No path exists." << endl;
        return;
    }

    vector<int> path;
    for (int at = end; at != -1; at = parent[at]) {
        path.push_back(at);
    }

    cout << "Shortest path: ";
    for (int i = path.size() - 1; i >= 0; --i) {
        cout << path[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;
}

bool isCyclicUtil(const vector<vector<Edge>>& graph, int v, int parent, vector<bool>& visited, vector<bool>& ancestors)
{
    visited[v] = true;
    ancestors[v] = true;

    for (const auto& edge : graph[v])
    {
        int dest = edge.second;

        if (!visited[dest])
        {
            if (isCyclicUtil(graph, dest, v, visited, ancestors))
                return true;
        }
        else if (dest != parent && ancestors[dest])
        {
            return true;
        }
    }

    ancestors[v] = false;
    return false;
}

bool hasCycle(const vector<vector<Edge>>& graph)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<bool> ancestors(n, false);

    for (int i = 0; i < n; ++i)
    {
        if (!visited[i])
        {
            if (isCyclicUtil(graph, i, -1, visited, ancestors))
                return true;
        }
    }

    return false;
}

int main() {
    int n; cin >> n;
    vector<vector<Edge>> graph(n + 1);
    cin.ignore();
    while (true) {
        string s;
        getline(cin, s);
        if (s.empty()) break;
        int x, y;
        stringstream ss(s);
        ss >> x >> y;
        addEdge(graph, x, y, 0);
    }
    int start; cin >> start;
    int end; cin >> end;

    vector<int> distance, parent;
    bfsShortestPath(graph, start, end, distance, parent);

    cout << "Shortest distance from " << start << " to " << end << ": " << distance[end] << endl;
    printShortestPath(parent, end);

    if (hasCycle(graph))
        cout << "The graph contains a cycle." << endl;
    else
        cout << "The graph does not contain a cycle." << endl;
    return 0;
}