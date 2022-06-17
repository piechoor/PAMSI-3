#define BOARD_SIZE 3
#define ALERT_TIME 2000
#define WINNING_LENGHT 3

//FOR GRAPHS
#define START_NODE 0 //node from which we measure distances to other nodes
#define IS_DIRECTED true //specifies if graphs are directed
#define NO_GRAPHS_TESTED 100 //number of graphs tested in 1 cycle

#define MAX_NODE_VAL 100 //maximum value of a node
#define MAX_DIST 9*MAX_NODE_VAL //number used as infinity value
#define RESULTS_FILE "graph_distances.txt"