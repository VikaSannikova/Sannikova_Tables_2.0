#include <string>
#include "ReadFunc.h"

#define stop 0 //конец строки/файла
#define let 1 //буква
#define sig 2 //знак препинания или цифра
#define del 3 //разделитель

using std::string;

inline int getSym(char c)
{
	if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
		return let;
	else if (c >= '!' && c <= '@')
		return sig;
	else if (c == '\0')
		return stop;
	else return del;
}
int readWord(char *start, char *& end, string &s, string &res) //честно признаюсь что не поняла как это делать
{
	int i = 0;
	int f = getSym(start[i]);

	while (f == del)
	{
		i++;
		f = getSym(start[i]);
	}

	if (f == stop)
		return stop;

	start += i;
	end = start;
	i = 0;

	if (f == sig)
	{
		end++;
		res = string(start, 1);
		return sig;
	}

	while (f == let)
	{
		i++;
		end++;
		f = getSym(start[i]);
	}
	res = string(start, i);
	return let;
}
