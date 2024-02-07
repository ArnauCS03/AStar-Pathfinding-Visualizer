# A* Pathfinding Visualizer
A* algorithm in c++ visulaized in the terminal with colors. Additionally you can create your own maze.

---

This project includes code from the original work by LukeProducts.

## Credits

**AStar Pathfinding Cpp Implementation**

- **Author:** LukeProducts
- **GitHub Repository:** [LukeProducts/AStar-Pathfinding-Cpp](https://github.com/LukeProducts/AStar-Pathfinding-Cpp)

**Maze Generator**
- **Website** https://www.dcode.fr/maze-generator


## Description

This project aims to visualize the A* pathfinding algorithm in a terminal environment, with this key features:
- Create a maze distribution with a start and finish point.
- Witness the algorithm in action as it displays the shortest path on the terminal.
- Modify the color code of the terminal with ANSI scape sequence to indicate the shortest path.
 
- The project has two main programs:


    `mainDefault` has a predefined maze

    `mainCustom`  can read mazes from .txt files

    You can create your own maze!
    1. Modify or create another file inside the `mazes` folder. Name it:  **maze**X  where X is a number.
    2. Specify in the first line the number of rows and columns, separated by a space.
    3. Starting in a new line, the actual maze. The walls with the character #, and don't forget to include a start position `s` and goal position `g`.

- The A* algorithm and functionalities are in `AStar.hh` 

- The black cells are the walkable paths and the gray the walls.


## Getting Started

How to use this project: 
- Download all the files
- Open a terminal 
- Run these commands to see the visualitzation:

`make compile` 

`make runDefault`   or   `make runCustom1`  (the number specifying the number of the maze txt file)


Disclaimer:
- The maze10.txt may take 6 seconds to run, and the width of the maze is huge, on some screens my appear cutted.

Extra functionality:
- If you want to allow diagonal moves, you can set the boolean to true in the main files. (Recommended check the maze3.txt)



