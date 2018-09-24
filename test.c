#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){

	FILE *file = fopen(argv[1], "r");
	char *col = argv[2];
	char* line = (char*)malloc(1000000*(sizeof(char)));
	char* token = (char*)malloc(1000000*(sizeof(char)));
	const char s[2] = ",";
        while(fscanf(file, "%s,", line)==1){
		//printf("%s\n", line);
		const char s[2] = ",";
		char * token;
		token = strtok(line,s);
		while(token!=NULL){
			printf("%s\n",token);
			token = strtok(NULL,s);
		}
		printf("done with this line\n");
	}

    return 0;
}
