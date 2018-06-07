# include <assert.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <stdlib.h>
# include "dataset.h"

# define EMPTY 0
# define FILLED 1
# define DELETED 2

//data structure to store information on students
typedef struct student {
    int id;
    int age;
} STU;

//data structure to store all students
typedef struct dataset {
    char *flags;    //Flags array to store array states
    STU **data;     //Student data, array of student pointers
    int length;
    int count;
} SET;

/**
 * @brief:  Compares two integers
 * @return: the difference between a and b
 */ 
static int compare(int a, int b){
    return a - b;
}

/**
 * @brief:  Uses a hash function with quadratic proving to find the student
 *          with the specified id
 *          Complexity: O(1) - Most times, O(n) - Worst case
 * @return: The student's index if it is found or an index to put the student
 */ 
static int search(SET *sp, int id, bool *found){

    assert(sp != NULL);

    int mem = -1;
    int n = 0;
    *found = false;

    for(int i = 0; i < sp->length; i++){
        //Quadratic hashing
        n = (id * 1151 + i * i) % sp->length;

        //Checks all three cases for the flag
        if(sp->flags[n] == FILLED){
            //Check if the values are the same if a filled element is encountered
            if(compare(sp->data[n]->id, id) == 0){
                *found = true;
                return n;
            }
        } else if(sp->flags[n] == EMPTY) {
            //Search ends when an empty element is encountered 
            if(mem > -1){
                //Return last deleted index if one is found
                return mem;
            } else {
                //Return hash otherwise
                return n;
            }
        } else if(sp->flags[n] == DELETED){ 
            //Remember the first deleted slot
            if(mem < 0){
                mem = n;
            }
        }
    } 
    return mem;
}

/**
 * @brief:  Creates a new set containing students
 * @return: the pointer to the new set
 */ 
SET *createSet(int m){

    //Allocate memory for the set, data, and flags pointers
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);

    sp->data = malloc(sizeof(STU*)*m);
    assert(sp->data != NULL);

    sp->flags = malloc(sizeof(char)*m);
    assert(sp->data != NULL);

    //Set all flags to empty and defualut values for other variables
    for(int i = 0; i < m; i++){
        sp->flags[i] = EMPTY;
    }

    sp->length = m;
    sp->count = 0;

    return sp;
}

/**
 * @brief:  Deallocate all memory associated with the SET pointed to by sp
 *          Complexity: O(n)
 */ 
void destroySet(SET *sp){
    assert(sp != NULL);

    //Free all filled elements in the array
    for(int i = 0; i < sp->length; i++){
        if(sp->flags[i] == FILLED){
            free(sp->data[i]);
        }
    }

    //Free the rest of the data
    free(sp->flags);
    free(sp->data);
    free(sp);
}

/**
 * @brief:  Uses a hashtable to find student with th specified id
 *          and print out whether it has be found
 *          Complexity: Complexity: O(1) - Most times, O(n) - Worst case
 */ 
void searchID(SET *sp, int id){
    assert(sp != NULL);
    printf("Searching Student %d ...\n", id);
    bool found = false;

    //Use hash function to find the index of the student
    int n = search(sp, id, &found);
    if(found){
        printf("Found Student %d | age: %d\n", id, sp->data[n]->age);
    } else {
        printf("Cannot Find Student %d\n", id);
    }
}
/**
 * @brief:  Insert student with specified id and age into the hashtable
 *          Complexity: O(1) - Most times, O(n) - Worst case
 */ 
void insert(SET *sp, int id, int age){
    assert(sp != NULL);
    bool found = false;

    //Use the hash function to find the index
    int n = search(sp, id, &found);

    //Add the student if it's not in the list
    if(!found){
        sp->data[n] = malloc(sizeof(STU));
        sp->data[n]->id = id;
        sp->data[n]->age = age;
        sp->flags[n] = FILLED;
        sp->count++;
        printf("Adding Student at [%d]   \tid: %d,\tage: %d\n", n, id, age);

    } else {
        printf("Student %d already exists\n", id);
    }
}

/**
 * @brief:  Remove student with specified id from the hashtable
 *          Complexity: O(1) - Most times, O(n) - Worst case
 */ 
void removeStu(SET *sp, int id){
    assert(sp != NULL);
    bool found = false;

    //Use the hash function to find the index
    int n = search(sp, id, &found);

    printf("Attempting to remove Student %d ...\n", id);
    
    //Remove the student if it is in the hashtable
    if(found){
        printf("Removing Student: %d | age %d\n", id, sp->data[n]->age);
        free(sp->data[n]);
        sp->flags[n] = DELETED;
        sp->count--;
    } else {
        printf("Cannot Find Student %d\n", id);
    }
}



