// Student Name: Yinsheng Dong
// Student Number: 11148648
// NSID: yid164
// Lecture Section: CMPT 214

// written by Tony Kusalik, NSID ajk449

#include <stdio.h>      // for puts()
#include <stdlib.h>     // for EXIT_FAILURE, EXIT_SUCCESS

#include "calc_state.h"         // for calc_state()
#include "input_state.h"        // for input_state()
#include "vector.h"             // for any definitions specific to this module

// =====================================

// global variable pointing to the vector being worked on
// in a coordinated fashion by main(), input_state(),
// and calc_state().  
Vector *wrk_vec_p;

// =====================================

// main:
//  Program entry point.  
// In:
//  Command line arguments are ignored
// Out:
//  return -- EXIT_SUCCESS if program terminates normally, 
//            EXIT_FAILURE otherwise

int main( int , char ** ) {
        bool exit_flag=false;

        wrk_vec_p = NULL;       // initially there is no work vector
        // Until we're told to exit, loop between input state and
        // calculator state.
        while( !exit_flag ) {
                input_state();                  // input starting vector
                exit_flag = calc_state();       // perform operations, resulting
                                                //  potentially in a new vector
                // We're finished with calc_state
                // If there is a global work vector allocated, deallocate it
                if( NULL != wrk_vec_p ) {
                        dealloc_vec( wrk_vec_p );
                        wrk_vec_p = NULL;
                }
                // And loop
        }                                       

        return EXIT_SUCCESS;
}

