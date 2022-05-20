#include "BoundedPriorityQueue.h"
#include <stdlib.h>

struct bounded_priority_queue_t {
    size_t capacity ;
    size_t size ;
    double *keys ;
    size_t *data ;
};

/*============================================================================*/
/*============================== STATIC FUNCTIONS ============================*/
/*============================================================================*/
/* ------------------------------------------------------------------------- *
 *  swapVariable
 *  The elements have been switched
 *
 *  PARAMETERS
 *  a       element to swap
 *  b       element to swap
 *
 *  RETURN
 *  /
 * ------------------------------------------------------------------------- */
// T(n) = O(1)
static void swap(double *a, double *b){
    double tmp = *a;
    *a = *b;
    *b = tmp;
}
/* ========================================================================== */
/* ------------------------------------------------------------------------- *
 *  maxHeapify
 *  Changing the addresses in the list from largest to smallest in the bi-tree
 *
 *  PARAMETERS
 *  keys        keys...
 *  data        ... and their associated values
 *  size        heap-size
 *  i           index with the largest value
 *
 *  RETURN
 *  /
 * ------------------------------------------------------------------------- */
// T(n) = O(log n)
static void maxHeapify(double *keys, size_t *data, size_t size, size_t i){
    size_t left, right, largest;
    largest = i;
    left = 2 * i + 1;
    right = 2 * i + 2;

    // Check if left child exists and is larger than its parent
    if (left < size && keys[left] > keys[largest])
        largest = left;
    // Check if right child exists and larger than its parent
    if (right < size && keys[right] > keys[largest])
        largest = right;

    // if root is not the largest
    if (largest != i) {
        swap(&keys[i], &keys[largest]); //make root the largest
        swap((double*)&data[i], (double*)&data[largest]);
        maxHeapify(keys, data, size, largest); // Apply heapify to the largest node
    }
}
/*============================================================================*/
/*================================ FUNCTIONS =================================*/
/*============================================================================*/
BoundedPriorityQueue* bpqCreate(size_t capacity) {
    BoundedPriorityQueue *bpq = (BoundedPriorityQueue*)malloc(sizeof(BoundedPriorityQueue));
    if(!bpq)
        return NULL;

    bpq->keys = (double*)malloc(capacity*sizeof(double));
    if(!bpq->keys){
        free(bpq);
        return NULL;
    }

    bpq->data = (size_t*)malloc(capacity*sizeof(size_t));
    if(!bpq->data){
        free(bpq->keys);
        free(bpq);
        return NULL;
    }

    bpq->size = 0 ;
    bpq->capacity = capacity ;

    return bpq ;
}
/* ========================================================================== */
void bpqFree(BoundedPriorityQueue* bpq) {
    free(bpq->data);
    free(bpq->keys);
    free(bpq);
}
/* ========================================================================== */
// T(n) = O(log n)
bool bpqInsert(BoundedPriorityQueue* bpq, double key, size_t value) {
    if(bpq->size >= bpq->capacity)
        return false;

    size_t i = bpq->size ;
    bpq->size++ ;

    bpq->keys[i] = key ;
    bpq->data[i] = value ;

    while(i > 0 && bpq->keys[i/2] < bpq->keys[i]){
        size_t parent_i = i/2 ;
        swap(&bpq->keys[i], &bpq->keys[parent_i]);
        swap((double*)&bpq->data[i], (double*)&bpq->data[parent_i]);
        i = parent_i ;
    }

    return true;
}
/* ========================================================================== */
// T(n) = O(1)
void bpqReplaceMaximum(BoundedPriorityQueue* bpq, double key, size_t value) {
    if(bpq->size < 1)
        return ;

    bpq->keys[0] = key ;
    bpq->data[0] = value ;

    if(bpq->size > 1)
        maxHeapify(bpq->keys, bpq->data, bpq->size, 0);
}
/* ========================================================================== */
// T(n) = O(1)
double bpqMaximumKey(const BoundedPriorityQueue* bpq) {
    return bpq->keys[0];
}
/* ========================================================================== */
// T(n) = O(1)
size_t* bpqGetItems(const BoundedPriorityQueue* bpq) {
    return bpq->data ;
}
/* ========================================================================== */
// T(n) = O(1)
size_t bpqSize(const BoundedPriorityQueue* bpq) {
    return bpq->size ;
}
/* ========================================================================== */
// T(n) = O(1)
size_t bpqCapacity(const BoundedPriorityQueue* bpq) {
    return bpq->capacity;
}
/* ========================================================================== */
