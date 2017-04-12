###Memory Manager
Created by: Matt Grant
Last updated: 12 Apr. 2017

This program creates a 5x5 grid of nodes.  Each node has four edge members, left, right, up, and down, which connect to it's neighboring nodes, as well as a position member, which holds the numerical position of the node in the graph.  Every edge is bidirectional and is implemented as a node pointer.  After initializing the memory manager grid, the program deletes a node at random, including the pointers going to and from that node, and continues to do so until the grid is empty.  If at any point, a node has no edges connecting it to another node, then that node is deleted as well.

To test the program:
1. In the root project directory, compile the program using:

make

2. Run the program while simultaneously checking for memory leaks using:

valgrind --leak-check=full ./main

*Optional: for more detail about memory leaks, add the '-v' flag to the valgrind command to use verbose mode.

Main Program (line 181):
- 184: Initialize random seed
- 185: Create the memory manager graph by invoking the Graph constructor
- 186: Output a visual representation of the initial graph, including edges
- 187: Create a variable to count the number of times the 'deleteRand()' method is called
- 188: Loop through the graph while nodes continue to exist
- 190: Call the 'deleteRand()' method, which deletes a node at a random set of coordinates on the graph
- 191: Output a visual representation of the graph after each call of 'deleteRand()'
- 192: Increment the counter for each call of the 'deleteRand()' method
- 194: Output the count of how many 'deleteRand()' calls were needed to clear the graph (for testing purposes)
- 195: Output "DONE!" to signal the end of the program

Graph Constructor (line 16):
- 18: Create a variable to number each node in the graph
- 19-27: Initialize the graph with blank nodes and number them accordingly
- 28-68: Link the nodes in the graph together using the edge member pointers of each node

Graph 'stringify()' method (line 72):
- 74: Create a variable to keep track of the number of each node in the graph
- 75-104: Parse the graph and print out the state of each node, including the edge connections of each node pointer
- 105: Output a line split to indicate the end of the graph

Graph 'exists()' method (line 110):
- 112-119: Parse the graph and if any position is not NULL return true to indicate that the graph is not yet empty
- 120: Return false, indicating that all positions in the graph are NULL

Graph 'deleteRand()' method (line 125):
- 127-128: Generate random integers, which correspond to the row and column coordinates in the graph
- 129-130: Output the row and column values to manually check that the proper node(s) and edges were deleted
- 131-134: Check if the node at the generated coordinates was already deleted; return if true
- 136-159: Set the pointers in the node at [row][col] to NULL
- 160: Delete the node at [row][col] from the heap
- 161: Set the value at [row][col] in the graph to NULL
- 162: Indicate that the random node at [row][col] was deleted
- 163-178: Delete any nodes that have no edges connecting it after the deletion of the random node, and set that location in the graph to NULL
