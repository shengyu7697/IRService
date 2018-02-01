#include "Spotify.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Util.h"

Spotify::Spotify()
{
    //printf("%s\n", __func__);
}

Spotify::~Spotify()
{
    //printf("%s\n", __func__);
}

void Spotify::open()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("spotify &");
#elif defined(__APPLE__) || defined(__MACH__)
	shellCmd("open -a /Applications/Spotify.app/");
#endif
}

void Spotify::close()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("xdotool search --name 'spotify' windowkill");
#elif defined(__APPLE__) || defined(__MACH__)

#endif
}

void Spotify::play()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.PlayPause");
#elif defined(__APPLE__) || defined(__MACH__)
	//shellCmd("osascript -e 'tell application \"Spotify\" to activate'");
    //usleep(50*1000);
	//shellCmd("osascript -e 'tell application \"System Events\" to key code 49'"); // space
    shellCmd("/Users/sheng/bin/osxMediaKey play");
	// applescript-key-codes
	// http://eastmanreference.com/complete-list-of-applescript-key-codes/
#endif
}

void Spotify::pause()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.PlayPause");
#elif defined(__APPLE__) || defined(__MACH__)
	//shellCmd("osascript -e 'tell application \"Spotify\" to activate'");
    //usleep(50*1000);
	//shellCmd("osascript -e 'tell application \"System Events\" to key code 49'"); // space
    shellCmd("/Users/sheng/bin/osxMediaKey play");
#endif
}

void Spotify::stop()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	
#elif defined(__APPLE__) || defined(__MACH__)
	shellCmd("osascript -e 'tell application \"Spotify\" to activate'");
    usleep(50*1000);
	shellCmd("osascript -e 'tell application \"System Events\" to key code 47 using {command down}'"); // Cmd+.
#endif
}

void Spotify::volUp()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("amixer -q sset Master 3%+");
#elif defined(__APPLE__) || defined(__MACH__)
	shellCmd("osascript -e 'tell application \"Spotify\" to activate'");
    //usleep(50*1000);
	//shellCmd("osascript -e 'tell application \"System Events\" to key code 126 using {command down}'"); // Cmd+UpArrow
    shellCmd("/Users/sheng/bin/osxMediaKey volup");
#endif
}

void Spotify::volDown()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("amixer -q sset Master 3%-");
#elif defined(__APPLE__) || defined(__MACH__)
	shellCmd("osascript -e 'tell application \"Spotify\" to activate'");
    //usleep(50*1000);
	//shellCmd("osascript -e 'tell application \"System Events\" to key code 125 using {command down}'"); // Cmd+DownArrow
    shellCmd("/Users/sheng/bin/osxMediaKey voldown");
#endif
}

void Spotify::volMute()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("amixer -q -D pulse sset Master toggle");
#elif defined(__APPLE__) || defined(__MACH__)
	shellCmd("osascript -e 'tell application \"Spotify\" to activate'");
    //usleep(50*1000);
	//shellCmd("osascript -e 'tell application \"System Events\" to key code 125 using {command down, option down}'"); // Cmd+Option+DownArrow
    shellCmd("/Users/sheng/bin/osxMediaKey mute");
#endif
}

void Spotify::next()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Next");
#elif defined(__APPLE__) || defined(__MACH__)
	//shellCmd("osascript -e 'tell application \"Spotify\" to activate'");
    //usleep(50*1000);
    //shellCmd("osascript -e 'tell application \"System Events\" to key code 125 using {command down, option down}'"); // Cmd+Option+DownArrow
    shellCmd("/Users/sheng/bin/osxMediaKey fast");
#endif
}

void Spotify::prev()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Previous");
#elif defined(__APPLE__) || defined(__MACH__)
	//shellCmd("osascript -e 'tell application \"Spotify\" to activate'");
    //usleep(50*1000);
    //shellCmd("osascript -e 'tell application \"System Events\" to key code 125 using {command down, option down}'"); // Cmd+Option+DownArrow
    shellCmd("/Users/sheng/bin/osxMediaKey rewind");
#endif
}

void Spotify::jumpForward()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)

#elif defined(__APPLE__) || defined(__MACH__)

#endif
}

void Spotify::jumpBackward()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)

#elif defined(__APPLE__) || defined(__MACH__)

#endif
}

void Spotify::maximize()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)

#elif defined(__APPLE__) || defined(__MACH__)

#endif
}

void Spotify::minimize()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)

#elif defined(__APPLE__) || defined(__MACH__)

#endif
}

void Spotify::show()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)

#elif defined(__APPLE__) || defined(__MACH__)

#endif
}

void Spotify::fullScreen()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)

#elif defined(__APPLE__) || defined(__MACH__)
	shellCmd("osascript -e 'tell application \"Spotify\" to activate'");
    usleep(50*1000);
	shellCmd("osascript -e 'tell application \"System Events\" to key code 3 using {command down}'"); // Cmd+f
#endif
}

int Spotify::isOpened()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)

#elif defined(__APPLE__) || defined(__MACH__)

#endif
	return 0;
}
