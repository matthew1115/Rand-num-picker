#include <QDialog>
#include "Random_picker.h"
#include "ui_Settings_window.h"

class SettingsWindow : public QDialog
{
	Q_OBJECT

public:
	SettingsWindow(QWidget* parent = nullptr, Random_picker* main_window_ptr = nullptr);
	~SettingsWindow();

public slots:
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();

private:
	Ui::Settings_window setting_ui;
	Random_picker* main_window;
};
