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

	connect(ui->timelineSlider, QSlider::sliderMoved, this, &ControlPanel::positionChanged);
	connect(ui->volumeSlider, QSlider::valueChanged, this, &ControlPanel::volumeChanged);

	emit volumeChanged(ui->volumeSlider->value());
}

ControlPanel::~ControlPanel()
{
	delete ui;
}

void ControlPanel::SetTitle(const QString &title)
{
	ui->titleLabel->setText(title);
}

void ControlPanel::SetDuration(const qint64 &duration)
{
	ui->timelineSlider->setRange(0, duration);
	ui->durationLabel->setText(QString::number(duration));
}

void ControlPanel::SetPosition(const qint64 &position)
{
	ui->timelineSlider->setValue(position);
	ui->currentTimeLabel->setText(QString::number(position));
}
