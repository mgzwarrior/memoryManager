// CSC 314 - Operating Systems
// Assignment 0 - Memory Manager
// Created by: Matt Grant
// Last updated: 14 Sep. 2016
// For more explicit comments see the README file

#include <iostream>
#include <main.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Constructor for memory management graph
Graph::Graph()
{
    int count = 0;

    // Initializes graph and sets the position of each node
    for(int i = 0; i < numDimensions; i++)
    {
        for(int j = 0; j < numDimensions; j++)
        {
            graph[i][j] = new Node();
            graph[i][j]->position = count;
            count++;
        }
    }

    // Sets the edge pointers to their perspective nodes
    for(int i = 0; i < numDimensions; i++)
    {
        for(int j = 0; j < numDimensions; j++)
        {
            if(j == 0) // Sets left pointer to NULL if node is at the left edge of the graph
            {
                delete graph[i][j]->left;
                graph[i][j]->left = NULL;
                graph[i][j]->right = graph[i][j+1];
            }
            else if(j == (numDimensions - 1)) // Sets right pointer to NULL if node is at the right edge of the graph
            {
                delete graph[i][j]->right;
                graph[i][j]->right = NULL;
                graph[i][j]->left = graph[i][j-1];
            }
            else
            {
                graph[i][j]->left = graph[i][j-1];
                graph[i][j]->right = graph[i][j+1];
            }
            if(i == 0) // Sets up pointer to NULL if node is at the top edge of the graph
            {
                delete graph[i][j]->up;
                graph[i][j]->up = NULL;
                graph[i][j]->down = graph[i+1][j];
            }
            else if(i == (numDimensions - 1)) // Sets down pointer to NULL if node is at the bottom edge of the graph
            {
                delete graph[i][j]->down;
                graph[i][j]->down = NULL;
                graph[i][j]->up = graph[i-1][j];
            }
            else
            {
                graph[i][j]->up = graph[i-1][j];
                graph[i][j]->down = graph[i+1][j];
            }
        }
    }
}

// Outputs a visual representation of the graph's nodes and all of their edge pointers
void Graph::stringify()
{
    int count = 0;
    for(int i = 0; i < numDimensions; i++)
    {
        cout << "\n";
        for(int j = 0; j < numDimensions; j++)
        {
            if(graph[i][j] == NULL)
                cout << "Node " << count << " was deleted." << endl;
            else
            {
                cout << "Node " << graph[i][j]->position << ": ";
                if(graph[i][j]->left == NULL)
                    cout << "Left --> NULL, ";
                else
                    cout << "Left --> " << graph[i][j]->left->position << ", ";
                if(graph[i][j]->right == NULL)
                    cout << "Right --> NULL, ";
                else
                    cout << "Right --> " << graph[i][j]->right->position << ", ";
                if(graph[i][j]->up == NULL)
                    cout << "Up --> NULL, ";
                else
                    cout << "Up --> " << graph[i][j]->up->position << ", ";
                if(graph[i][j]->down == NULL)
                    cout << "Down --> NULL" << endl;
                else
                    cout << "Down --> " << graph[i][j]->down->position << endl;
            }
            count++;
        }
    }
    cout << "-------------------------------------------------" << endl;
}

// Tests if there are any nodes remaining in the graph
bool Graph::exists()
{
    for(int i = 0; i < numDimensions; i++)
    {
        for(int j = 0; j < numDimensions; j++)
        {
            if(graph[i][j] != NULL)
                return true;
        }
    }
    return false;
}

// Deletes a node and all pointers associated with that node given a random set of coordinates
void Graph::deleteRandomNode()
{
    int row = rand() % numDimensions;
    int col = rand() % numDimensions;

    // Return if node has already been deleted
    if(graph[row][col] == NULL)
    {
        cout << "Node at row: " << row << ", column: " << col << " was already deleted." << endl;
        cout << "-------------------------------------------------" << endl;
        return;
    }

    // Delete random node
    cout << "Delete node " << graph[row][col]->position << endl;
    cout << "-------------------------------------------------" << endl;
    if(graph[row][col]->left != NULL)
    {
        Node *l = graph[row][col]->left;
        graph[row][col]->left = NULL;
        l->right = NULL;
    }
    if(graph[row][col]->right != NULL)
    {
        Node *r = graph[row][col]->right;
        graph[row][col]->right = NULL;
        r->left = NULL;
    }
    if(graph[row][col]->up != NULL)
    {
        Node *u = graph[row][col]->up;
        graph[row][col]->up = NULL;
        u->down = NULL;
    }
    if(graph[row][col]->down != NULL)
    {
        Node *d = graph[row][col]->down;
        graph[row][col]->down = NULL;
        d->up = NULL;
    }
    delete graph[row][col];
    graph[row][col] = NULL;

    // Delete nodes with no adjacent edges
    for(int i = 0; i < numDimensions; i++)
    {
        for(int j = 0; j < numDimensions; j++)
        {
            if(graph[i][j] != NULL)
            {
                if(graph[i][j]->left == NULL && graph[i][j]->right == NULL && graph[i][j]->up == NULL && graph[i][j]->down == NULL)
                {
                    delete graph[i][j];
                    graph[i][j] = NULL;
                }
            }
        }
    }
}

// Main method to test the functionality of the memory manager
int main()
{
    srand(time(NULL));
    Graph g;
    g.stringify();
    int count = 0;
    while(g.exists())
    {
        g.deleteRandomNode();
        g.stringify();
        count++;
    }
    cout << "Finished in " << count << " steps." << endl;
    cout << "-------------------------------------------------" << endl;
}
