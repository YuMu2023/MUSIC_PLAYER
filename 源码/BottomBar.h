#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include<QWidget>

class QSlider;
class QPushButton;
class QLabel;

class BottomBar :public QWidget {
	Q_OBJECT;
public:

	BottomBar(QWidget* parent = nullptr);

protected:

	void button_init();
	void slider_init();
	void label_init();

	void label_value_changed(int value);

public:

	QSlider* time_slider;
	QSlider* volume_slider;

	QLabel* left_label;
	QLabel* right_label;
	QLabel* name_label;
	QLabel* all_label;

	QPushButton* browse_button;
	QPushButton* mode_button;
	QPushButton* last_button;
	QPushButton* next_button;
	QPushButton* start_button;
	QPushButton* volume_button;

};

#endif//BOTTOMBAR_H