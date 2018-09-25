/*
// this struct contains all of the data in the rows
typedef struct _row{

    char* color;
    char* director_name;
    int num_critic_for_reviews;
    int duration; // int vs timeDate?
    int director_facebook_likes;
    int actor_3_facebook_likes;
    char* actor_2_name;
    int actor_1_facebook_likes;
    long gross;
    char* genres;
    char* actor_1_name;
    char* movie_title;
    int num_voted;
    int case_total_facebook_likes;
    char* actor_3_name;
    char* facenumber_in_poster;
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
    struct _row* next;

} row;

*/


// this struct is a node that only contains comparing data
//***UPDATE** - these are the different types of nodes we can have
	// it seems like the columns can come in any order, so we need a next field for any of the possible types (string, int, float)
	// we will make a 2D array of nodes
		// heads of each inner list: column we're sorting by
		// rest of list: whole row
		// don't need row struct anymore; too inflexible anyway

typedef struct _node{

    char* data;
    char* row; // ptr to string array of row in csv 
    struct _node* next; // ptr to next node in LL
    // row parent;

}strnode;

typedef struct node_{

    int data;
    char* row; // ptr to string	array of row in	csv
    struct node_* next;
    // row parent;

}intnode;

typedef struct _node_{

    float data;
    struct char** row; // ptr to string	array of row in	csv
    struct _node_* next;
    // row parent;

}floatnode;

// prototype function of the mergesort
void mergesort(intnode**);

void mergesort(floatnode**);

void mergesort(strnode**);
