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

		// trim values (strs) before adding to nodes!
	
	fscanf(file, "%s\n", line); // skip header line
	char* firstLine = (char*)malloc(sizeof(line));
	strcpy(firstLine, line); // copy headers into variable to use in output file later
	
	node* head = NULL; //(node*)malloc(sizeof(node));
	
	// put for loop in while fscanf loop
	while(fscanf(file, "%s\n", line)==1){
		int i = 0;
		int commaCount = 0;
		int isNull = 0;

		node* nullHead = NULL;
		int length = strlen(line);
		for(i = 0; i < length; i++){
			if(line[i] == ',') { commaCount++; }
			if(index == commaCount){ // if matching index (sorting column) 
				
				// are currently at sorting column
					// NULL CHECKS
					// if i = 0 || i = length - 1: if current char is ',' --> null val
					// if i > 0 && i < length - 1: if next char is a comma, it is null value

				if(i == 0 || i == length - 1){ // first + last columns
					if(line[i] == ','){
						isNull = 1;
					}
				}else{ // check middle columns
					if(line[i + 1] == ','){
						isNull = 1;
					}
				}
				if(isNull == 1){ // curr column has null val
					// add node to separate list
					// add to back
					// maintain head + tail pointers
					if(nullHead == NULL){
						nullHead = (node*)malloc(sizeof(node));
						nullHead->data = NULL;
						nullHead->row = line;
						nullHead->next = NULL;
						ptr = nullHead;	
					}else{
						ptr->next = (node*)malloc(sizeof(node));
						ptr->data = NULL;
						ptr->row = line; // make sure this doesn't need malloc
						ptr->next = NULL;
						ptr = ptr->next;
					}
				}else{ // not null - str or float
					// already know type from before
					// add to generic node (just cast appropriately)
					
					// first: isolate current entry
						 // from right after this comma to right before nxt one
						// c substring?

					// cast into node based on pre-determined type	
					node* node = (node*)malloc(sizeof(node));
                                        node->row = line; // make sure this doesn't need malloc

					if(isNum){ // numeric
						node->data = (char*)malloc(sizeof(item));
					}else{ // string
						node->data = (char*)malloc(sizeof(item));
					}
					node->next = head;
                                        head = node;					
					break; // go to next row
				}			
			}
		}	
	}


		// sort non null list  w/ mergesort - have to fix this (change var names, add more mergesorts for type)
			//mergesort(strhead);
	
		// add null list to front of sorted list
	
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
