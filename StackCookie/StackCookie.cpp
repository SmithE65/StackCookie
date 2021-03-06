// StackCookie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

int func1(double num);
int func2(int hi, int world, char* str);

// This program fails CheckStackVars
// I think the security cookie gets overwritten
int main()
{
	int i = func1(2.4);

	printf("func1 returned: %i", i);

    return 0;
}

// This function compiles with the following checks before ret
// 1) _RTC_CheckStackVars
// 2) __security_check_cookie
// 3) __RTC_CheckEsp
int func1(double num)
{
	num += 2;

	char myString[15] = "Hello World!/0";
	int res = (int)num + func2(1, 2, myString);

	return (int)num;
}

// This function makes no checks against the length of str
// and corrupts the stack frame of func1
int func2(int hi, int world, char* str)
{
	for (int i = 0; i < 25; i++)
		str[i] = 'G';
	return hi * world;
}
