// Name: Yinsheng Dong
// Student Number: 11148648
// NSID: yid164
// Lecture Section: CMPT 214 T01



#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <math.h>
#include <inttypes.h>

// typedef a Elem float
typedef float Elem;
// ... ( Elem e, Elem s )
//  ... e+s ...
//  ... e-s ...
//  ... e*s ...
//  ... e/s ...


// a sturct for Vector
// include Elem el that is an array to store floats
// make an size (S) that greater than 0
struct Vector
{
    Elem *el;
    uint16_t S;
};
// ... ( Vector v, ... ) {
//  ... v->N ...
//  ... v->data[i] ...


// set up a integer that limite the max elements number
const int MAX_ELEMS = UINT16_MAX;



// alloc_vec is allocate a new Vector
// Vector size is 0
// Input: Nothing
// Output: return an vector that size is 0,
// Nothing in the array
Vector *alloc_vec(void);



// dealloc_vec frees up the memory
// Input:should be a non-empty vector
// All memeory that *vector used should deallocated
// Output: nothing
void dealloc_vec(Vector*);


// extend_vec copy the old input vector and make a new vector that add 1 element
// Input: should have a non-NULL vector and an Elem
// Output: should have a new vector that include the old vector's elements added the new Elem
Vector *extend_vec(Vector*, Elem);


// print_vec print all of elements in the Vector
// Input: should have an unempety vector
// Output: should printout all of the elements in this input vector
bool print_vec(Vector*);



#endif
