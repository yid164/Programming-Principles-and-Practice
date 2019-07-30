/*
Written by Nickolas Gough. 
*/

#include <stdio.h>
#include <iostream>

using namespace std;

// Print "One" to standard out.
void printOne(){
    printf("%s\n", "One");
}

// Print "Not One" to standard out.
void printNotOne(){
    printf("%s\n", "Not one");
}

// Print "Two" to standard out.
void printTwo(){
    printf("%s\n", "Two");
}

// Print "Three" to standard out.
void printThree(){
    printf("%s", "Three");
}

// Main function.
int main(int, char **){

    /*
    Consider test cases: n = 1 and n = 3.
    
    
    Path coverage: 2/4 = 50%
    Condition coverage: 2/4 = 50%
    Function coverage: 3/4 = 75%
    
    Possible paths
   
    PATH n=1 or n>4: if -> printOne -> if -> if

    PATH n=2: if -> printNotOne -> if -> printTwo -> if

    PATH n=3: if -> printNotOne -> if -> if -> printThree

    PATH n=4: if -> printNotOne -> if -> if

    */

    // The code in question.

    if ( (n == 1) || (n > 4) ){
        printOne();
    }
    else {
        printNotOne();
    }
    if (n == 2){
        printTwo();
    }
    if (n == 3){
        printThree();
    }

    return 0;
}
