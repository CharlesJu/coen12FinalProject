# ifndef DATASET_H
# define DATASET_H

typedef struct dataset SET;

SET *createSet(int m);

void destroySet(SET *sp);

void searchAge(SET *sp, int a);          //Print

void insert(SET *sp, int id, int age);

void removeStu(SET *sp, int id);           //Print

void maxAgeGap(SET *sp);

# endif /* DATASET_H */