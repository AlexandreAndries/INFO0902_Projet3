#include <stdio.h>
#include "BoundedPriorityQueue.h"

int main(void){
    size_t cap = 10;
    BoundedPriorityQueue* bpq = bpqCreate(cap);

    printf("bpq created\n");


    bpqInsert(bpq, 1, 1);
    bpqInsert(bpq, 4, 4);
    bpqInsert(bpq, 2, 2);
    bpqInsert(bpq, 3, 3);
    bpqInsert(bpq, 9, 9);
    bpqInsert(bpq, 7, 7);
    bpqInsert(bpq, 8, 8);
    bpqInsert(bpq, 10, 10);
    bpqInsert(bpq, 14, 14);
    bpqInsert(bpq, 16, 16);

    size_t *it = bpqGetItems(bpq);

    printf("inserted\n");
    for(size_t i = 0; i < cap; i++){
      printf("%lu ", it[i]);
    }
    printf("\n\n");


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
