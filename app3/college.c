# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <time.h>
# include "dataset.h"

int random(int min, int max){
    return ((rand() % (max - min + 1)) + min);
}

int main(void){
    SET *sp = createSet();
    int id = random(1, 2);
    for(int i = 0; i < 1000; i++){
        int age = random(18, 30);
        insert(sp, age, id);
        id += random(1,2);
    }
    searchAge(sp, random(18, 30));
    searchID(sp, random(1, 2000));
    remove(sp, random(1, 2000));
    maxAgeGap(sp);
    destroySet(sp);
    return 0;
}