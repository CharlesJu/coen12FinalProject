# include <assert.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "list.h"

typedef struct dataset{
    LIST **data;
    int min;
    int max;
    int count;
    int length;
} SET;

SET *createSet(int m);

void destroySet(SET *sp);

int searchAge(SET *sp, int a);          //Print

void insert(SET *sp, int age, int id);

void remove(SET *sp, int id);           //Print

void maxAgeGap(SET *sp);