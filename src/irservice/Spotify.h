#ifndef __SPOTIFY_H__
#define __SPOTIFY_H__

class Spotify
{
public:
	Spotify();
	~Spotify();
	void open();
	void close();
	void play();
	void pause();
	void stop();
	void volUp();
	void volDown();
	void volMute();
	void next();
	void prev();
	void jumpForward();
	void jumpBackward();
	void maximize();
	void minimize();
	void show();
	void fullScreen();

	int isOpened();
};

#endif /* __SPOTIFY_H__ */
