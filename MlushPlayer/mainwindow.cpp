#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "VkManager/VkOAuthView.h"
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	m_vkAuthView(new VkOAuthView(this))
{
	ui->setupUi(this);

	// Порядок важен
	ui->stackedWidget->addWidget(m_vkAuthView.data());
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
	return m_vkAuthView.data();
}
