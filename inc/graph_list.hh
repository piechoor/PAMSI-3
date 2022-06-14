#pragma once

#include "graph.hh"

struct Node {
    int dest, weight;  //dest is an idx of a node
                       //weight is value of an edge between that node and the nex one
    struct Node *next; //pointer to the next node
};

struct AdjList {
    struct Node *head; //head is a pointer to the first node
};

class Graph_List : public Graph {
    int *dist_arr;

    protected:
        struct AdjList *adj_list; //pointer to the list consisting of node-number
                        //of elements, idx of each indicates 
                        //node idx which we refer to

        //support function for addEdge(...)
        Node* createNode(int dest_node, int weight); 
        //Function placing edges in the adjacency list
        void addEdge(int src_node, int dest_node, int edge_weight);
        

    public:
        Graph_List(const char *file_name); //creates graph from a specified file
        Graph_List(int no_vertices, int start_node, float graph_density, bool if_directed);
        
        void fillRandom(); //filling list with random values
        void display(); //displays adjacency list
        void BellmanFord(); //shortest path algorithm
        int* get_distances() {return this->dist_arr;} //returns pointer to the distances array
        void saveResults(const char *file_name); //saving distances array to a file

        ~Graph_List();
};