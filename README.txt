CSCE 2110 Project 2 - 
Loads campus data files and lets a user search facilities (customhash table), explore a building graph (BFS), and browse a department tree.

To build input 'Make'

To run input ./campus 

Folders and what they include 
data - input files
include - header files (.h)
src - implementation files (.cpp)
testdata - own test files

--------------------------------------------

We’re building a C++ program that helps users find places on campus. It reads four text files that contain information about buildings, walkways, facilities, and departments.

A custom hash table; finds a facility by its ID, such as F004.

A graph; shows which buildings are connected. Breadth-first search (BFS) finds the buildings you can reach from a starting point.

A tree; shows how colleges and departments are organized.

The final version adds shortest walking routes, searches by facility name or category, and summary reports.


