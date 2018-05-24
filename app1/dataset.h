# ifndef DATASET_H
# define DATASET_H

typedef struct dataset SET;

SET *createSet(int m);

void destroySet(SET *sp);

int searchAge(SET *sp, int a);          //Print

void insert(SET *sp, int age, int id);

void remove(SET *sp, int id);           //Print

void maxAgeGap(SET *sp);

# endif /* DATASET_H */