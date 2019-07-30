// Name: Yinsheng Dong
// Student Number: 11148648
// NSID: yid164
// Lecture Section: CMPT 214 T01


#include <assert.h>                     // for assert()
#include <stdio.h>                      // for fprintf(), fgets(), sscanf()
#include <stdlib.h>                     // for EXIT_FAILURE
#include <ctype.h>                      // for isspace()

#include "vector.h"                     // for MAX_ELEM, Vector, Elem


// Testing for alloc_vec()
void test_alloc()
{
    // create a new vector
    Vector *vec_test;
    vec_test= alloc_vec();
    assert (vec_test !=NULL);
    assert (vec_test->S==0);
    assert (vec_test->el ==NULL);
    // printout succed if testing apporved
    printf("allocate a new vector SUCCESS\n");
}


void test_extend()
{
    // create an empty vector
    Vector *vec_test;
    // allocate it
    vec_test= alloc_vec();
    
    // add elements in this vector
    Vector *vec_test1 = alloc_vec();
    // First testing for extend_vec()
    // the empty vector added to an element(21.5)
    // now the location 0 in the vector should have the element 21.5
    vec_test1 = extend_vec(vec_test, 21.5);
    assert (vec_test1 != NULL);
    assert (vec_test1->S ==1);
    assert (vec_test1->el[0]==21.5);
    // printout succed if testing apporved
    printf("extend_vec() testing 1 SUCCESS\n");
    
    // add an other element in this vector
    Vector *vec_test2 = alloc_vec();
    // Second testing for extend_vec() again
    // the previous vector added to an other element(1.5)
    // now the location 0 in the vector should have the previous element 21.5
    // now the location 1 in the vector should have the element 1.5
    vec_test2 = extend_vec(vec_test1, 1.5);
    assert (vec_test2!=NULL);
    assert (vec_test2->S == 2);
    assert (vec_test2->el[0]==21.5);
    assert (vec_test2->el[1]==1.5);
    // printout succed if testing apporved
    printf("extend_vec() testing 2 SUCCESS\n");

}


// testing print_vec function
void test_print()
{
    // create 3 empty vectors
    Vector *vec_test, *vec_test1, *vec_test2;
    // allocate it
    // add 18.2 to test1
    // add 1.6 to test2
    vec_test= alloc_vec();
    vec_test1 = extend_vec(vec_test, 18.2);
    vec_test2 = extend_vec(vec_test1, 1.6);
    // create a boolean varialbe
    bool print_test;
    // Testing print_vec() for print vec_test1
    print_test = print_vec(vec_test1);
    assert(print_test == true);
    
    // Testing print_vec() for print vec_test2
    print_test = print_vec(vec_test2);
    assert(print_test ==true);
    
    // printout succeed if testing approved
    printf("print_vec() testing SUCCESS\n");

    
}

// testing the dealloc_vec function
void test_dealloc()
{
    
    // create 3 new empty vectors
    Vector *vec_test = alloc_vec();
    Vector *vec_test1 = alloc_vec();
    Vector *vec_test2 = alloc_vec();
    // Testing dealloc_vec, delete all vec_test
    // and free up all testing vectors
    dealloc_vec(vec_test);
    dealloc_vec(vec_test1);
    dealloc_vec(vec_test2);
    // printout succed if testing apporved
    printf("dealloc_vec() testing SUCCESS\n");
}





// main:
// run all the test function
// Out: return:
// EXIT_SUCCESS if program terminates normally
// EXIT_FAILURE otherwise
int main(void)
{
    test_alloc();
    test_extend();
    test_print();
    test_dealloc();
    return EXIT_SUCCESS;
}


