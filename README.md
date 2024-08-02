# A* Pathfinding Visualizer
Visualization of the algorithm in the terminal with color output, implemented in C++. Providing an interactive and educational demonstration of the A* functionality.

This project includes code from the original work by [LukeProducts](https://github.com/LukeProducts).

---

## Credits

**AStar Pathfinding Cpp Implementation**

- **Author:** LukeProducts
- **GitHub Repository:** [LukeProducts/AStar-Pathfinding-Cpp](https://github.com/LukeProducts/AStar-Pathfinding-Cpp)

**Maze Generator**
- **Website** https://www.dcode.fr/maze-generator<br><br>

---

## Description

This project aims to visualize the A* pathfinding algorithm in a terminal environment, with this key features:
- Create a maze distribution with a start and finish point.
- Witness the algorithm in action as it displays the shortest path on the terminal.
- Modify the color code of the terminal with ANSI scape sequence to indicate the shortest path.<br><br>
   
- The project has two main programs:

    `mainDefault` has a predefined maze

    `mainCustom`  can read mazes from .txt files located in the folder mazes<br><br>

    You can create your own maze!
    1. Modify or create another file inside the `mazes` folder. Name it:  **maze**X  where X is a number.
    2. Specify in the first line the number of rows and columns, separated by a space.
    3. Starting on a new line, the actual maze. The walls with the character `#`, and don't forget to include a start position `s` and goal position `g`.<br><br>

- The A* algorithm and functionalities are in `AStar.hh` 

- The black cells are the walkable paths and the gray the walls.<br><br>


## Getting Started

How to use this project: 
- Download all the files
- Open a terminal 
- Run these commands to see the visualitzation:

`make compile` 

`make runDefault`   or   `make runCustom1`  (the number specifying the number of the maze txt file)<br><br>


Disclaimer:
- The maze10.txt may take 6 seconds to run, and the width of the maze is huge, on some screens my appear cutted.<br><br>

Extra functionality:
- If you want to allow diagonal moves, you can set the boolean to true in the main files. (Recommended check the maze3.txt)<br><br>
<br><br>
---

## Screenshots
<br><br>
![Screenshot from 2024-02-08 01-00-20](https://github.com/ArnauCS03/AStar-Pathfinding-Visualizer/assets/95536223/2d2d3a8c-6c4a-425f-912f-991c11c8fe3c)<br><br>

![Screenshot from 2024-02-08 00-58-48](https://github.com/ArnauCS03/AStar-Pathfinding-Visualizer/assets/95536223/c203fee1-7690-4a83-823d-c5b5559c629f)<br><br>

![Screenshot from 2024-02-08 01-01-06](https://github.com/ArnauCS03/AStar-Pathfinding-Visualizer/assets/95536223/cb8d83bd-273b-4be1-88c2-641c46868cfb)<br><br><br>



