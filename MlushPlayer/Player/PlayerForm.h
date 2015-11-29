#ifndef PLAYERFORM_H
#define PLAYERFORM_H

#include <QWidget>

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "Player/playlistitemdata.h"

namespace Ui {
class PlayerForm;
}

class PlayerForm : public QWidget
{
	Q_OBJECT

public:
	explicit PlayerForm(QWidget *parent = 0);
	~PlayerForm();

	void AddToPlaylist(QList<PlaylistItemData> playlistItemData, bool clear = false);

private slots:
	SetRandomMode(bool random);

signals:
	void PlaylistRequest();
	void SearchRequest(const QString& request);

private:
	Ui::PlayerForm *ui;

	QMediaPlayer m_player;
	QMediaPlaylist m_playlist;
	QList<PlaylistItemData> m_playlistData;

	bool m_randomMode;
};

#endif // PLAYERFORM_H
