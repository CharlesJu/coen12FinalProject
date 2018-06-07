# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <time.h>
# include "dataset.h"

# define MAX_STUDENTS 3000

int ran(int min, int max){
    return ((rand() % (max - min + 1)) + min);
}

int main(void){
    srand(time(NULL));
    SET *sp = createSet(MAX_STUDENTS);
    int id = ran(1, 2);
    for(int i = 0; i < 15; i++){
        int age = ran(18, 30);
        insert(sp, id, age);
        id += ran(1,2);
    }

    printAll(sp);
    searchAge(sp, ran(18,30));
    removeStu(sp, ran(18, 30));
    // printAll(sp);
    maxAgeGap(sp);
    destroySet(sp);
    return 0;
}