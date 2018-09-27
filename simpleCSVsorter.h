// this struct is a node that only contains comparing data
//***UPDATE** - these are the different types of nodes we can have
	// it seems like the columns can come in any order, so we need a next field for any of the possible types (string, int, float)
	// we will make a 2D array of nodes
		// heads of each inner list: column we're sorting by
		// rest of list: whole row
		// don't need row struct anymore; too inflexible anyway

typedef struct _node{

    void* data;
    char* row; // ptr to string array of row in csv 
    struct _node* next; // ptr to next node in LL
    // row parent;

}node;

/*
typedef struct node_{

    int data;
    char* row; // ptr to string	array of row in	csv
    struct node_* next;
    // row parent;

}intnode;

typedef struct _node_{

    float data;
    char* row; // ptr to string
    struct _node_* next;
    // row parent;

}floatnode;
*/

/*
// prototype function of the mergesort
void mergesort_i(intnode**);

void mergesort_f(floatnode**);

void mergesort_s(strnode**);
*/
