#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <algorithm>

using namespace std;

typedef pair<int, int> Edge; // {weight, destination}


void addEdge(vector<vector<Edge>>& graph, int u, int v, int weight) {
    graph[u].emplace_back(weight, v);
    graph[v].emplace_back(weight, u); // for undirected graph
}
vector<vector<int>> convertToAdjMatrix(const vector<vector<Edge>>& graph) {
    int n = graph.size();
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (const Edge& edge : graph[i]) {
            adjMatrix[i - 1][edge.second - 1] = 1;
            adjMatrix[edge.second - 1][i - 1] = 1;
        }
    }

    return adjMatrix;
}

vector<int> BFS(const vector<vector<Edge>>& graph, int startVertex) {
    int vertices = graph.size();
    vector<bool> visited(vertices, false);
    vector<int> result;
    queue<int> q;

    visited[startVertex] = true;
    q.push(startVertex);

    while (!q.empty()) {
        int currentVertex = q.front();
        result.push_back(currentVertex);
        q.pop();

        for (const auto& edge : graph[currentVertex]) {
            int neighbor = edge.second;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return result;
}

void DFSUtil(const vector<vector<Edge>>& graph, int currentVertex, vector<bool>& visited, vector<int>& result) {
    result.push_back(currentVertex);
    visited[currentVertex] = true;

    for (const auto& edge : graph[currentVertex]) {
        int neighbor = edge.second;
        if (!visited[neighbor]) {
            DFSUtil(graph, neighbor, visited, result);
        }
    }
}

vector<int> DFS(const vector<vector<Edge>>& graph, int startVertex) {
    int vertices = graph.size();
    vector<bool> visited(vertices, false);
    vector<int> result;
    DFSUtil(graph, startVertex, visited, result);
    return result;
}

int countConnectedComponents(const vector<vector<Edge>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    int componentCount = 0;

    for (int i = 1; i < n; ++i) {
        if (!visited[i]) {
            vector<int> res;
            DFSUtil(graph, i,visited,res);
            /*for (auto x : res) cout << x << " ";
            cout << endl;*/
            componentCount++;
        }
    }

    return componentCount;
}

int findMinKey(const vector<int>& key, const vector<bool>& inMST) {
    int minKey = INT_MAX, minIndex;

    for (int v = 0; v < key.size(); ++v) {
        if (!inMST[v] && key[v] < minKey) {
            minKey = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}

vector<pair<int, pair<int, int>>> PrimMST(const vector<vector<Edge>>& graph) {
    int vertices = graph.size();
    vector<int> parent(vertices, -1);
    vector<int> key(vertices, INT_MAX);
    vector<bool> inMST(vertices, false);

    key[0] = 0;  // Start with the first vertex

    for (int i = 0; i < vertices - 1; ++i) {
        int minKey = findMinKey(key, inMST);
        inMST[minKey] = true;

        for (const auto& edge : graph[minKey]) {
            int neighbor = edge.second;
            if (!inMST[neighbor] && key[neighbor] > edge.first) {
                parent[neighbor] = minKey;
                key[neighbor] = edge.first;
            }
        }
    }

    vector<pair<int, pair<int, int>>> result;
    for (int i = 1; i < vertices; ++i) {
        result.push_back({ key[i], {parent[i], i} });
    }

    return result;
}

vector<int> Dijkstra(const vector<vector<Edge>>& graph, int startVertex) {
    int vertices = graph.size();
    vector<int> distance(vertices, INT_MAX);
    distance[startVertex] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, startVertex });

    while (!pq.empty()) {
        int dist = pq.top().first;
        int currentVertex = pq.top().second;
        pq.pop();

        if (dist > distance[currentVertex]) {
            continue; // Skip outdated distances
        }

        for (const auto& edge : graph[currentVertex]) {
            int neighbor = edge.second;
            int weight = edge.first;

            if (distance[currentVertex] + weight < distance[neighbor]) {
                distance[neighbor] = distance[currentVertex] + weight;
                pq.push({ distance[neighbor], neighbor });
            }
        }
    }

    return distance;
}

vector<int> BellmanFord(const vector<vector<Edge>>& graph, int startVertex) {
    int vertices = graph.size();
    int edges = 0;
    for (const auto& neighbors : graph) {
        edges += neighbors.size();
    }

    vector<int> dist(vertices, INT_MAX);
    dist[startVertex] = 0;

    // Relax all edges |V| - 1 times
    for (int i = 1; i <= vertices - 1; ++i) {
        for (int u = 0; u < vertices; ++u) {
            for (const auto& edge : graph[u]) {
                int v = edge.second;
                int weight = edge.first;

                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u < vertices; ++u) {
        for (const auto& edge : graph[u]) {
            int v = edge.second;
            int weight = edge.first;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                // Negative-weight cycle detected
                cout << "Graph contains a negative weight cycle\n";
                return {};
            }
        }
    }

    return dist;
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
    vector<vector<int>> matrix = convertToAdjMatrix(graph);
    for (int i = 0; i < matrix.size(); i++) {
        for (auto x : matrix[i]) {
            cout << x << " ";
        }
        cout << endl;
    }
    cout << countConnectedComponents(graph) << endl;
    return 0;
}
