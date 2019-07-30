// Name: Yinsheng Dong
// Student Number: 11148648
// NSID: yid164
// Lecture Section: CMPT 214 T01

#include <assert.h>                     // for assert()
#include <stdio.h>                      // for fprintf(), fgets(), sscanf()
#include <stdlib.h>                     // for EXIT_FAILURE
#include <ctype.h>                      // for isspace()

#include "vector.h"                     // for MAX_ELEM, Vector, Elem
#include "scalar.h"





// test_scalarplus
// unit test for scalar_plus
void test_scalarplus()
{
    // start scalar operation tests
    // create a new Vector that named vx(empty)
    // use the extend_vec() to add one element (10.0) to new vector vx1
    Vector *vx = new Vector;
    vx=alloc_vec();
    Vector *vx1 = alloc_vec();
    vx1= extend_vec (vx, 10.0);
    
    // unit test for the scalar_plus:
    // use scalar_plus to add 3.0 to the vx1
    // so now the 10.0 should become to 13.0
    Vector *plus_test = alloc_vec ();
    plus_test = scalar_plus(vx1, 3.0);
    assert(plus_test!=NULL);
    assert(plus_test->S == 1);
    assert(plus_test->el[0]==13.0);
    // printout succed if testing apporved
    printf("scalar_plus() testing SUCCESS \n");
    // free up the all memories
}

// test_scalarminus
// unit test for scalar_mius
void test_scalarminus()
{
    // set up a one element (5.0) vector vx1
    Vector *vx = new Vector;
    Vector *vx1= alloc_vec();
    vx1 = extend_vec(vx,5.0);
    // unit test for the scalar_minus to minus 1.0
    // so now the 5.0 should be changed to 4.0
    Vector *minus_test = alloc_vec();
    minus_test = scalar_minus(vx1, 1.0);
    assert(minus_test!=NULL);
    assert(minus_test->S ==1);
    assert(minus_test->el[0]==4.0);
    // printout succed if testing apporved
    printf("scalar_minus() testing SUCCESS \n");

}

// test_scalarmult
// unit test for scalar_mult
void test_scalarmult()
{
    Vector *vx = new Vector;
    // set up a one element (3.0) vector vx1
    vx=alloc_vec();
    Vector *vx1 = alloc_vec();
    vx1 = extend_vec(vx,3.0);
    // unit test for the scalar_mult
    // so now the 3.0 should be changed to 6.0
    Vector *muti_test = alloc_vec();
    muti_test = scalar_mult(vx1, 2.0);
    assert(muti_test!=NULL);
    assert(muti_test->S ==1);
    assert(muti_test->el[0]==6.0);
    // printout succed if testing apporved
    printf("scalar_muti() testing SUCCESS \n");

}

// test_scalardiv
// unit test for scalar_div
void test_scalardiv()
{
    Vector *vx = new Vector;
    // set up a one element (9.0) vector vx1
    vx=alloc_vec();
    Vector *vx1= alloc_vec();
    vx1 = extend_vec(vx,9.0);
    // unit test for the scalar_div
    // so now the 9.0 should be changed to 3.0
    Vector *div_test;
    div_test = scalar_div(vx1, 3.0);
    assert(div_test!=NULL);
    assert(div_test->S ==1);
    assert(div_test->el[0]==3.0);
    // printout succed if testing apporved
    printf ("scalar_div() testing SUCCESS \n");
    // free up all memories
}



// main:
// run all the test function
// Out: return:
// EXIT_SUCCESS if program terminates normally
// EXIT_FAILURE otherwise
int main(void)
{
    test_scalarplus();
    test_scalarminus();
    test_scalarmult();
    test_scalardiv();
    
    return EXIT_SUCCESS;
    
    
    
    
}
