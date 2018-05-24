# ifndef DATASET_H
# define DATASET_H

typedef struct dataset SET;

SET *createSet(int m);

void destroySet(SET *sp);

void searchID(SET *sp, int id);

void insert(SET *sp, int id, int age);

void remove(SET *SP, int id);

# endif /* DATASET_H */