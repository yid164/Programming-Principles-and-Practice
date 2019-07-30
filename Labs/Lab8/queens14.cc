// Authors: Dan Neilson and Tony Kusalik

// Standard headers
#include <assert.h>    // for assert()
#include <inttypes.h>  // for fixed-width datatypes
#include <stdio.h>     // for fprintf(), sscanf(), etc.
#include <stdlib.h>    // for EXIT_SUCCESS, etc.

// =====================================

// A square is either EMPTY or contains a QUEEN
typedef enum { EMPTY, QUEEN } Square;
// ... (Square s, ...) {
//   switch (s) {
//   case EMPTY: ...; break;
//   case QUEEN: ...; break;
//   default: assert(false); break;
//   }
// }

// showSquare:
//   Show contents of square sq
// In:
//   sq in {EMPTY, QUEEN}
// Out:
//   return -- Character representation of the square's contents.
//             Character 'Q' represents a queen, '.' represents an empty square.
char showSquare(Square sq) {
  switch (sq) {
  case EMPTY: return '.'; break;
  case QUEEN: return 'Q'; break;
  default: assert(false); break;
  }
}

// =====================================

// A state of N-Queens consists of the board size and board's data.
typedef struct {
        uint8_t N;              // The board is NxN
        Square **data;          // State of each square on the board
} State;
// ... (State *s, uint8_t row, uint8_t col, ... ) {
//  ... s->data[row][col] ...
// }
const int MAX_QUEENS = UINT8_MAX; // Value chosen because row and column
                                  // indices are uint8_t;
                                  // type int chosen because the constant  
                                  // is used to compare against variables of 
                                  // type int.

// getSquare:
//   get state of Square row, col from board State *s.
// In:
//   s != NULL, s->N > 0, s->N <= MAX_QUEENS, s->data != NULL, 
//              s->data[row] != NULL
//   row >= 0, col >= 0, row < s->N, col < s->N
// Out:
//   return -- state of s->data[row][col] in {EMPTY, QUEEN}
Square getSquare(State *s, uint8_t row, uint8_t col) {
        return s->data[row][col];
}

// setSquare:
//   set state of Square row, col in board State *s to square.
// In:
//   s != NULL, s->N > 0, s->N <= MAX_QUEENS, s->data != NULL, 
//             s->data[row] != NULL
//   row >= 0, col >= 0, row < s->N, col < s->N
//   square in {EMPTY, QUEEN}
// Out:
//   No return value.
//   effect -- new State of s->data[row][col] set to one of {EMPTY, QUEEN}
void setSquare(State *s, uint8_t row, uint8_t col, Square square) {
        s->data[row][col] = square;
}

// allocateState:
//   Allocate a blank NxN board.
// In:
//   N > 0, N <= MAX_QUEENS
// Out:
//   return -- pointer to NxN board w/ all Squares EMPTY
//          -- NULL on error
State *allocateState(uint8_t N) {
        // allocate main structure
        State *toRet = new State;
        if (NULL == toRet)
                return NULL;
        toRet->N = N;
        // allocate vector to store pointers to rows
        toRet->data = new Square*[N];
        // on error, free up space allocated so far
        if (NULL == toRet->data) {
                delete toRet;
                return NULL;
        }
        // allocate space for rows
        for (uint8_t i=0; i<N; i++) {
                // allocate space for row i
                toRet->data[i] = new Square[N];
                // on error, free up space allocated so far
                if (NULL == toRet->data[i]) {
                        for (uint8_t j=0; j<i; j++)
                                delete[] toRet->data[j];
                        delete[] toRet->data;
                        delete toRet;
                        return NULL;
                }
                // initialize each column of row i to EMPTY
                for (uint8_t j=0; j<N; j++)
                        toRet->data[i][j] = EMPTY;
        }
        return toRet;
}

// deallocateState:
//   frees the memory used by State *s.
// In:
//   s != NULL, s->N > 0, s->N <= MAX_QUEENS, s->data != NULL, 
//              s->data[0 .. N-1] != NULL
// Out:
//   No return value.
//   effect -- all memory used by State *s is deallocated.
void deallocateState(State *s) {
        uint8_t N = s->N;
        // deallocate each row
        for (uint8_t i=0; i<N; i++) 
                delete[] s->data[i];
        // deallocate vector pointing to rows
        delete[] s->data;
        // deallocate structure
        delete s;
}

// printState:
//   print State *s to a FILE stream ofile
// In:
//   ofile != NULL
//   s != NULL, s->N > 0, s->N <= MAX_QUEENS, 
//              s->data != NULL, s->data[0 .. N-1] != NULL
// Out:
//   No return value.
//   effect -- representation of State *p printed to ofile
void printState(FILE *ofile, State *s) {
        for (uint8_t row=0; row < s->N; row++) {
                for (uint8_t col=0; col < s->N; col++)
                        fprintf(ofile, "%c", showSquare(getSquare(s, row,
                                col)));
                fprintf(ofile, "\n");
        }
}

// copyState:
//   Make a copy of the given State *s.
// In:
//   s != NULL, s->N > 0, s->N <= MAX_QUEENS, 
//              s->data != NULL, s->data[0 .. N-1] != NULL
// Out:
//   return -- NULL on allocation failure.
//          -- Pointer to the copy of the state
State *copyState(State *s) {
        State *toRet = allocateState(s->N);
        if (NULL == toRet)
                return NULL;
        // if allocateState succeeded, we have a new state with all squares
        // initialized to EMPTY.  Now we just need to copy over the square
        // settings from the original board state
        for (uint8_t i=0; i < toRet->N; i++)
                for (uint8_t j=0; j < toRet->N; j++)
                        setSquare(toRet, i, j, getSquare(s, i, j));
        return toRet;
}

// =====================================

// isBlocked:
//   Determine whether in State *s the square at row,col is blocked from
//   having a queen placed in it by another queen.  A queen is not blocked
//   by itself.
// In:
//   s != NULL, s->N > 0, s->N <= MAX_QUEENS, s->data != NULL, 
//              s->data[0 .. N-1] != NULL
//   0 <= row, 0 <= col, row < s-> N, col < s->N
// Out:
//   return -- true: square [row,col] is blocked by another queen.
//             false: square [row,col] is NOT blocked by another queen
bool isBlocked(State *s, uint8_t row, uint8_t col) {
        bool blocked = false;
        // by the way they are constructed,
        // logical expressions involving blocked will be evaluated lazily

        // Horizontal check
        for (uint8_t c=0; c < s->N; c++)
                blocked = blocked || ((c != col) && 
                                      (getSquare(s, row, c) == QUEEN));
        // Vertical check
        for (uint8_t r=0; r < s->N; r++)
                blocked = blocked || ((r != row) && 
                                      (getSquare(s, r, col) == QUEEN));
        
        // Slope -1 diagonal (assuming (0,0) in upper-left corner)
        // We need to establish the top-most, left-most position
        // to start checking, and the number of positions along the
        // diagonal to check.
        uint8_t r, c;
        uint8_t nSteps;
        if (row <= col) {       // checked position in upper-right triangle
                r = 0;          // hence diagonal will start in row 0
                c = col - row;
                nSteps = s->N - c;
        } else {                // checked position in lower-left triangle
                r = row - col;  // hence diagonal will start in column 0
                c = 0;
                nSteps = s->N - r;
        }
        // Check each position along diagonal
        for (uint8_t i=0; i < nSteps; i++, r++, c++)
                blocked = blocked || ((r!=row) && (c!=col) && 
                                      (getSquare(s, r, c) == QUEEN));
        // Slope +1 diagonal (assuming (0,0) in upper-left corner)
        // We need to establish the bottom-most, left-most position
        // to start checking, and the number of positions along the
        // diagonal to check.
        if (row+col < s->N) {   // checked position in upper-left triangle
                c = 0;          // diagonal will start in column 0
                r = col + row;
                nSteps = r + 1;
        } else {                // checked position in lower-right triangle
                r = s->N - 1;   // diagonal will start in bottom row
                c = col + row - r;
                nSteps = s->N - c;
        }
        for (uint8_t i=0; i < nSteps; i++, r--, c++)
                blocked = blocked || ((r!=row) && (c!=col) && 
                                      (getSquare(s, r, c) == QUEEN));

        return blocked;
}

// countQueens:
//   Count the number of queens in the given State *s.
// In:
//   s != NULL, s->N > 0, s->N <= MAX_QUEENS, s->data != NULL, 
//             s->data[0 .. N-1] != NULL
// Out:
//   return -- Number of queens in s
uint8_t countQueens(State *s) {
        uint8_t nQueens = 0;
        for (uint8_t row=0; row < s->N; row++)
                for (uint8_t col=0; col < s->N; col++)
                        if (QUEEN == getSquare(s, row, col)) {
                                nQueens += 1;
                        }
        return nQueens;
}

// noQueensThreatened:
//   Determine whether in State *s any queens are placed where they are 
//   threatened (i.e. blocked) by another queen.  A queen is not
//   threatened by itself.
// In:
//   s != NULL, s->N > 0, s->N <= MAX_QUEENS, s->data != NULL, 
//              s->data[0 .. N-1] != NULL
// Out:
//   return -- true: No queens are placed s.t. they're blocked.
//             false: At least one queen is blocked by another.
bool noQueensThreatened(State *s) {
        bool noneThreatened = true;
        for (uint8_t row=0; noneThreatened && row < s->N; row++)
                for (uint8_t col=0; noneThreatened && col < s->N; col++)
                        // when we find a queen at s[row][col] make sure that
                        // it is not threatened.  (It is considered threatened 
                        // if we would otherwise be blocked from placing a 
                        // queen at s[row][col].)  If it is threatened, set 
                        // noneThreatened to false.  Setting noneThreatened to 
                        // false will cause exit of our nested loops.
                        if ( (QUEEN == getSquare(s, row, col))
                             && isBlocked(s, row, col) ) {
                                noneThreatened = false;
                        }
                // if any queen was found to be blocked noneThreatened will 
                // be false
        return noneThreatened;
}

// queensThreatened:
//   This name (symbol) gives the logical inverse of noQueensThreatened.
//   Use as a function, as in
//        if( queensThreatened(s) ) { ... } else { ... }
#define queensThreatened(s)  (!noQueensThreatened(s))

// =====================================

// findSolution:
//   Recursive search for a solution starting from State *s
// In:
//  s != NULL, s->N > 0, s->N <= MAX_QUEENS, s->data != NULL, 
//             s->data[0 .. N-1] != NULL
// Out:
//   return -- NULL if no solution found
//             new State with solution if solution found
State *findSolution(State *s) {
        uint8_t nQueens = countQueens(s);
        // If too many queens have been placed, indicate a failure
        if (nQueens > s->N)
                return NULL;
        // If N queens have been placed, then we have a potential solution
        if (nQueens == s->N) {
                // If no queens are blocked, we have a solution.  Copy that
                // game state and return a pointer to it (non-NULL pointer will
                // indicate success to the calling program).  Otherwise,
                // indicate a failure.
                if (noQueensThreatened(s)) {
                        State *copy = copyState(s);
                        if (NULL == copy) {
                                fprintf(stderr, "Out of memory\n");
                                abort(); // Non-returning
                        }
                        return copy;
                } else
                        return NULL;
        }
        // If less than N queens have been placed, try to place one more
        // queen.  

        // Optimization: We will make use of the following optimization
        // subsequently in the course.  For now, it is commented out.
        //
        // Make sure that no queen is threatened in the current
        // board state.  Otherwise there is little use in extending it.
        //   if (queensThreatened( s ) ) {
        //        return( NULL );
        //   }
        // No queens are threatened in the current game state.  We can proceed.
        // End of optimization.

        // Make a copy of the current board state; that is, the board
        // state that we will try to extend.
        State *new_s = copyState(s);
        if (NULL == new_s) {
                fprintf(stderr, "Out of memory\n");
                abort(); // Non-returning
        }
        // Look through the board for empty squares.  For each one found,
        // set it to a queen, and then try to extend that board state to a
        // solution.
        for (uint8_t row=0; row < s->N; row++)
                for (uint8_t col=0; col < s->N; col++)
                        if (EMPTY == getSquare(s, row, col)) {
                                // Set empty square to queen
                                setSquare(new_s, row, col, QUEEN);
                                // Try to extend board to a full solution.  In
                                // that board state, there will be one more
                                // queen placed than in this call to
                                // findSolution().
                                State *ret = findSolution(new_s);
                                // If setting s->data[row][col] led to a sol'n
                                // then free up the board state we allocated
                                // earlier and return the solution
                                if (NULL != ret) {
                                        deallocateState(new_s);
                                        return ret;
                                }
                                // If setting s->data[row][col] did not lead
                                // to a sol'n set the square back to empty
                                // and try another square.
                                setSquare(new_s, row, col, EMPTY);
                        }
        // At this point we have tried to set each empty square in the board to
        // a queen and the resulting board did not lead to a solution.  
        // Thus the search is exhausted.  Free up the copy of the board state
        // which we created for this purpose.
        deallocateState(new_s);
        // If function returns from this point, a solution was not found.
        return NULL;
}

// =====================================

// main:
//   Program entry point
// In:
//   argc > 0
//   argv[0 .. argc-1] != NULL
// Out:
//   return -- EXIT_SUCCESS if program terminates normally, 
//             EXIT_FAILURE otherwise
int main(int argc, char *argv[]) {

#ifdef TESTING

        const int TEST_SIZE=4;

        // Testing for showSquare
        assert('.' == showSquare(EMPTY));
        assert('Q' == showSquare(QUEEN));

        // Testing for allocateState
        State *s = allocateState(TEST_SIZE);
        
        //  test structure that was allocated.
        assert(NULL != s);
        assert(TEST_SIZE == s->N);
        assert(NULL != s->data);
        for (uint8_t row=0; row < TEST_SIZE; row++) {
                assert(NULL != s->data[row]);
                for (uint8_t col=0; col < TEST_SIZE; col++)
                        assert(EMPTY == s->data[row][col]);
        }

        // Testing for getSquare

        // place some queens; i.e. impose a solution 
        s->data[0][1] = QUEEN;
        s->data[1][3] = QUEEN;
        s->data[2][0] = QUEEN;
        s->data[3][2] = QUEEN;

        // check that getSquare returns values that have been set
        assert(EMPTY == getSquare(s, 1, 0));
        assert(QUEEN == getSquare(s, 0, 1));
        assert(EMPTY == getSquare(s, 0, 0));
        assert(QUEEN == getSquare(s, 3, 2));
        assert(QUEEN == getSquare(s, 1, 3));
        assert(EMPTY == getSquare(s, 3, 3));

        // Testing for setSquare

        // set up test positions
	const int TEST_POSITIONS=7;
        struct {
                uint8_t r, c;
        } testPositions[TEST_POSITIONS] = { {0,1}, {2,0}, {0,0}, {1,2},
                                            {0,3}, {3,0}, {3,3} };
        
        // Start with whole board set to EMPTY.  
        // Achieved by resetting positions used above.
        s->data[0][1] = EMPTY;
        s->data[1][3] = EMPTY;
        s->data[2][0] = EMPTY;
        s->data[3][2] = EMPTY;

        // For each test position, use setSquare to set that position to
        // a queen.  Then make sure that the entire game board is empty except
        // for the square that was just set to a queen.  Output tracking
        // information to stdout.
        for (uint8_t i=0; i < TEST_POSITIONS; i++) {
                printf("Setter test %" PRIu8 "  EMPTY->QUEEN\n", i); 
                fflush(stdout);
                // EMPTY -> QUEEN at test position i
                setSquare(s, testPositions[i].r, testPositions[i].c, QUEEN);
                // check the setting of the board
                for (uint8_t row=0; row < TEST_SIZE; row++)
                        for (uint8_t col=0; col < TEST_SIZE; col++)
                                if (row == testPositions[i].r && 
                                    col == testPositions[i].c)
                                        assert(QUEEN == s->data[row][col]);
                                else
                                        assert(EMPTY == s->data[row][col]);
                // set the square back to EMPTY
                s->data[testPositions[i].r][testPositions[i].c] = EMPTY;
        }
        
        // Start with whole board set to queens
        for (uint8_t row=0; row < TEST_SIZE; row++)
                for (uint8_t col=0; col < TEST_SIZE; col++)
                        s->data[row][col] = QUEEN;

        // For each test position, use setSquare to set that position to
        // empty.  Then make sure that the entire game board is queens except
        // for the square that was just set to empty.  Output tracking
        // information to stdout.
        for (uint8_t i=0; i < TEST_POSITIONS; i++) {
                printf("Setter test %" PRIu8 "  QUEEN->EMPTY\n", i);
                fflush(stdout);
                // QUEEN -> EMPTY
                setSquare(s, testPositions[i].r, testPositions[i].c, EMPTY);
                // check the setting of the board
                for (uint8_t row=0; row < TEST_SIZE; row++)
                        for (uint8_t col=0; col < TEST_SIZE; col++)
                                if (row == testPositions[i].r && 
                                    col == testPositions[i].c)
                                        assert(EMPTY == s->data[row][col]);
                                else
                                        assert(QUEEN == s->data[row][col]);
                // set the square back to a queeen
                s->data[testPositions[i].r][testPositions[i].c] = QUEEN;
        }

        // State = Queens on diagonal, empty elsewhere.
        for (uint8_t row=0; row < TEST_SIZE; row++)
                for (uint8_t col=0; col < TEST_SIZE; col++)
                        if (row == col)
                                setSquare(s, row, col, QUEEN);
                        else
                                setSquare(s, row, col, EMPTY);

        // Testing for printState

        // Expect:
        // Q...
        // .Q..
        // ..Q.
        // ...Q
        printState(stdout, s);

        // Testing for copyState

        State *s2 = copyState(s);
        // Copy should represent same board as original
        assert(NULL != s2);
        assert(TEST_SIZE == s2->N);
        assert(NULL != s2->data);
        assert(s->data != s2->data);
        for (uint8_t row=0; row < TEST_SIZE; row++) {
                assert(NULL != s2->data[row]);
                assert(s->data[row] != s2->data[row]);
                for (uint8_t col=0; col < TEST_SIZE; col++)
                        assert(s->data[row][col] == s2->data[row][col]);
        }

        // Testing for deallocateState

        deallocateState(s2);
        deallocateState(s);
        // unfortunately, there is little that can be done from the program
        // perspective to test that all the dynamic memory tied up by the
        // structures pointed to by s and s2 has been freed

	// we need a larger board for the next suite of unit tests
        // use a 5x5 board 
        const int LARGER_TEST_SIZE=5;

        // Testing for isBlocked

        s = allocateState(LARGER_TEST_SIZE);

        // Board:
        // Q....
        // .....
        // .....
        // .....
        // .....
        // Blocked squares (X):
        // .XXXX
        // XX...
        // X.X..
        // X..X.
        // X...X
        setSquare(s, 0, 0, QUEEN);
        assert(false == isBlocked(s, 0, 0));
        assert(true  == isBlocked(s, 0, 1));
        assert(true  == isBlocked(s, 0, 2));
        assert(true  == isBlocked(s, 0, 3));
        assert(true  == isBlocked(s, 0, 4));

        assert(true  == isBlocked(s, 1, 0));
        assert(true  == isBlocked(s, 1, 1));
        assert(false == isBlocked(s, 1, 2));
        assert(false == isBlocked(s, 1, 3));
        assert(false == isBlocked(s, 1, 4));

        assert(true  == isBlocked(s, 2, 0));
        assert(false == isBlocked(s, 2, 1));
        assert(true  == isBlocked(s, 2, 2));
        assert(false == isBlocked(s, 2, 3));
        assert(false == isBlocked(s, 2, 4));

        assert(true  == isBlocked(s, 3, 0));
        assert(false == isBlocked(s, 3, 1));
        assert(false == isBlocked(s, 3, 2));
        assert(true  == isBlocked(s, 3, 3));
        assert(false == isBlocked(s, 3, 4));

        assert(true  == isBlocked(s, 4, 0));
        assert(false == isBlocked(s, 4, 1));
        assert(false == isBlocked(s, 4, 2));
        assert(false == isBlocked(s, 4, 3));
        assert(true  == isBlocked(s, 4, 4));
        // reset the board
        setSquare(s, 0, 0, EMPTY);

        // Board:
        // ....Q
        // .....
        // .....
        // .....
        // .....
        // Blocked squares (X):
        // XXXX.
        // ...XX
        // ..X.X
        // .X..X
        // X...X
        setSquare(s, 0, 4, QUEEN);
        assert(true  == isBlocked(s, 0, 0));
        assert(true  == isBlocked(s, 0, 1));
        assert(true  == isBlocked(s, 0, 2));
        assert(true  == isBlocked(s, 0, 3));
        assert(false == isBlocked(s, 0, 4));

        assert(false == isBlocked(s, 1, 0));
        assert(false == isBlocked(s, 1, 1));
        assert(false == isBlocked(s, 1, 2));
        assert(true  == isBlocked(s, 1, 3));
        assert(true  == isBlocked(s, 1, 4));

        assert(false == isBlocked(s, 2, 0));
        assert(false == isBlocked(s, 2, 1));
        assert(true  == isBlocked(s, 2, 2));
        assert(false == isBlocked(s, 2, 3));
        assert(true  == isBlocked(s, 2, 4));

        assert(false == isBlocked(s, 3, 0));
        assert(true  == isBlocked(s, 3, 1));
        assert(false == isBlocked(s, 3, 2));
        assert(false == isBlocked(s, 3, 3));
        assert(true  == isBlocked(s, 3, 4));

        assert(true  == isBlocked(s, 4, 0));
        assert(false == isBlocked(s, 4, 1));
        assert(false == isBlocked(s, 4, 2));
        assert(false == isBlocked(s, 4, 3));
        assert(true  == isBlocked(s, 4, 4));
        // reset the board
        setSquare(s, 0, 4, EMPTY);

        // Board:
        // .....
        // .....
        // .....
        // .....
        // Q....
        // Blocked squares (X):
        // X...X
        // X..X.
        // X.X..
        // XX...
        // .XXXX
        setSquare(s, 4, 0, QUEEN);
        assert(true  == isBlocked(s, 0, 0));
        assert(false == isBlocked(s, 0, 1));
        assert(false == isBlocked(s, 0, 2));
        assert(false == isBlocked(s, 0, 3));
        assert(true  == isBlocked(s, 0, 4));

        assert(true  == isBlocked(s, 1, 0));
        assert(false == isBlocked(s, 1, 1));
        assert(false == isBlocked(s, 1, 2));
        assert(true  == isBlocked(s, 1, 3));
        assert(false == isBlocked(s, 1, 4));

        assert(true  == isBlocked(s, 2, 0));
        assert(false == isBlocked(s, 2, 1));
        assert(true  == isBlocked(s, 2, 2));
        assert(false == isBlocked(s, 2, 3));
        assert(false == isBlocked(s, 2, 4));

        assert(true  == isBlocked(s, 3, 0));
        assert(true  == isBlocked(s, 3, 1));
        assert(false == isBlocked(s, 3, 2));
        assert(false == isBlocked(s, 3, 3));
        assert(false == isBlocked(s, 3, 4));

        assert(false == isBlocked(s, 4, 0));
        assert(true  == isBlocked(s, 4, 1));
        assert(true  == isBlocked(s, 4, 2));
        assert(true  == isBlocked(s, 4, 3));
        assert(true  == isBlocked(s, 4, 4));
        // reset the board
        setSquare(s, 4, 0, EMPTY);

        // Board:
        // .....
        // .....
        // .....
        // .....
        // ....Q
        // Blocked squares (X):
        // X...X
        // .X..X
        // ..X.X
        // ...XX
        // XXXX.
        setSquare(s, 4, 4, QUEEN);
        assert(true  == isBlocked(s, 0, 0));
        assert(false == isBlocked(s, 0, 1));
        assert(false == isBlocked(s, 0, 2));
        assert(false == isBlocked(s, 0, 3));
        assert(true  == isBlocked(s, 0, 4));

        assert(false == isBlocked(s, 1, 0));
        assert(true  == isBlocked(s, 1, 1));
        assert(false == isBlocked(s, 1, 2));
        assert(false == isBlocked(s, 1, 3));
        assert(true  == isBlocked(s, 1, 4));

        assert(false == isBlocked(s, 2, 0));
        assert(false == isBlocked(s, 2, 1));
        assert(true  == isBlocked(s, 2, 2));
        assert(false == isBlocked(s, 2, 3));
        assert(true  == isBlocked(s, 2, 4));

        assert(false == isBlocked(s, 3, 0));
        assert(false == isBlocked(s, 3, 1));
        assert(false == isBlocked(s, 3, 2));
        assert(true  == isBlocked(s, 3, 3));
        assert(true  == isBlocked(s, 3, 4));

        assert(true  == isBlocked(s, 4, 0));
        assert(true  == isBlocked(s, 4, 1));
        assert(true  == isBlocked(s, 4, 2));
        assert(true  == isBlocked(s, 4, 3));
        assert(false == isBlocked(s, 4, 4));
        // reset the board
        setSquare(s, 4, 4, EMPTY);

        // Board:
        // .....
        // .....
        // ..Q..
        // .....
        // .....
        // Blocked squares (X):
        // X.X.X
        // .XXX.
        // XX.XX
        // .XXX.
        // X.X.X
        setSquare(s, 2, 2, QUEEN);
        assert(true  == isBlocked(s, 0, 0));
        assert(false == isBlocked(s, 0, 1));
        assert(true  == isBlocked(s, 0, 2));
        assert(false == isBlocked(s, 0, 3));
        assert(true  == isBlocked(s, 0, 4));

        assert(false == isBlocked(s, 1, 0));
        assert(true  == isBlocked(s, 1, 1));
        assert(true  == isBlocked(s, 1, 2));
        assert(true  == isBlocked(s, 1, 3));
        assert(false == isBlocked(s, 1, 4));

        assert(true  == isBlocked(s, 2, 0));
        assert(true  == isBlocked(s, 2, 1));
        assert(false == isBlocked(s, 2, 2));
        assert(true  == isBlocked(s, 2, 3));
        assert(true  == isBlocked(s, 2, 4));

        assert(false == isBlocked(s, 3, 0));
        assert(true  == isBlocked(s, 3, 1));
        assert(true  == isBlocked(s, 3, 2));
        assert(true  == isBlocked(s, 3, 3));
        assert(false == isBlocked(s, 3, 4));

        assert(true  == isBlocked(s, 4, 0));
        assert(false == isBlocked(s, 4, 1));
        assert(true  == isBlocked(s, 4, 2));
        assert(false == isBlocked(s, 4, 3));
        assert(true  == isBlocked(s, 4, 4));
        // reset the board
        setSquare(s, 2, 2, EMPTY);

        // Testing for countQueens

        assert(0 == countQueens(s));
        setSquare(s, 0, 0, QUEEN);
        assert(1 == countQueens(s));
        setSquare(s, 4, 0, QUEEN);
        assert(2 == countQueens(s));

        // reset board to all empty squares
        setSquare(s, 0, 0, EMPTY);
        setSquare(s, 4, 0, EMPTY);

        // Testing for noQueensThreatened

        assert(true == noQueensThreatened(s));
        
        setSquare(s, 3, 0, QUEEN);
        setSquare(s, 1, 1, QUEEN);
        setSquare(s, 4, 2, QUEEN);
        setSquare(s, 2, 3, QUEEN);
        setSquare(s, 1, 4, QUEEN);
        // Board:
        // .....
        // .Q..Q
        // ...Q.
        // Q....
        // ..Q..
        // I.e. queen at (1,4) can attack the queen at (2,3)
        assert(false == noQueensThreatened(s));
        
        setSquare(s, 1, 1, EMPTY);
        // Board:
        // .....
        // ....Q
        // ...Q.
        // Q....
        // ..Q..
        // queen at (1,4) can still attack the queen at (2,3)
        assert(false == noQueensThreatened(s));
        
        setSquare(s, 1, 1, QUEEN);
        setSquare(s, 1, 4, EMPTY);
        setSquare(s, 0, 4, QUEEN);
        // Board:
        // ....Q
        // .Q...
        // ...Q.
        // Q....
        // ..Q..
        // no queen can be attacked by another queen
        assert(true == noQueensThreatened(s));

#else // not TESTING

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

#endif // TESTING

        return EXIT_SUCCESS;
}
