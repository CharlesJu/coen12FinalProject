# ifndef DATASET_H
# define DATASET_H

typedef struct dataset SET;

extern SET *createSet(int m);

extern void destroySet(SET *sp);

extern void searchID(SET *sp, int id);

extern void insert(SET *sp, int id, int age);

extern void removeStu(SET *SP, int id);

# endif /* DATASET_H */