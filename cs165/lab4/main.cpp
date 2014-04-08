#include <iostream>
#include <stdint.h>

using namespace std;

class LCRNG
{
	int M;
	int a;
	int b;
	int s;
	public:
		LCRNG();
		uint16_t Next();
		void reset();
};

LCRNG::LCRNG()
{
	int M = 0;
	int a = 0;
	int b = 0;
	int s = 0;
}
		
LCRNG::uint16_t Next()
{
	return( ((s*a) + b) % M) )
}

LCRNG::void reset( )
{
	
}

int main(int argc, char* argv[])
{
	int M = argv[1];
	int a = argv[2];
	int b = argv[3];
	int s = argv[4];

	int seed = s;

	uint16_t r_next = next(M, a, b, s);

		
	
	return 0;
}

