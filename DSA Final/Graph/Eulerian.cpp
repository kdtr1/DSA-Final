#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

typedef pair<int, int> Edge;  // pair<weight, destination>
void addEdge(vector<vector<Edge>>& graph, int u, int v, int weight) {
    graph[u].emplace_back(weight, v);
    graph[v].emplace_back(weight, u); // for undirected graph
}
void findEulerianPath( vector<vector<Edge>>& graph, vector<int>& path)
{
    int n = graph.size();
    vector<int> inDegree(n, 0), outDegree(n, 0);

    // Calculate in-degree and out-degree for each vertex
    for (int i = 0; i < n; ++i)
    {
        for (const auto& edge : graph[i])
        {
            int dest = edge.second;
            ++outDegree[i];
            ++inDegree[dest];
        }
    }

    int startVertex = 0;
    int oddDegreeCount = 0;

    // Find the start vertex for the Eulerian path
    for (int i = 0; i < n; ++i)
    {
        if (outDegree[i] - inDegree[i] == 1)
        {
            startVertex = i;
            ++oddDegreeCount;
        }
        else if (outDegree[i] - inDegree[i] > 1)
        {
            return;  // No Eulerian path exists
        }
    }

    if (oddDegreeCount != 2)
    {
        return;  // No Eulerian path exists
    }

    // Perform Hierholzer's algorithm to find the Eulerian path
    stack<int> stk;
    stk.push(startVertex);
    int currVertex = startVertex;

    while (!stk.empty())
    {
        if (outDegree[currVertex] != 0)
        {
            stk.push(currVertex);
            int nextVertex = graph[currVertex].back().second;
            graph[currVertex].pop_back();
            --outDegree[currVertex];
            currVertex = nextVertex;
        }
        else
        {
            path.push_back(currVertex);
            currVertex = stk.top();
            stk.pop();
        }
    }

    // Reverse the path to get the Eulerian path
    reverse(path.begin(), path.end());
}

void findEulerianCycle(vector<vector<Edge>>& graph, vector<int>& cycle)
{
    int n = graph.size();
    vector<int> inDegree(n, 0), outDegree(n, 0);

    // Calculate in-degree and out-degree for each vertex
    for (int i = 0; i < n; ++i)
    {
        for (const auto& edge : graph[i])
        {
            int dest = edge.second;
            ++outDegree[i];
            ++inDegree[dest];
        }
    }

    // Check if all vertices have the same in-degree and out-degree
    for (int i = 0; i < n; ++i)
    {
        if (inDegree[i] != outDegree[i])
        {
            return;  // No Eulerian cycle exists
        }
    }

    // Perform Hierholzer's algorithm to find the Eulerian cycle
    stack<int> stk;
    stk.push(0);  // Start with vertex 0
    int currVertex = 0;

    while (!stk.empty())
    {
        if (outDegree[currVertex] != 0)
        {
            stk.push(currVertex);
            int nextVertex = graph[currVertex].back().second;
            graph[currVertex].pop_back();
            --outDegree[currVertex];
            currVertex = nextVertex;
        }
        else
        {
            cycle.push_back(currVertex);
            currVertex = stk.top();
            stk.pop();
        }
    }

    // Reverse the cycle to get the correct order of vertices
    reverse(cycle.begin(), cycle.end());
}
int main() {
    int n; cin >> n;
    vector<vector<Edge>> graph(n);
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
    
    vector<int> eulerianPath;
    findEulerianPath(graph, eulerianPath);

    if (eulerianPath.empty())
    {
        cout << "No Eulerian path exists." << endl;
    }
    else
    {
        cout << "Eulerian Path: ";
        for (int v : eulerianPath)
        {
            cout << v << " ";
        }
        cout << endl;
    }

    vector<int> eulerianCycle;
    findEulerianCycle(graph, eulerianCycle);

    if (eulerianCycle.empty())
    {
        cout << "No Eulerian cycle exists." << endl;
    }
    else
    {
        cout << "Eulerian Cycle: ";
        for (int v : eulerianCycle)
        {
            cout << v << " ";
        }
        cout << endl;
    }


    return 0;
}