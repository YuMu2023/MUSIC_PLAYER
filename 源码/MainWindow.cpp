#include"MainWindow.h"
#include"MyWidget.h"
#include"BottomBar.h"

#include<QMediaPlayer>
#include<QDebug>

#include<QFileDialog>
#include<QPushButton>
#include<QSlider>
#include<QLabel>

MainWindow::MainWindow(QWidget* parent) :QWidget(parent) {

	player = new QMediaPlayer(this);

	listWidget = new MyWidget(this);
	listWidget->setGeometry(20, 20, 300, 800);

	bottomBar = new BottomBar(this);
	bottomBar->setGeometry(340, 620, 840, 200);

	resize(1200, 840);
	QPalette palette;
	QPixmap m_pixmap(":/image/background");
	QPixmap pixmap = m_pixmap.scaled(1200, 847);
	palette.setBrush(QPalette::Background, QBrush(pixmap));
	setPalette(palette);
	setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
	setFixedSize(this->width(), this->height());

	connect(listWidget, &QListWidget::doubleClicked, this, [this]() {music_changed(listWidget->currentItem()->data(Qt::UserRole).toString()); });
	connect(bottomBar->browse_button, &QPushButton::clicked, this, &MainWindow::browse_list);
	connect(bottomBar->mode_button, &QPushButton::clicked, this, &MainWindow::mode_changed);
	connect(bottomBar->start_button, &QPushButton::clicked, this, &MainWindow::music_pause);
	connect(bottomBar->volume_button, &QPushButton::clicked, this, &MainWindow::volumn_out);
	connect(bottomBar->volume_slider, &QSlider::sliderMoved, player, &QMediaPlayer::setVolume);
	connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::slider_do);
	connect(bottomBar->last_button, &QPushButton::clicked, this, &MainWindow::last_music);
	connect(bottomBar->next_button, &QPushButton::clicked, this, &MainWindow::next_music);
	connect(bottomBar->time_slider, &QSlider::sliderMoved, this, &MainWindow::to_time);
	connect(player, &QMediaPlayer::stateChanged, this, &MainWindow::ing_or_stop);
	connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::mode_show);

}

void MainWindow::browse_list() {

	QString str = QFileDialog::getExistingDirectoryUrl().toLocalFile();
	listWidget->setPath(str);

}

void MainWindow::mode_changed() {

	switch (Mode) {
	case Again:
		Mode = Nothing;
		bottomBar->mode_button->setIcon(QIcon(":/image/mode_button"));
		bottomBar->mode_button->setIconSize(QSize(50, 50));
		break;
	case Nothing:
		Mode = Next;
		bottomBar->mode_button->setIcon(QIcon(":/image/next"));
		bottomBar->mode_button->setIconSize(QSize(50, 50));
		break;
	case Next:
		Mode = Radom;
		bottomBar->mode_button->setIcon(QIcon(":/image/radom"));
		bottomBar->mode_button->setIconSize(QSize(50, 50));
		break;
	case Radom:
		Mode = Again;
		bottomBar->mode_button->setIcon(QIcon(":/image/again"));
		bottomBar->mode_button->setIconSize(QSize(50, 50));
		break;
	}

}

void MainWindow::volumn_out() {

	bool a = bottomBar->volume_slider->isVisible();
	if (a) {
		bottomBar->volume_slider->setVisible(false);
	}
	else {
		bottomBar->volume_slider->setVisible(true);
	}

}

void MainWindow::music_changed(const QString& path) {
	
	QFileInfo fileInfo(path);
	bottomBar->name_label->setText(fileInfo.baseName());

	player->setMedia(QUrl::fromLocalFile(path));
	player->play();

	connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::music_time);

}

void MainWindow::music_pause() {

	if (player->state() == player->PausedState) {
		player->play();
	}
	else if(player->state() == player->PlayingState){
		player->pause();
	}

}

void MainWindow::music_time() {

	int time = player->duration() / 1000;

	bottomBar->time_slider->setMaximum(time);
	bottomBar->time_slider->setMinimum(0);
	bottomBar->time_slider->setValue(0);
	if (time % 60 >= 10) {
		bottomBar->right_label->setText(QString::number(time / 60).append(':').append(QString::number(time % 60)));
	}
	else {
		bottomBar->right_label->setText(QString::number(time / 60).append(":0").append(QString::number(time % 60)));
	}

	disconnect(player, &QMediaPlayer::durationChanged, this, &MainWindow::music_time);

}

void MainWindow::slider_do(qint64 a) {

	int time = player->position() / 1000;
	bottomBar->time_slider->setValue(time);
	bottomBar->time_slider->update();
	if (time % 60 >= 10) {
		bottomBar->left_label->setText(QString::number(time / 60).append(':').append(QString::number(time % 60)));
	}
	else {
		bottomBar->left_label->setText(QString::number(time / 60).append(":0").append(QString::number(time % 60)));
	}

}

void MainWindow::last_music() {

	if (listWidget->count() == 0) { return; }

	int row = listWidget->currentItem()->data(Qt::UserRole + 1).toInt();
	if ( row == 0) { return; }

	music_changed(listWidget->item(row - 1)->data(Qt::UserRole).toString());
	listWidget->setCurrentRow(row - 1);

}

void MainWindow::next_music() {

	if (listWidget->count() == 0) { return; }

	int row = listWidget->currentItem()->data(Qt::UserRole + 1).toInt();
	if (row == listWidget->get_num() - 1) { return; }

	music_changed(listWidget->item(row + 1)->data(Qt::UserRole).toString());
	listWidget->setCurrentRow(row + 1);

}

void MainWindow::to_time(int time) {

	player->setPosition(time * 1000);

}

void MainWindow::mode_show(QMediaPlayer::MediaStatus status) {

	if (status != QMediaPlayer::MediaStatus::EndOfMedia) { return; }

	int radom_muisc = qrand() % (listWidget->get_num());
	int next_muisc = listWidget->currentItem()->data(Qt::UserRole + 1).toInt();

	switch (Mode) {
	case Nothing:
		player->stop();
		break;
	case Again:
		player->setPosition(0);
		player->play();
		break;
	case Radom:
		listWidget->setCurrentRow(radom_muisc);
		music_changed(listWidget->item(radom_muisc)->data(Qt::UserRole).toString());
		break;
	case Next:
		if (next_muisc == listWidget->get_num() - 1) { return; }
		listWidget->setCurrentRow(next_muisc + 1);
		music_changed(listWidget->item(next_muisc + 1)->data(Qt::UserRole).toString());
		break;
	}

}

void MainWindow::ing_or_stop() {

	if (player->state() == player->PausedState) {
		bottomBar->start_button->setIcon(QIcon(":/image/start_button"));
		bottomBar->start_button->setIconSize(QSize(50, 50));
	}
	else if (player->state() == player->PlayingState) {
		bottomBar->start_button->setIcon(QIcon(":/image/ing"));
		bottomBar->start_button->setIconSize(QSize(50, 50));
	}

}