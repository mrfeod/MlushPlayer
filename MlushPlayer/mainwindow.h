#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "VkManager/VkOAuthView.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	enum Pages
	{
		PageAuth = 0
	};

	explicit MainWindow(QWidget *parent = 0);
	virtual ~MainWindow();

	void SetPage(Pages page);
	VkOAuthView* GetAuthPage();

private:
	Ui::MainWindow *ui;

	QScopedPointer<VkOAuthView> m_vkAuthView;
};

#endif // MAINWINDOW_H
