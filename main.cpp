#include "Random_picker.h"
#include <QtWidgets/QApplication>
#include <random>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	Random_picker main_window;
	main_window.show();
	return app.exec();
}
