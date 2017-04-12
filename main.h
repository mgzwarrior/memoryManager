const int numDimensions = 5;

struct Node
{
    Node *left;     // Leftward facing pointer
    Node *right;    // Rightward facing pointer
    Node *up;       // Upward facing pointer
    Node *down;     // Downward facing pointer
    int position;   // Numerical position of each Node in graph
};

class Graph
{
    public:
        Node* graph[numDimensions][numDimensions];
        Graph();
        void stringify();
        bool exists();
        void deleteRandomNode();
};
