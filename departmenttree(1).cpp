// departmentTree.cpp Department general tree implementation //
#include "DepartmentTree.h"
#include "FileUtil.h"
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

namespace {
void printSequence(const vector<string>& seq) {
    for (size_t i = 0; i < seq.size(); i++) {
        if (i > 0) cout << ", ";
        cout << seq[i];
    }
    cout << "\n";
}
}

DepartmentTree::DepartmentTree() : root(0) {}
DepartmentTree::~DepartmentTree() { destroy(root); }

void DepartmentTree::destroy(DeptNode* n) {
    if (!n) return;
    for (size_t i = 0; i < n->children.size(); i++) destroy(n->children[i]);
    delete n;
}

bool DepartmentTree::isEmpty() const { return root == 0; }
int DepartmentTree::size() const { return static_cast<int>(all.size()); }

DeptNode* DepartmentTree::findNode(const string& name) const {
    unordered_map<string, DeptNode*>::const_iterator it = lookup.find(toLower(trim(name)));
    return it == lookup.end() ? 0 : it->second;
}

bool DepartmentTree::addDepartment(const string& name, const string& parentName, string& errorMsg) {
    string n = trim(name);
    if (n.empty()) { errorMsg = "Department name cannot be empty."; return false; }
    if (findNode(n)) { errorMsg = "Department '" + n + "' already exists."; return false; }
    if (root == 0) {                                     // empty tree: becomes root
        root = new DeptNode(n);
        all.push_back(root);
        lookup[toLower(n)] = root;
        return true;
    }
    DeptNode* p = findNode(parentName);
    if (!p) { errorMsg = "Parent department '" + trim(parentName) + "' does not exist."; return false; }
    DeptNode* child = new DeptNode(n);
    child->parent = p;
    child->depth = p->depth + 1;
    p->children.push_back(child);
    all.push_back(child);
    lookup[toLower(n)] = child;
    return true;
}

int DepartmentTree::loadFromFile(const string& filename) {
    ifstream in(filename.c_str());
    if (!in) return -1;
    string line;
    int lineNo = 0, added = 0;
    while (getline(in, line)) {
        lineNo++;
        if (lineNo == 1) line = stripBom(line);
        line = trim(line);
        if (isSkippable(line)) continue;
        vector<string> f = splitPipe(line);
        if (f.size() != 2 || f[0].empty() || f[1].empty()) {
            cout << "Warning (" << filename << " line " << lineNo << "): malformed line skipped.\n";
            continue;
        }
        string err;
        bool ok;
        if (checkEqual(f[1], "NONE")) {
            if (root != 0) {
                cout << "Warning (" << filename << " line " << lineNo << "): a root already exists; '" << f[0] << "' skipped.\n";
                continue;
            }
            ok = addDepartment(f[0], "", err);
        } else {
            if (root == 0) {
                cout << "Warning (" << filename << " line " << lineNo << "): no root defined yet; '" << f[0] << "' skipped.\n";
                continue;
            }
            ok = addDepartment(f[0], f[1], err);
        }
        if (!ok) { cout << "Warning (" << filename << " line " << lineNo << "): " << err << " Skipped.\n"; continue; }
        added++;
    }
    return added;
}

void DepartmentTree::preorderRec(const DeptNode* n, vector<string>& out) {
    out.push_back(n->name);
    for (size_t i = 0; i < n->children.size(); i++) preorderRec(n->children[i], out);
}

void DepartmentTree::postorderRec(const DeptNode* n, vector<string>& out) {
    for (size_t i = 0; i < n->children.size(); i++) postorderRec(n->children[i], out);
    out.push_back(n->name);
}

void DepartmentTree::hierarchyRec(const DeptNode* n, int depth) {
    cout << string(depth * 4, ' ') << n->name << "\n";
    for (size_t i = 0; i < n->children.size(); i++) hierarchyRec(n->children[i], depth + 1);
}

void DepartmentTree::searchDepartment(const string& name) const {
    if (isEmpty()) { cout << "The department tree is empty.\n"; return; }
    DeptNode* n = findNode(name);
    if (!n) { cout << "Department '" << trim(name) << "' was not found.\n"; return; }
    cout << "Department: " << n->name << "\n";
    cout << "Parent: " << (n->parent ? n->parent->name : string("None")) << "\n";
    cout << "Direct children: " << n->children.size() << "\n";
    cout << "Depth: " << n->depth << "\n";
}

void DepartmentTree::displayHierarchy() const {
    if (isEmpty()) { cout << "The department tree is empty.\n"; return; }
    cout << "Department Hierarchy:\n";
    hierarchyRec(root, 0);
}

void DepartmentTree::displayPreorder() const {
    if (isEmpty()) { cout << "The department tree is empty.\n"; return; }
    vector<string> seq;
    preorderRec(root, seq);
    cout << "Preorder: ";
    printSequence(seq);
}

void DepartmentTree::displayPostorder() const {
    if (isEmpty()) { cout << "The department tree is empty.\n"; return; }
    vector<string> seq;
    postorderRec(root, seq);
    cout << "Postorder: ";
    printSequence(seq);
}

void DepartmentTree::displayLevelOrder() const {
    if (isEmpty()) { cout << "The department tree is empty.\n"; return; }
    vector<string> seq;
    queue<const DeptNode*> q;
    q.push(root);
    while (!q.empty()) {
        const DeptNode* cur = q.front(); q.pop();
        seq.push_back(cur->name);
        for (size_t i = 0; i < cur->children.size(); i++) q.push(cur->children[i]);
    }
    cout << "Level-order: ";
    printSequence(seq);
}

void DepartmentTree::displayStatistics() const {
    if (isEmpty()) {
        cout << "The department tree is empty.\nTotal departments: 0\nLeaves: 0\nHeight: N/A\n";
        return;
    }
    int leaves = 0;
    for (size_t i = 0; i < all.size(); i++)
        if (all[i]->children.empty()) leaves++;
    cout << "Total departments: " << all.size() << "\n";
    cout << "Leaves: " << leaves << "\n";
    int height = 0;
    for (size_t i = 0; i < all.size(); i++)
        if (all[i]->depth > height) height = all[i]->depth;
    cout << "Height: " << height << "\n";
}

void promptAddDepartment(DepartmentTree& t) {
    string name, parent, err;
    cout << "Enter new department name: ";
    getline(cin, name);
    if (!t.isEmpty()) {
        cout << "Enter parent department: ";
        getline(cin, parent);
    }
    if (t.addDepartment(name, parent, err))
        cout << "Department '" << trim(name) << "' added" << (t.size() == 1 ? " as the root.\n" : ".\n");
    else
        cout << "Error: " << err << "\n";
}

void promptSearchDepartment(const DepartmentTree& t) {
    cout << "Enter department name to search: ";
    string name;
    getline(cin, name);
    t.searchDepartment(name);
}
