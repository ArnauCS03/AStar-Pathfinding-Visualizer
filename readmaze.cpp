#include "AStar.hh"


int main() {   

    AStarResult result = AStar(processMazeFromFile(), false); // maze, allowDiagonals       

    result.print_maze_solution_path(); 
}
