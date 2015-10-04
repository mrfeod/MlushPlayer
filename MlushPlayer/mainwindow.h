#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "VkManager/VkOAuthView.h"
#include "Player/PlayerForm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	enum Pages
	{
		PageAuth = 0,
		PagePlayer
	};

	explicit MainWindow(QWidget *parent = 0);
	virtual ~MainWindow();

	void SetPage(Pages page);
    VkOAuthView* GetAuthPage();
    PlayerForm* GetPlayerPage();

private:
	Ui::MainWindow *ui;

    VkOAuthView* m_vkAuthView;
    PlayerForm* m_playerView;
};

#endif // MAINWINDOW_H
