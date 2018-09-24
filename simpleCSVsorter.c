#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mergesort.h>
#include <time.h>

/*
typedef struct _row{
	// make a field for every column (?)
	char* color;
	char* director_name;
	int num_critic_for_reviews;
	int duration;
	int director_facebook_likes;
	int actor_3_facebook_likes;
	char* actor_2_name[];
	int actor_1_facebook_likes;
	long gross;
	char* genres;
	char* actor_1_name;
	char* movie_title;
	int num_voted;
	int case_total_facebook_likes;
	char* actor_3_name;
	int facenumber_in_poster;
	char* plot_keywords;
	char* movie_imdb_link;
	int num_user_for_reviews;
	char* language;
	char* country;
	char* content_rating;
	long budget;
	int title_year;
	int actor_2_facebook_likes;
	float imdb_score;
	float aspect_ratio;
	int movie_facebook_likes;
	struct row* next;
} row;
*/

node* makeStruct(FILE *file, char* column){

	
	// remaining problem: how to deal with different types?!?
		// some thoughts: atoi and .isdigit()
	

	// scan csv 
	
	// scan first row differently (bc names)
		// go column by column, incrementing counter as you go (use temp)
		// if input matches column, save this as counter value (counter = temp)
		// continue until end to save number of columns
	
	char *col = *column;
	int index = 0;
	int temp = 0;
	int r = 0, c = 0;
	char* line = (char*)malloc(1000000 * sizeof(char));
	char* token = (char*)malloc(1000000*(sizeof(char)));
	const char s[2] = ",";

	// tokenize first row, find column index + number of cols

	if(fscanf(file, "%s\n", line)==1){

                token = strtok(line, s);
                while(token != NULL){
                        // do stuff with token here
                         if(strcmp(col, token) == 0){
                                index = temp; // if input col = current col, set target index to current temp val 
                        }
			temp++;
			c++; // increment number of cols
                        token = strtok(NULL, s); // make new token
                }
        }

	// go thru file + count number of rows

	while(fscanf(file, "%s\n", line)==1){
		r++;
	}

	// malloc 2D array
		// 2D array of strings right? So a 3D array? lmao
	int i = 0;
	char* arr[r][c];
	int i = 0, j = 0;
	for(i = 0; i < r; i++){ // malloc space for each string
		for(j = 0; j < c; j++){
			// is ths type right? or should it be char** ????
			arr[i][j] = (char*)malloc(1000 * sizeof(char));
		}
	}

	rewind(file); // go back to beginning of file to initialize array
	
	// tokenize file 
		// initialize array AND set up LL nodes w/ refs to array rows	
	fscanf(file, "%s\n", line); // skip first line

	i = 0;
	j = 0;
	while(fscanf(file, "%s\n", line)==1){
		
		token = strtok(line, s);
		while(token != NULL){
			// do stuff with token here

			// if token is empty/NULL
				// add to separate LL
				// arr[i][j] = null ???
			arr[i][j] = token;
			if(j == index){
				// create node 
				node->data = token;
				node->parent = &arr[i]; // do i need ampersand?? or is just arr[i] enough?
			}
			token = strtok(NULL, s); // make new token	
			j++;
		}
		j = 0;
		i++;
	}

	// need number of rows for 2D array
		// traverse csv for numRows
		// rewind file
		// traverse and populate array
	
	// at this point, array is set up
		// traverse column of interest
			// if NULL, add to separate list
				// keep this in original order
				// must append to front of sorted list
				// save references to head and tail of this list!! 
			// make node - 2 fields
				// array[i][j]
				// reference to current row
	
	// sort list
	
	// null list tail -> next = head of sorted list
	
	// return head of null list
	


	/*
 
	// scan csv file
	row* head = (row*)malloc(sizeof(row));
	row* realHead = head;
	// do one scan to process column names

le (fscanf(file, "%s,%s,%d,%d,%d,%d,%s,%d,%d,%s,%s,%s,%d,%d,%s,%d,%s,%s,%d,%s,%s,%s,%d,%d,%d,%d,%d,%d\n",
                 &color, &director_name, &num_critic_for_reviews, &duration, &director_facebook_likes, &actor_3_facebook_likes, &actor_2_name, &actor_1_facebook_likes, &gross, &genres, &actor_1_name, &movie_title, &num_voted_users, &cast_total_facebook_likes, &actor_3_name, &facenumber_in_poster, &plot_keywords, &movie_imdb_link, &num_user_for_reviews, &language, &country, &content_rating, &budget, &title_year, &actor_2_facebook_likes, &imdb_score, &aspect_ratio, &movie_facebook_likes)==28){
	continue;
	// what would i need to do lol	
}
	// rest of scanning
	while (fscanf(file, "%s,%s,%d,%d,%d,%d,%s,%d,%d,%s,%s,%s,%d,%d,%s,%d,%s,%s,%d,%s,%s,%s,%d,%d,%d,%d,%d,%d\n",
		 &color, &director_name, &num_critic_for_reviews, &duration, &director_facebook_likes, &actor_3_facebook_likes, &actor_2_name, &actor_1_facebook_likes, &gross, &genres, &actor_1_name, &movie_title, &num_voted_users, &cast_total_facebook_likes, &actor_3_name, &facenumber_in_poster, &plot_keywords, &movie_imdb_link, &num_user_for_reviews, &language, &country, &content_rating, &budget, &title_year, &actor_2_facebook_likes, &imdb_score, &aspect_ratio, &movie_facebook_likes)==28){		
		// make each row a struct ptr
		row* temp = (row*)malloc(sizeof(row));
		*temp = {color, director_name, num_critic_for_reviews, duration, director_facebook_likes, actor_3_facebook_likes, actor_2_names, actor_1_facebook_likes, gross, genres, actor_1_name, movie_title, num_voted_users, cast_total_facebook_likes, actor_3_name, facenumber_in_poster, plot_keywords, movie_imdb_link, num_user_for_reviews, language, country, content_rating, budget, title_year, actor_2_facebook_likes, imdb_score, aspect_ratio, movie_facebook_likes, head};
		
		//head = temp;
		
		// REMEMBER to add attribute node and point it to row node
	}
	// create a LL + return head
	return realHead;	
	
	*/
}

void sortAndWrite(FILE* file, column){
	node* csvStruct = makeStruct(file); // scan csv and create struct LL to represent it
		// take nodes with null data and put in on list, keeping order that we read from
		// reattach these to the front after sorting
		// sort struct LL
	// convert to file
	FILE* result = fopen("result.csv", "w+");
	while(csvStruct != NULL){
		// each attribute struct links to a row struct
		row* temp = csvStruct->rowstruct;
		
		write(result, temp->color, sizeof(temp->color));		// ^^ is th:is right? 
		// access each field in row struct and write to csv file
		// ???????? lmao 
		csvStruct = csvStruct->next;
	}
	// return csv file
	return result;
}



int main(int argc, char* argv[]){

	// how is CSV file read in???????

	if(argc != 3){
		printf("Bad input\n");
		return -1;
	}
	FILE* file = fopen(stdin, "r");
	if (file == NULL){
		printf("Empty file");
		return -1;
	}
	char* column[] = argv[2];
	sortAndWrite(file, column);
	return 0;
}
