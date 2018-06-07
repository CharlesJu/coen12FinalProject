# include <assert.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "dataset.h"

//data structure to store information on students
typedef struct student {
    int id;
    int age;
} STU;

//data structure to store all students
typedef struct dataset{
    STU **data;     //Student data, array of student pointers
    int count;      
    int length;

} SET;
/**
 * @brief: Makes new student structure
 * @return: student struct pointer
 */ 
static STU *makeStudent(int id, int age){
    STU *stu = malloc(sizeof(STU));
    assert(stu != NULL);
    stu->age = age;
    stu->id = id;

    return stu;
}

/**
 * @brief:  compares the the id of two students
 *          Complexity: O(1)
 * @return: Negative int if the integer value of student a's id is less 
 *          than b. Positive int if the integer value of student a's id 
 *          is more than b. Zero if they're the same
 */ 
static int compareId(STU *a, STU *b){
    assert(a != NULL && b != NULL);
    return a->id - b->id;
}

/**
 * @brief:  compares the the age of two students
 *          Complexity: O(1)
 * @return: Negative int if the integer value of student a's age is less 
 *          than b. Positive int if the integer value of student a's age 
 *          ismore than b. Zero if they're the same
 */ 
static int compareAge(STU *a, STU *b){
    assert(a != NULL && b != NULL);
    return a->age - b->age;
}

/**
 * @brief:  Creates a new set containing students
 * @return: the pointer to the new set
 */ 
SET *createSet(int m){

    //Allocate memory for set and data pointers
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);

    sp->data = malloc(sizeof(STU*)*m);
    assert(sp->data != NULL);

    //Set default values for all values
    sp->count = 0;
    sp->length = m;

    return sp;
}

/**
 * @brief:  Deallocate all memory associated with the SET pointed to by sp
 *          Complexity: O(n)
 */ 
void destroySet(SET *sp){
    assert(sp != NULL);

    for(int i = 0; i < sp->count; i++){
        free(sp->data[i]);
    }
    free(sp->data);
    free(sp);
}
/**
 * @brief:  Uses binary search to determine an index in the data array
 *          of SET sp where student with specified age should be placed
 *          Complexity: O(logn)
 * @return: The index in the datay array of SET sp of where the student 
 *          should be place 
 */ 
static int bSearch(SET *sp, int age){
    assert(sp != NULL);

    //Set initial values for search
    int hi = sp->count - 1;
    int lo = 0;
    int mid = 0;

    //Divide set into half until the value is found
    while(lo <= hi){
        mid = (lo + hi)/2;
        if(sp->data[mid]->age > age){
            hi = mid - 1;
        } else if(sp->data[mid]->age < age){
            lo = mid + 1;
        } else {
            return mid;
        }
    }

    //Return the location where student is supposed to be if not found
    return lo;
}
/**
 * @brief:  Detects if the student id is in the data list of sp
 *          Complexity: O(n)
 * @return: Boolean true if found, false if not
 */ 
static bool searchID(SET *sp, int id){
    assert(sp != NULL);
    for(int i = 0; i < sp->count; i++){
        if(sp->data[i]->id == id){
            return true;
        }
    }
    return false;
}

/**
 * @brief:  Inserts a new student into the data array of SET sp in
 *          accending order in terms of age
 *          Complexity: O(n)
 */ 
void insert(SET *sp, int id, int age){
    assert(sp != NULL);

    //Make sure the student is not in the list
    if(searchID(sp, id)){
        printf("Insertion failed because student %d is already in the list", id);
        return;
    }

    //Determine index of where the new student should be placed
    int i = bSearch(sp, age);
    // printf("Inserting Student: %d | age: %d\n", id, age);

    //Shift all values above to make room in the array
    for(int j = sp->count; j > i; j--){
        sp->data[j] = sp->data[j-1];
    }

    //Make new student at the index
    sp->data[i] = makeStudent(id, age);
    sp->count ++;
}
/**
 * @brief:  Calculates and prints the max/min age and the max age gap
 *          Complexity: O(1)
 */ 
void maxAgeGap(SET *sp){
    int min = sp->data[0]->age;
    int max = sp->data[sp->count-1]->age;
    int gap = max - min + 1;

    printf("Max Age: %d | Min Age: %d | Age Gap: %d\n", max, min, gap);
}
/**
 * @brief:  Prints the id of all students with age a
 *          Complexity: O(n)
 */ 
void searchAge(SET *sp, int a){
    assert(sp != NULL);
    printf("Searing for students age %d\n", a);
    
    //Looks at value in the array until age a and print their id if the age is a
    for(int i = 0; (i < sp->count) && (sp->data[i]->age <= a); i++){
        if(sp->data[i]->age == a){
            printf("Found Student %d\n", sp->data[i]->id);
        }
    }
}

/**
 * @brief:  Remove the student with the matching id
 */ 
void removeStu(SET *sp, int id){
    assert(sp != NULL);
    bool found = false;
    int i;
    printf("Attempting to remove student %d\n", id);

    //Go through the array until the student if found
    for(i = 0; i < sp->count && !found; i++){
        if(sp->data[i]->id == id){
            found = true;
        }
    }
    if(found){
        i--;
        printf("Removing student id: %d | age %d\n", id, sp->data[i]->age);

        //Deallocate memory associated with the pointer and shift all values down
        free(sp->data[i]);
        for(int j = i + 1; j < sp->count; j++){
            sp->data[j-1] = sp->data[j];
        }
        sp->count--;
    } else {
        printf("Couldn't find student %d\n", id);
    }
    
}

/**
 * @brief:  prints the index, id, and age of every student in the student data array
 *          in the SET pointed to by sp
 */ 
void printAll(SET *sp){
    assert(sp != NULL);
    for(int i = 0; i < sp->count; i++){
        printf("[%d]\t#%d: %d \n", i, sp->data[i]->id, sp->data[i]->age);
    }
}