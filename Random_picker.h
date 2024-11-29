#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Random_picker.h"
#include <random>

class Random_picker : public QMainWindow
{
	Q_OBJECT

public:
	Random_picker(QWidget* parent = nullptr);
	~Random_picker();

public slots:
	void on_pushButton_clicked();
	void on_creditAction_clicked();

private:
	Ui::Random_pickerClass ui;
	std::ranlux24_base* mt_rand;
};
