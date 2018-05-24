# ifndef DATASET_H
# define DATASET_H

typedef struct dataset SET;

SET *createSet();

void destroySet(SET *sp);

void searchID(SET *sp, int id);

void searchAge(SET *sp, int age);

void insert(SET *sp, int id, int age);

void remove(SET *sp, int id);

void maxAgeGap(SET *sp);

# endif /* DATASET_H */