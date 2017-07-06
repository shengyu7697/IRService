#include "UnixSerial.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string>
#include <vector>
#include "Spotify.h"
#include "VLC.h"
#include "MPlayerX.h"
#include "Util.h"
#include "iniparser.h"
#include "Sound.h"

using namespace std;

static long t1 = 0;
static long t2 = 0;
int mode = 1;
bool isOsWakeUp = true;

Spotify spotify;
VLC vlc;
MPlayerX mplayerx;
Sound gSound;
std::vector<std::string> keymap;

bool loadSetting(const char *ini_name, std::vector<std::string> &keymap);
void onSerial(char *buf);
bool onSpotify(char *buf);
bool onVLC(char *buf);

int set_interface_attribs(int fd, int speed)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

void set_mincount(int fd, int mcount)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error tcgetattr: %s\n", strerror(errno));
        return;
    }

    tty.c_cc[VMIN] = mcount ? 1 : 0;
    tty.c_cc[VTIME] = 5;        /* half second timer */

    if (tcsetattr(fd, TCSANOW, &tty) < 0)
        printf("Error tcsetattr: %s\n", strerror(errno));
}

int unixSerial()
{
    if (!loadSetting("setting.ini", keymap)) {
        printf("can't load setting\n");
        return -1;
    }

#if defined(__unix__) || defined(__unix)
    const char *portname = "/dev/ttyACM0"; // Arduino Uno
    //const char *portname = "/dev/ttyUSB0"; // Arduino Nano
#elif defined(__APPLE__) || defined(__MACH__)
    //const char *portname = "/dev/cu.usbmodem1451"; // Arduino Uno
    const char *portname = "/dev/cu.usbmodem1411"; // Arduino Uno
    //const char *portname = "/dev/cu.wchusbserial1450"; // Arduino Nano
#endif
    int fd;
    int wlen;

    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf("Error opening %s: %s\n", portname, strerror(errno));
        return -1;
    }
    /*baudrate 115200, 8 bits, no parity, 1 stop bit */
    set_interface_attribs(fd, B9600);
    //set_mincount(fd, 0);                /* set to pure timed read */

    /* simple output */
    wlen = write(fd, "Hello!\n", 7);
    if (wlen != 7) {
        printf("Error from write: %d, %d\n", wlen, errno);
    }
    tcdrain(fd);    /* delay for output */

    char buf2[512];
    memset(buf2, 0, sizeof(buf2));
    /* simple noncanonical input */
    do {
        char buf[80];
        int rdlen;

        rdlen = read(fd, buf, sizeof(buf) - 1);
        if (rdlen > 0) {
#ifdef DISPLAY_STRING
            buf[rdlen] = 0;
            //printf("%s", buf);

            strcat(buf2, buf);
            char *pos = strstr(buf2, "\r\n");
            if (pos) { // if find string then put '\0'
                *pos = '\0';
                onSerial(buf2);
                memset(buf2, 0, sizeof(buf2));
            }
            //printf("Read %d: \"%s\"\n", rdlen, buf);
#else /* display hex */
            unsigned char   *p;
            printf("Read %d:", rdlen);
            for (p = buf; rdlen-- > 0; p++)
                printf(" 0x%x", *p);
            printf("\n");
#endif
        } else if (rdlen < 0) {
            printf("Error from read: %d: %s\n", rdlen, strerror(errno));
            return -1;
        }
        /* repeat read to get full message */
    } while (1);
}

bool loadSetting(const char *ini_name, std::vector<std::string> &keymap)
{
    printf("load setting...\n");
    dictionary *ini = NULL;

    ini = iniparser_load(ini_name);

    if (ini == NULL)
        return false;

    printf("controller name=%s\n", iniparser_getstring(ini, (char *)"profile:name", (char *)""));

    int num = iniparser_getsecnkeys(ini, (char *)"keymap");

	for (int i = 0; i < num; i++) {
		char keyname[64];
		sprintf(keyname, "keymap:key%d", i);

		keymap.push_back(iniparser_getstring(ini, keyname, (char *)""));

		printf("keymap[%d]=%s\n", i, keymap[i].c_str());
	}
	printf("---\n");

    iniparser_freedict(ini);

    return true;
}

void osWakeUp()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)

#elif defined(__APPLE__) || defined(__MACH__)
    // wake: caffeinate -u -t 1
    // https://apple.stackexchange.com/questions/53802/waking-display-from-terminal-general-waking
    shellCmd("caffeinate -u -t 1");
#endif
    isOsWakeUp ^= 1;
}

void osSleep()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)

#elif defined(__APPLE__) || defined(__MACH__)
    // sleep: pmset displaysleepnow
    // https://apple.stackexchange.com/questions/53802/waking-display-from-terminal-general-waking
    //shellCmd("pmset displaysleepnow");
    system("pmset displaysleepnow");
#endif
    isOsWakeUp ^= 1;
}

void onSerial(char *buf)
{
    t2 = getSystemTime();

    string timeString;
    getSystemTime(timeString);
    printf("%s onSerial= %s\n", timeString.c_str(), buf);

    if (strcmp(keymap[4].c_str(), buf) == 0) {
        if (t2 - t1 > 300) { // at least 300 ms
            if (!isOsWakeUp) {
                printf("power osWakeUp\n"); // it will block, need fix.
                gSound.playButton();
                osWakeUp();
            } else {
                printf("power osSleep\n");
                gSound.playButton();
                osSleep();
            }
        }
    } else if (strcmp(keymap[1].c_str(), buf) == 0) {
        if (t2 - t1 > 300) { // at least 300 ms
            printf("spotify\n");
            gSound.playSpotifySound();
            spotify.open();
            mode = 1;
        }
    } else if (strcmp(keymap[2].c_str(), buf) == 0) {
        if (t2 - t1 > 300) { // at least 300 ms
            printf("vlc\n");
            gSound.playVLCSound();
            vlc.open();
            mode = 2;
        }
    } else {
        if (mode == 1) {
            if (onSpotify(buf))
                gSound.playButton();
        } else if (mode == 2) {
            if (onVLC(buf))
                gSound.playButton();
        }
    }

    t1 = t2;
}

bool onSpotify(char *buf)
{
    bool ret = false;

    if (strcmp(keymap[5].c_str(), buf) == 0) {
        if (t2 - t1 > 300) { // at least 300 ms
            printf("spotify play\n");
            if (!isOsWakeUp)
                osWakeUp();
            spotify.play();
            ret = true;
        }
    } else if (strcmp(keymap[6].c_str(), buf) == 0) {
        printf("pause\n");
        if (!isOsWakeUp)
            osWakeUp();
        spotify.pause();
        ret = true;
    } else if (strcmp(keymap[7].c_str(), buf) == 0) {
        printf("stop\n");
        spotify.stop();
        ret = true;
    } else if (strcmp(keymap[8].c_str(), buf) == 0) {
        printf("volup\n");
        if (!isOsWakeUp)
            osWakeUp();
        spotify.volUp();
        ret = true;
    } else if (strcmp(keymap[9].c_str(), buf) == 0) {
        printf("voldown\n");
        if (!isOsWakeUp)
            osWakeUp();
        spotify.volDown();
        ret = true;
    } else if (strcmp(keymap[10].c_str(), buf) == 0) {
        printf("volmute\n");
        if (!isOsWakeUp)
            osWakeUp();
        spotify.volMute();
        ret = true;
    } else if (strcmp(keymap[11].c_str(), buf) == 0) {
        printf("next\n");
        if (!isOsWakeUp)
            osWakeUp();
        spotify.next();
        ret = true;
    } else if (strcmp(keymap[12].c_str(), buf) == 0) {
        printf("prev\n");
        if (!isOsWakeUp)
            osWakeUp();
        spotify.prev();
        ret = true;
    } else if (strcmp(keymap[13].c_str(), buf) == 0) {
        printf("jump_forward\n");
        spotify.jumpForward();
        ret = true;
    } else if (strcmp(keymap[14].c_str(), buf) == 0) {
        printf("jump_backward\n");
        spotify.jumpBackward();
        ret = true;
    } else if (strcmp(keymap[15].c_str(), buf) == 0) {
		if (t2 - t1 > 300) { // at least 300 ms
	        printf("fullscreen\n");
	        spotify.fullScreen();
            ret = true;
	    }
    }

    return ret;
}

bool onVLC(char *buf)
{
    bool ret = false;

    if (strcmp(keymap[5].c_str(), buf) == 0) {
        if (t2 - t1 > 300) { // at least 300 ms
            printf("vlc play\n");
            vlc.play();
            ret = true;
        }
    } else if (strcmp(keymap[6].c_str(), buf) == 0) {
        printf("pause\n");
        vlc.pause();
        ret = true;
    } else if (strcmp(keymap[7].c_str(), buf) == 0) {
        printf("stop\n");
        vlc.stop();
        ret = true;
    } else if (strcmp(keymap[8].c_str(), buf) == 0) {
        printf("volup\n");
        vlc.volUp();
        ret = true;
    } else if (strcmp(keymap[9].c_str(), buf) == 0) {
        printf("voldown\n");
        vlc.volDown();
        ret = true;
    } else if (strcmp(keymap[10].c_str(), buf) == 0) {
        printf("volmute\n");
        vlc.volMute();
        ret = true;
    } else if (strcmp(keymap[11].c_str(), buf) == 0) {
        printf("next\n");
        vlc.next();
        ret = true;
    } else if (strcmp(keymap[12].c_str(), buf) == 0) {
        printf("prev\n");
        vlc.prev();
        ret = true;
    } else if (strcmp(keymap[13].c_str(), buf) == 0) {
        printf("jump_forward\n");
        vlc.jumpForward();
        ret = true;
    } else if (strcmp(keymap[14].c_str(), buf) == 0) {
        printf("jump_backward\n");
        vlc.jumpBackward();
        ret = true;
    } else if (strcmp(keymap[15].c_str(), buf) == 0) {
		if (t2 - t1 > 300) { // at least 300 ms
	        printf("fullscreen\n");
	        vlc.fullScreen();
            ret = true;
	    }
    }

    return ret;
}
