#include "PlayerForm.h"
#include "ui_PlayerForm.h"

#include "ObjectsConnector/MlushConnectorID.h"
#include "ObjectsConnector/ObjectsConnector.h"

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

	connect(&m_playlist, &QMediaPlaylist::currentIndexChanged, [this](int position)
	{
		if(position < 0)
		{
			m_playlist.setCurrentIndex(0);
		}
		else
		{
			PlaylistItemData data = m_playlistData.at(position);
			ui->controlPanel->SetTitle(data.artist + " - " + data.title);
			ui->controlPanel->SetDuration(data.duration * 1000); //Передаем с миллисекундах
			ui->playlistWidget->setCurrentRow(position);
		}
	});
	connect(ui->playlistWidget, &QListWidget::itemActivated, [this]()
	{
		m_playlist.setCurrentIndex(ui->playlistWidget->currentRow());
	});

	connect(&m_player, &QMediaPlayer::positionChanged, ui->controlPanel, &ControlPanel::SetPosition);
	connect(ui->controlPanel, &ControlPanel::positionChanged, &m_player, &QMediaPlayer::setPosition);

	connect(ui->controlPanel, &ControlPanel::volumeChanged, &m_player, &QMediaPlayer::setVolume);

	connect(ui->searchButton, &QPushButton::clicked, [this]()
	{
		QString request = ui->searchLine->text();
		if(request.isEmpty())
			emit PlaylistRequest();
		else
			emit SearchRequest(request);
	});
	ObjectsConnector::registerEmitter(MlushConnectorID::PLAYLIST_REQUEST(), this, SIGNAL(PlaylistRequest()));
	ObjectsConnector::registerEmitter(MlushConnectorID::SEARCH_REQUEST(), this, SIGNAL(SearchRequest(QString)));

	m_player.setPlaylist(&m_playlist);
}

void PlayerForm::AddToPlaylist(QList<PlaylistItemData> playlistItemData, bool clear/*=false*/)
{
	if(clear)
	{
		m_playlistData.clear();
		m_playlist.clear();
		ui->playlistWidget->clear();
	}

	bool playlistEmpty = m_playlistData.size() == 0;
	Q_FOREACH(auto item, playlistItemData)
	{
		QMediaContent playlistItem(item.url);
		m_playlistData.append(item);
		m_playlist.addMedia(playlistItem);
		ui->playlistWidget->addItem(item.artist + " - " + item.title);
	}

	if(playlistEmpty)
	{
		m_playlist.setCurrentIndex(0);
	}
}

PlayerForm::~PlayerForm()
{
	delete ui;
}
