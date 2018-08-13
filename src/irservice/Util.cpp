#include "Util.h"

#include <stdio.h>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

bool shellCmd(const char *cmd) {
//	printf("ShellCmd: %s\n", cmd);
#if defined(__WIN32__) || defined(_WIN32)
	FILE *pp;
	if ((pp = _popen(cmd, "r")) == NULL) {
		return false;
	}
	_pclose(pp);
	return true;
#else
	FILE *pp;
	if ((pp = popen(cmd, "r")) == NULL) {
		return false;
	}
	pclose(pp);
	return true;
#endif
}

void getSystemTime(std::string &timeString)
{
    char buf[512];
    time_t rawtime;
    tm* timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buf, 80, "%Y/%m/%d %H:%M:%S", timeinfo);
    timeString = buf;

    duration<long long, milli> ms = duration_cast< duration<long long, milli> >(system_clock::now().time_since_epoch());
    sprintf(buf, ".%03lld", ms.count() % 1000);
    timeString += buf;
}

long getSystemTime()
{
    duration<long long, milli> ms = duration_cast< duration<long long, milli> >(system_clock::now().time_since_epoch());
    return ms.count();
}

void sleep_ms(int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
