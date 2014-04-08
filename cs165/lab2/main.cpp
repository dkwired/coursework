#include <iostream>

using namespace std;

int GCD( int a, int b )
{
	int r;
	int q;
	int temp;
	
	r = a % b;
	q = (a - r)/b;
	while( r != 0 )
	{
			
		a = b;
		b = r;
		q = a / b;
		r = a - b*q;
	}

	return r;
}

int main(int argc, char* argv[])
{
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);

	int result = GCD( a, b );

	cout << "Your result is: " << result;

	return 0;
}
