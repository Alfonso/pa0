#include <stdio.>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "simpleCSVsorter.h"
#include "mergesort.c"

int trim(char** strPtr){
    // dereference the ptr
    char* ptr = *strPtr;
    int lastNonWhite = indexOfLastNon(ptr);
    int charCount = countNonWhite(ptr);
    char* temp = (char*)malloc((charCount+1)*sizeof(char));
    int index = 0;
    int oldCount = 0;
    // remove the leading white spaces from the given char*
    // this works by moving the ptr along our char** and
    // keep track of our index
    // after we hit our first non-white space we stop moving
    // and then start copying over the chars from the original
    // to the temp char*. This getting rid of the white spaces
    // at the beginning of the original char*
    while(*ptr == ' ' || *ptr == '"'){
        ptr++;
        oldCount++;
    }
    // remove the trailing white spaces from the given char*
    // this works by traveling to the last nonwhite character
    // while copying over character by character over
    // to our temp char*
    while(oldCount < lastNonWhite){
        temp[index] = *ptr;
        index++;
        oldCount++;
        ptr++;
    }
    temp[index] = '\0';
    // do I free the old strPtr here?
    *strPtr = temp;
    // return the number of actual characters
    // NOT including the null terminator
    return charCount;
}


int indexOfLastNon(char* str){
    int counter = strlen(str)-1;
    char* end = str + strlen(str) - 1;
    while( *end == ' ' || *end == '"'){
        counter--;
        end--;
    }

    return counter+1;
}

int countNonWhite(char* str){
    int counter=0;
    char* ptr = str;
    while( *ptr != '\0' ){
        if( *ptr != ' ' || *ptr != '"')
            counter++;
        ptr++;
    }

    return counter;
}

void addToNull(node** nullHeadPtr, char* rowPtr){
	node* ptr = *nullHeadPtr;
	if(*nullHeadPtr == NULL){
        	*nullHeadPtr = (node*)malloc(sizeof(node));
        	(*nullHeadPtr)->data = NULL;
        	(*nullHeadPtr)->row = (char*)malloc((strlen(rowPtr)+1)*sizeof(char));
        	strcpy((*nullHeadPtr)->row, rowPtr);
        	(*nullHeadPtr)->next = NULL;
		return;
     }else{
		while(ptr->next != NULL){
			ptr = ptr->next;
		}
        ptr->next = (node*)malloc(sizeof(node));
        (ptr->next)->data = NULL;
        (ptr->next)->row = (char*)malloc(sizeof(char)*(strlen(rowPtr)+1));
        strcpy((ptr->next)->row, rowPtr);
        (ptr->next)->next = NULL;
		return;
    }
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
		errno = 5;
		perror("Incorrect number of arguments");
		return -1;
	}
	//FILE *file = fopen(stdin, "r");
	char *col = argv[2];
	char* line = NULL;   //(char*)malloc(1000000*(sizeof(char)));
	char* token = (char*)malloc(1000*(sizeof(char)));
	const char s[2] = ",";
    int counter = 0;
	int index = -1;
	
	node* head = (node*)malloc(sizeof(node));
	head = NULL;

 	node* nullHead = NULL;
	node* ptr = (node*)malloc(sizeof(node));
	ptr = NULL;
 	// tokenize col names + figure out index number
 	

    size_t n= 0;

	// first row only	
	int exists = getline(&line,&n,stdin);
	
	if(exists == -1){
		return -1;	
	}
	// remove the new line
	int len = strlen(line);
	if(line[len-1] == '\n')
		line[len-1] = '\0';
	
	char* linecpy = (char*)malloc((strlen(line)+1)*sizeof(char));
	strcpy(linecpy, line);
	
	char* firstLine = (char*)malloc((strlen(line)+1)*sizeof(char));
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
        errno = 5;
	perror("Column does not exist");
        return -1;
    }

    free(linecpy);	
	// determine the type of sorting column
    // use index found above, move past index - 1 commas
	// if NOT number (not comma or hyphen, or not isdigit()), you know it's string type. break
	// need a helper function to determine whether it's a number
	// if you get to the end of the column, it's a numeric
	// set boolean isNum (0 or 1)

	int isNum_ = 1;
	while(getline(&line,&n,stdin) != -1){
	
        // remove the \n if it is there
		int len = strlen(line);
        if(line[len-1] == '\n'){
            line[len-1] = '\0';
        }
        int i = 0;
        int commaCount = 0;
	    int isNull = 0;
        int quotation = 0;
    
        int length = strlen(line);
        for(i = 0; i < length; i++){
            // check if the column we are sorting by is the first one
	        if(index == 0){
		         // deal w it separately 
				 if(line[0] == ',' || line[0]== '\0'){
			        // this means that the column is null
					// have to make the null node
					addToNull(&nullHead, line);					
				 }else{
			        // add to the regular linked list
					int numBytes = 0; // number of bytes of substring
                    int ptrOffset = i;
                    /* what the fuck is this for??? index > 0?????
                    if(line[i] == ','){
                        i++;
                        ptrOffset++;
                    }
                    */
                    while(line[i] != ',' && line[i] != '\0' /* if at last column */){
                        numBytes++;
                        i++;
                    }
                                    
                    node* temp = (node*)malloc(sizeof(node));
                    char* tempItem = (char*)malloc(sizeof(char)*(numBytes+1)); // Allocating an extra byte for the null character
                    char* item; // allocate extra byte for null char
                    memcpy(tempItem, line + ptrOffset, numBytes);
                                	
                    tempItem[numBytes] = '\0'; // add null char end
					
                    // allocate the memory for item here
                    // by finding the amount of non-white space
                    // characters
                    int itemLength = trim(&tempItem);
// NOT DOING THIS WAY ANYMORE
                    item = (char*)malloc(sizeof(char)*(itemLength+1)); // adding one more for the null terminator
                    item[itemLength] = '\0';     // check trim to see if the null character was set already
					strcpy(item,tempItem);
                    //free(tempItem); // I THINK THIS IS BREAKING STUFF

                    // add to LL
                    temp->row = (char*)malloc((strlen(line)+1)*sizeof(char));
                    strcpy(temp->row, line);
                    temp->data =item; // changed from item to fix something

                    temp->next = head;
                    head = temp;

                    // check if item has any non-num chars
                    isNum_ = isNum_ & isNum(&item);
			    }
				break;
            }
            if(line[i] == '"'){
                if(quotation == 0)
                    quotation = 1;
                else quotation = 0;
            }
            if(quotation == 0)
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
				        addToNull(&nullHead, line);
						break;
					}
				}else{ // check end column
			        if(line[i + 1] == '\0'){
				        addToNull(&nullHead, line);
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
                char* tempItem = (char*)malloc(sizeof(char)*(numBytes+1)); // Allocating an extra byte for the null character
                char* item; // allocate extra byte for null char
                memcpy(tempItem, line + ptrOffset, numBytes);
                tempItem[numBytes] = '\0'; // add null char end                                     
                int itemLength = trim(&tempItem);

 // WE ARE NOT DOING THIS WAY BC IT IS BREAKING BECAUSE OF THE FREE
                item = (char*)malloc((itemLength+1)*sizeof(char));
                item[itemLength] = '\0';
                strcpy(item,tempItem);

                //printf("Pre-Free\n");
                //free(tempItem); // THIS LINE IS BREAKING OUR FUCKING CODE WHAT THE FUCK
                //printf("Post-Free\n");

				// add to LL
				node* temp = (node*)malloc(sizeof(node));
                //printf("Line length: %d, line: %s\n",strlen(line),line);
				//printf("PRE-ROW MALLOC\n");
                temp->row =(char*) malloc((strlen(line)+1)*sizeof(char));   //malloc(sizeof(line));
                //printf("POST-ROW MALLOC\n");	
                strcpy(temp->row, line);

                temp->data =item; // changing from just item
				temp->next = head;
                head = temp;

                //printf("Post-node creation\n");
				// check if item has any non-num chars
				isNum_ = isNum_ & isNum(&item);
			    //	i = length;
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
