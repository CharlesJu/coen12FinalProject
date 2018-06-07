# ifndef DATASET_H
# define DATASET_H

typedef struct dataset SET;

extern SET *createSet(int m); //done

extern void destroySet(SET *sp); //done

extern void searchAge(SET *sp, int a);   //done       //Print

extern void insert(SET *sp, int id, int age); //done

extern void removeStu(SET *sp, int age);           //Print

extern void maxAgeGap(SET *sp);  //done

extern void printAll(SET *sp);

# endif /* DATASET_H */