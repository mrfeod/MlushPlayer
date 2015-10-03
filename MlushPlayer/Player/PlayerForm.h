#ifndef PLAYERFORM_H
#define PLAYERFORM_H

#include <QWidget>

#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class PlayerForm;
}

class PlayerForm : public QWidget
{
	Q_OBJECT

public:
	explicit PlayerForm(QWidget *parent = 0);
	~PlayerForm();

    void AddToPlaylist(QList<QMediaContent> playlistContent) { m_playlist.addMedia(playlistContent); }

private:
	Ui::PlayerForm *ui;

    QMediaPlayer m_player;
    QMediaPlaylist m_playlist;
};

#endif // PLAYERFORM_H
