#include "graph_list.hh"

Graph_List::Graph_List(const char *file_name) {
    std::ifstream txt_file;
    txt_file.open(file_name);
    //giving an error if the file couldnt be opened
    if(!txt_file) {
        std::cerr << "File error - file could not be opened";
        exit(1);
    }

    int temp_from, temp_to, temp_weight; //temporary variables
    this->density = 100; //arbitrary number
    this->directed = false; //file specifies that, it doesnt really matter
    // Getting basic information from a file
    txt_file >> this->edges >> this->vertices >> this->start_node;

    this->dist_arr = new int[this->vertices]; //array with distances to each node

    //Creating an empty list
    this->adj_list = new AdjList[this->vertices];
    for (int i=0; i<this->vertices; ++i)
        adj_list[i].head = NULL;

    // adding edges as specified in a file till it ends
    while(!txt_file.eof()) {
        txt_file >> temp_from >> temp_to >> temp_weight;
        addEdge(temp_from, temp_to, temp_weight);
    }
}

Graph_List::Graph_List(int no_vertices, int start_node, float graph_density, bool if_directed) {
    //Setting basic values
    this->edges = 0;
    this->vertices = no_vertices;
    this->start_node = start_node;
    this->density = graph_density;
    this->directed = if_directed;
    this->dist_arr = new int[no_vertices]; //array with distances to each node
    
    //Creating a blank list of adj_lists, each index of that list is a branch for
    //nodes connected to the node of given index
    this->adj_list = new AdjList[this->vertices];
    for (int i=0; i<this->vertices; ++i)
        adj_list[i].head = NULL; //each head is NULL at the beggining

    //filling the list randomly with given density
    this->fillRandom();
}

//Creating node to destination node with a given edge weight beetwen that nodes
//Returns a pointer to the created node
Node* Graph_List::createNode(int dest_node, int weight) {
    Node *newNode = new Node;
    newNode->dest = dest_node;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

//Putting an edge to the adj_list between specified nodes with a given weight
void Graph_List::addEdge(int src_node, int dest_node, int edge_weight) {
    Node *newNode = createNode(dest_node, edge_weight);
    newNode->next = adj_list[src_node].head;
    adj_list[src_node].head = newNode;
    this->edges++; //adding edge to the counter
}

void Graph_List::fillRandom() {
    srand((unsigned)time(NULL));
    //determining number of nodes needed to be filled with density of the graph
    int nodesToFill = this->density*vertices*(vertices-1)/100;
    int common_val; //temp variable for undirected graphs
    //if directed all edges are random
    if (directed) {
        for (int i=0; i<this->vertices; ++i) {
            for (int j=0; j<this->vertices; ++j) {
                if (this->edges>=nodesToFill) break; //breaking if density is correct
                if (i==j) continue; //keeping 0 distance for identical node to node
                addEdge(i,j,(rand() % MAX_NODE_VAL)); //adding an edge with random value
            }
        }
    }
    //if undirected edges i->j and j->i are the same
    else if (!directed) {
        for (int i=0; i<this->vertices; ++i) {
            for (int j=0; j!=i; ++j) {
                if (this->edges>=nodesToFill) break; //breaking if density is right
                common_val = rand() % MAX_NODE_VAL; //determining value
                //adding identical edges
                addEdge(i,j,common_val);
                addEdge(j,i,common_val);
            }
        }
    }
}

//Displays a list in a terminal using pseudo-graphical form
void Graph_List::display() {
    for (int i=0; i<this->vertices; ++i) {
        Node* ptrNode = adj_list[i].head;
        std::cout << "Node " << i << ".\t";
        while (ptrNode) {
            std::cout << "->" << ptrNode->dest << "[W=" 
                      << ptrNode->weight << "]";
            ptrNode = ptrNode->next;
        }
        std::cout << std::endl;
    }
}

void Graph_List::BellmanFord() {
    Node* ptrNode; //temporary pointer

    //initializing distances with infinity-like value
    for (int i=0; i<this->vertices; ++i)
        this->dist_arr[i] = MAX_DIST;
    this->dist_arr[this->start_node] = 0; //distance to starting node is  always 0

    //relaxing edges vertices-1 times
    for (int k=1; k<this->vertices; ++k) {
        for (int i=0; i<this->vertices; ++i) {
            ptrNode = adj_list[i].head;
            while (ptrNode) {
                if (this->dist_arr[i] + ptrNode->weight < this->dist_arr[ptrNode->dest])
                    this->dist_arr[ptrNode->dest] = this->dist_arr[i] + ptrNode->weight;
                ptrNode = ptrNode->next;
            }
        }
    }
}

void Graph_List::saveResults(const char *file_name) {
    std::ofstream Results(file_name, std::ios_base::app);

    for (int i=0; i<this->vertices; ++i) {
        Results << this->start_node << " -> " << i << "\tdist: " << dist_arr[i] << "\n";
    }
    Results << std::endl;

    Results.close();
}

//Destructor frees all memory allocated by a graph instance
Graph_List::~Graph_List() {
    for (int i=0; i<this->vertices; ++i) {
        Node* current = adj_list[i].head;
        while(current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    delete [] this->adj_list;
    delete [] this->dist_arr;
}