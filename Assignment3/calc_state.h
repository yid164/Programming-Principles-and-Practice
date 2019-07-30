// Student Name: Yinsheng Dong
// Student Number: 11148648
// NSID: yid164
// Lecture Section: CMPT 214

// written by Tony Kusalik, NSID ajk449

#ifndef _CALC_STATE_H_
#define _CALC_STATE_H_

// calc_state
//   accepts input from the user specifying operations to be performed
//   on the vector pointed to by global wrk_vec_p.
// In:
//    accesses global wrk_vec_p
// Out:
//    return -- exit flag: set to true if program is to perform orderly
//              termination
//    global wrk_vec_p will have been updated if any 'a' commands were
//           performed
bool calc_state( void );

#endif // _CALC_STATE_H_


