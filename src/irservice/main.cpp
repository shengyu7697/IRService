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
	std::string portName;
#if defined(__unix__) || defined(__unix)
	portName = "/dev/ttyACM0"; // Arduino Uno
    //portName = "/dev/ttyUSB0"; // Arduino Nano
#elif defined(__APPLE__) || defined(__MACH__)
    //portName = "/dev/cu.usbmodem1451"; // Arduino Uno
    portName = "/dev/cu.usbmodem1411"; // Arduino Uno
    //portName = "/dev/cu.wchusbserial1450"; // Arduino Nano
#endif

	if (argc >= 2)
		settingName = argv[1];

	if (argc >= 3)
		portName = argv[2];

#if defined(__WIN32__) || defined(_WIN32)
	//winSerial();
#else
	unixSerial(settingName, portName);
#endif

    return 0;
}
