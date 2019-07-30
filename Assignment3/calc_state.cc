// Student Name: Yinsheng Dong
// Student Number: 11148648
// NSID: yid164
// Lecture Section: CMPT 214

// written by Tony Kusalik, NSID ajk449

#include <assert.h>     // for assert()
#include <ctype.h>      // for isspace()
#include <stdio.h>      // for fputs(), puts(), sscanf(), fprintf

#include "vector.h"     // for MAX_ELEM, Vector, Elem
#include "scalar.h"     // for scalar_plus(), scalar_minus(), etc.
#include "vecalc.h"     // for MAX_INPUT_BUF_SIZE, wrk_vec_p    

/*
 * Internal functions to calc_state.cc
 */

// oper_vec
//    performs a vector operation on vector pointed to by vec_p
//    as specified by the operation (character oper)
//    and the operand (pointed to by operand_p) passed to it.
//    A scalar division by 0 is checked for and not allowed.
// In:
//    vec_p != NULL
//    operand_p != NULL
//    oper is one of '/', '-', '+', or '*'
// Out:
//    Return - on success, pointer to new vector containing updated elements
//           - on failure, NULL
// Note:
Vector * oper_vec( Vector *vec_p, char oper, char *operand_p ) {
    Elem operand;
    Vector *ret = NULL;

    // skip over any whitespace between the operator and the operand
    while( ( *operand_p != '\0' ) && isspace( *operand_p ) )
        ++operand_p;
    // make sure there is an operand present
    if( *operand_p == '\0' ) {
        fputs( "**no operand specified\n", stderr );
        return( vec_p );
    }
    // operand should now be pointed to by operand_p

    // get operand as floating point value
    if( 1 != sscanf( operand_p, "%f", &operand ) ) {
        fputs( "**illegal operand value specified\n", stderr );
        return( vec_p );
    }
    
    // perform the specific operation with the retrieved operand
    switch( oper ) {
        case '/':
            // if the operation is division by 0, complain to the user
            //   and abort the operation
            if( 0.0 == operand  ) {
                fputs( "**divide-by-zero not allowed\n", stderr );
                ret = vec_p;
            } else
                ret = scalar_div( vec_p, operand ); 
             break;
        case '+':
            ret = scalar_plus( vec_p, operand ); 
            break;
        case '*':
            ret = scalar_mult( vec_p, operand ); 
            break;
        case '-':
            ret = scalar_minus( vec_p, operand ); 
            break;
        default:
            assert( true );     // should never get here
            break;
    }
    return( ret );
}

// append_to_vec
//    appends an element (specified by the string pointed to by
//    value_p) to the vector pointed to by vec_p
// In:
//    vec_p != NULL
//    value_p != NULL
// Out:
//    Return - on success, pointer to new vector containing updated elements
//           - on failure or illegal input, NULL
Vector * append_to_vec( Vector *vec_p, char *value_p ) {
    Elem new_value;

    // skip over any whitespace between the operator and the operand (value)
    while( ( *value_p != '\0' ) && isspace( *value_p ) )
        ++value_p;
    // make sure there is an operand (value) present
    if( *value_p == '\0' ) {
         fputs( "**no value specified\n", stderr );
         return( NULL );
    }
    // value should now be pointed to by value_p

    // get the operand as a floating-point value
    // return old vector if there was a problem
    if( 1 != sscanf( value_p, "%f", &new_value ) ) {
        fputs( "**illegal value specified\n", stderr );
        return( NULL );
    }

    // everything is fine.  Extend the vector and return result from
    // that operation
    return( extend_vec( vec_p, new_value ) );
}

// usage
//   Instruct user on how to use this program; i.e. the commands it
//   supports and the syntax of those commands.
// In: 
//    none
// Out:
//    output produced on standard output
void usage( void ) {
    puts( " Usage:" );
    puts( "  p   - print vector" );
    puts( "  q,e - quit, end" );
    puts( "  h   - print usage help" );
    puts( "  + <operand> - add <operand> to each element of vector" );
    puts( "  - <operand> - subtract <operand> from each element of vector" );
    puts( "  * <operand> - multiple each element of vector by <operand>" );
    puts( "  / <operand> - divide each element of vector by <operand>" );
    puts( "  a <value> - extend vector by additional value" );
}

/*
 * Functions available to outside code.  See calc_state.h for
 * function descriptions.
 */

// function calc_state()
//   see description in vecalc.h
bool calc_state( void ) {
    bool loop_flag = true;              // controls main loop
    char cbuf[MAX_INPUT_BUF_SIZE];      // buffer for input
    char *char_p;
    char *next_char_p;
    Vector *nvec_p;                     // to hold function return value
    bool exit_flag = false;             // whether program should exit

    // there must be a work vector when we enter this function
    assert( NULL != wrk_vec_p );                

    // Main loop: get operation, perform operation.
    // The main loop will terminate if loop_flag is set to false
    // within the body of the loop.
    while( loop_flag ) {
        // Get input from user 
        fputs( "operation: ", stdout );
        if( fgets( cbuf, MAX_INPUT_BUF_SIZE, stdin ) == NULL ) {
            fputs( "**unexpected error on input stream\n", stderr );
            exit_flag = true;
            loop_flag = false;
        }
        // strip out any leading spaces in the input
        char_p = cbuf;
        while( ( *char_p != '\0' ) && isspace( *char_p ) )
            ++char_p;
        // if input is blank, loop
        if( *char_p == '\0' )
            continue;
        // Immediately following the operator, there should either be
        // nothing or else white space.  If not, complain and loop.
        next_char_p = char_p+1;
        if( *next_char_p != '\0' && !isspace( *next_char_p ) ) {
            fputs( "**illegal operation\n", stderr );
            usage();
            continue;
        }
        // There appears to be a one-character operator, 
        // so branch depending on the first letter
        // of the operator field
        switch( *char_p ) {
            case 'p':
                print_vec( wrk_vec_p );
                break;
            case 'h':
                usage();
                break;
            case 'q':
            case 'e':
                exit_flag = true;
                loop_flag = false;
                break;
            case 'c':
                exit_flag = false;
                loop_flag = false;
                break;
            // handle a scalar operation
            case '+':
            case '-':
            case '/':
            case '*':
                nvec_p=oper_vec( wrk_vec_p, *char_p, char_p + 1 );
                if( NULL == nvec_p ) {
                    fputs( "**trouble completing scalar operation\n", stderr ); 
                } 
                break;
            // handle the append operation   
            case 'a':
                nvec_p=append_to_vec( wrk_vec_p, char_p + 1 );
                if( NULL == nvec_p ) {
                        // in this case a new vector was not allocated, so we
                        //  can ignore the value of nvec_p
                        fputs( "**couldn't extend vector\n", stderr ); 
                } else {
                        // new vector to work with.  Deallocate the old one.
                        dealloc_vec( wrk_vec_p );
                        wrk_vec_p = nvec_p;
                }  
                break;               
            default:
                fputs( "**operation not recognized\n", stderr );
                break;
        }
    }
    return( exit_flag );
}

