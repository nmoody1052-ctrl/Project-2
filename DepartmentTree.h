// DepartmentTree.h _ Department general tree
#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H
#include <string>
#include <vector>
#include <unordered_map>

struct DeptNode {
    std::string name;
    DeptNode* parent;                    
    int depth;                           // 
    std::vector<DeptNode*> children;     // 
    explicit DeptNode(const std::string& n) : name(n), parent(0), depth(0) {}
};

class DepartmentTree {
public:
    DepartmentTree();
    ~DepartmentTree();

    bool isEmpty() const;
    int size() const;

   .
    bool addDepartment(const std::string& name, const std::string& parentName, std::string& errorMsg);

  
    int loadFromFile(const std::string& filename);

   // tree - 4
    void searchDepartment(const std::string& name) const;
    // TREE-5
    void displayHierarchy() const;
    // TREE-6
    void displayPreorder() const;
    void displayPostorder() const;
    void displayLevelOrder() const;      // uses a queue
    // TREE-8 
    void displayStatistics() const;

private:
    DeptNode* root;
    std::vector<DeptNode*> all;          // every node in insertion order
    std::unordered_map<std::string, DeptNode*> lookup;   

    DeptNode* findNode(const std::string& name) const;
    static void preorderRec(const DeptNode* n, std::vector<std::string>& out);
    static void postorderRec(const DeptNode* n, std::vector<std::string>& out);
    static void hierarchyRec(const DeptNode* n, int depth);
    static void destroy(DeptNode* n);
    DepartmentTree(const DepartmentTree&);             
    DepartmentTree& operator=(const DepartmentTree&);
};

// Menu helpers for ;
void promptAddDepartment(DepartmentTree& t);
void promptSearchDepartment(const DepartmentTree& t);

#endif
