#ifndef __MPLAYERX_H__
#define __MPLAYERX_H__

class MPlayerX
{
public:
	MPlayerX();
	~MPlayerX();
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

#endif /* __MPLAYERX_H__ */
