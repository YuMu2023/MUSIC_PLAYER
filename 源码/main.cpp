#include<QApplication>
#include<QDebug>
#include<QTime>

#include"MainWindow.h"

int main(int argc, char* argv[]) {

	QApplication app(argc, argv);

	qsrand(QTime::currentTime().msec());

	MainWindow a;
	a.show();

	return app.exec();

}