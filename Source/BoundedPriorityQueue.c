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
 *  parent
 *  returns the parent of the argument
 *
 *  PARAMETERS
 *  i       child whose parent we are searching for
 *
 *  RETURN
 *  the parent of i
 * ------------------------------------------------------------------------- */
// T(n) = O(1)
static size_t parent(size_t i){
  return (i-1)/2;
}
/* ========================================================================== */
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
static void swap_double(double *a, double *b){
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

static void swap_int(size_t *a, size_t *b){
    size_t tmp = *a;
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
        swap_double(&keys[i], &keys[largest]); //make root the largest
        swap_int(&data[i], &data[largest]);
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

    bpq->keys[i] = key ;
    bpq->data[i] = value ;

    while(i > 0 && bpq->keys[parent(i)] < bpq->keys[i]){
        swap_double(&bpq->keys[i], &bpq->keys[parent(i)]);
        swap_int(&bpq->data[i], &bpq->data[parent(i)]);
        i = parent(i) ;
    }

    bpq->size++ ;

    return true;
}
/* ========================================================================== */
// T(n) = O(log n)
void bpqReplaceMaximum(BoundedPriorityQueue* bpq, double key, size_t value) {
    size_t n = bpq->size ;
    if(n < 1)
        return ;

    bpq->keys[0] = key ;
    bpq->data[0] = value ;

    if(n > 1)
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
    if(!bpq->size)
        return NULL;

    size_t *items = (size_t*)malloc(bpq->size*sizeof(size_t));

    for(size_t i = 0; i < bpq->size; i++){
        items[i] = bpq->data[i];
    }

    return items;
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
