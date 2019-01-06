#if defined(__WIN32__) || defined(_WIN32)
//#include "WinSerial.h"
#else
#include "UnixSerial.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string>

const char gVersion[] = GIT_VERSION_SHA1;
const char gBuildType[] = BUILD_TYPE;

void printInfo()
{
    printf("version = %s\n", gVersion);
    printf("build type = %s\n", gBuildType);
}

int main(int argc, char* argv[])
{
	printInfo();

	std::string settingName = "setting.ini";

	if (argc > 1)
		settingName = argv[1];

#if defined(__WIN32__) || defined(_WIN32)
	//winSerial();
#else
	unixSerial(settingName);
#endif

    return 0;
}
