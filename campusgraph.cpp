// CampusGraph.cpp - Campus graph implementation (adjacency list)
#include "CampusGraph.h"
#include "utility.h"
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

namespace {
// Splits a line on '|' and trims every field.
vector<string> splitPipe(const string& line) {
    vector<string> fields;
    string cur;
    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == '|') { fields.push_back(trim(cur)); cur.clear(); }
        else cur += line[i];
    }
    fields.push_back(trim(cur));
    return fields;
}
}

CampusGraph::CampusGraph() : edgeCount(0) {}

int CampusGraph::findIndex(const string& name) const {
    string key = trim(name);
    for (size_t i = 0; i < names.size(); i++)
        if (checkEqual(names[i], key)) return static_cast<int>(i);
    return -1;
}

bool CampusGraph::addBuilding(const string& name) {
    string n = trim(name);
    if (n.empty() || findIndex(n) != -1) return false;
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
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;      // blank / comment
        vector<string> f = splitPipe(line);
        if (f.size() != 2 || f[0].empty() || f[1].empty()) {
            cout << "Warning (" << filename << " line " << lineNo << "): malformed line skipped.\n";
            continue;
        }
        int ia = findIndex(f[0]), ib = findIndex(f[1]);
        if (ia == -1) { cout << "Warning (" << filename << " line " << lineNo << "): unknown building '" << f[0] << "', skipped.\n"; continue; }
        if (ib == -1) { cout << "Warning (" << filename << " line " << lineNo << "): unknown building '" << f[1] << "', skipped.\n"; continue; }
        if (ia == ib) { cout << "Warning (" << filename << " line " << lineNo << "): building connected to itself, skipped.\n"; continue; }
        if (!addConnection(f[0], f[1])) { cout << "Warning (" << filename << " line " << lineNo << "): duplicate connection, skipped.\n"; continue; }
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

void CampusGraph::bfsReachability(const string& startName) const {
    int start = findIndex(startName);
    if (start == -1) {                                   // BFS-3
        cout << "Error: building '" << trim(startName) << "' was not found.\n";
        return;
    }
    vector<int> dist(names.size(), -1);                  // -1 = not visited
    queue<int> q;
    vector<int> order;
    dist[start] = 0;                                     // mark visited when ENQUEUED
    q.push(start);
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        order.push_back(cur);
        for (size_t i = 0; i < adj[cur].size(); i++) {
            int nb = adj[cur][i];
            if (dist[nb] == -1) {
                dist[nb] = dist[cur] + 1;
                q.push(nb);
            }
        }
    }
    cout << "Buildings reachable from " << names[start] << " (BFS order, distance in connections):\n";
    for (size_t i = 0; i < order.size(); i++)
        cout << "  " << (i + 1) << ". " << names[order[i]] << " (distance " << dist[order[i]] << ")\n";
    cout << "Reachable: " << order.size() << " out of " << names.size() << " buildings\n";   // BFS-2
}

void CampusGraph::shortestPath(const string& startName, const string& destName) const {
    int s = findIndex(startName), d = findIndex(destName);
    if (s == -1 || d == -1) {
        if (s == -1) cout << "Error: starting building '" << trim(startName) << "' was not found.\n";
        if (d == -1) cout << "Error: destination building '" << trim(destName) << "' was not found.\n";
        return;
    }
    vector<int> dist(names.size(), -1), prev(names.size(), -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty() && dist[d] == -1) {
        int cur = q.front(); q.pop();
        for (size_t i = 0; i < adj[cur].size(); i++) {   // neighbor insertion order breaks ties
            int nb = adj[cur][i];
            if (dist[nb] == -1) {
                dist[nb] = dist[cur] + 1;
                prev[nb] = cur;
                q.push(nb);
            }
        }
    }
    if (dist[d] == -1) {
        cout << "No path exists between " << names[s] << " and " << names[d] << ".\n";
        return;
    }
    vector<int> path;
    for (int v = d; v != -1; v = prev[v]) path.push_back(v);
    cout << "Shortest path from " << names[s] << " to " << names[d] << ":\n";
    for (int i = static_cast<int>(path.size()) - 1; i >= 0; i--)
        cout << "  " << names[path[i]] << "\n";
    cout << "Number of connections: " << dist[d] << "\n";
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
