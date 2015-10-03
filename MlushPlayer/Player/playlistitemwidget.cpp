#include "playlistitemwidget.h"
#include "ui_playlistitemwidget.h"

PlaylistItemWidget::PlaylistItemWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PlaylistItemWidget)
{
	ui->setupUi(this);
}

PlaylistItemWidget::~PlaylistItemWidget()
{
	delete ui;
}
