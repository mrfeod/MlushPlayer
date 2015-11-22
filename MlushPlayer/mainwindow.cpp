#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QListWidget>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	m_tray(this),
	m_vkAuthView(new VkOAuthView(this)),
	m_playerView(new PlayerForm(this))
{
	ui->setupUi(this);

	// Порядок важен
	ui->stackedWidget->addWidget(m_vkAuthView);
	ui->stackedWidget->addWidget(m_playerView);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::SetPage(Pages page)
{
	ui->stackedWidget->setCurrentIndex(page);
}

VkOAuthView* MainWindow::GetAuthPage()
{
	return m_vkAuthView;
}

PlayerForm* MainWindow::GetPlayerPage()
{
	return m_playerView;
}
