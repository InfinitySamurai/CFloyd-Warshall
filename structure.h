//The structure for nodes that hold information for each place. 
typedef struct place_node{
	int node_num;
	char place_name[MAXFIELDLEN];
	char country[MAXFIELDLEN];
	int outdoors;
	int cultural;
}place_node;