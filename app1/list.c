#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include "list.h"

//Strucutre of a node in a linked list
typedef struct node{
    void *data;         //The generic void pointer to the data
    struct node *prev;  //Pointer to previous node
    struct node *next;  //Pointer to next node
} NODE;

//Strucutre of head of a list
typedef struct list {
    int length;         //The length of the linked list
    int (*compare)();   //The pointer to the compare function
    NODE *head;         //The pointer to the dummy node at the beginning of the list
} LIST;

/**
 * O(1) assuming malloc takes O(1)
 * @brief: Creates an empty circular doubly linked list with a dummy node
 * @param compare: pointer to the compare function
 * @return: pointer to a new list
 */
LIST *createList(int (*compare)()){
    
    //Allocate memory for the list structure
    LIST *lp;
    lp = malloc(sizeof(LIST));
    assert(lp != NULL);

    //Allocate memory for the dummy node
    NODE *dummy;
    dummy = malloc(sizeof(NODE));
    assert(dummy != NULL);

    //Set default values for the dummy node
    dummy->next = dummy;
    dummy->prev = dummy;

    //Set default values for the list
    lp->length = 0;
    lp->head = dummy;
    lp->compare = compare;

    return lp;
}

/**
 * O(n)
 * @brief: deallocate memory associated with the list pointed to by lp
 * @param lp: the pointer to the list to be deallocated
 */ 
void destroyList(LIST *lp){
    
    //Make sure lp points to a valid list
    assert(lp != NULL);
    
    //pDel is the pointer to be deleted
    NODE *pDel = lp->head;
    
    //Loops through every node including the dummy node and delet it
    while(pDel != lp -> head){
        lp->head = pDel->next;
        free(pDel);
        pDel = lp->head;
    }
    
    //Free the list pointer
    free(lp);
}

/**
 * O(1)
 * @breif: Shows how many numbers there are in the list
 * @param lp: the pointer to the linked list
 * @return: the number of items in the list pointed to by lp
 */ 
int numItems(LIST *lp){
    //Make sure lp points to a valid list
    assert(lp != NULL);
    return lp->length;
}

/**
 * O(1)
 * @breif: add item as the first element in the linked list
 * @param lp: the pointer to the linked list
 * @param item: the value of the data added to the linked list
 */ 
void addFirst(LIST *lp, void *item){
    
    //Make sure the lp and item pointers are valid
    assert(lp != NULL && item != NULL);
    
    //Allocate memory for the new node
    NODE *first = malloc(sizeof(NODE));
    assert(first != NULL);
    
    //Create variables for the dummy node and the old first node
        /*This is done to make the code easier to understand*/
    NODE *dummy = lp->head;
    NODE *next = dummy->next;
    
    //Set the data of the node to the item provided
    first->data = item;
    
    //Update pointers to the correct nodes
    first->next = next;
    first->prev = dummy;
    dummy->next = first;
    next->prev = first;
    
    //Increment the length for the list
    lp->length++;
}

/**
 * O(1)
 * @breif: add item as the last element in the linked list
 * @param lp: the pointer to the linked list
 * @param item: the value of the data added to the linked list
 */ 
void addLast(LIST *lp, void *item){
    
    //Make sure the lp and item pointers are valid
    assert(lp != NULL && item != NULL);
    
    //Allocate memory for the new node
    NODE *last = malloc(sizeof(NODE));
    assert(last != NULL);
    
    //Create variables for the dummy node and the old last node
        /*This is done to make the code easier to understand*/
    NODE *dummy = lp->head;
    NODE *prev = dummy->prev;
    
    //Set the data of the node to the item provided
    last->data = item;
    
    //Update pointers to the correct nodes
    last->next = dummy;
    last->prev = prev;
    prev->next = last;
    dummy->prev = last;
    
    //Increment the length of the list
    lp->length++;
}

/**
 * O(1)
 * @breif: remove the firts element of the linked list
 * @param lp: the pointer to the linked list
 * @return: the pointer of the data contained in the first node
 */ 
void *removeFirst(LIST *lp){
    
    //Make sure lp pointer is valid
    assert(lp != NULL);
    
    //Make sure the list is not empty
    assert(lp->length > 0);
    
    //Create variables for the dummy, first, and the new first node
        /*This is done to make the code easier to understand*/
    NODE *dummy = lp->head;
    NODE *first = dummy->next;
    NODE *next = first->next;
    
    //Update pointers to the correct nodes
    dummy->next = next;
    next->prev = dummy;
    
    //Create variable to store the pointer to the data in the node to be deleted
    void *data = first->data;
    first->data = NULL;
    
    //Deallocates the memory
    free(first);
    
    //Decrements the length of the list
    lp->length--;

    return data;
}

/**
 * O(1)
 * @breif: remove the last element of the linked list
 * @param lp: the pointer to the linked list
 * @return: the pointer of the data contained in the last node
 */ 
void *removeLast(LIST *lp){
    
    //Make sure the lp pointer is valid
    assert(lp != NULL);
    
    //Make sure the list is not empty
    assert(lp->length > 0);
    
    //Create variables for the dummy, last, and the new last node
        /*This is done to make the code easier to understand*/
    NODE *dummy = lp->head;
    NODE *last = dummy->prev;
    NODE *prev = last->prev;
    
    //Update pointers to the correct nodes
    dummy->prev = prev;
    prev->next = dummy;
    
    //Create variables to store the pointer to the data in the node to be deleted
    void *data = last->data;
    last->data = NULL;
    
    //Deallocates the memory
    free(last);
    
    //Decrements the length of the list
    lp->length--;
    
    return data;
}

/**
 * O(1)
 * @breif: show the data in the first node of the list
 * @param lp: the pointer to the linked list
 * @return: the pointer of the data contained in the first node
 */ 
void *getFirst(LIST *lp){
    //Make sure the lp pointer is valid
    assert(lp != NULL);
    //Make sure the list is not empty
    assert(lp->length > 0);
    
    //Return the first element in the linked list
    return lp->head->next->data;
}

/**
 * O(1)
 * @breif: show the data in the last node of the list
 * @param lp: the pointer to the linked list
 * @return: the pointer of the data contained in the last node
 */ 
void *getLast(LIST *lp){
    
    //Make sure the lp pointer is valid
    assert(lp != NULL);
   
    //Make sure the list is not empty
    assert(lp->length > 0);

    //Return the last element in the linked list
    return lp->head->prev->data;
}

/**
 * O(n)
 * @breif: finds an element in the linked list
 * @param lp: the pointer to the linked list
 * @param target: the value that the function that is trying to find
 * @param found: pointer to a boolean variable to indicate if the value has been found
 * @return: the pointer of node that contains data equal to the value target or NULL if it is not found
 */ 
static NODE *search(LIST *lp, void *target, bool *found){

    /* No need to assert for *lp and *item because it is a static 
    function and these values would have already been asserted.*/

    //Create variables for the dummy node
    NODE *dummy = lp->head;
    
    //Create variable for the node that is being compared
    NODE *pLoc = dummy->next;
        /*This is done to make the code easier to understand*/

    //Set default value for the found value to false
    *found = false;

    if(lp->length == 0){
        return NULL;
    }

    //Loop through the linked list to find the value
    while(pLoc != dummy){
        //If the data in the list is the same as target return the node to that element
        if((*lp->compare)(target, pLoc->data) == 0){
            *found = true;
            return pLoc;
        }
        pLoc = pLoc->next;
    }

    //If the data is not in the list, return NULL
    return NULL;
}

/**
 * O(n) because it uses the search function
 * @breif: if item is present in the list, then remove it
 * @param lp: the pointer to the linked list 
 * @param item: the value of the element that needs to be removed
 */ 
void removeItem(LIST *lp, void *item){

    //Make sure lp and item pointers are valid
    assert(lp != NULL && item != NULL);
    
    //Boolean to detect if the item is found
    bool found = false;
    
    //Run search function to find the pointer to the element
    NODE *del = search(lp, item, &found);
    
    //If the value is found, remove it
    if(found){
        
        //Set pointers to the correct nodes
        del->prev->next = del->next;
        del->next->prev = del->prev;
        
        //Deallocate the element
        free(del);
    }
}

/**
 * O(n) because it uses the search function
 * @breif: Find a specific element in the list
 * @param lp: the pointer to the linked list 
 * @param item: the value of the element the function is trying to find
 * @return: the pointer to the item in the list or NULL if it is not in the list
 */ 
void *findItem(LIST *lp, void *item){

    //Make sure lp and item pointers are valid
    assert(lp != NULL && item != NULL);

    //Boolean to detect if the item is found
    bool found = false;

    //Run search function to find pointer to the element
    NODE *pNode = search(lp, item, &found);

    //If the value is found, then return the pointer to that value
    if(found){
        return pNode->data;
    } 
    return NULL;
}

/**
 * O(n) because it needs to copy every value in the list
 * @brief: Get an array containing all values in the list
 * @param lp: the pointer to the linked list
 * @return: array of items in the list pointed to by lp
 */ 
void *getItems(LIST *lp){

    //Make sure lp pointer is valid
    assert(lp != NULL);
    
    //Allocate memory for the array
    void **values = malloc(sizeof(void*)*lp->length);
    assert(values != NULL);

    //Set initial node to the first element of the array
    NODE *loc = lp->head->next;
    
    //Put every value in the linked list into its corresponding index in the array
    for(int i = 0; i < lp->length; i++){
        values[i] = loc->data;
        loc = loc->next;
    }

    //Return the array
    return values;
}
