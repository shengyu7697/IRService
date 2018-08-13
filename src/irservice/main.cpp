#if defined(__WIN32__) || defined(_WIN32)
//#include "WinSerial.h"
#else
#include "UnixSerial.h"
#endif

#include <stdio.h>
#include <stdlib.h>

const char g_GIT_SHA1[] = GIT_SHA1;
void printGitSHA1()
{
    printf("git sh1 = %s\n", g_GIT_SHA1);
}

int main()
{
	printGitSHA1();

#if defined(__WIN32__) || defined(_WIN32)
	//winSerial();
#else
	unixSerial();
#endif

    return 0;
}
