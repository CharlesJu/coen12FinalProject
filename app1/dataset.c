# include <assert.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "dataset.h"

# define N_AGES 13

typedef struct student {
    int id;
    int age;
} STU;

typedef struct dataset{
    STU **data;
    int count;
    int length;

} SET;

static STU *makeStudent(int id, int age){
    STU *stu = malloc(sizeof(STU));
    assert(stu != NULL);
    stu->age = age;
    stu->id = id;

    return stu;
}

static int compareId(STU *a, STU *b){
    assert(a != NULL && b != NULL);
    return a->id - b->id;
}

static int compareAge(STU *a, STU *b){
    assert(a != NULL && b != NULL);
    return a->age - b->age;
}

SET *createSet(int m){
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);

    sp->count = 0;
    sp->length = m;
    
    sp->data = malloc(sizeof(STU*)*m);
    assert(sp->data != NULL);

    return sp;
}

void destroySet(SET *sp){
    assert(sp != NULL);

    for(int i = 0; i < sp->count; i++){
        free(sp->data[i]);
    }
    free(sp->data);
    free(sp);
}

static int bSearch(SET *sp, int age, bool *found){
    assert(sp != NULL);
    *found = false;
    int hi = sp->count - 1;
    int lo = 0;
    int mid = 0;

    while(lo <= hi){
        mid = (lo + hi)/2;
        if(sp->data[mid]->age > age){
            hi = mid - 1;
        } else if(sp->data[mid]->age < age){
            lo = mid + 1;
        } else {
            *found = true;
            return mid;
        }
    }

    return lo;
}

void insert(SET *sp, int id, int age){
    assert(sp != NULL);
    STU *stu = makeStudent(id, age);
    bool found = false;
    int i = bSearch(sp, age, &found);
    printf("Inserting Student: %d | age: %d\n", id, age);
    for(int j = sp->count; j > i; j--){
        sp->data[j] = sp->data[j-1];
    }
    sp->data[i] = makeStudent(id, age);
    sp->count ++;
}

void maxAgeGap(SET *sp){
    int min = sp->data[0]->age;
    int max = sp->data[sp->count-1]->age;
    int gap = max - min;

    printf("Max Age: %d | Min Age: %d | Age Gap: %d\n", max, min, gap);
}

void searchAge(SET *sp, int a){
    assert(sp != NULL);
    printf("Searing for students age %d\n", a);
    for(int i = 0; (i < sp->count) && (sp->data[i]->age <= a); i++){
        if(sp->data[i]->age == a){
            printf("Found Student %d\n", sp->data[i]->id);
        }
    }
}

void removeStu(SET *sp, int id){
    assert(sp != NULL);
    bool found = false;
    int i;
    printf("Attempting to remove student %d\n", id);
    for(i = 0; i < sp->count && !found; i++){
        if(sp->data[i]->id == id){
            found = true;
        }
    }
    if(found){
        printf("Removing student id: %d | age %d\n", id, sp->data[i]->age);
        free(sp->data[i]);
        for(int j = i + 1; j < sp->count; j++){
            sp->data[j-1] = sp->data[j];
        }
        sp->count--;
    } else {
        printf("Couldn't find student %d\n", id);
    }
    
}

void printAll(SET *sp){
    assert(sp != NULL);
    for(int i = 0; i < sp->count; i++){
        printf("#%d: %d \n", sp->data[i]->id, sp->data[i]->age);
    }
}