#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QWidget>
#include<QMediaPlayer>

class MyWidget;
class BottomBar;
class QMediaPlayer;

class MainWindow :public QWidget {
	Q_OBJECT;
public:

	enum MODE { Again, Nothing, Next, Radom };

	MainWindow(QWidget* paent = nullptr);

protected slots:

	void browse_list();
	void mode_changed();
	void volumn_out();
	void music_changed(const QString& path);
	void music_pause();
	void music_time();
	void slider_do(qint64 a);
	void last_music();
	void next_music();
	void to_time(int time);
	void mode_show(QMediaPlayer::MediaStatus status);
	void ing_or_stop();

private:

	MyWidget* listWidget;
	BottomBar* bottomBar;

	QMediaPlayer* player;

	enum MODE Mode = MODE::Nothing;

};

#endif//MAINWINDOW_H