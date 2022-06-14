#pragma once

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "settings.hh"

// General class for graphs

class Graph {
    protected:
        int edges, vertices, start_node;
        int density; //number of percents
        bool directed; //if graph is directed

    public:
        int get_edges() {return this->edges;}
        int get_vertices() {return this->vertices;}

        // General and specific constructors
        Graph();
        Graph(int no_vertices, int start_node, float graph_density);
};