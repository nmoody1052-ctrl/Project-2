// CampusGraph.h - Campus graph (GRAPH-1..6, BFS-1..5, Final connectivity report)
// DESIGN CHOICE (GRAPH-2): ADJACENCY LIST.
//   names[i]  = building name (index i = insertion order)
//   adj[i]    = vector of neighbor indices, in neighbor insertion order
//   lookup    = hash map  lowercase(trimmed name) -> index   (O(1) name matching, GRAPH-6)
// Walkways are undirected and unweighted: addConnection(a,b) stores b in adj[a]
// AND a in adj[b]. The same structure is used by display, statistics,
// BFS reachability, shortest path and the connectivity report (GRAPH-5).
#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H
#include <string>
#include <vector>
#include <unordered_map>

class CampusGraph {
public:
    CampusGraph();

    // Adds a building vertex. Returns false if the name is empty or a duplicate (case-insensitive).
    bool addBuilding(const std::string& name);

    // Adds an undirected walkway. Returns false if either building is unknown,
    // both are the same building, or the walkway already exists (either direction).
    bool addConnection(const std::string& a, const std::string& b);

    // Loads connections.txt. Returns number of connections added, or -1 if the file cannot be opened.
    // Bad lines are skipped with a warning (line number + reason).
    int loadConnections(const std::string& filename);

    // GRAPH-6: case-insensitive, trimmed, internal spaces preserved. Returns -1 if not found.
    int findIndex(const std::string& name) const;
    bool hasBuilding(const std::string& name) const;
    // Official spelling of a building as stored (e.g. "library" -> "Library"); "" if unknown.
    // Handy for the facility loader.
    std::string canonicalName(const std::string& name) const;

    int buildingCount() const;
    int connectionCount() const;              // each undirected edge counted once
    int degree(int index) const;
    const std::string& nameAt(int index) const;
    const std::vector<int>& neighbors(int index) const;

    // GRAPH-3: buildings in insertion order, neighbors in neighbor insertion order
    void displayGraph() const;
    // GRAPH-4: total buildings, total connections, degree of each building
    void displayStatistics() const;

    // BFS-1..3: reachable buildings in visit order with distance (number of connections)
    void bfsReachability(const std::string& startName) const;

    // BFS-4/5 (Final): fewest-connection path between two buildings
    void shortestPath(const std::string& startName, const std::string& destName) const;

    // Final: connectivity report = totals, highest degree (with ties), isolated buildings,
    // number of connected components
    void connectivityReport() const;

private:
    std::vector<std::string> names;
    std::vector<std::vector<int> > adj;
    std::unordered_map<std::string, int> lookup;
    int edgeCount;

    // Runs BFS from start. dist[i] == -1 means "not reached". Fills visit order.
    void runBfs(int start, std::vector<int>& dist, std::vector<int>& prev, std::vector<int>& order) const;
};

// Menu helpers: prompt the user, then call the function above.
void promptBfsReachability(const CampusGraph& g);
void promptShortestPath(const CampusGraph& g);

#endif
