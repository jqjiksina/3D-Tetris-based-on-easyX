#include <Windows.h>
#include "toString.h"
#include "paint.h"


std::string numToString(int num)
{
	std::string str;
	do
	{
		int r = num % 10;
		str += r + '0';
	} while (num /= 10);
	int size = str.size();
	for (int i = 0; i < size / 2; i++)
	{
		char temp = str[i];
		str[i] = str[size - 1 - i];
		str[size - 1 - i] = temp;
	}
	return str;
}

int stringToNum(const string& str)
{
	int num = 0;
	int pos = str.size();
	if(pos != 0)
	for (auto c : str)
	{
		num += (c - '0') * pow(10, --pos);
	}
	return num;
}

