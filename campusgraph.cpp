// CampusGraph.cpp - Campus graph implementation (adjacency list + hash lookup)
#include "CampusGraph.h"
#include "FileUtil.h"
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

static string keyOf(const string& name) { return toLower(trim(name)); }

CampusGraph::CampusGraph() : edgeCount(0) {}

int CampusGraph::findIndex(const string& name) const {
    unordered_map<string, int>::const_iterator it = lookup.find(keyOf(name));
    return it == lookup.end() ? -1 : it->second;
}

bool CampusGraph::hasBuilding(const string& name) const { return findIndex(name) != -1; }

string CampusGraph::canonicalName(const string& name) const {
    int i = findIndex(name);
    return i == -1 ? string() : names[i];
}

bool CampusGraph::addBuilding(const string& name) {
    string n = trim(name);
    if (n.empty() || findIndex(n) != -1) return false;
    lookup[keyOf(n)] = static_cast<int>(names.size());
    names.push_back(n);
    adj.push_back(vector<int>());
    return true;
}

bool CampusGraph::addConnection(const string& a, const string& b) {
    int ia = findIndex(a), ib = findIndex(b);
    if (ia == -1 || ib == -1 || ia == ib) return false;
    for (size_t i = 0; i < adj[ia].size(); i++)
        if (adj[ia][i] == ib) return false;          // duplicate (either direction)
    adj[ia].push_back(ib);
    adj[ib].push_back(ia);
    edgeCount++;
    return true;
}

int CampusGraph::loadConnections(const string& filename) {
    ifstream in(filename.c_str());
    if (!in) return -1;
    string line;
    int lineNo = 0, added = 0;
    while (getline(in, line)) {
        lineNo++;
        if (lineNo == 1) line = stripBom(line);
        line = trim(line);
        if (isSkippable(line)) continue;
        string where = "Warning (" + filename + " line " + to_string(lineNo) + "): ";
        vector<string> f = splitPipe(line);
        if (f.size() != 2 || f[0].empty() || f[1].empty()) { cout << where << "malformed line skipped.\n"; continue; }
        int ia = findIndex(f[0]), ib = findIndex(f[1]);
        if (ia == -1) { cout << where << "unknown building '" << f[0] << "', skipped.\n"; continue; }
        if (ib == -1) { cout << where << "unknown building '" << f[1] << "', skipped.\n"; continue; }
        if (ia == ib) { cout << where << "building connected to itself, skipped.\n"; continue; }
        if (!addConnection(f[0], f[1])) { cout << where << "duplicate connection, skipped.\n"; continue; }
        added++;
    }
    return added;
}

int CampusGraph::buildingCount() const { return static_cast<int>(names.size()); }
int CampusGraph::connectionCount() const { return edgeCount; }
int CampusGraph::degree(int index) const { return static_cast<int>(adj[index].size()); }
const string& CampusGraph::nameAt(int index) const { return names[index]; }
const vector<int>& CampusGraph::neighbors(int index) const { return adj[index]; }

void CampusGraph::displayGraph() const {
    if (names.empty()) { cout << "There are no buildings in the campus graph.\n"; return; }
    cout << "Campus Graph (building: connected buildings)\n";
    for (size_t i = 0; i < names.size(); i++) {
        cout << "  " << names[i] << ": ";
        if (adj[i].empty()) cout << "(no connections)";
        for (size_t j = 0; j < adj[i].size(); j++) {
            if (j > 0) cout << ", ";
            cout << names[adj[i][j]];
        }
        cout << "\n";
    }
}

void CampusGraph::displayStatistics() const {
    if (names.empty()) { cout << "There are no buildings in the campus graph.\n"; return; }
    cout << "Total buildings: " << buildingCount() << "\n";
    cout << "Total connections: " << connectionCount() << "\n";
    cout << "Degree of each building:\n";
    for (size_t i = 0; i < names.size(); i++)
        cout << "  " << names[i] << ": " << adj[i].size() << "\n";
}

// One BFS used by reachability, shortest path and the connectivity report (GRAPH-5).
// A vertex is marked visited (dist set) when it is ENQUEUED (BFS-1).
void CampusGraph::runBfs(int start, vector<int>& dist, vector<int>& prev, vector<int>& order) const {
    queue<int> q;
    dist[start] = 0;
    prev[start] = -1;
    q.push(start);
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        order.push_back(cur);
        for (size_t i = 0; i < adj[cur].size(); i++) {     // neighbor insertion order
            int nb = adj[cur][i];
            if (dist[nb] == -1) {
                dist[nb] = dist[cur] + 1;
                prev[nb] = cur;
                q.push(nb);
            }
        }
    }
}

void CampusGraph::bfsReachability(const string& startName) const {
    int start = findIndex(startName);
    if (start == -1) {                                   // BFS-3
        cout << "Error: building '" << trim(startName) << "' was not found.\n";
        return;
    }
    vector<int> dist(names.size(), -1), prev(names.size(), -1), order;
    runBfs(start, dist, prev, order);
    cout << "Buildings reachable from " << names[start] << " (BFS order, distance in connections):\n";
    for (size_t i = 0; i < order.size(); i++)
        cout << "  " << (i + 1) << ". " << names[order[i]] << " (distance " << dist[order[i]] << ")\n";
    cout << "Reachable: " << order.size() << " out of " << names.size() << " buildings\n";   // BFS-2
}

void CampusGraph::shortestPath(const string& startName, const string& destName) const {
    int s = findIndex(startName), d = findIndex(destName);
    if (s == -1 || d == -1) {                            // BFS-4: identify any unknown building
        if (s == -1) cout << "Error: starting building '" << trim(startName) << "' was not found.\n";
        if (d == -1) cout << "Error: destination building '" << trim(destName) << "' was not found.\n";
        return;
    }
    vector<int> dist(names.size(), -1), prev(names.size(), -1), order;
    runBfs(s, dist, prev, order);
    if (dist[d] == -1) {
        cout << "No path exists between " << names[s] << " and " << names[d] << ".\n";
        return;
    }
    vector<int> path;
    for (int v = d; v != -1; v = prev[v]) path.push_back(v);
    cout << "Shortest path from " << names[s] << " to " << names[d] << ":\n";
    for (int i = static_cast<int>(path.size()) - 1; i >= 0; i--)   // BFS-5: one per line
        cout << "  " << names[path[i]] << "\n";
    cout << "Number of connections: " << dist[d] << "\n";
}

void CampusGraph::connectivityReport() const {
    cout << "Connectivity Report\n";
    cout << "Total buildings: " << buildingCount() << "\n";
    cout << "Total connections: " << connectionCount() << "\n";
    if (names.empty()) {
        cout << "There are no buildings in the campus graph.\n";
        cout << "Highest degree: N/A\nIsolated buildings: None\nConnected components: 0\n";
        return;
    }
    size_t best = 0;
    for (size_t i = 0; i < adj.size(); i++) if (adj[i].size() > best) best = adj[i].size();
    cout << "Highest degree: " << best << " (";
    bool first = true;
    for (size_t i = 0; i < adj.size(); i++) {
        if (adj[i].size() == best) { if (!first) cout << ", "; cout << names[i]; first = false; }
    }
    cout << ")\n";
    cout << "Isolated buildings: ";
    first = true;
    for (size_t i = 0; i < adj.size(); i++) {
        if (adj[i].empty()) { if (!first) cout << ", "; cout << names[i]; first = false; }
    }
    if (first) cout << "None";
    cout << "\n";
    vector<int> dist(names.size(), -1), prev(names.size(), -1), order;
    int components = 0;
    for (size_t i = 0; i < names.size(); i++) {
        if (dist[i] == -1) { runBfs(static_cast<int>(i), dist, prev, order); components++; }
    }
    cout << "Connected components: " << components << "\n";
}

void promptBfsReachability(const CampusGraph& g) {
    cout << "Enter starting building: ";
    string start;
    getline(cin, start);
    g.bfsReachability(start);
}

void promptShortestPath(const CampusGraph& g) {
    string a, b;
    cout << "Enter starting building: ";
    getline(cin, a);
    cout << "Enter destination building: ";
    getline(cin, b);
    g.shortestPath(a, b);
}
