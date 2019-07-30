// Authors: Dan Neilson and Tony Kusalik

// Standard headers
#include <inttypes.h>   // for fixed-width datatypes
#include <stdio.h>      // for fprintf(), sscanf(), etc.
#include <stdlib.h>     // for EXIT_SUCCESS, etc.

// Class-wide headers
#include <state.h>      // for printState(), allocateState(), State, etc.
#include <solver.h>     // for findSolution()

// main:
//   Program entry point
// In:
//   argc > 0
//   argv[0 .. argc-1] != NULL
// Out:
//   return -- EXIT_SUCCESS if program terminates normally, 
//             EXIT_FAILURE otherwise
int main(int argc, char *argv[]) {
        // check input
        if (2 != argc) {
                fprintf(stderr, "Usage: %s <N>\n", argv[0]);
                return EXIT_FAILURE;
        }
        int32_t in;
        if ((1 != sscanf(argv[1], "%" SCNi32 , &in)) || (0 >= in)) {
                fprintf(stderr, "Usage: %s <N>\n", argv[0]);
                return EXIT_FAILURE;
        }
        if (in > MAX_QUEENS) {
                fprintf(stderr, "N too large\n");
                return EXIT_FAILURE;
        }
        // set up the board
        uint8_t N = in;
        State *empty = allocateState(N);
        if (NULL == empty) {
                fprintf(stderr, "Memory allocation failure.\n");
                return EXIT_FAILURE;
        }
        // find a solution
        State *solution = findSolution(empty);
        if (NULL != solution) {
                printf("A solution exists for N = %" PRIu8 "\n", N);
                printState(stdout, solution);
        } else {
                printf("No solution exists for N = %" PRIu8 "\n", N);
        }
        // done
        deallocateState(empty);

        return EXIT_SUCCESS;
}
