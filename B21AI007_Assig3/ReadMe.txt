Resolution Refutation Algorithm for Propositional Logic

This C++ program implements the resolution refutation algorithm for propositional logic. The algorithm attempts to prove or disprove a query by converting the knowledge base (KB) and the negation of the query into conjunctive normal form (CNF) and applying the resolution refutation steps.

Input Format
The program expects input in the following format:

The first line contains two integers, 'n' and 'm'. 'n' is the number of formulas in the KB, and 'm' is the mode (1 for verbose output, 0 for concise output).
The next 'n' lines contain one formula per line.
The last line contains the query that needs to be proved.

Code Structure
CNF Class: Responsible for converting a given propositional logic formula to CNF. It includes methods for adding brackets, removing implication and biconditional, moving negations inward, distributing OR over AND, and getting each clause.

Node Class: Represents a node in the search tree. Each node contains a knowledge base, an operation (used for tracking the resolution steps), and children nodes.

Conversion to CNF and Knowledge Base Handling: The convert_to_kb function converts a vector of propositional logic formulas into a knowledge base in CNF. It also adds the negation of the query to the knowledge base.

BFS Resolution Refutation (Uninformed Search): The resolution_refutation_bfs function performs resolution refutation using breadth-first search. It explores nodes in a breadth-first manner, attempting to resolve clauses and adding new clauses to the knowledge base.

Heuristics and Greedy Resolution Refutation (Informed Search): The heuristics function calculates a heuristic value for a knowledge base. The resolution_refutation_with_heuristics function uses this heuristic to perform a greedy search, exploring nodes with lower heuristic values first.

Path Retrieval and Output: The get_path function retrieves the path from the root to the goal state. The print_steps function prints the resolution steps. The count_steps function counts the number of steps taken.

Main Function: The main function takes user input and executes the uninformed and informed searches, printing the results, steps, and time taken for each.

Dependencies
The code doesn't have external dependencies beyond a standard C++ compiler.

Notes
The timing measurement is done using clock(), which might not be the most accurate method.