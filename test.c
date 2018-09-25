#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simpleCSVsorter.h"
//#include "mergesort.c"

int main(int argc, char** argv){

	FILE *file = fopen(argv[1], "r");
	char *col = argv[2];
	char* line = (char*)malloc(1000000*(sizeof(char)));
	char* token = (char*)malloc(1000000*(sizeof(char)));
	const char s[2] = ",";
        int counter = 0;
	int index = -1;
	
	// initialize head nodes
	intnode* inthead = (intnode*)malloc(sizeof(intnode));
	inthead = NULL;
	floatnode* floathead = (floatnode*)malloc(sizeof(floatnode));
	floathead = NULL;
	strnode* strhead = (strnode*)malloc(sizeof(strnode));
	strhead = NULL;

	const char s[2] = ",";
	
	while(fscanf(file, "%s\n", line)==1){
		
		// tokenize col names + figure out index number
		if (counter == 0){ // first row
			char* linecpy = (char*)malloc(sizeof(line));
			strcpy(linecpy, line);
			token = strtok(linecpy, s);
			while(token != NULL){
				if(strcmp(token, col) == 0){
					index = counter;
					break;
				}
				token = strtok(NULL, s);
				counter++; // increment counter
			}
		}

                if(index == -1){ // column specified in command line NOT valid
                        printf("Error: Column does not exist in table\n");
                        return -1;
                }
	}

	// determine the type of sorting column
		// use index found above, move past index - 1 commas
		// if NOT number, you know it's string type. break
			// need a helper function to determine whether it's a number
		// if you get to the end of the column, it's a numeric


	rewind(file);

		// trim values (strs)
	fscanf(file, "%s\n", line); // skip header line
	char* firstLine = (char*)malloc(sizeof(line));
	strcpy(firstLine, line); // copy headers into variable to use in output file later
	
	// put for loop in while fscanf loop
	//while(fscanf(file, "%s\n", line)==1){}
	int i = 0;
	int length = strlen(line);
	for(i = 0; i < length; i++){
			
		if(index == counter){ // if matching index (sorting column) 
			// null checks
			// add node to separate list
			// add to back
			// maintain head + tail ptrs
			if(i < length - 1){ // check middle columns
					
			}else{ // check last col
			}
		}
			// not null - str or float
				// check if number
					// add to LL as float 
					// use atof()
				// if not, string
					// see previous test.c	
	}	

	// sort non null list  w/ mergesort - have to fix this (change var names, add more mergesorts for type)
		//mergesort(strhead);
	
	// add null list to front of sorted list
	//
	// write whole list into output file
	// print LL (eventually change to creating output)
	while(inthead != NULL){
		//printf("%d | %s\n", inthead->data, inthead->row);
		printf("%d | %s\n", inthead->data, inthead->row);
		inthead = inthead->next;
	}

	while(floathead != NULL){
        	printf("%f | %s\n", floathead->data, floathead->row);
	        floathead = floathead->next;
        }
	while(strhead != NULL){
		//printf("should be in here\n");
		printf("%s | %s\n", strhead->data, strhead->row);
        	strhead	= strhead->next;
	}


//   	free(line);
  //  	free(token);

    	return 0;

}
