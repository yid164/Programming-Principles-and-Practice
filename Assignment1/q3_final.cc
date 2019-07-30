// Name: Yinsheng Dong
// Student Number: 11148648
// NSID: yid164
// Lecture Section: CMPT214

#include <stdio.h>
#include <string.h>


int outPut;
int inPutValue;

int main (int argc, char *argv[])
{

    char *copyPtr;              // space for the char-pointer value
    
    if (argc < 3)               // check that we have enough arguments
    {
        fprintf ( stderr, "Not enought arguments. \n"); // if argc <3, then
        return -1;
    }
    
    else                        // if we have enought arguments
    {
        if (0==strcmp(argv[1], "add"))    // set the operation code depending on the first argument
        {
            outPut = 5;
        }
        
        else if (0==strcmp(argv[1], "multiply") == 0)
        {
            outPut = 7;
        }
        else
        {
            fprintf (stderr, "operation not recognized! \n");
            return -1;
        }
    }
    
    // copy second argument into dynamically allocated
    // string
    copyPtr = new char [strlen(argv[2])];
    strcpy (copyPtr, argv[2]);
    
    // the the final input vlaue
    sscanf (copyPtr,"%d", &npvle);
    
    return 0;
}
