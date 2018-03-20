#include "VLC.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Util.h"

VLC::VLC()
{
	//printf("%s\n", __func__);
}

VLC::~VLC()
{
	//printf("%s\n", __func__);
}

void VLC::open()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("xdotool search --all --name 'VLC media player' windowactivate");
#elif defined(__APPLE__) || defined(__MACH__)
	shellCmd("open -a /Applications/VLC.app/");
#endif
}

void VLC::close()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("xdotool search --all --name 'VLC media player' windowkill");
#elif defined(__APPLE__) || defined(__MACH__)

#endif
}

void VLC::play()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.vlc /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.PlayPause");
	// or
	// shellCmd("xdotool key --window $(xdotool search --name 'VLC media player'|head -n1) XF86AudioPlay");
#elif defined(__APPLE__) || defined(__MACH__)
	shellCmd("osascript -e 'tell application \"VLC\" to activate'");
	shellCmd("osascript -e 'tell application \"System Events\" to key code 49'"); // space
	// applescript-key-codes
	// http://eastmanreference.com/complete-list-of-applescript-key-codes/
#endif
}

void VLC::pause()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.vlc /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Pause");
#elif defined(__APPLE__) || defined(__MACH__)
	shellCmd("osascript -e 'tell application \"VLC\" to activate'");
	shellCmd("osascript -e 'tell application \"System Events\" to key code 49'"); // space
#endif
}

void VLC::stop()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.vlc /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Stop");
#elif defined(__APPLE__) || defined(__MACH__)
	shellCmd("osascript -e 'tell application \"VLC\" to activate'");
	shellCmd("osascript -e 'tell application \"System Events\" to key code 47 using {command down}'"); // Cmd+.
#endif
}

void VLC::volUp()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("amixer -q sset Master 3%+");
#elif defined(__APPLE__) || defined(__MACH__)
	shellCmd("osascript -e 'tell application \"VLC\" to activate'");
	shellCmd("osascript -e 'tell application \"System Events\" to key code 126 using {command down}'"); // Cmd+UpArrow
#endif
}

void VLC::volDown()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("amixer -q sset Master 3%-");
#elif defined(__APPLE__) || defined(__MACH__)
	//shellCmd("/Users/sheng/bin/osxMediaKey voldown");
	shellCmd("osascript -e 'tell application \"VLC\" to activate'");
	shellCmd("osascript -e 'tell application \"System Events\" to key code 125 using {command down}'"); // Cmd+DownArrow
#endif
}

void VLC::volMute()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("amixer -q -D pulse sset Master toggle");
#elif defined(__APPLE__) || defined(__MACH__)
	//shellCmd("/Users/sheng/bin/osxMediaKey mute");
	shellCmd("osascript -e 'tell application \"VLC\" to activate'");
	shellCmd("osascript -e 'tell application \"System Events\" to key code 125 using {command down, option down}'"); // Cmd+Option+DownArrow
#endif
}

void VLC::next()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.vlc /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Next");
#elif defined(__APPLE__) || defined(__MACH__)
	shellCmd("/Users/sheng/bin/osxMediaKey fast");
#endif
}

void VLC::prev()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.vlc /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Previous");
#elif defined(__APPLE__) || defined(__MACH__)
	shellCmd("/Users/sheng/bin/osxMediaKey rewind");
#endif
}

void VLC::jumpForward()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("xdotool search --name 'VLC media player' windowactivate");
	shellCmd("xdotool key ctrl+Right");
#elif defined(__APPLE__) || defined(__MACH__)
	shellCmd("osascript -e 'tell application \"VLC\" to activate'");
	usleep(50*1000);
	shellCmd("osascript -e 'tell application \"System Events\" to key code 124 using {command down, option down}'"); // Cmd+Option+RightArrow
#endif
}

void VLC::jumpBackward()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("xdotool search --name 'VLC media player' windowactivate");
	shellCmd("xdotool key ctrl+Left");
#elif defined(__APPLE__) || defined(__MACH__)
	shellCmd("osascript -e 'tell application \"VLC\" to activate'");
	usleep(50*1000);
	shellCmd("osascript -e 'tell application \"System Events\" to key code 123 using {command down, option down}'"); // Cmd+Option+LeftArrow
#endif
}

void VLC::maximize()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)

#elif defined(__APPLE__) || defined(__MACH__)

#endif
}

void VLC::minimize()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)

#elif defined(__APPLE__) || defined(__MACH__)

#endif
}

void VLC::show()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)

#elif defined(__APPLE__) || defined(__MACH__)

#endif
}

void VLC::fullScreen()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)

#elif defined(__APPLE__) || defined(__MACH__)
	shellCmd("osascript -e 'tell application \"VLC\" to activate'");
	shellCmd("osascript -e 'tell application \"System Events\" to key code 3 using {command down}'"); // Cmd+f
#endif
}

int VLC::isOpened()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)

#elif defined(__APPLE__) || defined(__MACH__)

#endif
	return 0;
}
