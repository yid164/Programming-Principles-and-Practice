// Student Name: Yinsheng Dong
// Student Number: 11148648
// NSID: yid164
// Lecture Section: CMPT 214

// written by Tony Kusalik, NSID ajk449

#include <assert.h>                     // for assert()
#include <stdio.h>                      // for fprintf(), fgets(), sscanf()
#include <stdlib.h>                     // for EXIT_FAILURE
#include <ctype.h>                      // for isspace()

#include "vector.h"                     // for MAX_ELEM, Vector, Elem
#include "vecalc.h"                     // for MAX_INPUT_BUF_SIZE, wrk_vec_p    

// function input_state()
//   see description in input_state.h
void *input_state( void ) {
    int elem;                           // index for stepping through vector
    int num_elem = -1;                  // total num elements in vector
    char cbuf[MAX_INPUT_BUF_SIZE];      // buf for input
    char *char_p;                       // pointer into cbuf
    Vector *vec_p = NULL;               // pointer to allocated vector
    Vector *ret_p;                      // for return value from various
                                        //  calls to vector functions
    Elem f_val;                         // for temporarily storing an input
                                        //  value

    // there should be no work vector when we enter this function
    assert( NULL == wrk_vec_p );

    // keep repeating this loop until we get a legal number of elements
    // and are able to allocate memory for that number of elements.
    // An illegal number of arguments is any number < 0
    while( num_elem < 0 ) {
        // get raw input (number of elements)
        fputs( "number of vector elements: ", stdout );
        if( fgets( cbuf, MAX_INPUT_BUF_SIZE, stdin ) == NULL ) {
            fputs( "**problem reading input values\n", stderr );
            exit( EXIT_FAILURE );
        }
        // skip over any whitespace prior to the value
        for( char_p=cbuf; 
             ( *char_p != '\0' ) && isspace( *char_p );
              ++char_p )
        ;
        // convert raw input to an integer ignoring errors in the
        // conversion
        if( '\0' == *char_p ) {
            fputs( "**no value specified\n", stderr );
            continue;
        } 
        if( 1 != sscanf( char_p, "%d", &num_elem ) ) {
            fputs( "**number not well formed\n", stderr );
            num_elem = -1;
            continue;
        }
        // if the number of elements is illegal, loop again
        if( (num_elem < 0) || (num_elem >= MAX_ELEMS) ) {
            fputs( "**illegal number of elements\n", stderr );
            num_elem = -1;
            continue;
        }
        // we get to this point if num_elem is within an appropriate range

        // allocate an initial empty vector
        vec_p = alloc_vec();
        // if there was an error in allocating an empty vector
        // the number of elements was specified to be zero and loop
        // again
        if( NULL == vec_p ) {
             fputs( "**could not allocate empty vector\n", stderr );
             exit( EXIT_FAILURE );
        }
    }    
    
    // populate the allocated vector with floating-point values
    for( elem=0; elem < num_elem; ) {
        // prompt for specific element
        printf( "vector element %d: ", elem );
        // get raw input (a floating-point value)
        if( NULL == fgets( cbuf, MAX_INPUT_BUF_SIZE, stdin ) ) {
            fputs( "**problem reading input values\n", stderr );
            exit( EXIT_FAILURE );
        }
        // strip off any leading white space in the user's input
        for( char_p = cbuf; ( *char_p != '\0' ) && isspace( *char_p ); )
            ++char_p;
        // and check that the user actually gave a value.  If no
        // value given, loop around and try again
        if( '\0' == *char_p  ) {
            fputs( "**no value specified\n", stderr );
            continue;
        }
        // convert raw input to a floating-point value ignoring
        // any errors in the conversion.  Add the value as
        // the elem-th element of the vector (resulting in a new
        // vector, delete the old vector, and iterate 
        f_val = atof( cbuf );
        ret_p = extend_vec( vec_p, f_val );
        if( NULL == ret_p ) {
            fputs( "**could not extend vector\n", stderr );
            exit( EXIT_FAILURE );
        } else {
            dealloc_vec( vec_p );       // deallocate original vector
            vec_p = ret_p;              // continue working with new vector
            elem++;                     // record that we successfully added
        }                               //   another element to the vector
    }

    // set global wrk_vec_p to the point to the allocated, populated vector.
    wrk_vec_p = vec_p;

    // Done.  
    return vec_p;
}

