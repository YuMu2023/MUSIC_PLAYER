#ifndef MYWIDGET_H
#define MYWIDGET_H

#include<QListWidget>

class MyWidget :public QListWidget {
	Q_OBJECT;
public:

	MyWidget(QWidget* parent = nullptr);

	void setPath(const QString& path);
	int get_num();

protected:

	inline bool is_music(const QString& name);

private:

	int num = 0;

};

#endif//MYWIDGET_H