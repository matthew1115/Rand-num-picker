#include "Random_picker.h"  
#include "Settings_window.h"  
#include <random>  
#include <fstream>  
#include <qmessagebox.h>  
#include <QDebug>

void Random_picker::read_settings()
{
	std::fstream settings_file("settings.txt", std::ios::in);
	if (settings_file.is_open())
	{
		settings_file >> min >> max;
		std::string exclude_str;
		settings_file >> exclude_str;
		int temp;
		int num = 0;
		int count = 0;
		while (count < exclude_str.length())
		{
			char curr = exclude_str[count];
			if (curr == ',' || curr == ' ')
			{
				exclude_nums.push_back(num);
				num = 0;
			}
			else if (curr == '\n')
			{
				exclude_nums.push_back(num);
				break;
			}
			else
			{
				temp = curr - '0';
				if (temp > 9 || temp < 0)
					throw std::runtime_error("Settings file read error - exclude list num error");
				num = num * 10 + temp;
				if (count == exclude_str.length() - 1)
					exclude_nums.push_back(num);
			}
			count++;
		}
		settings_file.close();
	}
	else // file not exist or read error
	{
		std::fstream new_settings("settings.txt", std::ios::out);
		if (new_settings.is_open())
			new_settings << "1" << std::endl << "40" << std::endl;
		else
			throw std::runtime_error("existing settings file not found and new settings file creation error");
	}
}

Random_picker::Random_picker(QWidget* parent)
	: QMainWindow(parent)
{
	this->setWindowFlags(Qt::WindowStaysOnTopHint);
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
	connect(ui.actionCredits, SIGNAL(triggered()), this, SLOT(on_creditAction_clicked()));
	connect(ui.actionSettings, SIGNAL(triggered()), this, SLOT(on_settingAction_clicked()));
	rand_base = new std::ranlux24_base(time(0));
	read_settings();
}

Random_picker::~Random_picker()
{
}

void Random_picker::on_pushButton_clicked()
{
	int result = 0;
	if (min > max)
	{
		QMessageBox popup;
		popup.setWindowFlags(Qt::WindowStaysOnTopHint);
		popup.setText("Range settings min value is greater than max value");
		popup.exec();
		//throw std::runtime_error("Settings min max check failure");
		return;
	}
	std::uniform_int_distribution<int> dist(min, max);

	if (exclude_nums.size() > 0)
	{
		do {
			result = dist(*rand_base);
		} while (std::find(exclude_nums.begin(), exclude_nums.end(), result) != exclude_nums.end());
	}
	else
	{
		result = dist(*rand_base);
	}
	ui.lcdNumber->display(result);
}

void Random_picker::on_creditAction_clicked()
{
	QMessageBox popup;
	popup.setWindowFlags(Qt::WindowStaysOnTopHint);
	popup.setText("Made by Matthew He \nWith Qt 6.8 \nYear 2025");
	popup.exec();
}

void Random_picker::on_settingAction_clicked()
{
	//qDebug() << "Settings clicked";

	SettingsWindow* settings = new SettingsWindow(nullptr, this);
	// Don't ask me why its parent had to be nullptr, I don;t know.
	// All I know is that long as it had a parent, it would fail to showup.
	settings->setAttribute(Qt::WA_DeleteOnClose);
	settings->show();
}