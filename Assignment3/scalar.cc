// Name          : Yinsheng Dong
// Student Number: 11148648
// NSID          : yid164
// Lecture Sec   : CMPT 214 T01


#include <stdio.h>
#include <stdlib.h>

#include "vector.h"


// scalar_plus
// add the specified floating point value to each element in the vecoter
// in: the vec and an element
// out: return the vec that every element in the vector are plused
Vector *scalar_plus(Vector *vec, Elem el)
{
    int a =vec->S;
    // plus element to each element of the vector
    for (int i=0; i<a; i++)
    {
        vec->el[i]+=el;
    }
    return vec;
}

// scalar_minus
// subtract the value of el from every element of Vector vec
// In: the vec and the element user wants minus
// out: return the rect that every element in the vector are minused
Vector *scalar_minus(Vector*vec, Elem el)
{
    int a = vec->S;
    // minus element to ecah element of the vector
    for(int i =0; i<a;i++)
    {
        vec->el[i]-=el;
    }
    return vec;
}

// scalar_mult
// multiply the value of el from every element of Vector vec
// In: the vec and the element user wants multily
// out: return the rect that every element in the vector are multiplied
Vector *scalar_mult(Vector*vec, Elem el)
{
    // mult element to each element of the vector
    int a = vec->S;
    for(int i =0; i<a;i++)
    {
        vec->el[i]*=el;
    }
    return vec;
}

// scalar_div
// divide the value of el from every element of Vector vec
// In: the vec and the element user wants divide
// out: return the rect that every element in the vector are divided
Vector *scalar_div(Vector*vec, Elem el)
{
    // divide element to each element of the vector
    int a = vec->S;
    for(int i =0; i<a;i++)
    {
        vec->el[i]/=el;
    }
    
    return vec;
}

