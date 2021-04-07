# Boğaziçi University - Principles of Artificial Intelligence CMPE540 class Project 1
### BFS (Breadth First Search), DFS (Depth First Search), UCS (Uniform Cost Search), A STAR, A* C++ implementations

Original framework implementation in C++ is written by Emre Ugur.

He adapted the project from CS188 Berkeley course material.

BFS, DFS, UCS and A* Algorithms are implemented in C++ for path finding, collecting foods and visiting corners in Pacman-like Maze layouts.

![pic2](https://user-images.githubusercontent.com/67103746/113912072-669f0500-97e3-11eb-9487-957367ec6293.jpg)

### Running
- <./p1 -help> prints the help section, which looks like:
- ![pic3](https://user-images.githubusercontent.com/67103746/113912600-ff358500-97e3-11eb-8d52-697cf616a34c.jpg)


### Example Runs
- ./p1 -p eat-food -l layouts/bigMaze.lay -w calm -s DFS -u 200
- ./p1 -p eat-food -l layouts/bigMaze.lay -w calm -s BFS -u 200
- ./p1 -p eat-food -l layouts/mediumMaze.lay -w calm -s UCS -u 500
- ./p1 -p eat-food -l layouts/bigMaze.lay -w calm -s A_STAR -u 100
- ./p1 -p visit-corners -l layouts/tinyCorners.lay -w calm -s BFS -u 100
- ./p1 -p visit-corners -l layouts/mediumCorners.lay -w calm -s UCS -u 100
- ./p1 -p visit-corners -l layouts/tinyCorners.lay -w calm -s A_STAR -u 100
- ./p1 -p eat-all-foods -l layouts/trickySearch.lay -w calm -s A_STAR -u 100
