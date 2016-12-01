


/* max lengths for various parts of program */
#define MAXLINELEN 256
#define MAXFIELDLEN 80

/* errors that may occur */
#define ARGERROR 1
#define FILEERROR 2
#define DATAERROR 3
#define EMPTYFILE 4
#define MEMERROR 5

/*
Inputs: The filename for the places file

checks to see if the file is valid for places
*/
void check_places(char* filename);

/*
Inputs: The filename for the costs file

checks to see if the file is valid for costs
*/
void check_costs(char* filename);

/*
I didn't want to make this function here, I wanted to move it to graph.c.
For some reason when I did this it caused a seg fault, despite the code being the same,
and pointers being parsed in and the structure seemingly returning correctly

Inputs: None, grabs them from the main file in holiday.c due to major issues above
Creates the 2 graphs for costs and paths, as well as the storage space for the different locations and their information
*/
void initialise_space(void);

/*
Inputs: none

checks if the inputs are valid for another function before running it, and then executes that function
*/
void check_places_valid(void);

/*
checks if inputs are valid for another function before running it
*/
void check_costs_valid(void);

/*
Gets the users input for place to depart from, continent to travel to and if cultural and outdoors are required
*/
void get_user_input(void);