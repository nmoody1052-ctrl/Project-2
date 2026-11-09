// Purpose: Declare the interactive 

#ifndef CAMPUS_MENU_H
#define CAMPUS_MENU_H

#include <iosfwd>

class CampusGraph;
class DepartmentTree;
class Facility;

void runMenu(const CampusGraph& graph, const Facility& facilities,
             DepartmentTree& departments, bool milestone,
             std::istream& in, std::ostream& out);

#endif
