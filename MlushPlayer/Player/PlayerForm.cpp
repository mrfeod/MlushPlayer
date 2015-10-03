#include "PlayerForm.h"
#include "ui_PlayerForm.h"

PlayerForm::PlayerForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PlayerForm)
{
    ui->setupUi(this);

    connect(ui->controlPanel, &ControlPanel::next, &m_playlist, QMediaPlaylist::next);
    connect(ui->controlPanel, &ControlPanel::prev, &m_playlist, QMediaPlaylist::previous);
    connect(ui->controlPanel, &ControlPanel::play, [this](bool toggled)
    {
        if(toggled)
            m_player.play();
        else
            m_player.pause();
    });

    m_player.setPlaylist(&m_playlist);
}

PlayerForm::~PlayerForm()
{
	delete ui;
}
