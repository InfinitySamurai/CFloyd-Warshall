#include "holiday.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

// for every line in a file, it gets assigned to line
char line[MAXLINELEN];

//files that are going to be read in
FILE *cost_file;
FILE *place_file;

//data to be put into nodes that will be read in from file
char place[MAXFIELDLEN], country[MAXFIELDLEN];
char tempCult, tempOutdoor;
int cultural, outdoors, num_nodes, node_num;

int i = 0, j;
//the two graphs that are going to be used. One for costs between every node
//and another for the paths taken from one place to another
int** graph = NULL;
int** next_graph = NULL;

//list of places in node form with all their information
place_node *places_list = NULL;

//information for creating the graphs read in form file
int source, destination, weight;

//user input for searching for relevant locations
char user_continent[MAXFIELDLEN], user_start[MAXFIELDLEN];
int user_cultural, user_outdoors;

//pointer to an array for relvent places to search for based on user input
int* places_to_go;

int place_from;
int place_to;

int min_cost = -1;
int cheapest_place;

int
main(int argc, char **argv){
	
	printf("\nProgram started\n\n");

	if(argc != 3){
		printf("Usage: holiday x y, where x is the places files and y is the costs file\n");
		exit(ARGERROR);
	}

	check_places(argv[1]);
	check_costs(argv[2]);

	//initialise the space for the data structures (through a function in a place I don't want it to be)
	initialise_space();

	check_places_valid();


	if(i < num_nodes){
		printf("The number at the top of places was greater than the number of actual entries\n");
		exit(DATAERROR);
	}

	check_costs_valid();
	
	fill_graph(graph, next_graph, num_nodes);

	get_user_input();

	places_to_go = relevant_place_search(places_list, user_continent, user_cultural, user_outdoors, num_nodes);

	place_to = find_cheapest_place(graph, places_list, num_nodes, &min_cost, &cheapest_place, user_start, &place_from, places_to_go);


	//checks to see if there is actually any places you can travel to
	if(min_cost == 0 || min_cost == -1){
		printf("There is nowhere for you to go that fits your criteria\n");
		return 0;
	}

	printf("%s %d\n", places_list[cheapest_place].place_name, min_cost);
	

	
	i = place_from;
	j = cheapest_place;
	

	// goes through the next_graph to find the path to the location you want to go to
	while(i != j){

		printf("%s ", places_list[i].place_name);
		i = next_graph[i][j];

	}
	printf("%s\n", places_list[i].place_name);

	
	return 0;
}


void
check_places(char* filename){

	if( (place_file=fopen(filename, "r")) == NULL){
		printf("Error opening places file\n");
		exit(FILEERROR);
	}

	if(fgets(line, sizeof(line), place_file) == NULL){
		printf("places file is empty\n");
		exit(EMPTYFILE);
	}

	if(sscanf(line, "%d", &num_nodes) != 1){
		printf("The first line of the places file should state how many places there are\n");
		exit(DATAERROR);
	}

}

void
check_costs(char* filename){

	if( (cost_file=fopen(filename, "r")) == NULL){
		printf("Error opening costs file\n");
		exit(FILEERROR);
	}
	
}

void
initialise_space(void){

	graph = (int**) malloc(num_nodes*sizeof(int*));
	if(graph == NULL){
		printf("Error allocating memory for graph\n");
		exit(MEMERROR);
	}

	for(j=0; j<num_nodes; j++){
		graph[j] = (int*) malloc(num_nodes*sizeof(int));
		if(graph[j] == NULL){
			printf("Error allocating memory for graph\n");
			exit(MEMERROR);
		}
	}
	
	

	next_graph = (int**) malloc(num_nodes*sizeof(int*));

	if(next_graph == NULL){
		printf("Error allocating memory for graph\n");
		exit(MEMERROR);
	}

	for(j=0; j<num_nodes;j++){
		next_graph[j] = (int*)malloc(num_nodes*sizeof(int));
		if(next_graph[j] == NULL){
			printf("Error allocating memory for graph\n");
			exit(MEMERROR);
		}
	}

	for(i=0;i<num_nodes;i++){
		for(j=0;j<num_nodes;j++){
			next_graph[i][j] = -1;
		}
	}

	//Initialise the information array for places
	places_list = (place_node*) malloc(num_nodes*sizeof(place_node));

}

void
check_places_valid(){
	i=0;
	while(fgets(line, sizeof(line), place_file)){

		if(i == num_nodes){
			printf("There are more entries in the places file than defined at the top\n");
			exit(DATAERROR);
		}

		if(sscanf(line, "%d %s %s %c %c", &node_num, place, country, &tempCult, &tempOutdoor) != 5){
			printf("Not enough information on a line in the places file\n");
			exit(DATAERROR);
		}

		if(node_num-1 != i){
			printf("data entries in places file is incorrectly ordered\n");
			exit(DATAERROR);
		}
		
		if(tempCult == 'Y'){
			cultural = 1;
		}
		else{
			cultural = 0;
		}
		if(tempOutdoor == 'Y'){
			outdoors = 1;
		}
		else{
			outdoors = 0;
		}

		create_places_list(places_list, node_num-1, place, country, cultural, outdoors);

		i += 1;


	}
}

void
check_costs_valid(void){
	i = 0;
	while(fgets(line, sizeof(line), cost_file)){

		if(sscanf(line, "%d %d %d", &source, &destination, &weight) != 3){
			printf("number of variables stored on a line in costs in not correct\n");
			exit(DATAERROR);
		}
		source -= 1;
		destination -= 1;

		create_graph(graph, next_graph, source, destination, weight);

		i += 1;

	}
}

void
get_user_input(){


	printf("Enter your starting point\n");

	fgets(line, sizeof(line), stdin);

	sscanf(line, "%s", user_start);

	printf("Enter the continent you prefer\n");

	fgets(line, sizeof(line), stdin);

	sscanf(line, "%s", user_continent);

	printf("cultural?\n");

	fgets(line, sizeof(line), stdin);

	sscanf(line, "%c", &tempCult);

	if(tempCult == 'Y'){
		user_cultural = 1;
	}
	else{
		user_cultural = 0;
	}

	printf("outdoors?\n");

	fgets(line, sizeof(line), stdin);

	sscanf(line, "%c", &tempOutdoor);


	if(tempOutdoor == 'Y'){
			user_outdoors = 1;
		}
	else{
			user_outdoors = 0;
		}

}

/*
	strcpy(user_start, "Melbourne");
	strcpy(user_continent, "Europe");
	user_outdoors = 0;
	user_cultural = 0;
	*/