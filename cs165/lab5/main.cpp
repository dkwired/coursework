#include <iostream>
#include <vector>
#include <stdint.h>
#include <fcntl.h>

using namespace std;

class secureRNG
{
	public:
		secureRNG();
		void Next( const size_t & _quantity, vector<uint16_t> & _numbers );
};

secureRNG::secureRNG()
{

}

/* METHOD: Next
IMPLEMENTATION: 
Store in a vector a desired quantity of 16-bit random numbers
*/

void secureRNG::Next( const size_t & _quantity, vector<uint16_t> & _numbers )
{
	uint16_t _randomInteger;
	int _descriptor = open("/dev/random", O_RDONLY);

	for( int i = 0; i < _quantity; i++ )
	{
		read( _descriptor, & _randomInteger, sizeof _randomInteger);
		_numbers.push_back(_randomInteger);
		cout << _randomInteger << " - ";
	}
	
	close(_descriptor);
}

int main()
{
	secureRNG random;
	vector<uint16_t> _nums;
	size_t size = 10000;
	random.Next( size, _nums );

	return 0;
}
