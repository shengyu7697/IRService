#include "Sound.h"
#include "Util.h"

using namespace std;

void Sound::playButton()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("aplay button.wav &");
#elif defined(__APPLE__) || defined(__MACH__)

#endif
}

//http://www.texttomp3.online/
void Sound::playSpotifySound()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	// sudo apt-get install mpg321
	// shellCmd("mpg123 spotify.mp3 &");

	// ffmpeg -i vlc.mp3 vlc.wav
	shellCmd("aplay spotify.wav &");
#elif defined(__APPLE__) || defined(__MACH__)

#endif
}

void Sound::playVLCSound()
{
#if defined(__WIN32__) || defined(_WIN32)

#elif defined(__unix__) || defined(__unix)
	shellCmd("aplay vlc.wav &");
#elif defined(__APPLE__) || defined(__MACH__)

#endif
}
