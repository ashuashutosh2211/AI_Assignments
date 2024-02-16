Path Search Algorithms Comparison
This code demonstrates and compares various path search algorithms, including Breadth-First Search (BFS), Depth-First Search (DFS), Iterative Deepening, Uniform Cost Search (UCS), Greedy Search, A* Search, and Hill Climbing. It measures the average number of steps taken by each algorithm to solve a given problem.

Overview
BFS: Implements Breadth-First Search to explore nodes level by level.
DFS: Implements Depth-First Search to explore as deeply as possible along each branch before backtracking.
Iterative Deepening: Performs a series of Depth-First Searches with increasing depth limits.
UCS: Implements Uniform Cost Search, exploring nodes with the lowest path cost first.
Greedy Search: Uses Greedy Search with a heuristic function to guide exploration.
A Search*: Implements A* Search with a heuristic function for optimal pathfinding.
Hill Climbing: Utilizes Hill Climbing for local search and optimization.
Running the Code
Compilation: Compile the code using a C++ compiler. For example, you can use g++ to compile it.

Copy code
g++ -o path_search path_search.cpp
Execution: Run the compiled program.

bash
Copy code
./path_search
Input: The program will prompt you for input. Enter the following:

n: The number of elements in the array.
v: The elements of the array (space-separated).
Results: The program will calculate and display the average number of steps for each search algorithm over multiple random problem instances.

Notes
You can control the number of iterations and randomness by modifying the loop inside the main function.
The code uses various data structures like queues, stacks, and priority queues to implement different search algorithms.
The heuristic_function1 and heuristic_function2 functions are used for heuristic calculations in Greedy Search and A* Search, respectively.
Feel free to customize and extend this code as needed for your specific use case.

