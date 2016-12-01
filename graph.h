

#define MAXFIELDLEN 80


//The structure for nodes that hold information for each place. 
typedef struct place_node{
	int node_num;
	char place_name[MAXFIELDLEN];
	char country[MAXFIELDLEN];
	int outdoors;
	int cultural;
}place_node;

//MAJOR ISSUES CAUSES SEG FAULT FOR NO REASON I CAN FIND
//void initialise_space(int** graph, int** pred_graph, place_node* places_list, int num_nodes);


//Takes the matrix that stores all the costs information as well as the information about destination, source and the cost weighting
/*
Inputs:
int** graph - the 2d array that holds all the cost information. This will begin as an empty array of allocated space and will be filled in
int source - the number id of the place that you are travelling from
int destination- the number id of the place that one is travelling to
int weight - the wieght of the edge travelling from source to destination

after this has run for every line in the costs file from the main driver program, you should have a 2d array with all costs for every edge directly connected to other nodes
*/
void create_graph(int** graph, int** pred_graph, int source, int destination, int weight);


//takes the list that places are stored in and all the attributes for a new node and places it in the list
/*
Inputs:
place_node* places_list - This is the list for the main driver program that will contain all the informaiton for each location
int node_num - the identifier for each node. This number should be unique
char place[MAXFIELDLEN] - the name of the place for the nodes information
char country[MAXFIELDLEN] - the name of the country for the nodes information
int culturla - defines if there are cultural aspects in the place for the nodes information
int outdoors - defines if there are outdoors activites in the place for the nodes information

after this has run for every line in the places file form the main driver, you should have an array filled with information for every place that is available to be visited
*/
void create_places_list(place_node* places_list,int node_num, char place[MAXFIELDLEN], char country[MAXFIELDLEN], int cultural, int outdoors);


//used to fill out the graph with distance from every node to every other node
/*
Inputs:
int** graph - the graph that contains information for how muhc it costs to travel from one location to another
int num_nodes - the number of places that are available to visit in total

once this function has run, the graph should be filled out with total weights from every node to every other node. This includes travelling from point A to pint C through point B
*/
void fill_graph(int** graph, int** pred_graph, int num_nodes);

/*
Inputs:
places_list - the list of all places avilable to travel to
continent - the place that the user wants to travel to
cultural - if the user is intetrested in cultural aspects or not
outdoors - if the user is interested in outdoors aspects or not
num_nodes - number of palces that are available to travel to

returns a list of locations id numbers that are relevant to the users preferences in palces to travel to
*/
int* relevant_place_search(place_node* places_list, char continent[MAXFIELDLEN], int cultural, int outdoors, int num_nodes);

/*
Inputs:
graph - the information of the costs to travel from place A to palce B
palces_list - the inforamtion on alkl places that are available to travel to
num_nodes - the number of places that are available tot ravel to
min_cost - the minimum cost place to be able to travel to, a pointer so that the main function can have this value
cheapest_place - the palce that is cheapest to travel to, a pointer so that the main can have this value
user_start - the palce that the user is going to travel from in string form
place_from - the place that the is going to travel from in int form, a pointer so that this can be available in the main function
places_to_go - the palces that are relevant for the users inputs as defined earlier

Output:
return the value of the places that is cheapest to travel to

Finds the place that is cheapest to travel to depending on the users inputs and that cost
*/
int find_cheapest_place(int** graph, place_node* places_list, int num_nodes, int* min_cost, int* cheapest_place, char user_start[MAXFIELDLEN], int* place_from, int* places_to_go);







//testing method for printing out the 2d matrix
/*
Inputs:
int** matrix - this is the graph that we want to print out in a visual manner to be able to see
int num_nodes - the number of nodes that are in the graph

This will print to stdout a table with all the weights for travelling from 1 node to another
*/
void print_matrix(int** matrix,int num_nodes);
