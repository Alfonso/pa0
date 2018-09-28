#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simpleCSVsorter.h"
#include "mergesort.c"

int main(int argc, char** argv){

	if(argc != 3){ 
		printf("Bad input - wrong number of input strings.\n");
	}
	//FILE *file = fopen(stdin, "r");
	char *col = argv[2];
	char* line = (char*)malloc(1000000*(sizeof(char)));
	char* token = (char*)malloc(1000000*(sizeof(char)));
	const char s[2] = ",";
        int counter = 0;
	int index = -1;
	
	node* head = (node*)malloc(sizeof(node));
	head = NULL;

 	node* nullHead = NULL;
	node* ptr = (node*)malloc(sizeof(node));
	ptr = NULL;
 	// tokenize col names + figure out index number
 	
	// first row only	
	gets(line);
		
	char* linecpy = (char*)malloc(sizeof(line));
	strcpy(linecpy, line);
	
	char* firstLine = (char*)malloc(sizeof(line));
        strcpy(firstLine, line); // copy headers into variable to use in output file laterr

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

	
	// determine the type of sorting column
		// use index found above, move past index - 1 commas
		// if NOT number (not comma or hyphen, or not isdigit()), you know it's string type. break
			// need a helper function to determine whether it's a number
		// if you get to the end of the column, it's a numeric
		// set boolean isNum (0 or 1)
	int isNum = 1;
	while(gets(line) != NULL){
                int i = 0;
                int commaCount = 0;
		int isNull = 0;

                int length = strlen(line);
                for(i = 0; i < length; i++){
			if(index == 0){
				// deal w it separately 
				if(line[0] == ',' || line[0]== '\0'){
					// this means that the column is null
					isNull = 1;
					// have to make the null node
				}else{

					// add to the regular linked list
				}
			}
			if(line[i] == ',') { commaCount++; }
                        if(index == commaCount){ // if matching index (sorting column) 
				// check if null
				// if not, isolate item
					// check if there are any non digits. - and . are ok
					// if so, set isNum to 0 and break
					// if you get to the end of the word with no bad chars, break
				
				// NULL CHECKS
					// if i = 0 || i = length - 1: if current char is ',' --> null val
					// if i > 0 && i < length - 1: if next char is a comma, it is null value
				 
				if(i < length - 1){ // first + middle columns
                                        if(line[i + 1] == ','){ // it is null, so add to null list	
						isNull = 1;
					}
				}else{ // check ende columns
					if(line[i + 1] == '\0'){
						isNull = 1;
					}
				}	
     
			      if(isNull == 1){
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
				}else{			
					// if NOT null
					int numBytes = 0; // number of bytes of substring
                                	int ptrOffset = i;
				
					if(line[i] == ','){ 
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

					// add to LL
					node* temp = (node*)malloc(sizeof(node));
                                	temp->row = (char*)malloc(sizeof(line));
                                	strcpy(temp->row, line);
					temp->data = item;
				
					temp->next = head;
                                	head = temp;
					// check if item has any non-num chars
					int j = 0;
					for(j = 0; j < strlen(item); j++){
						if(item[j] != '.' && item[j] != '-' && !isdigit(item[j])){
							isNum = 0;
						}
					}
					break;
				}
			}	
		}
	}
	
		// if type is numeric, cast to float
		node* ptr2 = head;
		if(isNum == 1){
			while(ptr2 != NULL){
				char* str = ptr2->data;
                       		float * temp = (float*)malloc(sizeof(float));
				ptr2->data = temp;
				*temp = atof(str);
				ptr2 = ptr2->next;
			}
		}

		// sort non null list  w/ mergesort - have to fix this (change var names, make node data void type, make two comparators)
			if(isNum == 0){ // call with string comparator
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

    	return 0;

}
