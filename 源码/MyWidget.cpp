#include"MyWidget.h"

#include<QDir>
#include<QFileInfo>
#include<QDebug>
#include<QPainter>
#include<QGraphicsOpacityEffect>

MyWidget::MyWidget(QWidget* parent) :QListWidget(parent) {

	setAcceptDrops(true);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setFrameShape(QListWidget::NoFrame);

	setStyleSheet("QListWidget { background-color: rgba(255, 255, 255, 120); border-radius: 20px; }");

}

void MyWidget::setPath(const QString& path) {

	QFont font("Î¢ÑÅÈíºÚ", 15, 75);
	num = 0;

	QDir dir(path);
	if (dir.count() == 0) { return; }

	QFileInfoList fileList = dir.entryInfoList();
	for (int i = 0; i < fileList.count(); i++) {

		if (is_music(fileList[i].suffix())) {

			QString fileName = fileList[i].baseName();
			QString filePath = fileList[i].absoluteFilePath();

			QListWidgetItem* item = new QListWidgetItem;
			item->setFont(font);
			item->setSizeHint(QSize(200, 80));
			item->setText(fileName);
			item->setData(Qt::UserRole, QString(filePath));
			item->setData(Qt::UserRole + 1, num);

			addItem(item);
			num++;
			
		}

	}

	setCurrentItem(item(0));

}

bool MyWidget::is_music(const QString& name) {

	QString all[8];
	all[0] = "mp3"; all[1] = "wma"; all[2] = "wav"; all[3] = "ape";
	all[4] = "flac"; all[5] = "ogg"; all[6] = "aac"; all[7] = "m4a";

	for (int i = 0; i < 8; i++) {
		if (name == all[i]) { return true; }
	}

	return false;
}

int MyWidget::get_num() { return num; }