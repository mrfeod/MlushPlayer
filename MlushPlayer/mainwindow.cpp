#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "VkManager/VkOAuthView.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::PlaceWidget(QWidget *widget)
{
	widget->setParent(ui->centralWidget);
	widget->show();
}
