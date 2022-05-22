#include "NearestNeighbours.h"
#include "BoundedPriorityQueue.h"
#include "DynamicTimeWarping.h"
#include "math.h"
#include <stdlib.h>

SketchDistance* nearestNeighbours(const Dataset* dataset, Sketch query, size_t k) {
    BoundedPriorityQueue *bpq = bpqCreate(k);
    if(!bpq)
        return NULL;

    size_t n = dataset->size ;
    double maxK;


    for(size_t i = 0; i < k; i++)
        bpqInsert(bpq, dtw(query, dataset->sketches[i], INFINITY), i);

    maxK = bpqMaximumKey(bpq);
    size_t j = k ;

    while(j < n){
        double DTWtmp = dtw(query, dataset->sketches[j], maxK);
        if(DTWtmp < maxK)
            bpqReplaceMaximum(bpq, DTWtmp, j);

        maxK = bpqMaximumKey(bpq);
        j++;
    }

    size_t *items = bpqGetItems(bpq);

    SketchDistance* SDArray = (SketchDistance*)malloc(k*sizeof(SketchDistance));

    for(size_t i = 0; i < k; i++){
        SDArray[i].sketch = &dataset->sketches[items[i]];
        SDArray[i].distance =  dtw(query, *SDArray[i].sketch, INFINITY);
    }

    bpqFree(bpq);
    free(items);

    return SDArray ;
}
