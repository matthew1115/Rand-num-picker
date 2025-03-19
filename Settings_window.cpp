#include "Settings_window.h"
#include <fstream>
#include <qdebug>

SettingsWindow::SettingsWindow(QWidget* parent, Random_picker* main_win_ptr)
	: QDialog(parent)
{
	main_window = main_win_ptr;
	this->setWindowFlags(Qt::WindowStaysOnTopHint);
	//this->setAttribute(Qt::WA_DeleteOnClose);
	setting_ui.setupUi(this);

	connect(setting_ui.buttonBox, SIGNAL(accepted()), this, SLOT(on_buttonBox_accepted()));
	connect(setting_ui.buttonBox, SIGNAL(rejected()), this, SLOT(on_buttonBox_rejected()));

	std::fstream settings_file("settings.txt", std::ios::in);
	if (settings_file.is_open())
	{
		int min, max;
		std::string exclude_str;
		settings_file >> min >> max;
		settings_file.ignore();
		std::getline(settings_file, exclude_str);
		setting_ui.spinBox_min->setValue(min);
		setting_ui.spinBox_max->setValue(max);
		setting_ui.plainTextEdit_exclude->setPlainText(QString::fromStdString(exclude_str));
	}
	else
	{
		qDebug() << "Settings file not found";
	}
}

SettingsWindow::~SettingsWindow()
{
}

void SettingsWindow::on_buttonBox_rejected()
{
	main_window->read_settings();
	this->close();
}

void SettingsWindow::on_buttonBox_accepted()
{
	std::fstream settings_file("settings.txt", std::ios::out);
	if (settings_file.is_open())
	{
		settings_file << setting_ui.spinBox_min->value() << std::endl << setting_ui.spinBox_max->value() << std::endl << setting_ui.plainTextEdit_exclude->toPlainText().toStdString() << std::endl;
	}
	else
		throw std::runtime_error("Settings file write error");
	settings_file.close();
	main_window->read_settings();
	this->close();
}