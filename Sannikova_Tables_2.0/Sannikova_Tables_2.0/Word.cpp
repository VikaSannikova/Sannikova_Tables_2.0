
#include "Word.h"
#include <math.h>
int Word::calculateHash(string & s)
{
	int t = 0;
	for (int i = 0; i < s.length(); i++)
		t +=(int)( s[i]/**pow(10,i)*/);
	return t;
}
