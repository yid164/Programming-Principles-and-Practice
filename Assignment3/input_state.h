// Student Name: Yinsheng Dong
// Student Number: 11148648
// NSID: yid164
// Lecture Section: CMPT 214

// written by Tony Kusalik, NSID ajk449

#ifndef _INPUT_STATE_H_
#define _INPUT_STATE_H_

#include "vector.h"
// input_state
//   prompts the user for a size of vector,
//   allocates a vector of that size,
//   and then populates the vector with float values provided
//   by the user, one value at a time.
// In:
//   global wrk_vec_p
// Out:
//   global wrk_vec_p is set to point to the
//   newly allocated Vector containing the elements input
// Notes:
//   - causes program abort with non-zero exit status if a serious problem 
//     is encountered or an EOF is encountered on input
void *input_state( void );

#endif // _INPUT_STATE_H_
