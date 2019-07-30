// Name: Yinsheng Dong
// Student Number: 11148648
// NSID: yid164
// Lecture Section: CMPT 214 T01


#include <stdio.h>
#include <stdlib.h>
#include "vector.h"


// alloc_vec is allocate a new Vector
// Vector size is 0
// Input: Nothing
// Output: return an vector that size is 0,
// Nothing in the array
Vector *alloc_vec(void)
{
    Vector *vec = new Vector;
    if(vec !=NULL)
    {
        vec->S = 0;
        vec->el = NULL;
    }
    return vec;
}



// dealloc_vec frees up the memory
// Input:should be a non-empty vector
// All memeory that *vector used should deallocated
// Output: nothingvoid dealloc_vec(Vector *vec)
void dealloc_vec(Vector *vec)
{
    if (vec->S >0)
    {
        delete [] vec->el;
        delete vec;
    }
}


// extend_vec copy the old input vector and make a new vector that add 1 element
// Input: should have a non-NULL vector and an Elem
// Output: should have a new vector that include the old vector's elements added the new Elem
Vector *extend_vec(Vector *vec, Elem el)
{
    // check size of vector.
    if(vec->S >= MAX_ELEMS)
    {
        return NULL;
    }
    // allocate new structure
    Vector *newVec = new Vector;
    if (newVec == NULL)
    {
        return NULL;
    }
    // vector is one bigger than old
    int a = vec->S;
    // allocate space for vector elements
    newVec->S = a+1;
    newVec->el = new Elem[newVec->S];
    // if space allocation failed free up already-allocated space
    if(newVec->el == NULL)
    {
        delete newVec;
        return NULL;
    }
    // copy over old vector elements
    for (int i=0; i<a; i++)
    {
        newVec->el[i] = vec->el[i];
    // add (append) new vector element
    }
    newVec->el[a]=el;
    return newVec;
}


// print_vec print all of elements in the Vector
// Input: should have an unempety vector
// Output: should printout all of the elements in this input vector
bool print_vec(Vector *vec)
{
    // loop will be performed only if v->N>0
    if(vec->S <0)
    {
        return false;
    }
    // use the for loops to print out the vector
    for (int i=0; i<vec->S; i++)
    {
        printf("%f\t",vec->el[i]);
    }
    // print out next line
    printf("\n");
    return true;
}
