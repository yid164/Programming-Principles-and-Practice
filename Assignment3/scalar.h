// Student Name: Yinsheng Dong
// Student Number: 11148648
// NSID: yid164
// Lecture Section: CMPT 214


#ifndef _SCALAR_H_
#define _SCALAR_H_

#include "vector.h"





// scalar_plus
// add the specified floating point value to each element in the vecoter
// in: the vec and an element
// out: return the vec that every element in the vector are plused

Vector *scalar_plus(Vector*, Elem);





// scalar_minus
// subtract the value of el from every element of Vector vec
// In: the vec and the element user wants minus
// out: return the rect that every element in the vector are minused

Vector *scalar_minus(Vector*, Elem);




// scalar_mult
// multiply the value of el from every element of Vector vec
// In: the vec and the element user wants multily
// out: return the rect that every element in the vector are multiplied
Vector *scalar_mult(Vector*, Elem);




// scalar_div
// divide the value of el from every element of Vector vec
// In: the vec and the element user wants divide
// out: return the rect that every element in the vector are divided
Vector *scalar_div(Vector*, Elem);



#endif
