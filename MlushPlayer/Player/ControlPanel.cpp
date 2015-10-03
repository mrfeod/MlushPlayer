#include "ControlPanel.h"
#include "ui_ControlPanel.h"

ControlPanel::ControlPanel(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ControlPanel)
{
	ui->setupUi(this);

    connect(ui->playButton, &QPushButton::toggled, this, &ControlPanel::play);
    connect(ui->nextButton, &QPushButton::pressed, this, &ControlPanel::next);
    connect(ui->prevButton, &QPushButton::pressed, this, &ControlPanel::prev);
}

ControlPanel::~ControlPanel()
{
	delete ui;
}
