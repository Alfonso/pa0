#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include "simpleCSVsorter.h"

void splitHalf(node*,node**,node**);

node* combineList(node*,node*,int);

void pTraverse(node*);

void cleanList(node*);

void addToFront(node**,char*,int);

/*
// testing to see if the sorting works
int main(int argc,char** argv){

    node* front = (node*) malloc(1*sizeof(node));
    addToFront(&front,"100",0);
    addToFront(&front,"150",1);
    addToFront(&front,"120",1);
    addToFront(&front,"1",1);
    addToFront(&front,"200",1);
    
    printf("Before sorted: ");
    pTraverse(front);
    mergesort(&front);
    printf("After sorted: ");
    pTraverse(front);
    cleanList(front);
   
     return 0;
}
*/

// each "node" has a refernce to the attribute that will
// be compared to each other. It also has a reference to
// the next node in the list. As well as a reference to
// its "parent" node that contains all of the other
// information in that row. This will be used to easily
// output the information after sorting

void mergesort(node** head,int (*comparatorFnPtr)(void*,void*)){

    // we have to assume that there are no negative
    // numbers in order to easily lexlexicographicly sort

    // check if head is null or is the only element in lis
    if(((*head) == NULL) || ((*head)->next == NULL)) { 
       // printf("You are a failure\n");
        return;    
    }
    // creates two empty lists to feed into split
    node* l1;
    node* l2;
    // split the list and fill l1 and l2
    splitHalf(*head,&l1,&l2);
    // sort l1
    mergesort(&l1,comparatorFnPtr);
    // sort l2
    mergesort(&l2,comparatorFnPtr);
    
    //merge l1 and l2
    *head = combineList(l1,l2,comparatorFnPtr);

    return;

}

// splits head into two lists a and b
// if it is odd, the first half will be longer
void splitHalf(node* head,node** a,node** b){

    node* ptr = head;
    int counter =0;
    // counting how many nodes there are in the list
    while(ptr != NULL){
        counter+=1;
        ptr = ptr -> next;
    }
    
    ptr = head;
    int half = 0;
    // Checks to see if # is odd, so that a can have more
    if( counter % 2 == 0){
        half = counter / 2;
    }else{
        half = (counter / 2) + 1;
    }
    
    // assigning first half of head to a
    *a = head;
    while(half>1){
        half-=1;
        ptr = ptr -> next;
    }
    // setting b equal to the second half
    // disconnecting the lists
    *b = ptr -> next;
    ptr -> next = NULL;

    return;
}

// this combines two sorted lists together and
// returns a newly sorted list
// it is done recursively
node* combineList(node* list1,node*list2,int (*comparatorFnPtr)(void*,void*)){
    // new front node of the combined list
    node* newFront; 
    
    // if any of the lists are empty, return the other
    if(list1 == NULL)
        return list2;
    else if(list2 == NULL)
            return list1;
    
    // compare the data
    if( comparatorFnPtr(list1->data,list2->data) > 0 ){
        newFront = list1;
        newFront->next = combineList(list1->next,list2,comparatorFnPtr);
    }else{
        newFront = list2;
        newFront->next = combineList(list1,list2->next,comparatorFnPtr);
    }

    return newFront;

}

// traverses the list and prints out each node
void pTraverse(node* head){
    int counter = 0;
    while(head != NULL){
        printf("%s->",head->data);
        head = head->next;
        counter+=1;
    }    
    printf("\n");
    //printf("%d\n",counter);
    return;
}

// frees up the nodes
void cleanList(node* head){
    node* t1 = head;
    node* t2 = NULL;
    while(t1 != NULL){
        t2 = t1;
        t1 = t1->next;
        free(t2);
    }
    return;
}

// adds a node to the front of a given list
void addToFront(node** front,char* strAdd,int firstTime){
    node* temp = (node*) malloc(1*sizeof(node));    
    if(firstTime == 0){
        temp -> next = NULL;
        temp -> data = strAdd;
        *front = temp;
        return;
    }
    temp -> data = strAdd;
    temp -> next = *front;
    *front = temp;
    
    return;
}

