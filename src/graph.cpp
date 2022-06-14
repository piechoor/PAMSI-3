#include "graph.hh"

Graph::Graph() {
    //General constructor setting all values to zero
    this->edges=0;
    this->vertices=0;
    this->start_node=0;
    this->density=0;
    this->directed=false;
}

Graph::Graph(int no_vertices, int start_node, float graph_density) {
    //Constructor setting all values as specified in the parameters
    this->edges = 0; //nodes are counted while filling a graph
    this->vertices = no_vertices;
    this->start_node = start_node;
    this->density = graph_density;
    this->directed=false; //if directed is specified in inherited classes
}