#include "UnixSerial.h"

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

    unixSerial();

    return 0;
}
