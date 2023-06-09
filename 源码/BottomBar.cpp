#include"BottomBar.h"

#include<QFileDialog>
#include<QBitMap>

#include<QSlider>
#include<QLabel>
#include<QPushButton>

BottomBar::BottomBar(QWidget* parent) :QWidget(parent) {

	all_label = new QLabel(this);

	left_label	  = new QLabel(this);
	right_label   = new QLabel(this);
	name_label = new QLabel(this);

	browse_button = new QPushButton(this);
	mode_button   = new QPushButton(this);
	last_button   = new QPushButton(this);
	next_button   = new QPushButton(this);
	start_button  = new QPushButton(this);
	volume_button = new QPushButton(this);
	time_slider = new QSlider(this);
	volume_slider = new QSlider(this);

	all_label->setStyleSheet("QLabel { background-color: rgba(255, 255, 255, 120); border-radius: 20px; }");
	all_label->setGeometry(0, 0, 840, 200);

	button_init();
	slider_init();
	label_init();

	volume_slider->setVisible(false);

}

void BottomBar::button_init() {

	browse_button->setIcon(QIcon(QPixmap(":/image/browse_button")));
	browse_button->setIconSize(QSize(50, 50));
	browse_button->setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 150); border-radius: 20px; }"
		"QPushButton:hover { background-color: rgba(205, 205, 255, 130); }"
		"QPushButton:pressed { background-color: rgba(105, 105, 255, 130); }");

	mode_button->setIcon(QIcon(QPixmap(":/image/mode_button")));
	mode_button->setIconSize(QSize(50, 50));
	mode_button->setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 150); border-radius: 20px; }"
		"QPushButton:hover { background-color: rgba(205, 205, 255, 130); }"
		"QPushButton:pressed { background-color: rgba(105, 105, 255, 130); }");

	last_button->setIcon(QIcon(QPixmap(":/image/last_button")));
	last_button->setIconSize(QSize(50, 50));
	last_button->setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 150); border-radius: 20px; }"
		"QPushButton:hover { background-color: rgba(205, 205, 255, 130); }"
		"QPushButton:pressed { background-color: rgba(105, 105, 255, 130); }");

	next_button->setIcon(QIcon(QPixmap(":/image/next_button")));
	next_button->setIconSize(QSize(50, 50));
	next_button->setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 150); border-radius: 20px; }"
		"QPushButton:hover { background-color: rgba(205, 205, 255, 130); }"
		"QPushButton:pressed { background-color: rgba(105, 105, 255, 130); }");

	start_button->setIcon(QIcon(QPixmap(":/image/start_button")));
	start_button->setIconSize(QSize(50, 50));
	start_button->setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 150); border-radius: 20px; }"
		"QPushButton:hover { background-color: rgba(205, 205, 255, 130); }"
		"QPushButton:pressed { background-color: rgba(105, 105, 255, 130); }");

	volume_button->setIcon(QIcon(QPixmap(":/image/volumn_button")));
	volume_button->setIconSize(QSize(50, 50));
	volume_button->setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 150); border-radius: 20px; }"
		"QPushButton:hover { background-color: rgba(205, 205, 255, 130); }"
		"QPushButton:pressed { background-color: rgba(105, 105, 255, 130); }");

	browse_button->setGeometry(35, 120, 120, 70);
	mode_button->setGeometry(165, 120, 120, 70);
	last_button->setGeometry(295, 120, 120, 70);
	next_button->setGeometry(555, 120, 120, 70);
	start_button->setGeometry(425, 120, 120, 70);
	volume_button->setGeometry(685, 120, 120, 70);

}

void BottomBar::label_init() {

	QFont font("Î¢ÑÅÈíºÚ", 12, 75);

	left_label->setFont(font);
	left_label->setAlignment(Qt::AlignCenter);
	right_label->setFont(font);
	right_label->setAlignment(Qt::AlignCenter);

	left_label->setText(QString::number(0).append(tr(":")).append(QString::number(0)).append(QString::number(0)));
	right_label->setText(QString::number(0).append(tr(":")).append(QString::number(0)).append(QString::number(0)));

	font.setPointSize(15);
	name_label->setFont(font);
	name_label->setAlignment(Qt::AlignCenter);
	name_label->setText(tr("Wait..."));

	left_label->setGeometry(10, 50, 50, 50);
	right_label->setGeometry(780, 50, 50, 50);
	name_label->setGeometry(0, 10, 840, 30);

	connect(time_slider, &QSlider::sliderMoved, this, &BottomBar::label_value_changed);

}

void BottomBar::slider_init() {

	time_slider->setOrientation(Qt::Horizontal);
	time_slider->setValue(0);
	time_slider->setMaximum(300);
	time_slider->setMinimum(0);
	time_slider->setGeometry(65, 60, 700, 30);
	time_slider->setTracking(true);

	volume_slider->setOrientation(Qt::Vertical);
	volume_slider->setValue(100);
	volume_slider->setMaximum(100);
	volume_slider->setMinimum(0);
	volume_slider->setGeometry(715, 10, 40, 100);
	volume_slider->setStyleSheet("QSlider { background-color: rgba(255, 255, 255, 150); border-radius: 5px; }");

}

void BottomBar::label_value_changed(int value) {

	if (value % 60 >= 10) {
		left_label->setText(QString::number(value / 60).append(tr(":")).append(QString::number(value % 60)));
	}
	else {
		left_label->setText(QString::number(value / 60).append(tr(":")).append(QString::number(0)).append(QString::number(value % 60)));
	}

}