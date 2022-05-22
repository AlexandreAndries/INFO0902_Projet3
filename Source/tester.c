#include <stdio.h>
#include "BoundedPriorityQueue.h"

int main(void){
    size_t cap = 10;
    BoundedPriorityQueue* bpq = bpqCreate(cap);

    printf("bpq created\n");


    for(size_t i = 1 ; i < cap+3 ; i++){
        bool ret = bpqInsert(bpq, i, i);
        printf("%d\n", ret);
    }


    printf("inserted\n");


    bpqReplaceMaximum(bpq, 1.05, 56);
    printf("replaced 1 - ok\n");

    bpqReplaceMaximum(bpq, 16, 55);
    printf("replaced 2 - ok\n");


    double maxK = bpqMaximumKey(bpq);
    printf("maxK = %lf\n", maxK);
    size_t size = bpqSize(bpq);
    printf("size = %lu\n", size);
    size_t capacity = bpqCapacity(bpq);
    printf("cap = %lu\n", capacity);

    printf("constants ok\n");

    size_t *items = bpqGetItems(bpq);
    for(size_t i = 0; i < cap; i++){
      printf("%lu ", items[i]);
    }
    printf("\n\n");
    printf("items ok\n");

    bpqFree(bpq);
    printf("bpq freed\n");



    return 0;
}
