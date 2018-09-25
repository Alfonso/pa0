#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){

	FILE *file = fopen(argv[1], "r");
	char *col = argv[2];
	char* line = (char*)malloc(1000000*(sizeof(char)));
	char* token = (char*)malloc(1000000*(sizeof(char)));
	const char s[2] = ",";
        int counter = 0;
	int index = -1;
	while(fscanf(file, "%s,", line)==1){
		//printf("%s\n", line);
		const char s[2] = ",";
		//char * token;
		token = strtok(line,s);
		while(token!=NULL){
			//printf("%s\n",token);
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
						printf("float: %f\n", atof(token));

						// make a float node and point it to line. then break

					}else{ // is int
						// make a int node and point it to line. then break
					}
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
	}

   	 free(line);
    	free(token);

    	return 0;

}
