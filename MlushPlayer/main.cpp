#include "mainwindow.h"
#include "MlushApplication.h"

int main(int argc, char *argv[])
{
	MlushApplication app(argc, argv);
	MainWindow mainWindow;

	app.SetMainWindow(&mainWindow);
	app.Initialize();

	mainWindow.show();
	return app.exec();
}
