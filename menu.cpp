// Purpose: Read full-line choices 

#include "Menu.h"
#include "CampusGraph.h"
#include "DepartmentTree.h"
#include "Facilities.h"
#include "utility.h"

#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

enum class Action {
    AllFacilities, FacilityId, FacilityName, FacilityCategory,
    CampusMap, GraphDegrees, Reachable, ShortestPath,
    AddDepartment, FindDepartment, Hierarchy, Preorder, Postorder, LevelOrder,
    DepartmentStats, CategoryReport, ConnectivityReport
};

struct MenuItem {
    Action action;
    const char* label;
    bool inMilestoneOne;
};

// Rows follow Final menu order.
constexpr MenuItem kOptions[] = {
    {Action::AllFacilities, "View all facilities", true},
    {Action::FacilityId, "Search facility by ID", true},
    {Action::FacilityName, "Search facility by name", false},
    {Action::FacilityCategory, "Search facility by category", false},
    {Action::CampusMap, "View campus graph", true},
    {Action::GraphDegrees, "Display graph counts and degrees", true},
    {Action::Reachable, "Find reachable buildings (BFS)", true},
    {Action::ShortestPath, "Find shortest path (BFS)", false},
    {Action::AddDepartment, "Add department", true},
    {Action::FindDepartment, "Search department", true},
    {Action::Hierarchy, "Display department hierarchy", true},
    {Action::Preorder, "Preorder traversal", true},
    {Action::Postorder, "Postorder traversal", false},
    {Action::LevelOrder, "Level-order traversal", false},
    {Action::DepartmentStats, "Department statistics", false},
    {Action::CategoryReport, "Facility category report", false},
    {Action::ConnectivityReport, "Graph connectivity report", false},
};

// Read one complete name and return to the menu if it is blank.
bool readName(const char* prompt, std::istream& in, std::ostream& out, std::string& name) {
    out << prompt << '\n';
    if (!std::getline(in, name)) {
        return false;
    }

    name = text::trim(name);
    if (name.empty()) {
        out << "Error: name cannot be blank.\n";
        return false;
    }
    return true;
}

// Ask only for the inputs  by the selected operation.
void runAction(Action action, const CampusGraph& graph, const FacilityDatabase& facilities,
               DepartmentTree& departments, std::istream& in, std::ostream& out) {
    using Field = FacilityDatabase::Field;
    using Traversal = DepartmentTree::Traversal;

    std::string name;
    std::string other;
    switch (action) {
        case Action::AllFacilities:
            facilities.printAll(out);
            break;
        case Action::FacilityId:
            out << "Facility ID:\n";
            if (std::getline(in, name)) {
                facilities.printById(name, out);
            }
            break;
        case Action::FacilityName:
            if (readName("Facility name:", in, out, name)) {
                facilities.printMatches(name, Field::Name, out);
            }
            break;
        case Action::FacilityCategory:
            if (readName("Facility category:", in, out, name)) {
                facilities.printMatches(name, Field::Category, out);
            }
            break;
        case Action::CampusMap:
            graph.printGraph(out);
            break;
        case Action::GraphDegrees:
            graph.printDegrees(out);
            break;
        case Action::Reachable:
            if (readName("Start building:", in, out, name)) {
                graph.printReachable(name, out);
            }
            break;
        case Action::ShortestPath:
            if (readName("Start building:", in, out, name)
                && readName("Destination building:", in, out, other)) {
                graph.printShortestPath(name, other, out);
            }
            break;
        case Action::AddDepartment:
            if (readName("New department name:", in, out, name)
                && (departments.empty() || readName("Parent department:", in, out, other))) {
                const std::string error = departments.add(name, other);
                if (error.empty()) {
                    out << "Added department: " << name << '\n';
                } else {
                    out << "Error: " << error << ".\n";
                }
            }
            break;
        case Action::FindDepartment:
            if (readName("Department name:", in, out, name)) {
                departments.printSearch(name, out);
            }
            break;
        case Action::Hierarchy:
            departments.printHierarchy(out);
            break;
        case Action::Preorder:
            departments.printTraversal(Traversal::Preorder, out);
            break;
        case Action::Postorder:
            departments.printTraversal(Traversal::Postorder, out);
            break;
        case Action::LevelOrder:
            departments.printTraversal(Traversal::LevelOrder, out);
            break;
        case Action::DepartmentStats:
            departments.printStatistics(out);
            break;
        case Action::CategoryReport:
            facilities.printCategoryReport(out);
            break;
        case Action::ConnectivityReport:
            graph.printConnectivity(out);
            break;
    }
}

}

// Use a fresh string stream  bad line cannot poison later input.
void runMenu(const CampusGraph& graph, const FacilityDatabase& facilities,
             DepartmentTree& departments, bool milestoneOne,
             std::istream& in, std::ostream& out) {
    std::vector<MenuItem> menu;
    for (const MenuItem& item : kOptions) {
        if (!milestoneOne || item.inMilestoneOne) {
            menu.push_back(item);
        }
    }

    while (in) {
        out << "\nSmart Campus Navigation - " << (milestoneOne ? "Milestone 1" : "Final") << '\n';
        for (std::size_t i = 0; i < menu.size(); ++i) {
            out << i + 1 << ". " << menu[i].label << '\n';
        }
        out << "0. Exit\nChoice:\n";

        std::string line;
        if (!std::getline(in, line)) {
            break;
        }

        int choice = 0;
        char leftover;
        std::istringstream parsed(line);
        if (!(parsed >> choice) || (parsed >> leftover) || choice < 0
            || static_cast<std::size_t>(choice) > menu.size()) {
            out << "Error: enter a whole menu number from 0 to " << menu.size() << ".\n";
            continue;
        }
        if (choice == 0) {
            break;
        }

        runAction(menu[static_cast<std::size_t>(choice - 1)].action, graph, facilities,
                  departments, in, out);
    }
    out << "Goodbye.\n";
}
