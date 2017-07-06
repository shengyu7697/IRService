#ifndef __VLC_H__
#define __VLC_H__

class VLC
{
public:
	VLC();
	~VLC();
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

#endif /* __VLC_H__ */
