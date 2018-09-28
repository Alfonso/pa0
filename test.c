#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simpleCSVsorter.h"
#include "mergesort.c"

node* addToNull(node** nullHeadPtr, char** rowPtr){
	node* ptr = *nullHeadPtr;
	if(*nullHeadPtr == NULL){
        	*nullHeadPtr = (node*)malloc(sizeof(node));
        	(*nullHeadPtr)->data = NULL;
        	(*nullHeadPtr)->row = (char*)malloc(sizeof(*rowPtr));
        	strcpy((*nullHeadPtr)->row, *rowPtr);
        	(*nullHeadPtr)->next = NULL;
		return *nullHeadPtr;
        }else{
		while((*nullHeadPtr)->next != NULL){
			ptr = ptr->next;
		}
        	ptr->next = (node*)malloc(sizeof(node));
        	ptr->next->data = NULL;
                ptr->next->row = (char*)malloc(sizeof(*rowPtr));
               	strcpy(ptr->next->row, *rowPtr);
                ptr->next->next = NULL;
		return *nullHeadPtr;
        }
}

node* addToLL(){

}

int isNum(char** item){
	int j = 0;
	for(j = 0; j < strlen(*item); j++){
        	if((*item)[j] != '.' && (*item)[j] != '-' && !isdigit((*item)[j])){
             	   return 0;
                }
        }
	return 1;
}

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


	int isNum_ = 1;
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
					// have to make the null node
					nullHead = addToNull(&nullHead, &line);					
				}else{
					// add to the regular linked list
					int numBytes = 0; // number of bytes of substring
                                	int ptrOffset = i;

                                	if(line[i] == ','){
                                        	i++;
                                      		ptrOffset++;
                                	}
                                	while(line[i] != ',' && line[i] != '\0' /* if at last column */){
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
                                	isNum_ = isNum_ & isNum(&item);
				}
				break;
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
						nullHead = addToNull(&nullHead, &line);
						break;
					}
				}else{ // check end column
					if(line[i + 1] == '\0'){
						nullHead = addToNull(&nullHead, &line);
						break;
					}
				}	
     
				// if NOT null
				int numBytes = 0; // number of bytes of substring
                                int ptrOffset = i;
				
				if(line[i] == ','){ 
					i++;
					ptrOffset++;				
				}
                                while(line[i] != ',' && line[i] != '\0' /* if at last column */){
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
				isNum_ = isNum_ & isNum(&item);
				i = length;
				break;
			}
		}	
	}
		// if type is numeric, cast to float
		node* ptr2 = head;
		node* floatHead = NULL;
		if(isNum_ == 1){
			while(ptr2 != NULL){
				char* str = ptr2->data;
				char* row = ptr2->row;
				float val = atof(str);	
				
				node* temp_f = (node*)malloc(sizeof(node));
				float* floatPtr = (float*)malloc(sizeof(float));
				temp_f->data = floatPtr;

				temp_f->row = ptr2->row;
				*floatPtr = val;

				printf("val: %f\n",val);
				temp_f->next = floatHead;
				floatHead = temp_f;
				ptr2 = ptr2->next;
			}
			head = floatHead;
		}
		
		// sort non null list  w/ mergesort - have to fix this (change var names, make node data void type, make two comparators)
			if(isNum_ == 0){ // call with string comparator
				mergesort(&head, comparator_STR);
			}else{ // call with float/int comparator
				mergesort(&head, comparator_FLT);
			}

		// add null list to front of sorted list
	
		// write whole list into output file
		// print LL (eventually change to creating output)
	
	printf("%s\n", firstLine); // print columns
	if(nullHead != NULL){
		ptr = nullHead;
		while(ptr->next != NULL){ ptr = ptr->next; }
		ptr->next = head;
		while(nullHead != NULL){
			printf("%s\n", nullHead->row);
                	nullHead = nullHead->next;
        	}
	}else{
		while(head != NULL){
                        printf("%s\n", head->row);
			head = head->next;
        	}
	}

    	return 0;

}
