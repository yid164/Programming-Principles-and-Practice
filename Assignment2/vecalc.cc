//============================================================================
// Name        : vector.cpp
// Author      : Yinsheng Dong
// Student#    : 11148648
// NSID        : yid164
// Lecture Sec : CMPT 214 T01
//============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// typedef a float for Elem
typedef float Elem;

// make a struct Vector that include a Elem array, and a size and count
// Elem el create a array to store float elements
// int size is provide the initial size
// int count is provide the user's size
struct Vector
{
    Elem *el;
    int size;
    int count;
};

// print_vec
// printout everything in the vector
// In: None
// Out:everything in the vector
bool print_vec(Vector* vec)
{
    for (int i=0; i<vec->count; i++)
    {
        printf("%f\n",vec->el[i]);
    }
    return true;
}

// alloc_vec
// to create a new vector
// the intial size is 65535
// In: none
// Out: return the new vector
Vector *alloc_vec(void)
{
    Vector *vec = new Vector;
    vec->size = 65535;
    vec->count= 0;
    vec->el = new Elem[vec->count];
    return vec;
}

// delalloc_vec
// to delete everything in the vector and free up memory
// in: the vector
// Out: none; the vector is freed up
void delalloc_vec(Vector* vec)
{
    vec->count=0;
    vec->size=0;
    delete []vec->el;
    vec->el = NULL;
    delete vec;
    
}

// extend_vec
// to add one element in the vector
// in: a vec, and an element
// out: return the vec that is added the element
Vector *extend_vec(Vector* vec, Elem el)
{
    vec->el[vec->count]=el;
    vec->count++;
    vec->size--;
    return vec;
}

// scalar_plus
// add the specified floating point value to each element in the vecoter
// in: the vec and an element
// out: return the vec that every element in the vector are plused
Vector *scalar_plus(Vector *vec, Elem el)
{
    Elem a;
    for (int i=0; i<vec->count; i++)
    {
        a = vec->el[i]+el;
        vec->el[i]=a;
    }
    return vec;
}

Vector *scalar_minus(Vector*vec, Elem el)
{
    Elem a;
    for(int i =0; i<vec->size;i++)
    {
        a = vec->el[i]-el;
        vec->el[i]=a;
    }
    return NULL;
}

Vector *scalar_mult(Vector*vec, Elem el)
{
    Elem a;
    for(int i =0; i<vec->size;i++)
    {
        a = (vec->el[i])*el;
        vec->el[i]=a;
    }
    return NULL;
}

Vector *scalar_div(Vector*vec, Elem el)
{
    Elem a;
    if(el==0)
    {
        printf("divide-by-zero not allowed\n");
        return vec;
    }
    assert(el!=0);
    for(int i =0; i<vec->size;i++)
    {
        a = (vec->el[i])/el;
        vec->el[i]=a;
    }
    
    return NULL;
}


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





int main(void)
{
    
#ifdef TESTING
    Vector *vec_test;
    
    // Testing for alloc_vec()
    assert(vec_test= alloc_vec());
    printf("allocate a new vector succeed\n");
    
    assert(vec_test->size);
    printf("vector initial size:%d\n",vec_test->size);
    
    // create a new integer for user vector size
    const int TEST_SIZE=3;
    vec_test->count = TEST_SIZE;
    printf("user makes their vector size:%d\n",vec_test->count);
    // assume user's input is 1.2, 2.3, 3
    Elem s[TEST_SIZE]={1.2,2.3,3};
    
    // use a for-loop to put user's input values into the vector
    for (int i=0; i<TEST_SIZE; i++)
    {
        assert(vec_test->el[i]=s[i]);
    }
    printf("the to store the elements in the vector succed\n");
    
    // Now trying to test the print_vec()
    assert(print_vec(vec_test));
    printf("The print_vec() fuction works\n");
    
    // test the extend_vec()
    // assume user want to add a num is 5.5
    Elem add_test = 5.5;
    assert(extend_vec(vec_test,add_test));
    printf("The extend_vec() works \n");
    
    //Printout the elements in the vector and size to show if it's correct
    print_vec(vec_test);
    printf("Now the size of user's vector: %d\n", vec_test->count);
    
    // test the scalar_plus()
    // assume user want to use plus option to add 3 to those elements
    Elem a=3;
    assert(scalar_plus(vec_test,a));
    printf("The scalar_plus() works\n");
    // printout the vector to show if the elements are plused
    print_vec(vec_test);
           
    // test the usage()
    // if the usage function can be printed
    usage();
    printf("the usage function works\n");
           
    // test the decllocate fucntion
    // suppose user wants to delete the functions
    delalloc_vec(vec_test);
    printf("the delalloc_vec() works\n");
    // to call the print function show that are empty.
    print_vec(vec_test);
    
    //test the scalar_minus()
    Elem b =2;
    assert(scalar_minus(vec_test,b)!=NULL);
    printf("The scalar_minus function works");
#endif
           
           
           
    /**
     Vector *vec = alloc_vec();
     printf("number of vector elements:");
     char s[100];
     fgets(s,100,stdin);
     int a=atoi(s);
     fflush(stdin);
     fflush(stdout);
     if(!atoi(s))
     {
     printf("illegal numbers\n");
     return main();
     }
     assert(atoi(s));
     
     if(a<0)
     {
     printf("illegal numbers\n");
     return main();
     }
     assert (a>=0);
     if(a>vec->size)
     {
     printf("The vector max size exceeded\n");
     return main();
     }
     assert(a<vec->size);
     
     Elem input;
     for (int i=0; i<a;i++)
     {
     printf("vector element %d:",i);
     scanf("%f",&input);
     extend_vec(vec,input);
     }
     char letter;
     Elem num;
     while(vec->count>=0)
     {
     printf("operation:");
     scanf(" %c",&letter);
     
     if(letter=='h')
     {
     usage();
     }
     else if(letter=='p')
     {
     print_vec(vec);
     }
     else if(letter == 'e'|| letter =='q')
     {
     delalloc_vec(vec);
     exit(1);
     }
     else if (letter == 'c')
     {
     delalloc_vec(vec);
     main();
     
     }
     else if (letter == 'a')
     {
     scanf("%f",&num);
     extend_vec(vec,num);
     }
     else if (letter == '+')
     {
     scanf("%f",&num);
     scalar_plus(vec,num);
     }
     else if (letter == '-')
     {
     scanf("%f", &num);
     scalar_minus(vec,num);
     }
     else if (letter=='*')
     {
     scanf("%f",&num);
     scalar_mult(vec,num);
     }
     else if(letter=='/')
     {
     scanf("%f",&num);
     scalar_div(vec,num);
     }
     else
     {
     printf("Please enter the correct operators\n");
     }
     fflush(stdout);
     }
     **/
    return 0;
}