/*
 * program from stack frame example in GDB documentation
 */

#include <stdio.h>
#include <stdlib.h>      /* for EXIT_SUCCESS */
int fact( int n )
{
  if( 0 == n ) {
    return 1;
  }
  else {
    return n * fact( n - 1 );
  }
}

int main()
{
  int i, f;

  for( i = 0; i < 10; i++ ) {
    f = fact( i );
    printf( "%d! = %d\n", i, f );
  }
  return EXIT_SUCCESS;
}
