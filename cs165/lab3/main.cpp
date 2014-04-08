#include <iostream>
#include <math.h>

using namespace std;

int gcd( int a, int b )
{
	int c;

	if( b == 0  ) return a;
	else
	{
		c = gcd( b, a % b );
		return c;
	}
}

int phi( int & n )
{
	int count = 0;
	
	for( int i = 1; i <= n-1; i++ )
	{
		if( gcd(i, n) == 1 ) count++;
	}

	return count;
}

bool IsPrimitiveRoot( int & n, int & phi_n, int & p )
{
	int count = 1;
	int pprime = p;
	
	if(gcd(p, n) != 1) return false;
	else
	{
		while( p != 1 )
		{
			p = (p * pprime) % n;
			count++;
		}
		return( count == phi_n );
	}
}

void GetPrimitiveRoots( int n )
{
	int phi_n = phi(n);
	for( int i = 0; i <= n-1; i++ )
	{
		if( IsPrimitiveRoot( n, phi_n, i ) )
		{
			cout << i << endl;
		}
	}
}

int main(int argc, char* argv[])
{
	int n = atoi(argv[1]);

	GetPrimitiveRoots(3);
	
	return 0;
}
