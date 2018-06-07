# include <assert.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <stdlib.h>
# include "dataset.h"

# define EMPTY 0
# define FILLED 1
# define DELETED 2

typedef struct student {
    int id;
    int age;
} STU;

typedef struct dataset {
    char *flags;
    STU **data;
    int length;
    int count;
} SET;

SET *createSet(int m){
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);

    sp->data = malloc(sizeof(STU*)*m);
    assert(sp->data != NULL);

    sp->flags = malloc(sizeof(char)*m);
    assert(sp->data != NULL);

    for(int i = 0; i < m; i++){
        sp->flags[i] = EMPTY;
    }

    sp->length = m;
    sp->count = 0;

    return sp;
}

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

// static unsigned idhash(int id){
//     return id * id * 1153;
// }

static int compare(int a, int b){
    return a - b;
}

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

void searchID(SET *sp, int id){
    assert(sp != NULL);
    printf("Searching Student %d ...\n", id);
    bool found = false;
    int n = search(sp, id, &found);
    if(found){
        printf("Found Student %d | age: %d\n", id, sp->data[n]->age);
    } else {
        printf("Cannot Find Student %d\n", id);
    }
}

void insert(SET *sp, int id, int age){
    assert(sp != NULL);

    bool found = false;

    int n = search(sp, id, &found);

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

void removeStu(SET *sp, int id){
    assert(sp != NULL);
    bool found = false;
    int n = search(sp, id, &found);

    printf("Attempting to remove Student %d ...\n", id);
    
    if(found){
        printf("Removing Student: %d | age %d\n", id, sp->data[n]->age);
        free(sp->data[n]);
        sp->flags[n] = DELETED;
        sp->count--;
    } else {
        printf("Cannot Find Student %d\n", id);
    }
}



