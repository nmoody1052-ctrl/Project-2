// DepartmentTree.h - Department general tree (TREE-1..8)
// A node can have any number of children (vector of child pointers, TREE-1).
// Children are kept in insertion order, which is the sibling visiting order.
#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H
#include <string>
#include <vector>

struct DeptNode {
    std::string name;
    DeptNode* parent;                    // nullptr for the root
    std::vector<DeptNode*> children;     // insertion order
    explicit DeptNode(const std::string& n) : name(n), parent(0) {}
};

class DepartmentTree {
public:
    DepartmentTree();
    ~DepartmentTree();

    bool isEmpty() const;
    int size() const;

    // TREE-3: if the tree is empty the department becomes the root (parentName ignored).
    // Otherwise parentName must exist and name must not be a duplicate (case-insensitive).
    // On failure returns false and fills errorMsg.
    bool addDepartment(const std::string& name, const std::string& parentName, std::string& errorMsg);

    // TREE-2: loads departments.txt. Returns departments added, or -1 if the file cannot be opened.
    // Rules used: '#' comment lines and blank lines ignored, fields split on '|' and trimmed,
    // parent "NONE" (any case) = root, a parent must appear earlier in the file than its children.
    int loadFromFile(const std::string& filename);

    // TREE-4: search by name (case-insensitive); shows name, parent, child count, depth
    void searchDepartment(const std::string& name) const;
    // TREE-5: hierarchy in preorder, 4 spaces of indent per depth
    void displayHierarchy() const;
    // TREE-6 / TREE-7: traversals shown as a sequence without indentation
    void displayPreorder() const;
    void displayPostorder() const;
    void displayLevelOrder() const;      // uses a queue
    // TREE-8: total departments, leaves, height
    void displayStatistics() const;

private:
    DeptNode* root;
    std::vector<DeptNode*> all;          // every node in insertion order (for lookup)

    DeptNode* findNode(const std::string& name) const;
    static int depthOf(const DeptNode* n);
    static int heightOf(const DeptNode* n);
    static void preorderRec(const DeptNode* n, std::vector<std::string>& out);
    static void postorderRec(const DeptNode* n, std::vector<std::string>& out);
    static void hierarchyRec(const DeptNode* n, int depth);
    static void destroy(DeptNode* n);
    DepartmentTree(const DepartmentTree&);             // not copyable
    DepartmentTree& operator=(const DepartmentTree&);
};

// Menu helpers
void promptAddDepartment(DepartmentTree& t);
void promptSearchDepartment(const DepartmentTree& t);

#endif
