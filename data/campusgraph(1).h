#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H
#include <string>
#include <vector>
#include <unordered_map>

class CampusGraph {
public:
    CampusGraph();

    // Adds a building 
    bool addBuilding(const std::string& name);


    bool addConnection(const std::string& a, const std::string& b);

    // Loads connections.txt
    int loadConnections(const std::string& filename);

    // GRAPH-6: case-insensitive.
    int findIndex(const std::string& name) const;
    bool hasBuilding(const std::string& name) const;
 
    std::string canonicalName(const std::string& name) const;

    int buildingCount() const;
    int connectionCount() const;              
    int degree(int index) const;
    const std::string& nameAt(int index) const;
    const std::vector<int>& neighbors(int index) const;

    // GRAPH-3: buildings in insertion order.
    void displayGraph() const;
    // GRAPH 4
    void displayStatistics() const;

    
    void bfsReachability(const std::string& startName) const;

    // //
    void shortestPath(const std::string& startName, const std::string& destName) const;

    
    // number of connected components
    void connectivityReport() const;

private:
    std::vector<std::string> names;
    std::vector<std::vector<int> > adj;
    std::unordered_map<std::string, int> lookup;
    int edgeCount;

    // Runs BFS 
    void runBfs(int start, std::vector<int>& dist, std::vector<int>& prev, std::vector<int>& order) const;
};

// Menu helpers:
void promptBfsReachability(const CampusGraph& g);
void promptShortestPath(const CampusGraph& g);

#endif
