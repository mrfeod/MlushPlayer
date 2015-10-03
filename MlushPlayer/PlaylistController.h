#ifndef PLAYLISTCONTROLLER_H
#define PLAYLISTCONTROLLER_H

#include <QObject>

#include <QList>

#include <QMediaContent>

struct PlaylistItemData
{
	QString artist;
	QString title;
	QString url;
	int duration;
};

class PlaylistController : public QObject
{
	Q_OBJECT
public:
	explicit PlaylistController(QObject *parent = 0);

    QList<QMediaContent> GetMediaPlaylist() { return m_mediaPlaylist; }

public slots:
	void SetPlaylistFromJSON(const QString& jsonString);

private:
    QList<PlaylistItemData> m_playlist;
    QList<QMediaContent> m_mediaPlaylist;
};

#endif // PLAYLISTCONTROLLER_H
