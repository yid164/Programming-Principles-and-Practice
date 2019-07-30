// Student Name: Yinsheng Dong
// Student Number: 11148648
// NSID: yid164
// Lecture Section: CMPT 214

// written by Tony Kusalik, NSID ajk449

#ifndef _VECALC_H_
#define _VECALC_H_

#include "vector.h"

// global variable pointing to the vector being worked on
// in a coordinated fashion by main(), input_state(),
// and calc_state().  
extern Vector *wrk_vec_p;       

// limit of input buffer sizes
const int MAX_INPUT_BUF_SIZE=128;

#endif // _VECALC_H_
