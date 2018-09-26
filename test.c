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

 	// tokenize col names + figure out index number	
	while(fscanf(file, "%s\n", line)==1){
		
		// first row only
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

                if(index == -1){ // column specified in command line NOT valid
                        printf("Error: Column does not exist in table\n");
                        return -1;
                }
	}


	// determine the type of sorting column
		// use index found above, move past index - 1 commas
		// if NOT number (not comma or hyphen, or not isdigit()), you know it's string type. break
			// need a helper function to determine whether it's a number
		// if you get to the end of the column, it's a numeric
		// set boolean isNum (0 or 1)



	rewind(file);


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
						// c substring: memcpy

					int numBytes = 0; // number of bytes of substring
					int ptrOffset = i;
					//i++;
					while(line[i] != ',' || line[i] != '\0' /* if at last column */){
						numBytes++;
						i++;
					}
					char* item = (char*)malloc(sizeof(numBytes + 1)); // allocate extra byte for null char
					memcpy(item, line + ptrOffset + 1, numBytes);
					item[numBytes] = '\0'; // add null char end					


					// cast into node based on pre-determined type
						// need to malloc node differently based on type??	
					node* node = (node*)malloc(sizeof(node));
                                        node->row = line; // make sure this doesn't need malloc?

					if(isNum){ // numeric
						node->data = atof(item);
					}else{ // string
						 // trim values (strs) before adding to nodes 
						item = trim(item); // make this helper function
						node->data = item;
						// if you need to malloc
							//node->data = (char*)malloc(sizeof(item));
							//strcpy(node->data, item);
					}
					node->next = head;
                                        head = node;					
					break; // go to next row
				}			
			}
		}	
	}


		// sort non null list  w/ mergesort - have to fix this (change var names, make node data void type, make two comparators)
			if(isStr){ // call with string comparator
				mergesort(head, strcomparator);
			}else{ // call with float/int comparator
				mergesort(head, numcomparator);
			}

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
