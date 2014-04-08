#ifndef __CHARFREQUENCY_H__
#define __CHARFREQUENCY_H__

#include <iostream>
#include <map>

using namespace std;

class CharFrequency
{
	map<char, int> charfreq;
	int total;
	public:
		CharFrequency();
		void CharCount(string&, char);
};

CharFrequency::CharFrequency()
{

}

void CharFrequency::CharCount( string & str, char letter )
{
	int strpos = 0;

	for(char c = 'A'; c <= 'Z'; c++)
	{
		for(int i = 0; i < str.size(); i++)
		{
			if(str[strpos++] == c)
			{
				charfreq[c]++;
			}
		}
		strpos = 0;
	}
	total = 0;
	for(char c = 'A'; c <= 'Z'; c++)
		total += charfreq[c];

	for(char c = 'A'; c <= 'Z'; c++)
		cout << c << " occurs: " << (float)charfreq[c]/total * 100 << " times." << endl;
}

#endif 
