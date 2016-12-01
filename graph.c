#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "holiday.h"



//Takes the matrix that stores all the costs information as well as the information about destination, source and the cost weighting
void 
create_graph(int** graph,int** next_graph, int source, int destination, int weight){

	graph[source][destination] = weight;
	next_graph[source][destination] = destination;

}


//takes the list that places are stored in and all the attributes for a new node and places it in the list
void 
create_places_list(place_node* places_list,int node_num, char place[MAXFIELDLEN], char country[MAXFIELDLEN], int cultural, int outdoors){

	place_node node;

	node = places_list[node_num];

	node.node_num = node_num;
	strcpy(node.place_name, place);
	strcpy(node.country, country);
	node.outdoors = outdoors;
	node.cultural = cultural;



	places_list[node_num] = node;

}

void
fill_graph(int** graph, int** next_graph, int num_nodes){

	int s,d,k;

	//floyd-warshall algorithm to fill out the graph with the distance from every place to every other place posible
	for(k=0;k<num_nodes;k++){
		for(s=0;s<num_nodes;s++){
			for(d=0;d<num_nodes;d++){
				if(s == d){continue;}
				if(graph[s][k] && graph[k][d]){
					if((graph[s][d] > (graph[s][k] + graph[k][d])) || graph[s][d] == 0){
						graph[s][d] = graph[s][k] + graph[k][d];
						next_graph[s][d] = next_graph[s][k];
					}
				}
			}
		}
	}

}


int *
relevant_place_search(place_node* places_list, char continent[MAXFIELDLEN], int cultural, int outdoors, int num_nodes){
	
	int i = 0, j = 0;
	
	int* array;

	array = (int*) malloc(num_nodes+1*sizeof(int));



	for(i=0;i<num_nodes+1;i++){
		array[i] = -1;
	}

	//checks all possible places to see if their information matches what the user is searching for
	i = 0;
	while(i < num_nodes){
		if((strcmp(places_list[i].country, continent) == 0) || (strcmp(continent, "") == 0)){
			if(!cultural || (cultural && places_list[i].cultural)){
				if(!outdoors || (outdoors && places_list[i].outdoors)){
					array[j] = places_list[i].node_num;
					j++;
				}
			}
		}

		i++;
	}

	return array;


}

int 
find_cheapest_place(int** graph, place_node* places_list, int num_nodes, int* min_cost, int* cheapest_place, char user_start[MAXFIELDLEN], int* place_from, int* places_to_go){

	int i;
	int place_to;

	//figures out what number the users places of origin is from the places_list based on their input
	for(i=0;i<num_nodes;i++){
		if(strcmp(user_start, places_list[i].place_name) == 0){
			*place_from = places_list[i].node_num;
		}
	}

	
	i=0;
	while(places_to_go[i] != -1){

		

		place_to = places_to_go[i];

		if(place_to == *place_from){
			i++;
			continue;
		}
		//updates the minimum cost and cheapest places if it es better than the previous one searched for
		if((*min_cost == -1) || graph[*place_from][place_to] < *min_cost){
			*min_cost = graph[*place_from][place_to];
			*cheapest_place = place_to;
		}
		i++;
	}

	return place_to;

}







//testing methods for printing out the 2d matrix
void
print_matrix(int** matrix,int num_nodes){
    int i = 0;
    int j = 0;
    
    printf("--------------------------\n");

    for(i=0;i<num_nodes;i++){
    	printf("%6d", i);
    }

    printf("\n\n");
    
    for(i=0;i<num_nodes;i++){
        printf("%d", i);
        for(j=0;j<num_nodes;j++){
            printf("%5d ", matrix[i][j]);
        }
        printf("-\n");
        
    }
                  
}



/*
//initialisation for the data structures used MAJOR ISSUES CAUSES SEG FAULT FOR UNKNOWN REASON
void
initialise_space(int** graph, int** next_graph, place_node* places_list, int num_nodes){

	int i,j;


	//Initialise the 2d graph structure
	graph = (int**) malloc(num_nodes*sizeof(int*));
	if(graph == NULL){
		printf("Error allocating memory for graph\n");
		exit(MEMERROR);
	}

	for(i=0; i<num_nodes; i++){
		graph[i] = (int*) malloc(num_nodes*sizeof(int));
		if(graph[i] == NULL){
			printf("Error allocating memory for graph\n");
			exit(MEMERROR);
		}
	}

	//Initialise the information array for places
	places_list = (place_node*) malloc(num_nodes*sizeof(place_node));

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



}
*/