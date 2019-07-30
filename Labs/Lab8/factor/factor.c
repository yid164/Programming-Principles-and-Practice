/* factor - prime-factor numbers
**
** Copyright (C)1987,1990,1995,2000 by Jef Poskanzer <jef@mail.acme.com>.
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
** OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
** LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
** OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
** SUCH DAMAGE.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "low_primes.h"


static char* argv0;


static void print_ull( unsigned long long ull );
static void print_fact( unsigned long long fact, int power );
static int test_fact( unsigned long long* numP, unsigned long long fact );
static void factor( unsigned long long num );
static unsigned long long atoull( const char* str );
static void parse_arg( char* arg );


int
main( int argc, char** argv )
    {
    int i;
    char buf[1000];

    argv0 = argv[0];

    if ( argc == 1 )
	{
	/* No args, read numbers from stdin. */
        while ( fgets( buf, sizeof(buf), stdin ) != NULL )
	    parse_arg( buf );
	}
    else
	{
        for ( i = 1; i < argc; ++i )
            parse_arg( argv[i] );
	}

    exit( 0 );
    }


static void
print_ull( unsigned long long ull )
    {
    if ( ull >= 10 )
	print_ull( ull / 10 );
    putchar( ( ull % 10 ) + '0' );
    }


static void
print_fact( unsigned long long fact, int power )
    {
    putchar( ' ' );
    print_ull( fact );

    if ( power != 1 )
        (void) printf( "^%d", power );
    }


static int
test_fact( unsigned long long* numP, unsigned long long fact )
    {
    int power;
    unsigned long long t;

    power = 0;
    while ( ( t = *numP / fact ) * fact == *numP )
        {
        ++power;
        *numP = t;
        }

    if ( power != 0 )
        print_fact( fact, power );

    if ( t > fact )
        return 1;

    return 0;
    }


static void
factor( unsigned long long num )
    {
    int p;
    unsigned long long lnum, fact;

    lnum = num;
    print_ull( lnum );
    (void) printf( " =" );

    if ( lnum == 0 || lnum == 1 )
        print_fact( lnum, 1 );
    else
        {
	for ( p = 0; p < sizeof(low_primes)/sizeof(*low_primes); ++p )
	    if ( ! test_fact( &lnum, low_primes[p] ) )
		goto done;
	fact = ( low_primes[p - 1] + 5 ) / 6 * 6 - 1;
	for (;;)
	    {
	    if ( ! test_fact( &lnum, fact ) )
		break;
	    fact += 2;
	    if ( ! test_fact( &lnum, fact ) )
		break;
	    fact += 4;
	    }
	done:
        if ( lnum != 1 )
            print_fact( lnum, 1 );
        }

    printf( "\n" );
    }


static unsigned long long
atoull( const char* str )
    {
    unsigned long long ull;

    for ( ull = 0; *str >= '0' && *str <= '9'; ++str )
	ull = ull * 10 + ( *str - '0' );
    return ull;
    }


static void
parse_arg( char* arg )
    {
    unsigned long long i, n1, n2, n;

    i = strspn( arg, "0123456789" );
    if ( i == strlen( arg ) )
	factor( atoull( arg ) );
    else
	{
	if ( arg[i] == '-' )
	    {
	    n1 = atoull( arg );
	    n2 = atoull( &arg[i+1] );
	    for ( n = n1; n <= n2; ++n )
		factor( n );
	    }
	else if ( arg[i] == '.' )
	    {
	    if ( strspn( &arg[i], "." ) != strlen( arg ) - i )
		{
		(void) fprintf(
		    stderr, "%s: wildcards must trail number\n", argv0 );
		exit( 1 );
		}
	    n1 = atoull( arg );
	    switch ( strlen( arg ) - i )
		{
		case 1:
		n1 *= 10;
		n2 = n1 + 9;
		break;

		case 2:
		n1 *= 100;
		n2 = n1 + 99;
		break;

		case 3:
		n1 *= 1000;
		n2 = n1 + 999;
		break;

		default:
		(void) fprintf(
		    stderr, "%s: too many wildcard chars\n", argv0 );
		exit( 1 );
		}
	    for ( n = n1; n <= n2; ++n )
		factor( n );
	    }
	else
	    {
	    (void) fprintf(
		stderr, "usage:  %s <int> <int>-<int> ...\n", argv0 );
	    exit( 1 );
	    }
	}
    }
