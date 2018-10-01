/ this struct is a node that only contains comparing data
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

}node;

// return > 0 ---> then data1 > data0
// return < 0 ---> then data1 < data0
// return == 0 ---> then data1 == data0
int comparator_FLT(void*,void*);

int comparator_STR(void*,void*);

// prototype function of the mergesort
void mergesort(node**,int(*)(void*,void*));
