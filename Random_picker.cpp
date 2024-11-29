#include "Random_picker.h"
#include <random>
#include <qmessagebox.h>

Random_picker::Random_picker(QWidget* parent)
	: QMainWindow(parent)
{
	this->setWindowFlags(Qt::WindowStaysOnTopHint);
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
	connect(ui.actionCredits, SIGNAL(triggered()), this, SLOT(on_creditAction_clicked()));
	mt_rand = new std::ranlux24_base(time(0));
}

Random_picker::~Random_picker()
{}

void Random_picker::on_pushButton_clicked()
{
	int result = 0;
	std::uniform_int_distribution<int> dist(1, 42);

	//standerd
	result = dist(*mt_rand);

	// 2612 special
	//do
	//{
	//	result = dist(*mt_rand);
	//} while (result == 10 || result == 15 || result == 19 || result == 20 || result == 28 || result == 35);

	ui.lcdNumber->display(result);
}

void Random_picker::on_creditAction_clicked()
{
	QMessageBox popup;
	popup.setWindowFlags(Qt::WindowStaysOnTopHint);
	popup.setText("Made by Matthew He \nWith Qt 6.8 \nYear 2024");
	popup.exec();
}