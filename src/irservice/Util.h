#ifndef __UTIL_H__
#define __UTIL_H__

#include <string>

void shellCmd(const char *cmd);
void getSystemTime(std::string &timeString);
long getSystemTime();
void sleep_ms(int milliseconds);

#endif /* __UTIL_H__ */
