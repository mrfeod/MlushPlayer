#ifndef MLUSHAPPLICATION_H
#define MLUSHAPPLICATION_H

#include <QApplication>

#include "mainwindow.h"

#include "VkManager/VkManager.h"

class MlushApplication : public QApplication
{
	Q_OBJECT
public:
	explicit MlushApplication(int &argc, char **argv);

public:
	void SetMainWindow(QWidget* mainWindow) { m_mainWindow = mainWindow; }
	QWidget* GetMainWindow() { return m_mainWindow; }

	void Initialize();

private:
	MainWindow* mainWindow() { return static_cast<MainWindow*>(m_mainWindow); }

private:
	QWidget* m_mainWindow;

	VkManager* m_vkManager;
};

#define mlushApp (static_cast<MlushApplication*>(QApplication::instance()))

#endif // MLUSHAPPLICATION_H
