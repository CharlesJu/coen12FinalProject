# include <assert.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "list.h"

# define N_AGES 13

typedef struct student {
    int id;
    int age;
} STU;

typedef struct dataset{
    LIST **data;
    int min;
    int max;
    int count;
} SET;

static unsigned agehash(int age){
    return age - 18;
}

static STU *makeStudent(int id, int age){
    STU *stu = malloc(sizeof(STU));
    assert(stu != NULL);
    stu->age = age;
    stu->id = id;
}

static int compare(STU *a, STU *b){
    return a->id - b->id;
}

SET *createSet(){
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);

    sp->min = -1;
    sp->max = -1;
    sp->count = 0;

    sp->data = malloc(sizeof(LIST*)*N_AGES);
    assert(sp->data != NULL);

    return sp;
}

void destroySet(SET *sp){
    assert(sp != NULL);

    for(int i = 0; i < N_AGES; i++){
        if(sp->data[i] != NULL){
            destroyList(sp->data[i]);
        }
    }
    free(sp->data);
    free(sp);
}

void searchAge(SET *sp, int age){
    assert(sp != NULL);

    STU **students = getItems(sp->data[agehash(age)]);
    int n = sizeof(students) / sizeof(STU);
    for(int i = 0; i < n; i++){
        printf("Student ID: %d\n", students[i]->id);
    }
};          //Print

void insert(SET *sp, int id, int age){
    assert(sp != NULL);

    STU *stu = makeStudent(id, age);
    if(sp->min == -1 && sp->max == -1){
        sp->min = age;
        sp->max = age;
    } else if(age < sp->min){
        sp->min = age;
    } else if(age > sp->max){
        sp->max = age;
    }
    sp->count ++;
    if(sp->data[agehash(age)] == NULL){
        sp->data[agehash(age)] = createList(compare);
    }

    addFirst(sp->data[agehash(age)], stu); 
}

void removeStu(SET *sp, int id){
    assert(sp != NULL);
    STU *stu;
    int i;
    for(i = agehash(sp->min); i < agehash(sp->max) + 1; i++){
        stu = findItem(sp->data[i], makeStudent(id, 0));
        if(stu != NULL){
            break;
        }
    }
    if(stu != NULL){
        printf("Removing Student %d | age: %d\n", id, stu->age);
        sp->count--;
        if(numItems(sp->data[i]) == 1){
            if(stu->age < sp->min){
                
            }  
        }
    } else {
        printf("Cannot Find Student &d\n", id);
    }
}           //Print

void maxAgeGap(SET *sp);