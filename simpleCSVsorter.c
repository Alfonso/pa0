#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simpleCSVsorter.h"
#include "mergesort.c"

int main(int argc, char** argv){

	FILE *file = fopen(argv[1], "r");
	char *col = argv[2];
	char* line = (char*)malloc(1000000*(sizeof(char)));
	char* token = (char*)malloc(1000000*(sizeof(char)));
	const char s[2] = ",";
        int counter = 0;
	int index = -1;
	
	// initialize head nodes
	/*
 	intnode* inthead = (intnode*)malloc(sizeof(intnode));
	inthead = NULL;
	floatnode* floathead = (floatnode*)malloc(sizeof(floatnode));
	floathead = NULL;
	strnode* strhead = (strnode*)malloc(sizeof(strnode));
	strhead = NULL;
	*/
	node* head = (node*)malloc(sizeof(node));
	head = NULL;

 	node* nullHead = NULL;
	node* ptr = (node*)malloc(sizeof(node));
	ptr = NULL;
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
	fscanf(file, "%s\n", line);	
	int isNum = 1;
	while(fscanf(file, "%s\n", line)==1){
                int i = 0;
                int commaCount = 0;

                int length = strlen(line);
                for(i = 0; i < length; i++){
                        if(i != 0 && line[i] == ',') { commaCount++; }
                        if(index == commaCount){ // if matching index (sorting column) 
				// check if null
				// if not, isolate item
					// check if there are any non digits. - and . are ok
					// if so, set isNum to 0 and break
					// if you get to the end of the word with no bad chars, break
				 
				if(i == 0 || i == length - 1){ // first + last columns
                                        if(line[i] == ','){
                                                break; // it is null, so break to next line
                                        }
                                 }else{ // check middle columns
                                        if(line[i + 1] == ','){
                                                break; // it is null, so break to next line
                                        }
                                 }
			
				// if NOT null
				int numBytes = 0; // number of bytes of substring
                                int ptrOffset = i;

                                while(line[i] != ',' && line[i] != '\0' /* if at last colum */){
                                	numBytes++;
                                        i++;
                                }

                                char* item = (char*)malloc(sizeof(numBytes + 1)); // allocate extra byte for null char
                                memcpy(item, line + ptrOffset, numBytes);
                               	item[numBytes] = '\0'; // add null char end                                     

				// check if item has any bad chars
				int j = 0;
				for(j = 0; j < strlen(item); j++){
					if(item[j] != '.' && item[j] != '-' && !isdigit(item[j])){
						isNum = 0;
						break;
					}
				}
			}	
		}
		if(isNum == 0){ break; }
	}


	rewind(file);

	fscanf(file, "%s\n", line); // skip header line
	char* firstLine = (char*)malloc(sizeof(line));
	strcpy(firstLine, line); // copy headers into variable to use in output file laterr

	// put for loop in while fscanf loop
	while(fscanf(file, "%s\n", line)==1){
		int i = 0;
		int commaCount = 0;
		int isNull = 0;

		int length = strlen(line);
		for(i = 0; i < length; i++){
			if(i != 0 && line[i] == ',') { commaCount++; }
			if(index == commaCount){ // if matching index (sorting column) 
				//printf("line: %s\n", line);
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
						nullHead->row = (char*)malloc(sizeof(line));
						strcpy(nullHead->row, line);
						nullHead->next = NULL;
						ptr = nullHead;	
					}else{
						ptr->next = (node*)malloc(sizeof(node));
						ptr->next->data = NULL;
						ptr->next->row = (char*)malloc(sizeof(line));
                                                strcpy(ptr->next->row, line);
						ptr->next->next = NULL;
						ptr = ptr->next;
					}
					break;
				}else{ // not null - str or float
					// already know type from before
					// add to generic node (just cast appropriately)
					
					// first: isolate current entry
						 // from right after this comma to right before nxt one
						// c substring: memcpy
					
					int numBytes = 0; // number of bytes of substring
					int ptrOffset = i;
				        
					if(i > 0 && line[i] == ','){ 
						i++; 
						ptrOffset++;
					}							
					while(line[i] != ',' && line[i] != '\0' /* if at last colum */){
						numBytes++;
						i++;
					}
					
					char* item = (char*)malloc(sizeof(numBytes + 1)); // allocate extra byte for null char
					memcpy(item, line + ptrOffset, numBytes);
					item[numBytes] = '\0'; // add null char end					

					// cast into node based on pre-determined type
						// need to malloc node differently based on type??	
					node* temp = (node*)malloc(sizeof(node));
					temp->row = (char*)malloc(sizeof(line));
					strcpy(temp->row, line);
					//temp->row = line; // make sure this doesn't need malloc?

					if(isNum == 1){ // numeric
						float* ptr = (float*)malloc(sizeof(float));
						temp->data = ptr;
						*ptr = atof(item);
					}else{ // string
						 // trim values (strs) before adding to nodes 
						//item = trim(item); // make this helper function
						
						// if you need to malloc
						temp->data = item;
					}
					temp->next = head;
                                        head = temp;

					break; // go to next row
				}			
			}
		}	
	}



		// sort non null list  w/ mergesort - have to fix this (change var names, make node data void type, make two comparators)
			if(isStr){ // call with string comparator
				mergesort(&head, comparator_STR);
			}else{ // call with float/int comparator
				mergesort(&head, comparator_FLT);
			}
		// add null list to front of sorted list
	
		// write whole list into output file
		// print LL (eventually change to creating output)
	
	
	if(nullHead != NULL){
		ptr->next = head;
		while(nullHead != NULL){
			if(isNum){
				printf("%f | %s\n", *(float*)(nullHead->data), nullHead->row);
			}else{
				printf("%s | %s\n", (nullHead->data), nullHead->row);
			}
                	nullHead = nullHead->next;
        	}
	}else{
		while(head != NULL){
                	if(isNum){
                                printf("%f | %s\n", *(float*)(head->data), head->row);
                        }else{
                                printf("%s | %s\n", (head->data), head->row);
                        }
			head = head->next;
        	}
	}

/*
	while(floathead != NULL){
        	printf("%f | %s\n", floathead->data, floathead->row);
	        floathead = floathead->next;
        }
	while(strhead != NULL){
		//printf("should be in here\n");
		printf("%s | %s\n", strhead->data, strhead->row);
        	strhead	= strhead->next;
	}
	*/

//   	free(line);
  //  	free(token);

    	return 0;

}
