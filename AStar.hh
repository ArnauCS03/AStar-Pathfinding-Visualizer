#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>


/*
  Determine the shortest path from s to g on a two-dimensional field called maze.
  Using the A* Pathfinding Algorithm to visualize the shortest path.
*/

/*
Copyright (c) 2022, LukeProducts
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#define BARRIER '#'      // Barrier marks non-walkable path (wall)
#define PENETRABLE ' '   // marks walkable terrain (empty/floor)
#define WALKABLE 0      
#define NOT_WALKABLE 1  


using namespace std;

using pos_type = vector<int>; 
using VI = vector<int>;

pos_type start_position;
pos_type end_position;


struct Node {
    vector<pos_type> path;    // saves the path to its origin
    pos_type position;

    double g = 0, h = 0, f = 0;

    Node(pos_type p): position(p), path{p} {} // has no parent node, store actual move action
       

    Node(const Node& c, pos_type p): position(p), path(c.path) {
        path.push_back(position); // the actual move action
    }
    
    bool operator==(const Node& other) { return position == other.position; }
    
    bool operator<(const Node& other) { return f < other.f; }
    
    bool operator>(const Node& other) { return f > other.f; }
};

class CompareNode {
public:
    bool operator()(const Node& a, const Node& b) {
        return -a.f > -b.f; // Negate the values for min-heap behavior
    }
};


class AStarResult {

    vector<vector<int>> defaultmaze;

public:

    vector<pos_type> path_went;

    AStarResult(const vector<pos_type>& m, const vector<vector<int>>& old) { 
        path_went = m; 
        defaultmaze = old; 
    }

    void print_maze_solution_path() {

        cout << endl << endl;

        int rowSize = defaultmaze.size();
        int colSize = defaultmaze[0].size();

        int startColor[] = {182, 244, 146};     // starting yellow of the path
        int endColor[] = {51, 139, 147};        // ending green of the path

        for (int i = 0; i < rowSize; ++i) {
            
            for (int j = 0; j < colSize; ++j) {
                
                vector<int> currentPosition = {i, j};
                
                auto it = find(path_went.begin(), path_went.end(), currentPosition); // check if currentPosition is in path_went
                
                if (it != path_went.end()) {
                    if (currentPosition == path_went[0]) {
            
                        // color using ANSI escape sequence
                        cout << "\033[48;2;75;130;255m" << " " << "\033[0m";  // Blue text for start symbol.

                        // \033 is the escape character, 48 means background color, ';' the separation, 2 the RGB mode, after <r>;<g>;<b>  m indicates end of escape sequence  
                        // "\033[0m" afterwards to reset the color
                    }
                    else if (currentPosition == path_went.back()) {
                        cout << "\033[48;2;255;0;55m" << " " << "\033[0m";  // goal in red
                    }
                    else {
                        int currentColor[3];
                        for (int k = 0; k < 3; ++k) {
                            currentColor[k] = startColor[k] + (endColor[k] - startColor[k])*(i * colSize + j) / (rowSize * colSize - 1); // linear interpolation
                        }     
                        cout << "\033[48;2;" << currentColor[0] << ";" << currentColor[1] << ";" << currentColor[2] << "m" << " " << "\033[0m"; // green path
                    }
                }
                else {
                    if (defaultmaze[i][j] == 1) cout << "\033[47m \033[0m";  // Barrier
                    else cout << "\033[48;2;30;30;30m" << " " << "\033[0m";  // penetrable 
                }
            }
            cout << endl;
        }
        cout << endl << endl;
    }
};


// find the node with the smallest f score, which means, it is located potentially nearest to the end Node
Node pop(priority_queue<Node, vector<Node>, CompareNode>& heap) {
    
    Node smallest_node = heap.top(); // Get the smallest Node
    heap.pop(); // Remove the smallest Node
    return smallest_node;
}


// calculate the h score, if the diagonals are allowed, uses Euclidean Distance (distance squared) if not Manhattan Distance
double calculateHeuristic(const pos_type& actualPosition, const pos_type& endPosition, bool allowDiagonals) {
    
    if (allowDiagonals) {
        return (pow(actualPosition[0] - endPosition[0], 2)) + (pow(actualPosition[1] - endPosition[1], 2));
    }
    else {
        return abs(actualPosition[0] - endPosition[0]) + abs(actualPosition[1] - endPosition[1]);
    }
}

// The algorithm
//   maze 2-dimensional integer list between 0 and 1, where (if WALKABLE = 0) 
//   and 1 (if NOT_WALKABLE = 1) symbolizes a barrier

AStarResult AStar(const vector<vector<int>>& maze, bool allow_diagonal_moves) {

    // create start and end node
    Node start_node{start_position}; // has no parent
    start_node.g = start_node.h = start_node.f = 0;

    Node end_node{end_position}; // has not parent
    end_node.g = end_node.h = end_node.f = 0;

    
    priority_queue<Node, vector<Node>, CompareNode> open_list;  // min heap, to store the best candidate of the adjacents, with smallest 'f'

    vector<Node> closed_list;  // for exploded Nodes

    // push start_node into open list in order to start inspecting its neighbours and spawning child Nodes
    start_node.f = -start_node.f;
    open_list.push(start_node);

    
    // stop condition is equal to the area of the maze, to be able to figure out whether it is possible to find the solution path or not
     
    int rowSize = maze.size();
    int colSize = maze[0].size();

    int outer_iterations = 0;
    int max_iterations = (rowSize * colSize)*2;

    // which squares to search
    vector<pos_type> adjected_squares{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    if (allow_diagonal_moves) { // if diagonal moves are allowed, we need to look further around the current parent node
        adjected_squares = vector<pos_type>{{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    }

    while (not open_list.empty()) {

        ++outer_iterations;

        if (outer_iterations > max_iterations) {
            cerr << "Could not find path to destination" << endl; 
            return AStarResult(vector<pos_type>{{}}, maze);
        }

        // get the current Node
        Node current_node = pop(open_list);
        closed_list.push_back(current_node);

        if (current_node.position == end_node.position) { // found the goal
            return AStarResult(current_node.path, maze);
        }

        //generate children

        vector<Node> children;

        for (const pos_type& new_position : adjected_squares) { // iterating through every square to cover all possible movement possibilities

            //get nodes new position
            pos_type node_position{current_node.position[0] + new_position[0], current_node.position[1] + new_position[1]};

            // check if in range of maze
            if (node_position[0] >= 0 and node_position[0] < rowSize and node_position[1] >= 0 and node_position[1] < colSize) {
                
                // if we're operating within walkable terrain
                if (maze[node_position[0]][node_position[1]] == WALKABLE) {
                    // create new node to inspect
                    Node new_node{current_node, node_position};

                    // add our new child to the childrens vector to be examined in the following
                    children.push_back(new_node);
                }
            }
        }

        // loop through every children
        for (Node& child : children) {
            // if child is on the closed list
            vector<Node> bad;
            for (const Node& closed_child : closed_list) {
                if (child == closed_child) bad.push_back(closed_child);
            }
            if (bad.empty()) { // child not explored, not in closed_list
                // create f, g and h scores
                child.g = current_node.g + 1;
                child.h = calculateHeuristic(child.position, end_node.position, allow_diagonal_moves);
                child.f = child.g + child.h;
                child.f = -child.f;

                open_list.push(child);
            }
        }
    }
    cerr << "Could not find path to destination" << endl;
    return AStarResult(vector<pos_type>{{}}, maze);
}


vector<VI> processMaze(const vector<string>& curr_maze) {
    int rowSize = curr_maze.size();
    int colSize = curr_maze[0].length();

    vector<vector<int>> res(rowSize, vector<int>(colSize));

    for (int i = 0; i < rowSize; ++i) {
        for (int j = 0; j < colSize; ++j) {
            if (curr_maze[i][j] == BARRIER) res[i][j] = NOT_WALKABLE;
            else if (curr_maze[i][j] == PENETRABLE) res[i][j] = WALKABLE;
            else if (curr_maze[i][j] == 's') {
                start_position = vector<int>{i, j};
                res[i][j] = WALKABLE;
            }
            else if (curr_maze[i][j] == 'g') {
                end_position = vector<int>{i, j};
                res[i][j] = WALKABLE;
            }
        }
    }
    return res;
}


vector<VI> processMazeFromFile() {
    int rows, cols;
    cin >> rows >> cols;  
    string line;
    getline(cin, line);     // ignore the first line

    vector<VI> maze(rows, VI(cols, 0));

    for (int row_index = 0; row_index < rows; ++row_index) {
        getline(cin, line);
        for (int col_index = 0; col_index < cols; ++col_index) {
            if (line[col_index] == BARRIER) maze[row_index][col_index] = 1;
            else if (line[col_index] == PENETRABLE) maze[row_index][col_index] = 0;
            else if (line[col_index] == 's') {
                start_position = vector<int>{row_index, col_index};
                maze[row_index][col_index] = 0;
            }
            else if (line[col_index] == 'g') {
                end_position = vector<int>{row_index, col_index};
                maze[row_index][col_index] = 0;
            }
        }
    }
    return maze;
}

