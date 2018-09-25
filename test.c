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
	
	while(fscanf(file, "%s\n", line)==1){
		const char s[2] = ",";
		//char * token;
		
		// tokenize a copy of line
		char* linecpy = (char*)malloc(sizeof(line));
		linecpy = strcpy(linecpy, line);
		token = strtok(linecpy,s);

		while(token!=NULL){
			//token = trim(token); How to trim strings!?
			if(strcmp(token, col)==0){ // first row
				index = counter; // mark column as sorting column
			}
			else if(counter == index && strcmp(token, col)!=0){  // if sorting column
				// if int or float, must cast back to correct type
				
				// if number
				if(isdigit(token[0])){ // if first char is a digit
					// if float
					if(strstr(token, ".") != NULL){ // if string contains "."
						// cast to float - atof

						// make a float node and point it to line. then break
						floatnode* node = (floatnode*)malloc(sizeof(floatnode));
						node->data = atof(token);
						node->row = (char*)malloc(sizeof(line));	
						node->row = strcpy((node->row), line);  // copy of line
						node->next = floathead;
						floathead = node;
						break; // move onto next row
					}else{ // is int
						// make a int node and point it to line. then break
						intnode* node	= (intnode*)malloc(sizeof(intnode));
                                                node->data = atoi(token);
						node->row = (char*)malloc(sizeof(line));
						node->row = strcpy((node->row), line);  // copy of line
                                                node->next = inthead;
                                                inthead = node;
						break; // move onto next row
					}
				}else{ // just a string
					strnode* node = (strnode*)malloc(sizeof(strnode));
                                        node->data = (char*)malloc(sizeof(token));
					node->data = strcpy(node->data, token);					
					node->row = (char*)malloc(sizeof(line));
					node->row = strcpy((node->row), line);  // copy of line
                                        node->next = strhead;
                                        strhead = node;
					break; // move onto next row
				}
			}
		token = strtok(NULL,s); // create next token
                counter++; // increment counter
		}
		if(index == -1){ // column specified in command line NOT valid
			printf("Error: Column does not exist in table\n");
			return -1;
		}
		counter = 0;
		r++;
	}

	// sort w/ mergesort - have to fix this (change var names, add more mergesorts for type)
		//mergesort(strhead);

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
