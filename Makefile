# COMPILATION

compile: mainDefault mainCustom

mainDefault: prepare_maze.cpp AStar.hh
	g++ -o mainDefault.exe prepare_maze.cpp AStar.hh


mainCustom: readmaze.cpp AStar.hh
	g++ -o mainCustom.exe readmaze.cpp AStar.hh


# EXECUTION

runDefault:
	./mainDefault.exe


runCustom%: mazes/maze%.txt
	./mainCustom.exe < $<



clean:
	rm -f *.o
	rm -f *.exe